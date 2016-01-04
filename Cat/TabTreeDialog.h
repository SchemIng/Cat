#pragma once
#include "afxcmn.h"


// CTabTreeDialog 对话框

class CTabTreeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTabTreeDialog)

public:
	CTabTreeDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabTreeDialog();

	// 对话框数据
	enum { IDD = IDD_TAB_TREE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnUpdateBill(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl mTree;
	virtual BOOL OnInitDialog();
};
