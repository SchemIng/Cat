// FrameDetailView.cpp : 实现文件
//

#include "stdafx.h"
#include "Cat.h"
#include "FrameDetailView.h"
#include "DataUtils.h"
#include "CatView.h"
#include "CatDoc.h"
#include "FrameListView.h"
#include "Classify.h"

// CFrameDetailView

IMPLEMENT_DYNCREATE(CFrameDetailView, CFormView)

CFrameDetailView::CFrameDetailView()
	: CFormView(CFrameDetailView::IDD)
	, mTitle(_T(""))
	, mMoney(0)
{
	mId = -1;
}

CFrameDetailView::~CFrameDetailView()
{
}

void CFrameDetailView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TITLE, mTitle);
	DDX_Text(pDX, IDC_EDIT_MONEY, mMoney);
	DDX_Control(pDX, IDC_COMBO, mCombo);
	DDX_Control(pDX, IDC_DATETIMEPICKER, mDatePicker);
	DDX_Control(pDX, IDC_BITMAP, mBitmapCtrl);
}

BEGIN_MESSAGE_MAP(CFrameDetailView, CFormView)
	ON_BN_CLICKED(IDC_BTN_INSERT, &CFrameDetailView::OnBnClickedBtnInsert)
	ON_BN_CLICKED(IDC_BTN_UPDATE, &CFrameDetailView::OnBnClickedBtnUpdate)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CFrameDetailView::OnBnClickedBtnDelete)
	ON_MESSAGE(WM_LIST_CLICK, &CFrameDetailView::OnListClick)
	ON_MESSAGE(WM_CLASSIFY_UPDATE, &CFrameDetailView::OnClassify)
	ON_CBN_SELCHANGE(IDC_COMBO, &CFrameDetailView::OnCbnSelchangeCombo)
END_MESSAGE_MAP()


// CFrameDetailView 诊断

#ifdef _DEBUG
void CFrameDetailView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFrameDetailView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFrameDetailView 消息处理程序


void CFrameDetailView::OnBnClickedBtnInsert()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	CDataUtils utils;
	CBill bill;

	if (!getInfo(bill))
		return;
	
	utils.insertBill(bill);
	clearInfo();

	CCatDoc* pDoc = (CCatDoc*)GetDocument();
	::PostMessage(pDoc->catView->mTabTree.m_hWnd, WM_UPDATE_BILL, 0, 0);
	::PostMessage(pDoc->listView->m_hWnd, WM_UPDATE_BILL, 0, 0);
}


void CFrameDetailView::OnBnClickedBtnUpdate()
{
	// TODO:  在此添加控件通知处理程序代码
	if (-1 == mId)
		return;
	CDataUtils utils;
	CBill bill;

	if (!getInfo(bill))
		return;
	getInfo(bill);
	bill.m_id = mId;

	utils.updateBill(bill);
	clearInfo();

	CCatDoc* pDoc = (CCatDoc*)GetDocument();
	::PostMessage(pDoc->catView->mTabTree.m_hWnd, WM_UPDATE_BILL, 0, 0);
	::PostMessage(pDoc->listView->m_hWnd, WM_UPDATE_BILL, 0, 0);

}


void CFrameDetailView::OnBnClickedBtnDelete()
{
	// TODO:  在此添加控件通知处理程序代码
	if (-1 == mId)
		return;

	CDataUtils utils;
	utils.deleteBillById(mId);
	clearInfo();

	CCatDoc* pDoc = (CCatDoc*)GetDocument();
	::PostMessage(pDoc->catView->mTabTree.m_hWnd, WM_UPDATE_BILL, 0, 0);
	::PostMessage(pDoc->listView->m_hWnd, WM_UPDATE_BILL, 0, 0);
}


void CFrameDetailView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	((CCatDoc*)GetDocument())->detailView = this;
	
	OnClassify(0,0);
	mDatePicker.SetFormat(_T("yyyy-MM-dd"));
}

afx_msg LRESULT CFrameDetailView::OnListClick(WPARAM wParam, LPARAM lParam)
{
	CBill bill;
	CDataUtils utils;
	utils.getBillById(wParam, bill);
	vector<CClassify> classifys = utils.getAllClassify();

	for (UINT i = 0; i < classifys.size(); i++)
	{
		if (mCombo.GetItemData(i) == bill.m_classify_id)
		{
			mCombo.SetCurSel(i);
			break;
		}
	}

	mId = wParam;
	mTitle = bill.m_title;
	mMoney = bill.m_money;
	mDate = bill.m_date;
	mDatePicker.SetTime(&mDate);

	UpdateData(FALSE);
	OnCbnSelchangeCombo();
	return 0;
}

void CFrameDetailView::clearInfo()
{
	mId = -1;
	mTitle = "";
	mMoney = 0;
	mCombo.SetCurSel(0);
	CTime t = CTime::GetCurrentTime();
	mDatePicker.SetTime(&t);
	UpdateData(FALSE);
}

BOOLEAN CFrameDetailView::getInfo(CBill &bill)
{
	UpdateData(TRUE);
	
	mDatePicker.GetTime(mDate);

	if (mTitle.GetLength() == 0)
	{
		AfxMessageBox(_T("名称不能为空"));
		return FALSE;
	}

	bill.m_title = mTitle;
	bill.m_money = mMoney;
	bill.m_classify_id = mCombo.GetItemData(mCombo.GetCurSel());
	bill.m_date = mDate;

	return TRUE;
}

void CFrameDetailView::OnCbnSelchangeCombo()
{
	// TODO:  在此添加控件通知处理程序代码
	CBitmap bitmap;
	HBITMAP hBmp;

	switch (mCombo.GetCurSel())
	{
	case 0:
		bitmap.LoadBitmap(IDB_FOOD);
		break;
	case 1:
		bitmap.LoadBitmap(IDB_DAILY);
		break;
	case 2:
		bitmap.LoadBitmap(IDB_ELEC);
		break;
	default:
		bitmap.LoadBitmap(IDB_OTHER);
		break;
	}

	hBmp = (HBITMAP)bitmap.GetSafeHandle();
	mBitmapCtrl.SetBitmap(hBmp);
}
afx_msg LRESULT CFrameDetailView::OnClassify(WPARAM wParam, LPARAM lParam)
{
	mCombo.ResetContent();
	CDataUtils utils;
	vector<CClassify> classifys = utils.getAllClassify();

	for (UINT i = 0; i < classifys.size(); i++)
	{
		mCombo.InsertString(i, classifys[i].name);
		mCombo.SetItemData(i, classifys[i].id);
	}
	mCombo.SetCurSel(0);

	return 0;
}