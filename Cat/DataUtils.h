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
	//��ȡ���е��˵�
	vector<CBill> getAllBills();
	//��ȡ�����˵�
	vector<CBill> getBillsByClassify(UINT type);
	//��ȡ���ݿ������е�����
	vector<CString> getDates();
	//�������ڻ�ȡ�˵�---ĳһ��
	vector<CBill> getBillsByDate(CString date);
	//����---�������ڻ�ȡ�˵�---ʱ���
	vector<CBill> getBillsByDate(CString startDate, CString endDate, int type);
	//�����˵�
	void insertBill(CBill bill);
	//�����˵�id��ȡ�˵�
	void getBillById(int id, CBill &bill);
	//ɾ���˵�
	void deleteBillById(int id);
	//�����˵�
	void updateBill(CBill &bill);
	//��ȡ�����������
	vector<CClassify> getAllClassify();
	//�����������
	void insertClassify(CClassify &classify);
	//ɾ���������
	void deleteClassifyById(int id);
	//�����������
	void updateClassify(CClassify &classify);
private:
	CDatabase db;
	vector<CBill> getBills(CString sql);
};

