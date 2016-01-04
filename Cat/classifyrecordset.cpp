// classify.h : CClassify 类的实现



// CClassify 实现

// 代码生成在 2016年1月3日, 星期日, 10:37

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
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Long(pFX, _T("[id]"), m_id);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Long(pFX, _T("[color]"), m_color);
}
/////////////////////////////////////////////////////////////////////////////
// CClassify 诊断

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


