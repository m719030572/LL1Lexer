#pragma once
#include<vector>
#include<stack>
#include<iostream>
#include"LCTable.h"
#include"Grammar.h"
//LL1�������࣬���������һ��Ԥ�������
class LL1ASY
{
public:
	LL1ASY();
	LL1ASY(LCTable predit_tab);
	bool  LL1ASY::AsyFunc(std::string str);//����Ԥ�����������ַ���
	bool GetIdentyString(std::string str);//����ķ���ʶ���
	~LL1ASY();
protected:
	std::string analysis_stack;//����ջ
	std::string less_stack;//�ַ���ʣ��ջ
	LCTable predit_table;//Ԥ�������
};

