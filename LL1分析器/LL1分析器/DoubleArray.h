#pragma once
#include<vector>
#include<fstream>
/*
	��ά�����࣬�ṩ��ά��������ݽṹ
*/
template <typename Type>
class DoubleArray
{
public:
	DoubleArray();
	DoubleArray(unsigned line, unsigned column);//��ʼ��һ����ø�������ֵ�ķ�ʽ��Ҳ����ͨ��֮���ļ��������Զ���ʼ����С
	Type& LookValue(unsigned line, unsigned column);//�鿴һ����ά�����ֵ������Ĳ���������ֵ
	void DisPlayArray(void);//��ʾ�Ӻ����������̨�����Ϣ
	void InitValueFromFiles(const char* files);//���ļ��ж�����Ϣ
	Type& SetValue(unsigned line, unsigned column);//����һ��λ�õ�ֵ
	~DoubleArray();

protected:
	std::vector<std::vector<Type>> doublearray;
	unsigned line;
	unsigned column;
	 Type failed{ "@@" };
};


template <typename Type>
DoubleArray<Type>::DoubleArray()
{
	;
}


template <typename Type>
DoubleArray<Type>::DoubleArray(unsigned line, unsigned column)
{
	this->line = line;
	this->column = column;
	doublearray.resize(line);
	for (auto &clo : doublearray)
	{
		clo.resize(column);
	}
}


template <typename Type>
void DoubleArray<Type>::InitValueFromFiles(const char* files)
{
	std::ifstream in(files, std::ios::in);
	for (auto i : doublearray)
	{
		for (Type &value : i)
		{
			in >> value;
		}
	}
}


template <typename Type>
Type& DoubleArray<Type>::LookValue(unsigned line, unsigned column)
{
	if (line > this->line||column > this->column)
	{
		return failed;
	}
	if (doublearray[line][column].empty())
	{
		return failed;
	}
	return doublearray[line][column];
}


template <typename Type>
Type& DoubleArray<Type>::SetValue(unsigned line, unsigned column)
{
	return doublearray[line][column];
}


template <typename Type>
void DoubleArray<Type>::DisPlayArray(void)
{
	for (unsigned i = 0; i < line; i++)
	{
		for (unsigned j = 0; j < column; j++)
		{
				std::cout << LookValue(i, j) << "\t";
		}
		std::cout << std::endl;
	}
}


template <typename Type>
DoubleArray<Type>::~DoubleArray()
{
	;
}