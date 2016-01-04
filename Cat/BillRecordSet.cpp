// Bill.h : CBill ���ʵ��



// CBill ʵ��

// ���������� 2015��12��28��, ����һ, 15:32

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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[id]"), m_id);
	RFX_Text(pFX, _T("[title]"), m_title);
	RFX_Long(pFX, _T("[money]"), m_money);
	RFX_Date(pFX, _T("[date]"), m_date);
	RFX_Long(pFX, _T("[classify_id]"), m_classify_id);
	RFX_Text(pFX, _T("[name]"), m_classify_name); 
}
/////////////////////////////////////////////////////////////////////////////
// CBill ���

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


