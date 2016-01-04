// TabResultDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Cat.h"
#include "TabResultDialog.h"
#include "afxdialogex.h"
#include "DataUtils.h"
#include "CSeries.h"
#include "CApplication.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
#include "CFont0.h"
#include "CRange.h"
#include "Classify.h"


// CTabResultDialog �Ի���

IMPLEMENT_DYNAMIC(CTabResultDialog, CDialogEx)

CTabResultDialog::CTabResultDialog(CWnd* pParent /*=NULL*/)
: CDialogEx(CTabResultDialog::IDD, pParent)
{
}

CTabResultDialog::~CTabResultDialog()
{
}

void CTabResultDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_START, mDatePickerStart);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END, mDatePickerEnd);
	DDX_Control(pDX, IDC_COMBO_RESULT, mCombo);
	DDX_Control(pDX, IDC_LIST_RESULT, mList);
	DDX_Control(pDX, IDC_TCHART1, mChart);
}


BEGIN_MESSAGE_MAP(CTabResultDialog, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_COUNT, &CTabResultDialog::OnBnClickedBtnCount)
	ON_BN_CLICKED(IDC_BTN_DETAIL, &CTabResultDialog::OnBnClickedBtnDetail)
	ON_BN_CLICKED(IDC_BTN_EXPORT, &CTabResultDialog::OnBnClickedBtnExport)
END_MESSAGE_MAP()


// CTabResultDialog ��Ϣ�������


BOOL CTabResultDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CDataUtils utils;
	vector<CClassify> classifys = utils.getAllClassify();
	mCombo.InsertString(0, _T("����"));
	mCombo.SetItemData(0, 0);

	for (UINT i = 0; i < classifys.size(); i++)
	{
		mCombo.InsertString(i + 1, classifys[i].name);
		mCombo.SetItemData(i + 1, classifys[i].id);
	}

	mCombo.SetCurSel(0);

	mDatePickerStart.SetFormat(_T("yyyy-MM-dd"));
	mDatePickerEnd.SetFormat(_T("yyyy-MM-dd"));
	mDatePickerEnd.GetTime(mEndTime);
	int year, month;
	month = mEndTime.GetMonth() - 1;
	year = mEndTime.GetYear();
	if (month == 0)
	{
		month = 12;
		year = mEndTime.GetYear() - 1;
	}
	mStartTime = CTime(year, month, mEndTime.GetDay(), mEndTime.GetHour(), mEndTime.GetMinute(), mEndTime.GetSecond());
	mDatePickerStart.SetTime(&mStartTime);

	CRect rect;
	mList.GetClientRect(&rect);
	mList.SetExtendedStyle(mList.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	mList.InsertColumn(0, _T("���"), LVCFMT_CENTER, rect.Width() / 5, 0);
	mList.InsertColumn(1, _T("����"), LVCFMT_CENTER, rect.Width() / 5, 1);
	mList.InsertColumn(2, _T("����"), LVCFMT_CENTER, rect.Width() / 5, 2);
	mList.InsertColumn(3, _T("Ǯ��"), LVCFMT_CENTER, rect.Width() / 5, 3);
	mList.InsertColumn(4, _T("����"), LVCFMT_CENTER, rect.Width() / 5, 4);

	return TRUE;
}


void CTabResultDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������

}


void CTabResultDialog::OnBnClickedBtnCount()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	mList.ShowWindow(SW_HIDE);
	mChart.ShowWindow(SW_NORMAL);

	CDataUtils utils;
	mDatePickerStart.GetTime(mStartTime);
	mDatePickerEnd.GetTime(mEndTime);

	bills = utils.getBillsByDate(mStartTime.Format(_T("%y-%m-%d")), mEndTime.Format(_T("%y-%m-%d")), mCombo.GetItemData(mCombo.GetCurSel()));
	vector<CClassify> classifys = utils.getAllClassify();
	int* sums = new int[classifys.size()];

	for (UINT i = 0; i < classifys.size(); i++)
	{
		sums[i] = 0;
		classifys[i].index = i;
	}

	int sum = 0;;
	for (UINT i = 0; i < bills.size(); i++)
	{
		sum += bills[i].m_money;
		for (UINT j = 0; j < classifys.size(); j++)
		{
			if (bills[i].m_classify_id == classifys[j].id)
			{
				sums[classifys[j].index] += bills[i].m_money;
			}
		}
	}

	CSeries series = mChart.Series(0);
	series.put_Title(_T("����ͳ��"));
	series.Clear();

	for (UINT i = 0; i < classifys.size(); i++)
	{
		series.Add(sums[i], classifys[i].name, classifys[i].color);
	}

	delete[] sums;
}


