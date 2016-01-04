// TabTreeDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Cat.h"
#include "TabTreeDialog.h"
#include "afxdialogex.h"
#include "DataUtils.h"
#include "Bill.h"
#include "Classify.h"


// CTabTreeDialog 对话框

IMPLEMENT_DYNAMIC(CTabTreeDialog, CDialogEx)

CTabTreeDialog::CTabTreeDialog(CWnd* pParent /*=NULL*/)
: CDialogEx(CTabTreeDialog::IDD, pParent)
{

}

CTabTreeDialog::~CTabTreeDialog()
{
}

void CTabTreeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE, mTree);
}


BEGIN_MESSAGE_MAP(CTabTreeDialog, CDialogEx)
	ON_MESSAGE(WM_UPDATE_BILL, &CTabTreeDialog::OnUpdateBill)
END_MESSAGE_MAP()


// CTabTreeDialog 消息处理程序


BOOL CTabTreeDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	OnUpdateBill(0, 0);
	return TRUE;
}
afx_msg LRESULT CTabTreeDialog::OnUpdateBill(WPARAM wParam, LPARAM lParam)
{
	mTree.DeleteAllItems();
	CDataUtils utils;
	vector<CString> times = utils.getDates();
	vector<CClassify> classifys = utils.getAllClassify();
	int* sums = new int[classifys.size()];

	for (UINT i = 0; i < classifys.size(); i++)
	{
		classifys[i].index = i;
	}

	for (UINT i = 0; i < times.size(); i++)
	{
		int sum = 0;
		vector<CBill> bills = utils.getBillsByDate(times[i]);
		HTREEITEM item = mTree.InsertItem(times[i]);

		for (UINT j = 0; j < classifys.size(); j++)
		{
			sums[j] = 0;
		}

		for (UINT j = 0; j < bills.size(); j++)
		{
			sum += bills[j].m_money;
			for (UINT k = 0; k < classifys.size(); k++)
			{
				if (bills[j].m_classify_id == classifys[k].id)
				{
					sums[classifys[k].index] += bills[j].m_money;
				}
			}
		}

		CString temp;
		temp.Format(_T("总消费数:%d"), sum);
		mTree.InsertItem(temp, item);

		for (UINT i = 0; i < classifys.size(); i++)
		{
			temp.Format(_T("%s:%d"), classifys[i].name,sums[classifys[i].index]);
			mTree.InsertItem(temp, item);
		}

	}

	delete[] sums;
	return 0;
}