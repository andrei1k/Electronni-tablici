#include "StringCell.h"

StringCell::StringCell(unsigned row, unsigned column, std::string value) : Cell(row, column, value.size(), STRING, value)
{
	this->myValue = value;

	

	bool first = true;
	for (unsigned i = 0; i < this->myValue.size(); i++) {
		if (this->myValue[i] == '\\') {
			if (first) {
				
				this->myValue.erase(i, 1);
			}
			first = false;
			continue;
		}
		first = true;

	}
	this->myValue.erase(0, 1);
	this->myValue.pop_back();

	this->width = this->myValue.size();

}

const std::string StringCell::getValue() const
{
	return this->myValue;
}

double StringCell::compareValue() const
{
	if (typeOfString(this->getValue()) == INT) {
		return stoi(this->getValue());
	}
	else if (typeOfString(this->getValue()) == DOUBLE) {
		return stod(this->getValue());
	}
	else
		return 0;
}

const std::string EmptyCell::getValue() const
{
	return this->myValue;
}

double EmptyCell::compareValue() const
{
	return 0.0;
}
