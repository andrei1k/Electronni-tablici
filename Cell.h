#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <exception>
#include <vector>
#include <string>

enum CellType {
    INVALID = -1,
    INT,
    DOUBLE,
    STRING,
    VALUTE,
    EMPTY
};

struct Pair {
    
    Pair() : fst(0), snd(0) {}
    Pair(unsigned fst, unsigned snd) : fst(fst), snd(snd) {}
    Pair(const Pair& copy) = default;
    Pair& operator=(const Pair& copy) = default;

    unsigned fst, snd;

};

class Cell {

public:

    Cell() = default;
    Cell(unsigned row, unsigned column, unsigned width, CellType type, std::string value);
    // operatoor=() and copy ctor are by defaut
    CellType getType() const;
    std::string val() const;
    unsigned getWidth() const;
    Pair getPosition() const;
    void changeRow(unsigned row);
    virtual double compareValue() const;

protected:

    Pair position{};
    unsigned width{};
    CellType type{EMPTY};
    std::string value{};

};

CellType typeOfString(const std::string& value);
Cell* createCell(unsigned row, unsigned column, std::string value);
std::string removeWhiteSpaces(const std::string& value);

#endif // !CELL_H
