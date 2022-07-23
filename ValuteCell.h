#ifndef VALUTECELL_H
#define VALITECELL_H

#include "Cell.h"

class ValuteCell : public Cell {

public:

	ValuteCell() = default;
	ValuteCell(unsigned row, unsigned column, std::string value);

	const std::string getValue() const;
	virtual double compareValue() const;


private:

	static const double euroRatio;
	static const double dollarRatio;
	std::string myValue{};
};

#endif // !VALUTECELL_H
