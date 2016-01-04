
// ChildFrm.cpp : CChildFrame ���ʵ��
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

// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	// TODO:  �ڴ���ӳ�Ա��ʼ������
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame ���

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

// CChildFrame ��Ϣ�������


BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO:  �ڴ����ר�ô����/����û���
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
	// TODO:  �ڴ����ר�ô����/����û���
	nCmdShow = SW_MAXIMIZE;
	CMDIChildWnd::ActivateFrame(nCmdShow);
}


void CChildFrame::OnSet()
{
	// TODO:  �ڴ���������������
	CClassifyDialog dialog;
	if (IDOK == dialog.DoModal())
	{
		CCatDoc* pDoc = (CCatDoc*)GetActiveView()->GetDocument();
		::PostMessage(pDoc->detailView->m_hWnd, WM_CLASSIFY_UPDATE, 0, 0);
	}
	
}
