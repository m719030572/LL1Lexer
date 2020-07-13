#include "LL1ASY.h"



LL1ASY::LL1ASY()
{
}


LL1ASY::LL1ASY(LCTable predit_tab)
	:predit_table(predit_tab)
{
}


bool LL1ASY::GetIdentyString(std::string str)
{
	less_stack.push_back('#');
	for (auto stp = str.rbegin(); stp != str.rend(); stp++)
	{
		less_stack.push_back(*stp);
	}
	return 0;
}





bool  LL1ASY::AsyFunc(std::string strs)
{
	std::string str{ strs };
	analysis_stack.push_back('#');
	analysis_stack.push_back(predit_table.LookIdentifier());//文法识别符入分析栈
	GetIdentyString(str);
	std::string low_less_stack;
	int count = 0;
	std::cout << "\n\n分析过程如下" << std::endl;
	std::cout << "步骤数" << "\t" << "分析栈" << "\t\t" << "剩余栈" << "\t\t状态" << std::endl;
	while (1)
	{
		char analysis_ch;
		char less_ch;
		std::string result_string;
		analysis_ch = *analysis_stack.rbegin();
		less_ch = *less_stack.rbegin();
		if (analysis_ch==less_ch)
		{
			if (analysis_ch == '#')
			{
				count++;
				low_less_stack = less_stack;
				std::reverse(low_less_stack.begin(), low_less_stack.end());
				std::cout<<count<<"\t"<<analysis_stack<<"\t\t"<< low_less_stack <<"\t\t识别" << std::endl;
				break;
			}
			
			count++;
			low_less_stack = less_stack;
			low_less_stack.reserve();
			low_less_stack = less_stack;
			std::reverse(low_less_stack.begin(), low_less_stack.end());
			std::cout << count << "\t" << analysis_stack << "\t\t" << low_less_stack<< "\t\t"<< analysis_ch <<"匹配" << std::endl;
			analysis_stack.pop_back();
			less_stack.pop_back();
			continue;
		}
		result_string = predit_table.LookValue(analysis_ch, less_ch);
		if (result_string==std::string("@@"))
		{
			count++;
			low_less_stack = less_stack;
			std::reverse(low_less_stack.begin(), low_less_stack.end());
			std::cout << count << "\t" << analysis_stack << "\t\t" << low_less_stack << "\t\t不匹配" << std::endl;
			return 0;
		}
		if (*result_string.begin() == '$')
		{
			
			count++;
			low_less_stack = less_stack;
			std::reverse(low_less_stack.begin(), low_less_stack.end());
			std::cout << count << "\t" << analysis_stack << "\t\t" << low_less_stack << "\t\t使用"<<analysis_ch << "->$" << std::endl;
			analysis_stack.pop_back();
			continue;
		}
		count++;
		low_less_stack = less_stack;
		std::reverse(low_less_stack.begin(), low_less_stack.end());
		std::cout << count << "\t" << analysis_stack << "\t\t" << low_less_stack << "\t\t使用" << analysis_ch << "->" << result_string << std::endl;
		analysis_stack.pop_back();
		for (auto stp = result_string.rbegin(); stp != result_string.rend(); stp++)
		{
			analysis_stack.push_back(*stp);
		}
	}
	return 0;
}


LL1ASY::~LL1ASY()
{
}
