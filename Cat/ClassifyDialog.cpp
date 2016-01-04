// ClassifyDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Cat.h"
#include "ClassifyDialog.h"
#include "afxdialogex.h"
#include "DataUtils.h"
#include "CatDoc.h"
#include "MainFrm.h"

#define white 16777215


// CClassifyDialog �Ի���

IMPLEMENT_DYNAMIC(CClassifyDialog, CDialogEx)

CClassifyDialog::CClassifyDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClassifyDialog::IDD, pParent)
	, mName(_T(""))
{
	mId = -1;
	mColor = white;
}

CClassifyDialog::~CClassifyDialog()
{
}

void CClassifyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CLASSIFY_COLOR, mPic);
	DDX_Control(pDX, IDC_CLASSIFY_LIST, mList);
	DDX_Text(pDX, IDC_EDIT_CLASSIFY, mName);
}


BEGIN_MESSAGE_MAP(CClassifyDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_CLASSIFY_INSERT, &CClassifyDialog::OnBnClickedBtnClassifyInsert)
	ON_BN_CLICKED(IDC_BTN_CLASSIFY_DELETE, &CClassifyDialog::OnBnClickedBtnClassifyDelete)
	ON_BN_CLICKED(IDC_BTN_CLASSIFY_COLOR, &CClassifyDialog::OnBnClickedBtnClassifyColor)
	ON_NOTIFY(NM_CLICK, IDC_CLASSIFY_LIST, &CClassifyDialog::OnNMClickClassifyList)
	ON_BN_CLICKED(IDC_BTN_CLASSIFY_UPDATE, &CClassifyDialog::OnBnClickedBtnClassifyUpdate)
END_MESSAGE_MAP()


// CClassifyDialog ��Ϣ�������


void CClassifyDialog::OnBnClickedBtnClassifyInsert()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDataUtils utils;
	CClassify classify;
	UpdateData();

	classify.name = mName;
	classify.color = mColor;
	utils.insertClassify(classify);
	updateList();
	clearInfo();
}


void CClassifyDialog::OnBnClickedBtnClassifyDelete()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	if (-1 != mId)
	{
		if (IDYES == AfxMessageBox(_T("ɾ���÷����,����˵�Ҳ��ɾ����"),MB_ICONQUESTION | MB_YESNO))
		{
			CDataUtils utils;
			utils.deleteClassifyById(mId);
			updateList();
			clearInfo();
		}
	}
}


void CClassifyDialog::OnBnClickedBtnClassifyColor()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CColorDialog colorDlg;
	COLORREF color;

	if (IDOK == colorDlg.DoModal())
	{
		color = colorDlg.GetColor();
		showColor(color);
	}
}

void CClassifyDialog::showColor(COLORREF color)
{
	mColor = color;
	CDC* pDc = mPic.GetDC();
	CRect rct;
	mPic.GetWindowRect(&rct);
	CBrush brs;
	brs.CreateSolidBrush(color);
	CRect picrct;
	picrct.top = 0;
	picrct.left = 0;
	picrct.bottom = rct.Height();
	picrct.right = rct.Width();
	pDc->FillRect(&picrct, &brs);
}


BOOL CClassifyDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;
	mList.GetClientRect(&rect);
	mList.SetExtendedStyle(mList.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	mList.InsertColumn(0, _T("���"), LVCFMT_CENTER, rect.Width() / 4, 0);
	mList.InsertColumn(1, _T("����"), LVCFMT_CENTER, 3 * rect.Width() / 4, 1);

	updateList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CClassifyDialog::updateList()
{
	CDataUtils utils;
	mClassifys = utils.getAllClassify();

	mList.DeleteAllItems();
	for (UINT i = 0; i < mClassifys.size(); i++)
	{
		CString temp;
		temp.Format(_T("%d"), i + 1);

		mList.InsertItem(i, temp);
		mList.SetItemText(i, 1, mClassifys[i].name);
	}
}

void CClassifyDialog::OnNMClickClassifyList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CCatDoc* pDoc = (CCatDoc*)pMain->MDIGetActive()->GetActiveView()->GetDocument();

	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;
	if (-1 == pNMListView->iItem)
		return;
	
	mName = mClassifys[pNMListView->iItem].name;
	mId = mClassifys[pNMListView->iItem].id;
	if (mId >= 1 && mId <= 3)
	{
		GetDlgItem(IDC_BTN_CLASSIFY_DELETE)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_BTN_CLASSIFY_DELETE)->EnableWindow(TRUE);
	}
	UpdateData(FALSE);
	showColor(mClassifys[pNMListView->iItem].color);
}


void CClassifyDialog::OnBnClickedBtnClassifyUpdate()
{
	UpdateData();
	CClassify classify;
	CDataUtils utils;

	classify.id = mId;
	classify.name = mName;
	classify.color = mColor;

	utils.updateClassify(classify);
	updateList();
	clearInfo();
}
void CClassifyDialog::clearInfo()
{
	mName = _T("");
	UpdateData(FALSE);
	showColor(white);
}