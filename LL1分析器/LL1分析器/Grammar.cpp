#include "Grammar.h"



Grammar::Grammar(const char * files)
{
	std::ifstream in(files, std::ios::in);
	RegularExpression<char> temp_exp;
	char temp_ch;
	std::string temp_str;
	while (1)
	{
		temp_ch=in.get();
		if (temp_ch == -1)
			break;
		else if((temp_ch==' ')||(temp_ch=='\t'||(temp_ch=='\n')))
		{
			continue;
		}
		else
		{
			temp_exp.ReturnLeft() = temp_ch;
			in >> temp_exp.ReturnRight();
			regular_exp_cellection.push_back(temp_exp);
		}
	}
}


Grammar::~Grammar()
{
}


void Grammar::DeleteLeftFunc(void)
{
	for (auto vnt : not_terminal_cellection)
	{
		auto result_vec = FindNotTerLeft(vnt.ReturnName());
	}
}


LCTable Grammar::CallAll(void)
{
	CalNotTerCollection();
	CalTerCollection();
	CalAllFirstCol();
	CalAllFollowCol();
	CalRegularExpFirstColl();
	CalSelectCollection();
	if (!ISLL1Grammar())
	{
		std::cout << "���ķ�����LL1�ķ�" << std::endl;
		getchar();
		exit(0);
	}
	else
	{
		std::cout << "���ķ���LL1�ķ�" << std::endl;
	}
	return CreatePreditTable(*this);
}


void Grammar::CalNotTerCollection(void)
{
	int repeat_flag;
	for (auto chp : regular_exp_cellection)
	{
		repeat_flag = 0;
		for (auto i : not_terminal_cellection)
		{
			if (chp.ReturnLeft() == i.ReturnName())
			{
				repeat_flag = 1;
				break;
			}
		}
		if (repeat_flag == 0)
			not_terminal_cellection.push_back(chp.ReturnLeft());
	}
	grammar_identifier = not_terminal_cellection.begin()->ReturnName();
}


void Grammar::CalTerCollection(void)
{
	int repeat_flag;
	for (auto chp : regular_exp_cellection)
	{
		if (chp.ReturnRight() == "$")
			continue;
		for (auto stp : chp.ReturnRight())
		{
			repeat_flag = 0;
			for (auto ni : not_terminal_cellection)
			{
				if (ni.ReturnName() == stp)
				{
					repeat_flag = 1;
					break;
				}
			}
			for (auto i : terminal_cellection)
			{
				if (stp == i)
				{
					repeat_flag = 1;
					break;
				}
			}
			if (repeat_flag == 0)
			{
				terminal_cellection.push_back(stp);
			}
		}
	}

}


void Grammar::CalAllFirstCol(void)
{
	for (auto nop = not_terminal_cellection.begin(); nop != not_terminal_cellection.end(); nop++)
	{
		nop->ReturnFirstCol()=CalFirstCollection(nop->ReturnName(), std::string("$"));
		nop->ReturnFirstCol().erase(unique(nop->ReturnFirstCol().begin(), nop->ReturnFirstCol().end()), nop->ReturnFirstCol().end());
	}
}


