#include"Display.h"
using namespace std;
void Display(Grammar gra, LCTable lcb)
{
	gra.Display();
	lcb.DisPlayArray();
	cout << "请输入要识别的字符串" << endl;

}