#pragma once
#include "Bill.h"

class CPie
{
public:
	CPie(CPaintDC* dc, CPoint o, int r);
	~CPie();
	void Draw(vector<CBill> bills);

private:
	CPoint o;
	int r;
	CPaintDC dc;
	void count(vector<CBill> bills, double* a);
};

