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
	�ķ��࣬�ṩ�ķ��Ĺ��ܣ����Ա���һ���ķ���������FIRST��FOLLOW��SELECT���ϣ���������Ԥ�������
*/
class Grammar
{
public:
	Grammar(const char * files);//���캯���Ĳ�����һ���ļ������Ǵ���ķ����ļ�
	std::vector<RegularExpression<char>*>FindNotTerLeft(char ch);//�ҵ��Ӳ���ʽ���ָ�����ս�������в���ʽ
	std::vector<RegularExpression<char>*>FindNotTerRight(char ch);//�ҵ��Ӳ���ʽ�Ҳ�ָ�����ս�������в���ʽ
	void DeleteLeftFunc(void);
	char FindNextCharFromNT(char ch, RegularExpression<char> re);//����FOLLOW����ʹ�ã����ظ÷��ս���Ҳ��ֵ
	std::vector<RegularExpression<char>*>FindNotTerLeft(char ch, std::vector<RegularExpression<char>>& regc);
	bool IsTerminal(char ch);//�ж�һ���ַ����ս��
	NonTerminal& ReturnNonTerminal(char ch);//����ĳ�����ս�������ݽṹ
	void CalNotTerCollection(void);//�����ķ������з��ս�����ұ���
	void CalTerCollection(void); //�����ķ��������ս�����ұ���
	void CalDedueEmpty(void);//�����������Ƴ��յ�first�����Ѿ�����
	std::string CalFirstCollection(char ch,std::string str);//�ݹ�ʵ�ּ���һ�����ս����FIRST��
	std::string CalFollowCollection(char ch, std::string str);//�ݹ�ʵ�ּ���һ�����ս����FOLLOW��
	void CalAllFirstCol(void);//�ܿس���һ���������з��ս����FIRST����FOLLOW��
	void CalAllFollowCol(void);
	bool ISLL1Grammar(void);
	void CalRegularExpFirstColl(void);//����һ������ʽ��FIRST��
	void CalSelectCollection(void);//����һ������ʽ��SELECT��
	LCTable CreatePreditTable(Grammar gra);//����Ԥ�������
	LCTable CallAll(void);//�ܿس��򡣼�����ķ����뵽Ԥ�������ɣ�����Ԥ���
	void Display(void);//�����Щ��
	~Grammar();
protected:
	std::vector<RegularExpression<char>> regular_exp_cellection;//��Ų���ʽ
	std::vector<NonTerminal>not_terminal_cellection;//��ŷ��ս������������
	std::vector<char>terminal_cellection;//����ս��
	char grammar_identifier;//����ķ�ʶ���
};