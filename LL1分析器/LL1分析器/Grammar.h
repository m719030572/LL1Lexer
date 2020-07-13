#pragma once
#include"RegularExpression.h"
#include"NonTerminal.h"
#include<vector>
#include<fstream>
#include<map>
#include <algorithm>
#include"LCTable.h"
#include<iostream>
/*
	文法类，提供文法的功能，可以保存一个文法，并计算FIRST，FOLLOW，SELECT集合，并且生成预测分析表
*/
class Grammar
{
public:
	Grammar(const char * files);//构造函数的参数是一个文件，就是存放文法的文件
	std::vector<RegularExpression<char>*>FindNotTerLeft(char ch);//找到从产生式左侧指定非终结符的所有产生式
	std::vector<RegularExpression<char>*>FindNotTerRight(char ch);//找到从产生式右侧指定非终结符的所有产生式
	void DeleteLeftFunc(void);
	char FindNextCharFromNT(char ch, RegularExpression<char> re);//在求FOLLOW集中使用，返回该非终结符右侧的值
	std::vector<RegularExpression<char>*>FindNotTerLeft(char ch, std::vector<RegularExpression<char>>& regc);
	bool IsTerminal(char ch);//判断一个字符是终结符
	NonTerminal& ReturnNonTerminal(char ch);//返回某个非终结符的数据结构
	void CalNotTerCollection(void);//产生文法的所有非终结符并且保存
	void CalTerCollection(void); //产生文法的所有终结符并且保存
	void CalDedueEmpty(void);//计算所有能推出空的first集，已经废弃
	std::string CalFirstCollection(char ch,std::string str);//递归实现计算一个非终结符的FIRST集
	std::string CalFollowCollection(char ch, std::string str);//递归实现计算一个非终结符的FOLLOW集
	void CalAllFirstCol(void);//总控程序。一次生成所有非终结符的FIRST集和FOLLOW集
	void CalAllFollowCol(void);
	bool ISLL1Grammar(void);
	void CalRegularExpFirstColl(void);//计算一个产生式的FIRST集
	void CalSelectCollection(void);//计算一个产生式的SELECT集
	LCTable CreatePreditTable(Grammar gra);//生成预测分析表
	LCTable CallAll(void);//总控程序。计算从文法输入到预测表的生成，返回预测表
	void Display(void);//输出这些表
	~Grammar();
protected:
	std::vector<RegularExpression<char>> regular_exp_cellection;//存放产生式
	std::vector<NonTerminal>not_terminal_cellection;//存放非终结符，是类类型
	std::vector<char>terminal_cellection;//存放终结符
	char grammar_identifier;//存放文法识别符
};