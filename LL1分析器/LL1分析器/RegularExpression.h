#pragma once
#include<string>

//����ʽ��
/*
	һ������ʽӦ�þ����������� һ������ʽ��FIRST�����ܷ��Ƴ��գ���SELECT��
*/
template<typename Type>
class RegularExpression
{
public:
	RegularExpression(void);
	RegularExpression(Type left, std::string right);//���������һ������ʽ�������Ҳ࣬�����������0-3���ķ�
	int &ReturnCanDeEmpty(void);//�����ܷ��Ƴ���
	Type& ReturnLeft(void);//��������ʽ���
	std::string& ReturnRight(void);//��������ʽ�Ҳ�
	std::string& ReturnFirstCol(void);//����һ������ʽ��FIRST��
	std::string& ReturnSelectCol(void);//����һ������ʽ��SELECT��
	~RegularExpression();
protected:
	Type left;//�������ʽ����ֵ
	std::string right;//�������ʽ�Ҳ��ֵ
	std::string first_collection;//����FIRST��
	std::string select_collection;//����SELECT��
	int can_dedue_empty;//�ܷ��Ƴ���
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