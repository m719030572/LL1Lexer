#pragma once
#include<vector>
#include<fstream>
/*
	二维数组类，提供二维数组的数据结构
*/
template <typename Type>
class DoubleArray
{
public:
	DoubleArray();
	DoubleArray(unsigned line, unsigned column);//初始化一般采用给出行列值的方式，也可以通过之后文件的输入自动初始化大小
	Type& LookValue(unsigned line, unsigned column);//查看一个二维数组的值，这里的参数是行列值
	void DisPlayArray(void);//显示子函数，向控制台输出信息
	void InitValueFromFiles(const char* files);//从文件中读入信息
	Type& SetValue(unsigned line, unsigned column);//设置一个位置的值
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