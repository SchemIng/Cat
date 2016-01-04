#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "Bill.h"


// CFrameDetailView ������ͼ

class CFrameDetailView : public CFormView
{
	DECLARE_DYNCREATE(CFrameDetailView)

protected:
	CFrameDetailView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CFrameDetailView();

public:
	enum { IDD = IDD_FRAMEDETAILVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg LRESULT OnListClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClassify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CString mTitle;
	UINT mMoney;
	CComboBox mCombo;
	CDateTimeCtrl mDatePicker;
	CTime mDate;
	CStatic mBitmapCtrl;
	afx_msg void OnBnClickedBtnInsert();
	afx_msg void OnBnClickedBtnUpdate();
	afx_msg void OnBnClickedBtnDelete();
	virtual void OnInitialUpdate();

private:
	int mId;
	void clearInfo();
	BOOLEAN getInfo(CBill &bill);
public:
	afx_msg void OnCbnSelchangeCombo();
};


