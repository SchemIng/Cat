// FrameListView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Cat.h"
#include "FrameListView.h"
#include "DataUtils.h"
#include "CatDoc.h"

// CFrameListView

IMPLEMENT_DYNCREATE(CFrameListView, CFormView)

CFrameListView::CFrameListView()
	: CFormView(CFrameListView::IDD)
{

}

CFrameListView::~CFrameListView()
{
}

void CFrameListView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, mList);
}

BEGIN_MESSAGE_MAP(CFrameListView, CFormView)
	ON_MESSAGE(WM_UPDATE_BILL, &CFrameListView::OnUpdateBill)
	ON_NOTIFY(NM_CLICK, IDC_LIST, &CFrameListView::OnNMClickList)
END_MESSAGE_MAP()


// CFrameListView ���

#ifdef _DEBUG
void CFrameListView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFrameListView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFrameListView ��Ϣ�������


void CFrameListView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	((CCatDoc*)GetDocument())->listView = this;

	CRect rect;
	mList.GetClientRect(&rect);
	mList.SetExtendedStyle(mList.GetExtendedStyle() | 
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	mList.InsertColumn(0, _T("���"), LVCFMT_CENTER, rect.Width() / 4, 0);
	mList.InsertColumn(1, _T("����"), LVCFMT_CENTER, rect.Width() / 4, 1);
	mList.InsertColumn(2, _T("����"), LVCFMT_CENTER, rect.Width() / 4, 2);
	mList.InsertColumn(3, _T("Ǯ��"), LVCFMT_CENTER, rect.Width() / 4, 3);
}


void CFrameListView::OnDraw(CDC* /*pDC*/)
{
	// TODO:  �ڴ����ר�ô����/����û���
	mList.DeleteAllItems();

	CDataUtils utils;
	vector<CBill> bills = utils.getAllBills();
	CString temp;

	for (UINT i = 0; i < bills.size(); i++)
	{
		temp.Format(_T("%d"), i + 1);
		mList.InsertItem(i, temp);
		mList.SetItemData(i, bills[i].m_id);

		mList.SetItemText(i, 1, bills[i].m_classify_name);
		mList.SetItemText(i, 2, bills[i].m_title);
		temp.Format(_T("%d"), bills[i].m_money);
		mList.SetItemText(i, 3, temp);
	}
}
afx_msg LRESULT CFrameListView::OnUpdateBill(WPARAM wParam, LPARAM lParam)
{
	Invalidate();
	return 0;
}

void CFrameListView::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	CCatDoc* pDoc = (CCatDoc*)GetDocument();
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;
	if (-1 == pNMListView->iItem)
		return;
	int a = mList.GetItemData(pNMListView->iItem);
	::PostMessage(pDoc->detailView->m_hWnd, WM_LIST_CLICK, 
		mList.GetItemData(pNMListView->iItem) , 0);
}
