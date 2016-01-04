#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Classify.h"

// CClassifyDialog 对话框

class CClassifyDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CClassifyDialog)

public:
	CClassifyDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CClassifyDialog();

// 对话框数据
	enum { IDD = IDD_CLASSIFY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void showColor(COLORREF color);
	void updateList();
	void clearInfo();

	DECLARE_MESSAGE_MAP()

	vector<CClassify> mClassifys;
	int mId;
	long mColor;
public:
	afx_msg void OnBnClickedBtnClassifyInsert();
	afx_msg void OnBnClickedBtnClassifyDelete();
	afx_msg void OnBnClickedBtnClassifyColor();
	CStatic mPic;
	virtual BOOL OnInitDialog();
	CListCtrl mList;
	afx_msg void OnNMClickClassifyList(NMHDR *pNMHDR, LRESULT *pResult);
	CString mName;
	afx_msg void OnBnClickedBtnClassifyUpdate();
};
