#pragma once
#include "afxdtctl.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "tchart1.h"
#include "Bill.h"


// CTabResultDialog 对话框

class CTabResultDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTabResultDialog)

public:
	CTabResultDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabResultDialog();

	// 对话框数据
	enum { IDD = IDD_TAB_RESULT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CRect listRect;
	CTime mStartTime, mEndTime;
	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl mDatePickerStart;
	CDateTimeCtrl mDatePickerEnd;
	CComboBox mCombo;
	virtual BOOL OnInitDialog();
	CListCtrl mList;
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnCount();
	afx_msg void OnBnClickedBtnDetail();
	CTchart1 mChart;
	vector<CBill> bills;
	afx_msg void OnBnClickedBtnExport();
};
