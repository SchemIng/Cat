
#include "stdafx.h"
#include "DataUtils.h"
#include "BillRecordSet.h"
#include "classifyrecordset.h"

CDataUtils::CDataUtils()
{
	db.Open(NULL, FALSE, FALSE, L"ODBC;DSN=cat;UID=root;PWD=Shy66017");
}

CDataUtils::~CDataUtils()
{
	db.Close();
}

vector<CBill> CDataUtils::getAllBills()
{
	return getBills(_T("SELECT bill.id,title,money,date,classify_id,classify.`name` FROM bill,classify WHERE bill.classify_id=classify.id;"));
}

vector<CBill> CDataUtils::getBillsByClassify(UINT type)
{
	CString sql; 
	sql.Format(_T("SELECT bill.id,title,money,date,classify_id,classify.`name` FROM bill,classify WHERE bill.classify_id = classify.id and classify.id=%d;"), type);
	return getBills(sql);
}

vector<CBill> CDataUtils::getBills(CString sql)
{
	vector<CBill> result;
	CBill bill;

	CBillRecordSet rs;
	rs.Open(CRecordset::forwardOnly,sql);
	while (!rs.IsEOF())
	{
		bill.m_id = rs.m_id;
		bill.m_title = rs.m_title;
		bill.m_money = rs.m_money;
		bill.m_date = rs.m_date;
		bill.m_classify_id = rs.m_classify_id;
		bill.m_classify_name = rs.m_classify_name;

		result.push_back(bill);
		rs.MoveNext();
	}
	rs.Close();
	return result;
}

void CDataUtils::insertBill(CBill bill)
{
	CString sql,date;

	date = bill.m_date.Format("%y-%m-%d");
	sql.Format(_T("INSERT INTO bill (title,money,date,classify_id) VALUES('%s', %d, DATE_FORMAT('%s', '%%y-%%m-%%d'), %d); "),
		bill.m_title, bill.m_money, date, bill.m_classify_id);
	db.ExecuteSQL(sql);
}

vector<CString> CDataUtils::getDates()
{
	vector<CString> result;
	CRecordset rs(&db);

	rs.Open(CRecordset::forwardOnly, _T("SELECT date FROM bill GROUP BY date;"));
	while (!rs.IsEOF())
	{
		CString time;
		rs.GetFieldValue(_T("date"),time);

		result.push_back(time);
		rs.MoveNext();
	}
	
	return result;
}

vector<CBill> CDataUtils::getBillsByDate(CString date)
{
	CString temp;
	temp.Format(_T("SELECT bill.id,title,money,date,classify_id,classify.`name` FROM bill,classify WHERE bill.classify_id = classify.id and date=DATE_FORMAT('%s', '%%y-%%m-%%d');"), date);
	return getBills(temp);
}

vector<CBill> CDataUtils::getBillsByDate(CString startDate, CString endDate,int type)
{
	CString temp;
	if (type == 0)
	{
		temp.Format(_T("SELECT bill.id,title,money,date,classify_id,classify.`name` from bill,classify WHERE DATE_FORMAT(date,'%%y-%%m-%%d')>= DATE_FORMAT('%s','%%y-%%m-%%d') AND DATE_FORMAT(date,'%%y-%%m-%%d')<= DATE_FORMAT('%s','%%y-%%m-%%d') AND bill.classify_id=classify.id;"),
			startDate, endDate);
	}
	else
	{
		temp.Format(_T("SELECT bill.id,title,money,date,classify_id,classify.`name` from bill,classify WHERE DATE_FORMAT(date,'%%y-%%m-%%d')>= DATE_FORMAT('%s','%%y-%%m-%%d') AND DATE_FORMAT(date,'%%y-%%m-%%d')<= DATE_FORMAT('%s','%%y-%%m-%%d') AND bill.classify_id= %d AND bill.classify_id=classify.id;"),
			startDate, endDate, type);
	}
	return getBills(temp);
}


void CDataUtils::getBillById(int id, CBill &bill)
{
	CString sql;
	sql.Format(_T("SELECT bill.id,title,money,date,classify_id,classify.`name` from bill, classify where bill.id = %d;"),id);
	bill = getBills(sql)[0];
}

void CDataUtils::deleteBillById(int id)
{
	CString sql;
	sql.Format(_T("DELETE FROM bill where bill.id = %d;"), id);
	db.ExecuteSQL(sql);
}

void CDataUtils::updateBill(CBill &bill)
{
	CString sql, date;

	date = bill.m_date.Format("%y-%m-%d");
	sql.Format(_T("UPDATE bill SET title='%s',money=%d,date=DATE_FORMAT('%s','%%y-%%m-%%d'),classify_id=%d WHERE id=%d;"), 
		bill.m_title,bill.m_money,date,bill.m_classify_id,bill.m_id);
	db.ExecuteSQL(sql);
}

vector<CClassify> CDataUtils::getAllClassify()
{
	vector<CClassify> classifys;
	CClassifyRecordSet recordset;

	recordset.Open(CClassifyRecordSet::forwardOnly,_T("SELECT id,name,color FROM classify;"));
	while (!recordset.IsEOF())
	{
		CClassify classify;
		classify.id = recordset.m_id;
		classify.name = recordset.m_name;
		classify.color = recordset.m_color;
		classifys.push_back(classify);
		recordset.MoveNext();
	}

	return classifys;
}

void CDataUtils::insertClassify(CClassify &classify)
{
	CString sql;
	sql.Format(_T("INSERT INTO classify (`name`,color) VALUES('%s',%d);"),
		classify.name,classify.color);
	db.ExecuteSQL(sql);
}

void CDataUtils::deleteClassifyById(int id)
{
	CString sql;
	sql.Format(_T("DELETE FROM classify where classify.id = %d;"), id);
	db.ExecuteSQL(sql);
}

void CDataUtils::updateClassify(CClassify &classify)
{
	CString sql;
	sql.Format(_T("UPDATE classify SET `name`='%s',color=%d WHERE id=%d;"),
		classify.name,classify.color,classify.id);
	db.ExecuteSQL(sql);
}