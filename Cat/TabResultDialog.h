#pragma once
#include "afxdtctl.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "tchart1.h"
#include "Bill.h"


// CTabResultDialog �Ի���

class CTabResultDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTabResultDialog)

public:
	CTabResultDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabResultDialog();

	// �Ի�������
	enum { IDD = IDD_TAB_RESULT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
