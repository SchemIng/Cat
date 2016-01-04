
// CatView.h : CCatView ��Ľӿ�
//

#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "TabResultDialog.h"
#include "TabTreeDialog.h"
//#include "CatDoc.h"

class CCatView : public CFormView
{
protected: // �������л�����
	CCatView();
	DECLARE_DYNCREATE(CCatView)

public:
	enum{ IDD = IDD_CAT_FORM };

// ����
public:
	//CCatDoc* GetDocument() const;
	CTabCtrl mTab;
	CTabResultDialog mTabResult;
	CTabTreeDialog mTabTree;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CCatView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // CatView.cpp �еĵ��԰汾
inline CCatDoc* CCatView::GetDocument() const
   { return reinterpret_cast<CCatDoc*>(m_pDocument); }
#endif

