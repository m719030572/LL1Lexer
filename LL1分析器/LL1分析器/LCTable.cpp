#include "LCTable.h"



LCTable::LCTable()
{
	;
}


LCTable::LCTable(unsigned line, unsigned column)
	:DoubleArray(line, column)
{
	;
}


void LCTable::InitValueFromFiles(const char* files)
{
	std::ifstream in(files, std::ios::in);
	char temp_ch;
	while (1)//先读取第一行的列名
	{
		int li_count = 0;
		in.get(temp_ch);
		if (temp_ch == '\n')
			break;
		if ((temp_ch == ' ')|| (temp_ch == '\t'))
			continue;
		else
		{
			line_name.push_back(temp_ch);
			continue;
		}
	}
	for (auto& i : doublearray)
	{
		in >> temp_ch;
		std::string str;
		if (temp_ch == ' ')
			continue;
		else
		{
			column_name.push_back(temp_ch);
			for (auto& value : i)
			{
				in >> str;
				value = str;

			}

		}
	}
}


void LCTable::SetLineName(std::vector<char> str)
{
	line_name = str;
}


void LCTable::SetColumnName(std::vector<char> str)
{
	column_name = str;
}


std::vector<char>& LCTable::ReturnLineName(void)
{
	return line_name;
}


std::vector<char>& LCTable::ReturnColumnName(void)
{
	return column_name;
}


std::string& LCTable::LookValue(char A, char a)
{
	unsigned line, column;
	for (line = 0; line < this->line; line++)
	{
		if (a == line_name[line])
			break;
	}
	for (column = 0; column < this->column; column++)
	{
		if (A == column_name[column])
			break;
	}
	if (line>this->line||column==this->column)
	{
		return failed;
	}
	return DoubleArray<std::string>::LookValue(column, line);
}


std::string& LCTable::SetValue(char A, char a)
{
	unsigned line, column;
	for (line = 0; line < this->line; line++)
	{
		if (a == line_name[line])
			break;
	}
	for (column = 0; column < this->column; column++)
	{
		if (A == column_name[column])
			break;
	}
	return DoubleArray<std::string>::SetValue(column, line);
}


char LCTable::LookIdentifier(void)
{
	return column_name[0];

}


void LCTable::DisPlayArray(void)
{
	std::cout << "\n\n预测表如下" << std::endl;
	for (auto i : line_name)
	{
		std::cout <<"\t"<< i;
	}
	std::cout << std::endl;
	for (unsigned i = 0; i < line; i++)
	{
		std::cout << column_name[i] << "\t";
		for (unsigned j = 0; j < column; j++)
		{
			std::cout << doublearray[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}


LCTable::~LCTable()
{
}
