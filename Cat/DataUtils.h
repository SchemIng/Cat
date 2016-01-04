#pragma once
#include <odbcinst.h>
#include "afxdb.h"
#include "stdafx.h"
#include "Bill.h"
#include "Classify.h"

class CDataUtils
{
public:
	CDataUtils();
	~CDataUtils();
	//获取所有的账单
	vector<CBill> getAllBills();
	//获取分类账单
	vector<CBill> getBillsByClassify(UINT type);
	//获取数据库里所有的日期
	vector<CString> getDates();
	//根据日期获取账单---某一天
	vector<CBill> getBillsByDate(CString date);
	//重载---根据日期获取账单---时间段
	vector<CBill> getBillsByDate(CString startDate, CString endDate, int type);
	//插入账单
	void insertBill(CBill bill);
	//根据账单id获取账单
	void getBillById(int id, CBill &bill);
	//删除账单
	void deleteBillById(int id);
	//更新账单
	void updateBill(CBill &bill);
	//获取所有消费类别
	vector<CClassify> getAllClassify();
	//插入消费类别
	void insertClassify(CClassify &classify);
	//删除消费类别
	void deleteClassifyById(int id);
	//更新消费类别
	void updateClassify(CClassify &classify);
private:
	CDatabase db;
	vector<CBill> getBills(CString sql);
};

