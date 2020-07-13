#pragma once
#include<vector>
#include<stack>
#include<iostream>
#include"LCTable.h"
#include"Grammar.h"
//LL1分析器类，传入参数是一个预测分析表
class LL1ASY
{
public:
	LL1ASY();
	LL1ASY(LCTable predit_tab);
	bool  LL1ASY::AsyFunc(std::string str);//根据预测分析表分析字符串
	bool GetIdentyString(std::string str);//获得文法的识别符
	~LL1ASY();
protected:
	std::string analysis_stack;//分析栈
	std::string less_stack;//字符串剩余栈
	LCTable predit_table;//预测分析表
};

