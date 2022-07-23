#include "DoubleCell.h"

DoubleCell::DoubleCell(unsigned row, unsigned column, std::string value) : Cell(row, column, value.size(), DOUBLE, value)
{
	this->myValue = stod(value);
}

double DoubleCell::getValue() const
{
	return this->myValue;
}

double DoubleCell::compareValue() const
{
	return this->getValue();
}