std::string Grammar::CalFirstCollection(char ch,std::string str)
{
	//std::string return_str;
	//for (auto chp : str)//�����Լ����Լ�
	//{
	//	if (chp == ch)
	//	{
	//		return return_str;
	//	}
	//}
	//if (IsTerminal(ch))
	//{
	//	return_str += ch;
	//	return return_str;
	//}
	//if (ch == '$')
	//{
	//	return return_str;
	//}
	//auto result_vec = FindNotTerLeft(ch);
	//for(auto i:result_vec)
	//{
	//	if (i->ReturnRight().empty())
	//	{
	//		return return_str;
	//	}
	//	for (auto j : i->ReturnRight())
	//	{
	//		if (IsTerminal(j))
	//		{
	//			return_str += j;
	//			return return_str;
	//		}
	//		else if (ReturnNonTerminal(j).ReturnCanDeEmpty())
	//		{
	//			return_str += CalFirstCollection(j, str + ch);
	//			return_str.erase('$');
	//		}
	//		else
	//		{
	//			return_str += CalFirstCollection(j, str + ch);
	//			return return_str;
	//		}
	//	}
	//}
	//return return_str;

	/*
		�ݹ����һ�����ս����FIRST����ch��Ҫ����FIRST���ķ��ս����str�Ǻ���ִ�е�����ʱ���Ѿ�ִ�й��ķ��ս�������ӡ�$����ʼ��ÿ�εݹ���ã����ѱ��εķ��ս�����뵽str��
		���str�г������ظ������ʾ�������Լ����Լ����������ʱ�����ε���û�����壬ֱ�ӷ��ء������ڵ��õĹ����У�ÿ�ε����ڷ��ص�ͬʱ���Զ��޸ĺø÷��ս����first�������
		�ڵ��ù����г��������������Ӧ��ֱ�ӷ���FIRST���������ܷ��Ƴ��ձ�־�ֵ����޸�λ�����ж��Ƿ��Ѿ����ɹ��ˡ�
		�������£�
		���ÿ�ʼ���Ƚ�����ʽ���Ϊ���ս���Ĳ���ʽ�ҵ���Ȼ�������Щ����ʽ�����һ������ʽΪ�ղ���ʽ���򽫿ա�$������FIRST�У������ܷ��Ƴ��ձ��Ϊ�ǡ�������һ��ѭ��������ͱ�������ʽ�Ҳ���һ��
		�����ս���������ս�������FIRST��������ɨ����һ������ʽ�����򣬳��ַ��ս�����͵�����÷��ս������FIRST���򣬼��÷��ս���ı�־λ�����Ϊ�ǣ��ͽ���ǿ�Ԫ�ط��뱾first��������ɨ�豾
		����ʽ������������˲���ʽβ�����ǽ��ռ���first�����޸ı���־λΪ�ǡ������־Ϊ�񣬾ͽ��ü������first��������������ʽ��ɨ����һ������ʽ��
		������еĲ���ʽ���Ѿ�ɨ����ϣ�����ʱ�ı�־λ��Ϊδ�޸ģ����޸ı�־λΪ�񣬷���FIRST����
	*/

	if (ReturnNonTerminal(ch).ReturnCanDeEmpty() != -1)//֮ǰ�Ѿ���������
	{
		return ReturnNonTerminal(ch).ReturnFirstCol();
	}
	std::string display;
	auto result_vec = FindNotTerLeft(ch);//������ʽ�����ս��Ϊ��ch���Ĳ���ʽ�ҵ�
	for (auto i : result_vec)
	{
		if (i->ReturnRight() == "$")
		{
			ReturnNonTerminal(ch).ReturnFirstCol().push_back('$');
			ReturnNonTerminal(ch).ReturnCanDeEmpty() = true;
			continue;
		}
		for (auto chp : i->ReturnRight())
		{
			if (IsTerminal(chp))//�����ս�����Ͱ������룬������������ʽ�ı���
			{
				ReturnNonTerminal(ch).ReturnFirstCol().push_back(chp);
				break;
			}
			else
			{
				str.push_back(chp);
				std::string result_str = CalFirstCollection(chp, str);
				if (!ReturnNonTerminal(chp).ReturnCanDeEmpty())//������ص�first�������Ƴ��գ���ô��ʱӦ�������Ա�����ʽ��ɨ��
				{
					ReturnNonTerminal(ch).ReturnFirstCol() += result_str;
					break;
				}
				else
				{
					if (chp==*(i->ReturnRight().rbegin()))//������˲���ʽβ
					{
						ReturnNonTerminal(ch).ReturnFirstCol() += result_str;
						ReturnNonTerminal(ch).ReturnCanDeEmpty() = true;
					}
					else
					{
						for (auto chp = result_str.begin(); chp != result_str.end(); chp++)
						{
							if (*chp == '$')
							{
								result_str.erase(chp);
								break;
							}
						}
						ReturnNonTerminal(ch).ReturnFirstCol() += result_str;
					}
				}
			}
		}
	}
	if (ReturnNonTerminal(ch).ReturnCanDeEmpty() == -1)//��������Ϊ��
		ReturnNonTerminal(ch).ReturnCanDeEmpty() = 0;
	std::sort(ReturnNonTerminal(ch).ReturnFirstCol().begin(), ReturnNonTerminal(ch).ReturnFirstCol().end());//ȥ��
	ReturnNonTerminal(ch).ReturnFirstCol().erase(std::unique(ReturnNonTerminal(ch).ReturnFirstCol().begin(), ReturnNonTerminal(ch).ReturnFirstCol().end()), ReturnNonTerminal(ch).ReturnFirstCol().end());
	return ReturnNonTerminal(ch).ReturnFirstCol();
}


