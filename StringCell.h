#ifndef STRINGCELL_H
#define STRINGCELL_H

#include "Cell.h"

class StringCell : public Cell {

public:

	StringCell() = default;
	StringCell(unsigned row, unsigned column, std::string value);

	const std::string getValue() const;
	virtual double compareValue() const;

private:

	std::string myValue{};

};

class EmptyCell : public Cell {

public:

	EmptyCell() = default;
	EmptyCell(unsigned row, unsigned column) : Cell(row, column, 0, EMPTY, ""), myValue("") {}
	const std::string getValue() const;


private:

	const std::string myValue = "";
	virtual double compareValue() const;

};


#endif // !STRINGCELL_H