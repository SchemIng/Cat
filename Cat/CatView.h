
// CatView.h : CCatView 类的接口
//

#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "TabResultDialog.h"
#include "TabTreeDialog.h"
//#include "CatDoc.h"

class CCatView : public CFormView
{
protected: // 仅从序列化创建
	CCatView();
	DECLARE_DYNCREATE(CCatView)

public:
	enum{ IDD = IDD_CAT_FORM };

// 特性
public:
	//CCatDoc* GetDocument() const;
	CTabCtrl mTab;
	CTabResultDialog mTabResult;
	CTabTreeDialog mTabTree;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CCatView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // CatView.cpp 中的调试版本
inline CCatDoc* CCatView::GetDocument() const
   { return reinterpret_cast<CCatDoc*>(m_pDocument); }
#endif

