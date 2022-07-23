#ifndef DOUBLECELL_H
#define DOUBLECELL_H

#include "Cell.h"

class DoubleCell : public Cell {

public:

    DoubleCell() = default;
    DoubleCell(unsigned row, unsigned column, std::string value);

    double getValue() const;
    virtual double compareValue() const;

    //DoubleCell() = default;
    //DoubleCell(unsigned row, unsigned column, unsigned width, double value) : Cell(row, column, width, DOUBLE), value(value) {};

    //void print() const override {

    //    std::cout << this->value << '|';
    //}

    //std::ostream& write(std::ostream& outFile) const override {

    //    outFile << this->value << ',';

    //    return outFile;

    //}


private:

    double myValue{};

};

#endif // !DOUBLECELL_H
