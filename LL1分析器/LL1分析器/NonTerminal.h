#pragma once
#include<vector>
#include<string>

/*���ս����
	һ�����ս��Ӧ�����������ԣ�FIRST����FOLLOW�����ܲ����Ƴ���
*/
class NonTerminal
{
public:
	NonTerminal(char name);
	char &ReturnName(void);
	int &ReturnCanDeEmpty(void);//�����ܷ��Ƴ���
	std::string&ReturnFirstCol(void);//����FIRST��
	std::string&ReturnFollowCol(void);//����FOLLOW��
	int &ReturnFolModified(void);
	~NonTerminal();
protected:
	std::string first_cellection;//���FIRST��
	std::string follow_cellection;//���FOLLOW��
	int can_dedue_empty;//����ܷ��Ƴ���
	int follow_has_modified;
	char name;
};