void Grammar::CalAllFollowCol(void)
{
	ReturnNonTerminal(grammar_identifier).ReturnFollowCol() += '#';//�ķ�ʶ����������#�����ڸ�follow��
	for (auto nop = not_terminal_cellection.begin(); nop != not_terminal_cellection.end(); nop++)
	{
		nop->ReturnFollowCol() = CalFollowCollection(nop->ReturnName(), std::string("$"));
	}
	
}


std::string Grammar::CalFollowCollection(char ch, std::string str)
{
	/*
		�ݹ����һ�����ս����FOLLOW����ch��Ҫ����FOLLOW���ķ��ս����str�Ǻ���ִ�е�����ʱ���Ѿ�ִ�й��ķ��ս�������ӡ�$����ʼ��ÿ�εݹ���ã����ѱ��εķ��ս�����뵽str��
		���str�г������ظ������ʾ�������Լ����Լ����������ʱ�����ε���û�����壬ֱ�ӷ��ء������ڵ��õĹ����У�ÿ�ε����ڷ��ص�ͬʱ���Զ��޸ĺø÷��ս����FOLLOW�������
		�ڵ��ù����г��������������Ӧ��ֱ�ӷ���FOLLOW����
		�������£�
		���ÿ�ʼ���ж��Ƿ����ķ�ʶ��������ǣ���#���뵽FOLLOW����������ʽ�Ҳ���ڸ��ս���Ĳ���ʽ�ҵ���Ȼ�������Щ����ʽ���ڲ���ʽ���ҵ��÷��ս������һ�����ţ������һ����һ���ս��������һ�������Ƴ��յ�һ�����ս��
		���÷���/���ս����FIRST������FOLLOW��������ɨ����һ������ʽ��������FIRST�ǿ�Ԫ�ز����FOLLOW���������ò���ʽ�����ս����FOLLOW����������ս���ĺ�������ǿյģ�
		��ͬ�����ò���ʽ�����ս����FOLLOW����ȥ���Ժ󷵻�FOLLOW��

	*/
	std::string return_str;
	for (auto chp : str)//�����Լ����Լ�
	{
		if (chp == ch)
		{
			return "$";
		}
	}
	auto result_vec = FindNotTerRight(ch);
	for (auto i : result_vec)//��������������ʽ
	{
		char nextnt = FindNextCharFromNT(ch,*i );
		if (nextnt == '$')//�����Ϊ��
		{
			ReturnNonTerminal(ch).ReturnFollowCol() += CalFollowCollection(i->ReturnLeft(), str+ch);
		}
		else if(IsTerminal(nextnt))//��������ս��
		{
			ReturnNonTerminal(ch).ReturnFollowCol() += nextnt;
		}
		else//�����Ƿ��ս��
		{
			if (ReturnNonTerminal(nextnt).ReturnCanDeEmpty())//�����������Ƴ���
			{
				std::string without_empty = ReturnNonTerminal(nextnt).ReturnFirstCol();
				for (auto chp = without_empty.begin(); chp != without_empty.end(); chp++)
				{
					if (*chp == '$')
					{
						without_empty.erase(chp);
						break;
					}
				}
				ReturnNonTerminal(ch).ReturnFollowCol() += without_empty;//��first�еķǿ�Ԫ������Follow��
				ReturnNonTerminal(ch).ReturnFollowCol() += CalFollowCollection(i->ReturnLeft(), str + ch);//��������ʽ���ķ��ս��follow��Ҳ���ڴ�follow��
			}
			
			
		}
	}
	for (auto chp = ReturnNonTerminal(ch).ReturnFollowCol().begin(); chp != ReturnNonTerminal(ch).ReturnFollowCol().end(); chp++)
	{
		if (*chp == '$')
		{
			ReturnNonTerminal(ch).ReturnFollowCol().erase(chp);
			break;
		}
	}
	std::sort(ReturnNonTerminal(ch).ReturnFollowCol().begin(), ReturnNonTerminal(ch).ReturnFollowCol().end());
	ReturnNonTerminal(ch).ReturnFollowCol().erase(std::unique(ReturnNonTerminal(ch).ReturnFollowCol().begin(), ReturnNonTerminal(ch).ReturnFollowCol().end()), ReturnNonTerminal(ch).ReturnFollowCol().end());
	return ReturnNonTerminal(ch).ReturnFollowCol();
}


