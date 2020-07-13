#pragma once
#include<vector>
#include<string>

/*非终结符类
	一个非终结符应该有如下属性：FIRST集，FOLLOW集，能不能推出空
*/
class NonTerminal
{
public:
	NonTerminal(char name);
	char &ReturnName(void);
	int &ReturnCanDeEmpty(void);//返回能否推出空
	std::string&ReturnFirstCol(void);//返回FIRST集
	std::string&ReturnFollowCol(void);//返回FOLLOW集
	int &ReturnFolModified(void);
	~NonTerminal();
protected:
	std::string first_cellection;//存放FIRST集
	std::string follow_cellection;//存放FOLLOW集
	int can_dedue_empty;//存放能否推出空
	int follow_has_modified;
	char name;
};

