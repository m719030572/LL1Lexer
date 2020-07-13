#pragma once
#include<string>

//正规式类
/*
	一个正规式应该具有如下属性 一个正规式的FIRST集，能否推出空，和SELECT集
*/
template<typename Type>
class RegularExpression
{
public:
	RegularExpression(void);
	RegularExpression(Type left, std::string right);//传入参数是一个正规式的左侧和右侧，这里可以输入0-3型文法
	int &ReturnCanDeEmpty(void);//返回能否推出空
	Type& ReturnLeft(void);//返回正规式左侧
	std::string& ReturnRight(void);//返回正规式右侧
	std::string& ReturnFirstCol(void);//返回一个正规式的FIRST集
	std::string& ReturnSelectCol(void);//返回一个正规式的SELECT集
	~RegularExpression();
protected:
	Type left;//保存产生式左侧的值
	std::string right;//保存产生式右侧的值
	std::string first_collection;//保存FIRST集
	std::string select_collection;//保存SELECT集
	int can_dedue_empty;//能否推出空
};


template<typename Type>
RegularExpression<Type>::RegularExpression(void)
{
	;
}


template<typename Type>
RegularExpression<Type>::RegularExpression(Type left, std::string right)
{
	this->left = left;
	this->right = right;
}


template<typename Type>
RegularExpression<Type>::~RegularExpression()
{

}


template<typename Type>
Type& RegularExpression<Type>::ReturnLeft(void)
{
	return left;
}


template<typename Type>
std::string& RegularExpression<Type>::ReturnRight(void)
{
	return right;
}


template<typename Type>
int &RegularExpression<Type>::ReturnCanDeEmpty(void)
{
	return can_dedue_empty;
}


template<typename Type>
std::string& RegularExpression<Type>::ReturnSelectCol(void)
{
	return select_collection;
}


template<typename Type>
std::string& RegularExpression<Type>::ReturnFirstCol(void)
{
	return first_collection;
}