bool Grammar::IsTerminal(char ch)
{
	for (auto stp : terminal_cellection)
	{
		if (stp == ch)
			return true;
	}
	return false;
}


NonTerminal& Grammar::ReturnNonTerminal(char ch)
{
	for (auto& tep : not_terminal_cellection)
	{
		if (tep.ReturnName()==ch)
		{
			return tep;
		}
	}
	return *not_terminal_cellection.end();

}


std::vector<RegularExpression<char>*> Grammar::FindNotTerLeft(char ch)
{
	std::vector<RegularExpression<char>*> result_vec;
	for (auto chp = regular_exp_cellection.begin(); chp != regular_exp_cellection.end(); chp++)
	{
		if (ch == chp->ReturnLeft())
			result_vec.push_back(&(*chp));
	}
	return result_vec;
}


std::vector<RegularExpression<char>*> Grammar::FindNotTerRight(char ch)
{
	std::vector<RegularExpression<char>*> result_vec;
	for (auto chp = regular_exp_cellection.begin(); chp != regular_exp_cellection.end(); chp++)
	{
		for (auto stp = chp->ReturnRight().begin(); stp != chp->ReturnRight().end(); stp++)
		{
			if (ch == *stp)
			{
				result_vec.push_back(&(*chp));
				break;
			}
		}
	}
	return result_vec;
}


std::vector<RegularExpression<char>*>Grammar::FindNotTerLeft(char ch, std::vector<RegularExpression<char>> &regc)
{
	std::vector<RegularExpression<char>*> result_vec;
	for (auto chp = regc.begin(); chp != regc.end(); chp++)
	{
		if (ch == chp->ReturnLeft())
			result_vec.push_back(&(*chp));
	}
	return result_vec;
}


void Grammar::CalRegularExpFirstColl(void)
{
	for (auto &rep : regular_exp_cellection)
	{
		if (*rep.ReturnRight().begin()=='$')//���ֻ�Ƴ���
		{
			rep.ReturnFirstCol() = '$';
			rep.ReturnCanDeEmpty() = true;
			continue;
		}
		for (auto stp : rep.ReturnRight())//�����Ҳ�
		{
			
			if (IsTerminal(stp))//�����һ���ս��
			{
				rep.ReturnFirstCol() += stp;
				rep.ReturnCanDeEmpty() = false;
				break;
			}
			else if (ReturnNonTerminal(stp).ReturnCanDeEmpty())//����Ǹ��ս�������Ƴ���
			{
				std::string without_empty = ReturnNonTerminal(stp).ReturnFirstCol();//
				for (auto chp = without_empty.begin(); chp != without_empty.end(); chp++)
				{
					if (*chp == '$')
					{
						without_empty.erase(chp);
						break;
					}
				}
				rep.ReturnFirstCol()+= without_empty;//����ǿ�Ԫ�ز���first
			}
			else//�����Ƴ���
			{
				rep.ReturnFirstCol() += ReturnNonTerminal(stp).ReturnFirstCol();//����firstԪ�ز���first
				rep.ReturnCanDeEmpty() = false;
				break;
			}
		}
		
		if (rep.ReturnCanDeEmpty() == -1)
		{
			rep.ReturnFirstCol() += '$';
			rep.ReturnCanDeEmpty() = true;
		}
		std::sort(rep.ReturnFirstCol().begin(), rep.ReturnFirstCol().end());
		rep.ReturnFirstCol().erase(std::unique(rep.ReturnFirstCol().begin(), rep.ReturnFirstCol().end()), rep.ReturnFirstCol().end());
	}
	
}


