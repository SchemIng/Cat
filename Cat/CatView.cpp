
// CatView.cpp : CCatView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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

// CCatView 构造/析构

CCatView::CCatView()
: CFormView(CCatView::IDD)
{
	// TODO:  在此处添加构造代码

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
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CCatView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

	((CCatDoc*)GetDocument())->catView = this;

	CRect tabRect;
	mTab.InsertItem(0, _T("纲要"));
	mTab.InsertItem(1, _T("统计"));

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


// CCatView 诊断

#ifdef _DEBUG
void CCatView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCatView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

//CCatDoc* CCatView::GetDocument() const // 非调试版本是内联的
//{
//	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCatDoc)));
//	return (CCatDoc*)m_pDocument;
//}
#endif //_DEBUG


// CCatView 消息处理程序


void CCatView::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;

	CRect tabRect;    // 标签控件客户区的Rect   

	// 获取标签控件客户区Rect，并对其调整，以适合放置标签页   
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
