#pragma once

//账单的实体型
class CBill
{

public:
	const static UINT TYPE_FOOD = 1;
	const static UINT TYPE_DAILY = 2;
	const static UINT TYPE_ELECTRICAL = 3;
	const static UINT TYPE_OTHER = 4;


public:
	CBill();
	~CBill();

	long	m_id;
	CString	m_title;
	long	m_money;
	CTime	m_date;
	long	m_classify_id;
	CString m_classify_name;
};

