// Bill.h : CBill 类的实现



// CBill 实现

// 代码生成在 2015年12月28日, 星期一, 15:32

#include "stdafx.h"
#include "BillRecordSet.h"
IMPLEMENT_DYNAMIC(CBillRecordSet, CRecordset)

CBillRecordSet::CBillRecordSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_id = 0;
	m_title = L"";
	m_money = 0;
	m_date;
	m_classify_id = 0;
	m_nFields = 6;
	m_nDefaultType = dynaset;
	m_classify_name = L"";
}

CString CBillRecordSet::GetDefaultConnect()
{
	return _T("DSN=cat;SERVER=localhost;UID=root;PWD=Shy66017;DATABASE=cat;PORT=3306");
}

CString CBillRecordSet::GetDefaultSQL()
{
	return _T("[bill]");
}

void CBillRecordSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Long(pFX, _T("[id]"), m_id);
	RFX_Text(pFX, _T("[title]"), m_title);
	RFX_Long(pFX, _T("[money]"), m_money);
	RFX_Date(pFX, _T("[date]"), m_date);
	RFX_Long(pFX, _T("[classify_id]"), m_classify_id);
	RFX_Text(pFX, _T("[name]"), m_classify_name); 
}
/////////////////////////////////////////////////////////////////////////////
// CBill 诊断

#ifdef _DEBUG
void CBillRecordSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CBillRecordSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


