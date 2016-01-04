
// ChildFrm.cpp : CChildFrame 类的实现
//

#include "stdafx.h"
#include "Cat.h"

#include "ChildFrm.h"
#include "CatDoc.h"
#include "FrameDetailView.h"
#include "FrameListView.h"
#include "CatView.h"
#include "ClassifyDialog.h"
#include "CatDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	ON_COMMAND(ID_SET, &CChildFrame::OnSet)
END_MESSAGE_MAP()

// CChildFrame 构造/析构

CChildFrame::CChildFrame()
{
	// TODO:  在此添加成员初始化代码
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame 诊断

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}
#endif //_DEBUG

// CChildFrame 消息处理程序


BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO:  在此添加专用代码和/或调用基类
	CRect rect;
	GetClientRect(&rect);

	int width = rect.Width() / 3;

	if (!m_Splitter_1.CreateStatic(this, 1, 2))
	{
		return FALSE;
	}

	if (!m_Splitter_1.CreateView(0, 0, RUNTIME_CLASS(CCatView),
		CSize(width, rect.Height()), pContext))
	{
		return FALSE;
	}

	if (!m_Splitter_2.CreateStatic(&m_Splitter_1, 2, 1, WS_CHILD | WS_VISIBLE,
		m_Splitter_1.IdFromRowCol(0, 1)))
	{
		return FALSE;
	}

	if (!m_Splitter_2.CreateView(0, 0, RUNTIME_CLASS(CFrameDetailView),
		CSize(width * 2, rect.Height()), pContext))
	{
		return FALSE;
	}

	if (!m_Splitter_2.CreateView(1, 0, RUNTIME_CLASS(CFrameListView),
		CSize(width * 2, rect.Height() / 2), pContext))
	{
		return FALSE;
	}

	return TRUE;
}


void CChildFrame::ActivateFrame(int nCmdShow)
{
	// TODO:  在此添加专用代码和/或调用基类
	nCmdShow = SW_MAXIMIZE;
	CMDIChildWnd::ActivateFrame(nCmdShow);
}


void CChildFrame::OnSet()
{
	// TODO:  在此添加命令处理程序代码
	CClassifyDialog dialog;
	if (IDOK == dialog.DoModal())
	{
		CCatDoc* pDoc = (CCatDoc*)GetActiveView()->GetDocument();
		::PostMessage(pDoc->detailView->m_hWnd, WM_CLASSIFY_UPDATE, 0, 0);
	}
	
}
