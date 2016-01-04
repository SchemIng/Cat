// TabResultDialog.cpp : 实现文件
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


// CTabResultDialog 对话框

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


// CTabResultDialog 消息处理程序


BOOL CTabResultDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CDataUtils utils;
	vector<CClassify> classifys = utils.getAllClassify();
	mCombo.InsertString(0, _T("所有"));
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
	mList.InsertColumn(0, _T("序号"), LVCFMT_CENTER, rect.Width() / 5, 0);
	mList.InsertColumn(1, _T("类型"), LVCFMT_CENTER, rect.Width() / 5, 1);
	mList.InsertColumn(2, _T("名称"), LVCFMT_CENTER, rect.Width() / 5, 2);
	mList.InsertColumn(3, _T("钱数"), LVCFMT_CENTER, rect.Width() / 5, 3);
	mList.InsertColumn(4, _T("日期"), LVCFMT_CENTER, rect.Width() / 5, 4);

	return TRUE;
}


void CTabResultDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码

}


void CTabResultDialog::OnBnClickedBtnCount()
{
	// TODO:  在此添加控件通知处理程序代码
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
	series.put_Title(_T("消费统计"));
	series.Clear();

	for (UINT i = 0; i < classifys.size(); i++)
	{
		series.Add(sums[i], classifys[i].name, classifys[i].color);
	}

	delete[] sums;
}


void CTabResultDialog::OnBnClickedBtnDetail()
{
	// TODO:  在此添加控件通知处理程序代码
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
	// TODO:  在此添加控件通知处理程序代码
	if (0 == bills.size())
	{
		AfxMessageBox(_T("无数据导出！"));
		return;
	}
	CString defaultName;
	defaultName.Format(_T("%s 至 %s消费明细表"), mStartTime.Format(_T("20%y-%m-%d")), mEndTime.Format(_T("20%y-%m-%d")));

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
			AfxMessageBox(_T("创建失败！"));
			return;
		}

		books = app.get_Workbooks();
		book = books.Add(covOptional);
		sheets = book.get_Worksheets();
		sheet = sheets.get_Item(COleVariant((short)1));
		sheet.put_Name(_T("消费统计"));

		range.AttachDispatch(sheet.get_Cells(), TRUE);//加载所有单元格
		//这里的_variant_t可以使用COleVariant代替
		range.put_Item(COleVariant((long)1), COleVariant((long)1), COleVariant(_T("名称")));
		range.put_Item(COleVariant((long)1), COleVariant((long)2), COleVariant(_T("钱数")));
		range.put_Item(COleVariant((long)1), COleVariant((long)3), COleVariant(_T("日期")));
		range.put_Item(COleVariant((long)1), COleVariant((long)4), COleVariant(_T("类型")));

		// 水平对齐   垂直对齐
		range.put_VerticalAlignment(_variant_t((long)-4108));
		range.put_HorizontalAlignment(_variant_t((long)-4108));
		range.put_ColumnWidth(_variant_t((long)10));

		/////////////设置标题字体及颜色/////////
		range.AttachDispatch(sheet.get_Range(_variant_t("A1"), _variant_t("D1")));
		font.AttachDispatch(range.get_Font());
		font.put_Bold(_variant_t((long)1));//粗体
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
		range.AttachDispatch(sheet.get_UsedRange());//加载已使用的单元格

		book.SaveCopyAs(COleVariant(file));

		range.ReleaseDispatch();
		sheet.ReleaseDispatch();
		sheets.ReleaseDispatch();
		book.ReleaseDispatch();
		books.ReleaseDispatch();
		//m_ExlApp一定要释放，否则程序结束后还会有一个Excel进程驻留在内存中，而且程序重复运行的时候会出错 
		app.ReleaseDispatch();

		AfxMessageBox(_T("文件已保存"));
	}
}
