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
		std::cout << "该文法不是LL1文法" << std::endl;
		getchar();
		exit(0);
	}
	else
	{
		std::cout << "该文法是LL1文法" << std::endl;
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
	//for (auto chp : str)//出现自己并自己
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
		递归计算一个非终结符的FIRST集，ch是要计算FIRST集的非终结符，str是函数执行到本次时，已经执行过的非终结符串，从‘$’开始，每次递归调用，都把本次的非终结符加入到str中
		如果str中出现了重复，则表示出现了自己并自己的情况，此时，本次调用没有意义，直接返回。另外在调用的过程中，每次调用在返回的同时，自动修改好该非终结符的first集，如果
		在调用过程中出现了上述情况，应该直接返回FIRST集。这里能否推出空标志又当做修改位，来判定是否已经生成过了。
		正文如下：
		调用开始后，先将产生式左侧为该终结符的产生式找到，然后遍历这些产生式，如果一个产生式为空产生式，则将空‘$’放入FIRST中，将其能否推出空标记为是。继续下一个循环，否则就遍历产生式右部，一旦
		出现终结符，将该终结符并入次FIRST集，继续扫描下一个产生式。否则，出现非终结符，就调用求该非终结符的求FIRST程序，检测该非终结符的标志位，如果为是，就将其非空元素放入本first集，继续扫描本
		产生式，但是如果到了产生式尾，还是将空加入first集，修改本标志位为是。如果标志为否，就将该集并入此first集，跳出本产生式，扫描下一个产生式。
		如果所有的产生式都已经扫描完毕，但此时的标志位还为未修改，则修改标志位为否，返回FIRST集。
	*/

	if (ReturnNonTerminal(ch).ReturnCanDeEmpty() != -1)//之前已经遍历过了
	{
		return ReturnNonTerminal(ch).ReturnFirstCol();
	}
	std::string display;
	auto result_vec = FindNotTerLeft(ch);//将产生式左侧非终结符为‘ch’的产生式找到
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
			if (IsTerminal(chp))//若是终结符，就把他加入，跳出本个产生式的遍历
			{
				ReturnNonTerminal(ch).ReturnFirstCol().push_back(chp);
				break;
			}
			else
			{
				str.push_back(chp);
				std::string result_str = CalFirstCollection(chp, str);
				if (!ReturnNonTerminal(chp).ReturnCanDeEmpty())//如果返回的first集不能推出空，那么此时应该跳出对本产生式的扫描
				{
					ReturnNonTerminal(ch).ReturnFirstCol() += result_str;
					break;
				}
				else
				{
					if (chp==*(i->ReturnRight().rbegin()))//如果到了产生式尾
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
	if (ReturnNonTerminal(ch).ReturnCanDeEmpty() == -1)//将其设置为否
		ReturnNonTerminal(ch).ReturnCanDeEmpty() = 0;
	std::sort(ReturnNonTerminal(ch).ReturnFirstCol().begin(), ReturnNonTerminal(ch).ReturnFirstCol().end());//去重
	ReturnNonTerminal(ch).ReturnFirstCol().erase(std::unique(ReturnNonTerminal(ch).ReturnFirstCol().begin(), ReturnNonTerminal(ch).ReturnFirstCol().end()), ReturnNonTerminal(ch).ReturnFirstCol().end());
	return ReturnNonTerminal(ch).ReturnFirstCol();
}


void Grammar::CalAllFollowCol(void)
{
	ReturnNonTerminal(grammar_identifier).ReturnFollowCol() += '#';//文法识别器符，‘#’属于该follow集
	for (auto nop = not_terminal_cellection.begin(); nop != not_terminal_cellection.end(); nop++)
	{
		nop->ReturnFollowCol() = CalFollowCollection(nop->ReturnName(), std::string("$"));
	}
	
}


std::string Grammar::CalFollowCollection(char ch, std::string str)
{
	/*
		递归计算一个非终结符的FOLLOW集，ch是要计算FOLLOW集的非终结符，str是函数执行到本次时，已经执行过的非终结符串，从‘$’开始，每次递归调用，都把本次的非终结符加入到str中
		如果str中出现了重复，则表示出现了自己并自己的情况，此时，本次调用没有意义，直接返回。另外在调用的过程中，每次调用在返回的同时，自动修改好该非终结符的FOLLOW集，如果
		在调用过程中出现了上述情况，应该直接返回FOLLOW集。
		正文如下：
		调用开始后，判断是否是文法识别符，若是，将#加入到FOLLOW集。将产生式右侧存在该终结符的产生式找到，然后遍历这些产生式，在产生式中找到该非终结符的下一个符号，如果下一个是一个终结符或者是一个不能推出空的一个非终结符
		将该符号/非终结符的FIRST集并入FOLLOW集，继续扫描下一个产生式。否则将其FIRST非空元素并入此FOLLOW集，并调用产生式左侧非终结符的FOLLOW程序。如果该终结符的后跟符号是空的，
		则同样调用产生式左侧非终结符的FOLLOW程序，去重以后返回FOLLOW集

	*/
	std::string return_str;
	for (auto chp : str)//出现自己并自己
	{
		if (chp == ch)
		{
			return "$";
		}
	}
	auto result_vec = FindNotTerRight(ch);
	for (auto i : result_vec)//遍历整个结果表达式
	{
		char nextnt = FindNextCharFromNT(ch,*i );
		if (nextnt == '$')//后面的为空
		{
			ReturnNonTerminal(ch).ReturnFollowCol() += CalFollowCollection(i->ReturnLeft(), str+ch);
		}
		else if(IsTerminal(nextnt))//后面的是终结符
		{
			ReturnNonTerminal(ch).ReturnFollowCol() += nextnt;
		}
		else//后面是非终结符
		{
			if (ReturnNonTerminal(nextnt).ReturnCanDeEmpty())//如果后面的能推出空
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
				ReturnNonTerminal(ch).ReturnFollowCol() += without_empty;//其first中的非空元素属于Follow集
				ReturnNonTerminal(ch).ReturnFollowCol() += CalFollowCollection(i->ReturnLeft(), str + ch);//则其正规式左侧的非终结符follow集也属于此follow集
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
		if (*rep.ReturnRight().begin()=='$')//如果只推出空
		{
			rep.ReturnFirstCol() = '$';
			rep.ReturnCanDeEmpty() = true;
			continue;
		}
		for (auto stp : rep.ReturnRight())//遍历右侧
		{
			
			if (IsTerminal(stp))//如果是一个终结符
			{
				rep.ReturnFirstCol() += stp;
				rep.ReturnCanDeEmpty() = false;
				break;
			}
			else if (ReturnNonTerminal(stp).ReturnCanDeEmpty())//如果是个终结符且能推出空
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
				rep.ReturnFirstCol()+= without_empty;//将其非空元素并入first
			}
			else//不能推出空
			{
				rep.ReturnFirstCol() += ReturnNonTerminal(stp).ReturnFirstCol();//将其first元素并入first
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
		if (!rep.ReturnCanDeEmpty())//如果产生式不能推出空
		{
			rep.ReturnSelectCol() = rep.ReturnFirstCol();//那么select集就是其first集
			continue;
		}
		else//不然
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
			rep.ReturnSelectCol().erase(std::unique(rep.ReturnSelectCol().begin(), rep.ReturnSelectCol().end()), rep.ReturnSelectCol().end());//删除重复元素
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
		auto result_vec = FindNotTerLeft(ntp.ReturnName());//将产生式左侧非终结符为‘ch’的产生式找到
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
	//步骤一
	for (auto chp = not_terminal_cellection.begin(); chp != not_terminal_cellection.end(); chp++)
	{
		auto result_vec = FindNotTerLeft(chp->ReturnName(),cop_regular_exp_cel);
		int allisempty=1;
		for (auto rep : result_vec)
		{
			auto first = rep->ReturnRight().begin();
			auto end = rep->ReturnRight().end();
			for (auto chp=rep->ReturnRight().begin();chp!=end;chp++)//预留错误：这步操作会使得空被删除
			{
				if (IsTerminal(*chp))
				{
					rep->ReturnRight().erase(chp);
					first = rep->ReturnRight().begin();
					end = rep->ReturnRight().end();
					chp = first;
				}
			}
			if (!rep->ReturnRight().empty())//如果有不是空的的产生式
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
				if (ReturnNonTerminal(*chp).ReturnCanDeEmpty())//如果标志为是
				{
					rep->ReturnRight().erase(chp);//删去该非终结符
					first = rep->ReturnRight().begin();
					end = rep->ReturnRight().end();
					chp = first;
				}
			}
			if (rep->ReturnRight().empty())//如果这导致整个产生式为空
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
				if (!ReturnNonTerminal(*chp).ReturnCanDeEmpty())//如果标志为否
				{
					rep->ReturnRight().erase(chp);//删去该非终结符
					first = rep->ReturnRight().begin();
					end = rep->ReturnRight().end();
					chp = first;
				}
			}
			if (rep->ReturnRight().empty())//如果这导致整个产生式为空
			{
				ReturnNonTerminal(rep->ReturnLeft()).ReturnCanDeEmpty() = false;
			}
		}
	}
}


void Grammar::Display(void)
{
	std::cout << "\n\n正规式表述如下" << std::endl;
	for (auto exp : regular_exp_cellection)
	{
		std::cout << exp.ReturnLeft() << "->" << exp.ReturnRight() << std::endl;
	}
	std::cout << "\n\nFIRST集和FOLLOW集表示如下" << std::endl;
	std::cout << "Vn\t\tFIRST\t\tFOLLOW\t\t" << std::endl;
	for (auto vnp : not_terminal_cellection)
	{
		std::cout << vnp.ReturnName() << "\t\t" << vnp.ReturnFirstCol() << "\t\t" << vnp.ReturnFollowCol() << std::endl;
	}
	std::cout << "\n\nSELECT集表述如下" << std::endl;
	for (auto exp : regular_exp_cellection)
	{
		std::cout << "SELECT("<<exp.ReturnLeft() << "->" << exp.ReturnRight() <<")\t=\t"<<exp.ReturnSelectCol()<< std::endl;
	}
}