#pragma once
#include "afxcmn.h"



// CFrameListView 窗体视图

class CFrameListView : public CFormView
{
	DECLARE_DYNCREATE(CFrameListView)

protected:
	CFrameListView();           // 动态创建所使用的受保护的构造函数
	virtual ~CFrameListView();

public:
	enum { IDD = IDD_FRAMELISTVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnUpdateBill(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	CListCtrl mList;
	virtual void OnDraw(CDC* /*pDC*/);
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
};


