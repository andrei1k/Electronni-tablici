#include "ValuteCell.h"

const double ValuteCell::euroRatio = 1.96;
const double ValuteCell::dollarRatio = 1.95;

ValuteCell::ValuteCell(unsigned row, unsigned column, std::string value) : Cell(row, column, value.size(), VALUTE, value)
{
	this->myValue = value;
}

const std::string ValuteCell::getValue() const
{
	return this->myValue;
}

double ValuteCell::compareValue() const
{
	std::string money = this->getValue();

	if (money[0] == '$') {
		return stod(money.erase(0, 1)) * ValuteCell::dollarRatio;
	}
	if (money[0] == 'ˆ') {
		return stod(money.erase(0, 1)) * ValuteCell::euroRatio;
	}

	return stod(money);
}
