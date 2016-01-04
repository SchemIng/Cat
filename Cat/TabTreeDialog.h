#pragma once
#include "afxcmn.h"


// CTabTreeDialog �Ի���

class CTabTreeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTabTreeDialog)

public:
	CTabTreeDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabTreeDialog();

	// �Ի�������
	enum { IDD = IDD_TAB_TREE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg LRESULT OnUpdateBill(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl mTree;
	virtual BOOL OnInitDialog();
};