void Grammar::CalSelectCollection()
{

	for (auto &rep : regular_exp_cellection)
	{
		if (!rep.ReturnCanDeEmpty())//�������ʽ�����Ƴ���
		{
			rep.ReturnSelectCol() = rep.ReturnFirstCol();//��ôselect��������first��
			continue;
		}
		else//��Ȼ
		{
			std::string without_empty = rep.ReturnFirstCol();
			for (auto chp = without_empty.begin(); chp != without_empty.end(); chp++)
			{
				if (*chp == '$')
				{
					without_empty.erase(chp);
					break;
				}
			}
			rep.ReturnSelectCol() = without_empty + ReturnNonTerminal(rep.ReturnLeft()).ReturnFollowCol();
			std::sort(rep.ReturnSelectCol().begin(), rep.ReturnSelectCol().end());
			rep.ReturnSelectCol().erase(std::unique(rep.ReturnSelectCol().begin(), rep.ReturnSelectCol().end()), rep.ReturnSelectCol().end());//ɾ���ظ�Ԫ��
		}
	}
}


char Grammar::FindNextCharFromNT(char ch, RegularExpression<char> re)
{
	for (auto chp=re.ReturnRight().begin(); chp != re.ReturnRight().end();chp++)
	{
		if (ch==*chp)
		{
			auto end = --re.ReturnRight().end();
			if (chp == end)
			{
				return '$';
			}
			else
			{
				return *(++chp);
			}
		}
	}
	return '`';
}


LCTable Grammar::CreatePreditTable(Grammar gra)
{
	LCTable predit_table(not_terminal_cellection.size(), terminal_cellection.size()+1);
	for (auto vnp : not_terminal_cellection)
	{
		predit_table.ReturnColumnName().push_back(vnp.ReturnName());
	}
	for (auto vtp : terminal_cellection)
	{
		predit_table.ReturnLineName().push_back(vtp);
	}
	predit_table.ReturnLineName().push_back('#');
	for (auto i : predit_table.ReturnColumnName())
	{
		for (auto j : predit_table.ReturnLineName())
		{
			predit_table.SetValue(i, j) = "\0";
		}
	}
	for (auto rep : regular_exp_cellection)
	{
		for (auto chp : rep.ReturnSelectCol())
		{
			predit_table.SetValue(rep.ReturnLeft(), chp) = rep.ReturnRight();
		}
	}
	return predit_table;
}


bool Grammar::ISLL1Grammar(void)
{
	std::string right_exp;
	for (auto ntp : not_terminal_cellection)
	{
		auto result_vec = FindNotTerLeft(ntp.ReturnName());//������ʽ�����ս��Ϊ��ch���Ĳ���ʽ�ҵ�
		if (result_vec.size() < 2)
		{
			continue;
		}
		else
		{
			for (auto stp : result_vec)
			{
				right_exp += stp->ReturnRight();
			}
			if (std::unique(right_exp.begin(),right_exp.end())!=right_exp.end())
			{
				return 0;
			}
		}
	}
	return 1;
}


