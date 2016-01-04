// classify.h : CClassify ���ʵ��



// CClassify ʵ��

// ���������� 2016��1��3��, ������, 10:37

#include "stdafx.h"
#include "classifyrecordset.h"
IMPLEMENT_DYNAMIC(CClassifyRecordSet, CRecordset)

CClassifyRecordSet::CClassifyRecordSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_id = 0;
	m_color = 0;
	m_name = L"";
	m_nFields = 3;
	m_nDefaultType = dynaset;
}

CString CClassifyRecordSet::GetDefaultConnect()
{
	return _T("DSN=cat;SERVER=localhost;UID=root;PWD=Shy66017;DATABASE=cat;PORT=3306");
}

CString CClassifyRecordSet::GetDefaultSQL()
{
	return _T("[classify]");
}

void CClassifyRecordSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[id]"), m_id);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Long(pFX, _T("[color]"), m_color);
}
/////////////////////////////////////////////////////////////////////////////
// CClassify ���

#ifdef _DEBUG
void CClassifyRecordSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CClassifyRecordSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


