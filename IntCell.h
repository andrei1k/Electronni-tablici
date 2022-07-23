#ifndef INTCELL_H
#define INTCELL_H

#include "Cell.h"


class IntCell : public Cell {

public:

    IntCell() = default;
    IntCell(unsigned row, unsigned column, std::string value);

    int getValue() const;
    virtual double compareValue() const;

private:

    int myValue{};

};

#endif // !INTCELL_H
