#pragma once
#include "DoubleArray.h"
#include<string>
#include<iostream>
//带行列值的二维数组类，继承普通二维数组类的同时，具象化模板为string结构，重写输入函数，添加输入行，列的功能
class LCTable :
	public DoubleArray<std::string>
{
public:
	LCTable();
	LCTable(unsigned line, unsigned column);
	void InitValueFromFiles(const char* files);//从文件中读入预测分析表
	std::string& LookValue(char A, char a);//重写找值函数，可以通过传入非终结符和终结符返回结果。
	std::string& SetValue(char A, char a);//冲洗设置值函数
	void SetLineName(std::vector<char> str);//设置行，列的名字
	void SetColumnName(std::vector<char> str);
	void DisPlayArray(void);
	std::vector<char>& ReturnLineName(void);
	std::vector<char>& ReturnColumnName(void);
	char LookIdentifier(void);
	~LCTable();
protected:
	std::vector<char> line_name;
	std::vector<char> column_name;
};

