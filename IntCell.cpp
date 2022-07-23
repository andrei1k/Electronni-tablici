#include "IntCell.h"

IntCell::IntCell(unsigned row, unsigned column, std::string value) : Cell(row, column, value.size(), INT, value)
{	
	this->myValue = stoi(value);
}

int IntCell::getValue() const
{
	return this->myValue;
}

double IntCell::compareValue() const
{
	return this->myValue;
}
