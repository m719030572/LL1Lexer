#pragma once
#include "DoubleArray.h"
#include<string>
#include<iostream>
//������ֵ�Ķ�ά�����࣬�̳���ͨ��ά�������ͬʱ������ģ��Ϊstring�ṹ����д���뺯������������У��еĹ���
class LCTable :
	public DoubleArray<std::string>
{
public:
	LCTable();
	LCTable(unsigned line, unsigned column);
	void InitValueFromFiles(const char* files);//���ļ��ж���Ԥ�������
	std::string& LookValue(char A, char a);//��д��ֵ����������ͨ��������ս�����ս�����ؽ����
	std::string& SetValue(char A, char a);//��ϴ����ֵ����
	void SetLineName(std::vector<char> str);//�����У��е�����
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

