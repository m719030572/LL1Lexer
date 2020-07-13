#include "NonTerminal.h"



NonTerminal::NonTerminal(char name)
{
	this->name = name;
	can_dedue_empty = -1;
	follow_has_modified = -1;
}


NonTerminal::~NonTerminal()
{
}


char &NonTerminal::ReturnName(void)
{
	return name;
}


int &NonTerminal::ReturnCanDeEmpty(void)
{
	return can_dedue_empty;
}


std::string & NonTerminal::ReturnFirstCol(void)
{
	return first_cellection;
}


std::string & NonTerminal::ReturnFollowCol(void)
{
	return follow_cellection;
}


int &NonTerminal::ReturnFolModified(void)
{
	return follow_has_modified;
}