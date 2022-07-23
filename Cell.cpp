#include "Cell.h"
#include "IntCell.h"
#include "DoubleCell.h"
#include "StringCell.h"
#include "ValuteCell.h"



Cell::Cell(unsigned row, unsigned column, unsigned width, CellType type, std::string value) : position(row, column), width(width), type(type), value(value) {}

CellType Cell::getType() const
{
	return this->type;
}

std::string Cell::val() const {

	return this->value;
}

unsigned Cell::getWidth() const
{
	return this->width;
}

Pair Cell::getPosition() const
{
	return this->position;
}

double Cell::compareValue() const
{
	return 0.0;
}

void Cell::changeRow(unsigned row)
{
	this->position.fst = row;
}

std::string removeWhiteSpaces(const std::string& value)
{
	std::string newVal;
	bool start = true;
	for (unsigned i = 0; i < value.size(); i++) {
		if ((value[i] == ' ' || value[i] == 9) && start)
			continue;
		else {
			start = false;
			newVal.push_back(value[i]);
		}
	}

	return newVal;
}

CellType typeOfString(const std::string& value)
{
	if (value == "" || value[0] == '\0')
		return EMPTY;

	if (value[0] == '"' && value.back() == '"' && value.size() > 1) {

		bool first = true;
		bool isString = true;
		for (unsigned i = 1; i < value.size() - 1; i++) {
			if (value[i] == '\\') {
				if (first) {
					if (value[i + 1] != '\\' && value[i + 1] != '\'' && value[i + 1] != '\"') {
						isString = false;
						break;
					}
					first = false;
					continue;
				}
				
			}
			first = true;
			if ((value[i] == '\'' || value[i] == '\"') && value[i - 1] != '\\') {
				isString = false;
				break;
			}
		}

		if (isString) {
			return STRING;
		}	
	}

	if (value.find("$") != std::string::npos || value.find("ˆ") != std::string::npos) {

		bool isValute = true;
		if (value.size() < 3)
			return INVALID;
		if (value[1] != ' ' && (value[1] < '0' || value[1] > '9'))
			isValute = false;

		for (unsigned i = 2; i < value.size() - 3; i++) {

			if ((value[i] < '0' || value[i] > '9')) {

				isValute = false;
				break;
			}
		}
		
		if (value[value.size() - 3] != '.')
			isValute = false;
		if ((value[value.size() - 2] < '0' || value[value.size() - 2] > '9') || (value[value.size() - 1] < '0' || value[value.size() - 1] > '9'))
			isValute = false;

		if (isValute)
			return VALUTE;

	}

	if (value.find("lv.") != std::string::npos ) {

		bool isValute = true;
		try {
			double valuteValue = stod(value);
			for (unsigned i = 0; i < value.find("lv.") - 4; i++) {

				if ((value[i] < '0' || value[i] > '9')) {

					isValute = false;
					break;
				}
			}
			if (value.size() != value.find("lv.") + 3)
				isValute = false;
			if (value[value.find("lv.") - 1] != ' ')
				isValute = false;
			if (value[value.find("lv.") - 4] != '.')
				isValute = false;
			if ((value[value.find("lv.") - 3] < '0' || value[value.find("lv.") - 3] > '9') || (value[value.find("lv.") - 2] < '0' || value[value.find("lv.") - 2] > '9'))
				isValute = false;
		}
		catch (...) {

			isValute = false;
			return INVALID;
		}
		

		if (isValute)
			return VALUTE;
	}

	for (unsigned i = 0; i < value.size(); i++) {
		if (value[0] == '+' || value[0] == '-')
			if (i == 0)
				continue;

		if (i + 1 == value.size() && !(value[i] < '0' || value[i] > '9'))
			return INT;

		if (value[i] < '0' || value[i] > '9')
			break;
	}

	bool oneDecimalDot = false;
	for (unsigned i = 0; i < value.size(); i++) {
		if (value[0] == '+' || value[0] == '-')
			if (i == 0)
				continue;

		if (i + 1 == value.size() && !(value[i] < '0' || value[i] > '9'))
			return DOUBLE;

		if ((value[i] < '0' || value[i] > '9')) {
			if (value[i] == '.') {
				if (!oneDecimalDot)
					oneDecimalDot = true;
				else break;
			}
			else break;
		}
	}

	return INVALID;
}


Cell* createCell(unsigned row, unsigned column, std::string value)
{
	value = removeWhiteSpaces(value);

	CellType typeCheck = typeOfString(value);
	//std::cout << value << typeCheck;
	switch (typeCheck)
	{
	case INVALID: throw std::invalid_argument(value);
	case INT: return new IntCell(row, column, value);
	case DOUBLE: return new DoubleCell(row, column, value);
	case STRING: return new StringCell(row, column, value);
	case VALUTE: return new ValuteCell(row, column, value); 
	case EMPTY: return new EmptyCell(row, column);
	default: return nullptr;
	}

}