void CTabResultDialog::OnBnClickedBtnDetail()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	mList.ShowWindow(SW_NORMAL);
	CDataUtils utils;
	mDatePickerStart.GetTime(mStartTime);
	mDatePickerEnd.GetTime(mEndTime);

	bills = utils.getBillsByDate(mStartTime.Format(_T("%y-%m-%d")), mEndTime.Format(_T("%y-%m-%d")), mCombo.GetCurSel());
	CString temp;

	for (UINT i = 0; i < bills.size(); i++)
	{
		temp.Format(_T("%d"), i + 1);
		mList.InsertItem(i, temp);
		mList.SetItemText(i, 1, bills[i].m_classify_name);
		mList.SetItemText(i, 2, bills[i].m_title);
		temp.Format(_T("%d"), bills[i].m_money);
		mList.SetItemText(i, 3, temp);
		mList.SetItemText(i, 4, bills[i].m_date.Format(_T("%y-%m-%d")));
	}
}


void CTabResultDialog::OnBnClickedBtnExport()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (0 == bills.size())
	{
		AfxMessageBox(_T("�����ݵ�����"));
		return;
	}
	CString defaultName;
	defaultName.Format(_T("%s �� %s������ϸ��"), mStartTime.Format(_T("20%y-%m-%d")), mEndTime.Format(_T("20%y-%m-%d")));

	CFileDialog fileDialog(FALSE, _T("(*.xlsx)"), defaultName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("(*.xlsx)|*.xlsx||"), NULL);

	if (fileDialog.DoModal() == IDOK){
		CString file = fileDialog.GetPathName();

		COleVariant
			covTrue((short)TRUE),
			covFalse((short)FALSE),
			covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

		CApplication   app;
		CWorkbooks   books;
		CWorkbook   book;
		CWorksheets   sheets;
		CWorksheet   sheet;
		CRange   range;
		CFont0 font;

		if (!app.CreateDispatch(_T("Excel.Application")))
		{
			AfxMessageBox(_T("����ʧ�ܣ�"));
			return;
		}

		books = app.get_Workbooks();
		book = books.Add(covOptional);
		sheets = book.get_Worksheets();
		sheet = sheets.get_Item(COleVariant((short)1));
		sheet.put_Name(_T("����ͳ��"));

		range.AttachDispatch(sheet.get_Cells(), TRUE);//�������е�Ԫ��
		//�����_variant_t����ʹ��COleVariant����
		range.put_Item(COleVariant((long)1), COleVariant((long)1), COleVariant(_T("����")));
		range.put_Item(COleVariant((long)1), COleVariant((long)2), COleVariant(_T("Ǯ��")));
		range.put_Item(COleVariant((long)1), COleVariant((long)3), COleVariant(_T("����")));
		range.put_Item(COleVariant((long)1), COleVariant((long)4), COleVariant(_T("����")));

		// ˮƽ����   ��ֱ����
		range.put_VerticalAlignment(_variant_t((long)-4108));
		range.put_HorizontalAlignment(_variant_t((long)-4108));
		range.put_ColumnWidth(_variant_t((long)10));

		/////////////���ñ������弰��ɫ/////////
		range.AttachDispatch(sheet.get_Range(_variant_t("A1"), _variant_t("D1")));
		font.AttachDispatch(range.get_Font());
		font.put_Bold(_variant_t((long)1));//����
		font.put_Size(_variant_t((long)16));
		CString temp;

		for (UINT i = 0; i < bills.size(); i++)
		{
			temp.Format(_T("%d"), bills[i].m_money);
			range.put_Item(COleVariant((long)i + 2), COleVariant((long)1), COleVariant(bills[i].m_title));
			range.put_Item(COleVariant((long)i + 2), COleVariant((long)2), COleVariant(temp));
			range.put_Item(COleVariant((long)i + 2), COleVariant((long)3), COleVariant(bills[i].m_date.Format(_T("20%y-%m-%d"))));
			range.put_Item(COleVariant((long)i + 2), COleVariant((long)4), COleVariant(bills[i].m_classify_name));
		}
		range.AttachDispatch(sheet.get_UsedRange());//������ʹ�õĵ�Ԫ��

		book.SaveCopyAs(COleVariant(file));

		range.ReleaseDispatch();
		sheet.ReleaseDispatch();
		sheets.ReleaseDispatch();
		book.ReleaseDispatch();
		books.ReleaseDispatch();
		//m_ExlAppһ��Ҫ�ͷţ������������󻹻���һ��Excel����פ�����ڴ��У����ҳ����ظ����е�ʱ������ 
		app.ReleaseDispatch();

		AfxMessageBox(_T("�ļ��ѱ���"));
	}
}
