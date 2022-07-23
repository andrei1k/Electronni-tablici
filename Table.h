#ifndef TABLE_H
#define TABLE_H

#include <exception>
#include <fstream>
#include <vector>
#include "Cell.h"
#include "StringCell.h"

class Table {

public:

	Table() = default;
	Table(const Table& copy) = delete;
	Table operator=(const Table& copy) = delete;
	~Table();
	
	void load(const char* path);
	void save(const char* path) const;
	void print() const;
	void edit(unsigned row, unsigned column, const std::string& newValue);
	void sort(unsigned column, bool asc = true);
	// obedini ili puk ne
	//Table* extraction(std::string whatToExtract) const;
	Table* extractionInRange(const Pair& start, const Pair& end) const;
	Table* extractionByColumns(std::vector<unsigned> columns) const;
	Table* extractionByCondition(std::string condition) const;

private:

	std::vector<Cell*> valuesOfTable{};
	std::vector<unsigned> maxWidthOnColumn{};
	unsigned numOfColumns{};
	unsigned numOfRows{};

	std::string needsCommaAfter(std::string buffer);
	void destroy();
	void createTableCell(unsigned row, unsigned column, std::string& buffer);
	void widthCange(unsigned column);
	void swapRows(unsigned row1, unsigned row2);
	void thirdExtract(Table* extract, const Cell* one, unsigned col, bool (*whatComparation) (const Cell* one1, const Cell* two1)) const;


};
bool compareTwoCellsBigger(const Cell* one, const Cell* two);
bool compareTwoCellsSmaller(const Cell* one, const Cell* two);
bool compareTwoCellsBiggerOrEqual(const Cell* one, const Cell* two);
bool compareTwoCellsSmallerOrEqual(const Cell* one, const Cell* two);
bool compareTwoCellsEqual(const Cell* one, const Cell* two);
bool compareTwoCellsDifferent(const Cell* one, const Cell* two);
int getEquasion(std::string& condition);
#endif // !TABLE_H
