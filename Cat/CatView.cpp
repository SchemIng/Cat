
// CatView.cpp : CCatView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Cat.h"
#endif

#include "CatView.h"
#include "CatDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCatView

IMPLEMENT_DYNCREATE(CCatView, CFormView)

BEGIN_MESSAGE_MAP(CCatView, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CCatView::OnTcnSelchangeTab)
END_MESSAGE_MAP()

// CCatView ����/����

CCatView::CCatView()
: CFormView(CCatView::IDD)
{
	// TODO:  �ڴ˴���ӹ������

}

CCatView::~CCatView()
{
}

void CCatView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, mTab);
}

BOOL CCatView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CCatView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

	((CCatDoc*)GetDocument())->catView = this;

	CRect tabRect;
	mTab.InsertItem(0, _T("��Ҫ"));
	mTab.InsertItem(1, _T("ͳ��"));

	mTabTree.Create(IDD_TAB_TREE_VIEW, &mTab);
	//mTabResult.Create(IDD_TAB_RESULT_VIEW, &mTab);

	mTab.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;

	mTabTree.SetWindowPos(NULL, tabRect.left, tabRect.top,
		tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
}


// CCatView ���

#ifdef _DEBUG
void CCatView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCatView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

//CCatDoc* CCatView::GetDocument() const // �ǵ��԰汾��������
//{
//	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCatDoc)));
//	return (CCatDoc*)m_pDocument;
//}
#endif //_DEBUG


// CCatView ��Ϣ�������


void CCatView::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CRect tabRect;    // ��ǩ�ؼ��ͻ�����Rect   

	// ��ȡ��ǩ�ؼ��ͻ���Rect����������������ʺϷ��ñ�ǩҳ   
	mTab.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;

	switch (mTab.GetCurSel())
	{
	case 0:
		mTabTree.SetWindowPos(NULL, tabRect.left, tabRect.top,
			tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		break;
	case 1:
		mTabTree.SetWindowPos(NULL, tabRect.left, tabRect.top,
			tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		if (IDCANCEL == mTabResult.DoModal())
		{
			mTab.SetCurSel(0);
			mTabTree.SetWindowPos(NULL, tabRect.left, tabRect.top,
				tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		}

		break;
	}
}
