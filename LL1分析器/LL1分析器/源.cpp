#include<iostream>
#include<fstream>
#include<vector>
#include"LCTable.h"
#include"LL1ASY.h"
#include"Grammar.h"
#include"Display.h"
using namespace std;
int main()
{
	Grammar ll1_grammar("grammar.txt");
	LCTable analysis_table = ll1_grammar.CallAll();
	LL1ASY analysis_body(analysis_table);
	Display(ll1_grammar, analysis_table);
	string identy_str;
	cin >> identy_str;
	analysis_body.AsyFunc(identy_str);
	getchar();
	getchar();
	return 0;
}