void Grammar::CalDedueEmpty()
{
	std::vector<RegularExpression<char>> cop_regular_exp_cel(regular_exp_cellection);
	//����һ
	for (auto chp = not_terminal_cellection.begin(); chp != not_terminal_cellection.end(); chp++)
	{
		auto result_vec = FindNotTerLeft(chp->ReturnName(),cop_regular_exp_cel);
		int allisempty=1;
		for (auto rep : result_vec)
		{
			auto first = rep->ReturnRight().begin();
			auto end = rep->ReturnRight().end();
			for (auto chp=rep->ReturnRight().begin();chp!=end;chp++)//Ԥ�������ⲽ������ʹ�ÿձ�ɾ��
			{
				if (IsTerminal(*chp))
				{
					rep->ReturnRight().erase(chp);
					first = rep->ReturnRight().begin();
					end = rep->ReturnRight().end();
					chp = first;
				}
			}
			if (!rep->ReturnRight().empty())//����в��ǿյĵĲ���ʽ
			{
				allisempty = 0;
				break;
			}
			if (rep->ReturnRight()==std::string("$"))
			{
				chp->ReturnCanDeEmpty() = true;
				break;
			}
		}
		if (allisempty)
		{
			chp->ReturnCanDeEmpty() = false;
		}
	}
	while (1)
	{
		int all_has_modified = 1;
		for (auto chp = not_terminal_cellection.begin(); chp != not_terminal_cellection.end(); chp++)
		{
			if (chp->ReturnCanDeEmpty() == -1)
				all_has_modified = 0;
		}
		if (all_has_modified)
		{
			break;
		}
		for (auto rep = cop_regular_exp_cel.begin(); rep != cop_regular_exp_cel.end(); rep++)
		{
			auto first = rep->ReturnRight().begin();
			auto end = rep->ReturnRight().end();
			for (auto chp = rep->ReturnRight().begin(); chp != end; chp++)
			{
				if (ReturnNonTerminal(rep->ReturnLeft()).ReturnCanDeEmpty() != -1)
				{
					break;
				}
				if (ReturnNonTerminal(*chp).ReturnCanDeEmpty())//�����־Ϊ��
				{
					rep->ReturnRight().erase(chp);//ɾȥ�÷��ս��
					first = rep->ReturnRight().begin();
					end = rep->ReturnRight().end();
					chp = first;
				}
			}
			if (rep->ReturnRight().empty())//����⵼����������ʽΪ��
			{
				ReturnNonTerminal(rep->ReturnLeft()).ReturnCanDeEmpty() = true;
				continue;
			}
			for (auto chp = rep->ReturnRight().begin(); chp != end; chp++)
			{
				if (ReturnNonTerminal(rep->ReturnLeft()).ReturnCanDeEmpty() != -1)
				{
					break;
				}
				if (!ReturnNonTerminal(*chp).ReturnCanDeEmpty())//�����־Ϊ��
				{
					rep->ReturnRight().erase(chp);//ɾȥ�÷��ս��
					first = rep->ReturnRight().begin();
					end = rep->ReturnRight().end();
					chp = first;
				}
			}
			if (rep->ReturnRight().empty())//����⵼����������ʽΪ��
			{
				ReturnNonTerminal(rep->ReturnLeft()).ReturnCanDeEmpty() = false;
			}
		}
	}
}


void Grammar::Display(void)
{
	std::cout << "\n\n����ʽ��������" << std::endl;
	for (auto exp : regular_exp_cellection)
	{
		std::cout << exp.ReturnLeft() << "->" << exp.ReturnRight() << std::endl;
	}
	std::cout << "\n\nFIRST����FOLLOW����ʾ����" << std::endl;
	std::cout << "Vn\t\tFIRST\t\tFOLLOW\t\t" << std::endl;
	for (auto vnp : not_terminal_cellection)
	{
		std::cout << vnp.ReturnName() << "\t\t" << vnp.ReturnFirstCol() << "\t\t" << vnp.ReturnFollowCol() << std::endl;
	}
	std::cout << "\n\nSELECT����������" << std::endl;
	for (auto exp : regular_exp_cellection)
	{
		std::cout << "SELECT("<<exp.ReturnLeft() << "->" << exp.ReturnRight() <<")\t=\t"<<exp.ReturnSelectCol()<< std::endl;
	}
}