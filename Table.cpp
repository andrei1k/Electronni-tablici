#include "Table.h"

Table::~Table()
{
	this->destroy();
}

void Table::load(std::string path)
{

	std::ifstream in(path);
	if (!in.is_open()) {
		std::cout << "Could not load the file.\n";
		return;
	}
		
	this->destroy();

	int columns = 1, maxColumns = 1;

	for (; !in.eof();) {
		
		char c;
		in.get(c);
		if (in.eof())
			break;
		if (c == ',')
			columns++;
		else if (c == '\n')
		{
			if (columns > maxColumns)
				maxColumns = columns;
			columns = 1;
		}	
	}
	this->numOfColumns = maxColumns;

	in.clear();
	in.seekg(0);

	unsigned row = 1, column = 1;
	std::string buffer;

	try{

		bool emptyLine = false;
		char c;

		for (;!in.eof();) {

			in.get(c);
			if (in.eof())
				break;

			if (c == '\n' && emptyLine || c == '\n' && in.tellg() == 2) {
				for (unsigned j = 0; j < this->numOfColumns; j++) {
					buffer = "";
					this->createTableCell(row, column, buffer);
					column++;
				}
				row++;
				column = 1;
				continue;
			}
			emptyLine = false;
			if (c == ',') {
				this->createTableCell(row, column, buffer);
				column++;

			}
			else if (c == '\n') {
				this->createTableCell(row, column, buffer);
				column++;
				for (; column <= this->numOfColumns; column++) {
					buffer = "";
					this->createTableCell(row, column, buffer);
				}
				row++;
				column = 1;
				emptyLine = true;
			}
			else {
				
				buffer.push_back(c);
			}		

		}
		this->numOfRows = row;
		this->createTableCell(row, column, buffer);	
		for (; column <= this->valuesOfTable.size() % this->numOfRows; columns++) {
			buffer = "";
			this->createTableCell(row, column, buffer);
		}
		
	}
	catch (const std::exception& ex)
	{
		//std::cout << std::boolalpha << needsCommaAfter(buffer) << '\n';
		if(needsCommaAfter(buffer) == "no")
			std::cout << "Error: row " << row << ", col " << column << ", " << ex.what() << " is unknown data type";
		else
			std::cout << "Error on row " << row << ": missing comma after " << needsCommaAfter(buffer) << '.';

		in.close();
		this->destroy();
		exit(0);
	}

	this->numOfRows = (this->valuesOfTable.size() / this->numOfColumns);
	in.close();
}

void Table::save(std::string path) const
{
	std::ofstream out(path);
	if (!out.is_open()) {
		std::cout << "Can not save table in this file.";
		return;
	}

	for (unsigned i = 0, col = 1; i < this->valuesOfTable.size(); i++, col++) {

		out << this->valuesOfTable[i]->val();

		if (i == this->valuesOfTable.size() - 1)
			break;
		else if (col == this->numOfColumns) {
			out << '\n';
			col = 0;
		}
		else {
			out << ',';
		}
	}
	out.close();
}

void Table::print() const
{
	for (unsigned i = 0, column = 1, row = 1; i < this->valuesOfTable.size(); i++) {
		
		if (column > this->numOfColumns) {
			row++;
			column = 1;
			std::cout << '\n';
		}

		for (unsigned j = 0; j < this->maxWidthOnColumn[column - 1] - this->valuesOfTable[i]->getWidth(); j++) {
			std::cout << ' ';
		}
		
		if(this->valuesOfTable[i]->getType() == CellType::STRING)
			std::cout << dynamic_cast<StringCell*>(this->valuesOfTable[i])->getValue() << '|';
		else
			std::cout << this->valuesOfTable[i]->val() << '|';
		column++;
	}
}

void Table::edit(unsigned row, unsigned column, const std::string& newValue)
{
	if (typeOfString(newValue) == CellType::INVALID || column > this->numOfColumns || column < 1 || row > (this->valuesOfTable.size()/this->numOfColumns) || row < 1) {
		std::cout << "Invalid arguments are entered.\n";
		return;
	}
	int index = (row - 1) * this->numOfColumns + column - 1;
	delete this->valuesOfTable[index];
	this->valuesOfTable[index] = createCell(row, column, newValue);
	this->widthCange(column);
}

void Table::sort(unsigned column, bool asc)
{
	if (column > this->numOfColumns || column < 1) {
		std::cout << "There is not such column. Table was not changed\n";
		return;
	}

	for (unsigned i = 0; i < this->numOfRows - 1; i++) {
	
		for (unsigned j = 0, index = column - 1; j < this->numOfRows - i - 1; j++, index += this->numOfColumns) {

			if (asc == 1) {
				if (compareTwoCellsBigger(this->valuesOfTable[index], this->valuesOfTable[index + this->numOfColumns])) {

					this->swapRows(this->valuesOfTable[index]->getPosition().fst, this->valuesOfTable[index + this->numOfColumns]->getPosition().fst);
				}
			}
			else
				if (compareTwoCellsSmaller(this->valuesOfTable[index], this->valuesOfTable[index + this->numOfColumns])) {

					this->swapRows(this->valuesOfTable[index]->getPosition().fst, this->valuesOfTable[index + this->numOfColumns]->getPosition().fst);
				}
		}
	}
}

std::string Table::needsCommaAfter(std::string buffer)
{
	for (unsigned i = 0; i < buffer.size(); i++) {

		if (buffer[i] == ' ') {
			std::string buf1 = "", buf2 = "";
			unsigned j = 0;
			for (; j < i; j++) {
				buf1.push_back(buffer[j]);
			}
			for (; j < buffer.size(); j++) {
				buf2.push_back(buffer[j]);
			}
			buf1 = removeWhiteSpaces(buf1);
			buf2 = removeWhiteSpaces(buf2);

			if (typeOfString(buf1) != CellType::INVALID && typeOfString(buf2) != CellType::INVALID) {
				return buf1;
			}
		}
	}
	return "no";
}

Table* Table::extractionInRange(const Pair& start, const Pair& end) const
{
	bool wrong = false;
	if (start.fst > end.fst || end.fst > this->numOfRows || start.fst < 1 || start.snd > end.snd || end.snd > this->numOfColumns || start.snd < 1)
		wrong = true;
	if (wrong) {
		std::cout << "Invalid range is entered. Empty table is created.";
		Table* empty = new Table{};
		return empty;
	}

	Table* extract = new Table{};

	unsigned row = 1, column = 1;
	for (unsigned i = start.fst, b = 0; i < end.fst + 1; i++, row++, b++) {

		column = 1;
		for (unsigned j = start.snd; j < end.snd + 1; j++, column++) {

			int index = (i - 1) * this->numOfColumns + (j - 1);
			std::string buffer = this->valuesOfTable[index]->val();
			extract->createTableCell(row, column, buffer);
		}
	}
	extract->numOfRows = row - 1;
	extract->numOfColumns = column - 1;

	return extract;
}

Table* Table::extractionByColumns(std::vector<unsigned> columns) const
{
	for (unsigned i = 0; i < columns.size() - 1; i++) {
		for (unsigned j = 0; j < columns.size() - i - 1; j++) {
			if (columns[j] > columns[j + 1]) {
				unsigned temp = columns[j];
				columns[j] = columns[j + 1];
				columns[j + 1] = temp;
			}
		}
	}
	
	if (columns.back() > this->numOfColumns || columns[0] == 0) {
		std::cout << "Table does not have all the columns entered. Empty table is created.";
		Table* empty = new Table{};
		return empty;
	}

	Table* extract = new Table{};
	extract->numOfColumns = columns.size();
	extract->numOfRows = this->numOfRows;

	for (unsigned i = 1; i < extract->numOfRows + 1; i++) {

		unsigned column = 1;
		for (unsigned j = 0; j < columns.size(); j++, column++) {

			int index = (i - 1) * this->numOfColumns + (columns[j] - 1);
			std::string buffer = this->valuesOfTable[index]->val();
			extract->createTableCell(i, column, buffer);
		}
	}

	return extract;
}

Table* Table::extractionByCondition(std::string condition) const
{
	condition.erase(0, 1);
	unsigned column;
	try{
		column = stoi(condition);
		if (column > this->numOfColumns || column < 1)
			throw std::invalid_argument("Invalid column");
	}
	catch (...) {
		std::cout << "Invalid column number. Empty table is returned.";
		Table* empty = new Table{};
		return empty;
	}

	int equasion = getEquasion(condition);

	if (equasion == 0 || equasion == 2)
		condition.erase(0, 1);
	else
		condition.erase(0, 2);

	std::string compare = removeWhiteSpaces(condition);
	Table* extract = new Table{};
	Cell* cellToCmp = createCell(0, 0, compare);

	try {

		switch (equasion)
		{
		case 0: thirdExtract(extract, cellToCmp, column, &compareTwoCellsBigger); break;
		case 1: thirdExtract(extract, cellToCmp, column, &compareTwoCellsBiggerOrEqual); break;
		case 2: thirdExtract(extract, cellToCmp, column, &compareTwoCellsSmaller); break;
		case 3: thirdExtract(extract, cellToCmp, column, &compareTwoCellsSmallerOrEqual); break;
		case 4: thirdExtract(extract, cellToCmp, column, &compareTwoCellsEqual); break;
		case 5: thirdExtract(extract, cellToCmp, column, &compareTwoCellsDifferent); break;
		default: throw std::invalid_argument("Invalid operator."); break;
		}
		delete cellToCmp;
	}
	catch(std::exception& ex){

		delete cellToCmp;
		std::cout << ex.what() << "! Empty table is returned\n";
		Table * empty = new Table{};
		return empty;
	}

	return extract;

}


void Table::swapRows(unsigned row1, unsigned row2) {

	for (unsigned i = 0; i < this->numOfColumns; i++) {
		int index1 = (row1 - 1) * this->numOfColumns + i;
		int index2 = (row2 - 1) * this->numOfColumns + i;
		Cell* temp = this->valuesOfTable[index1];
		this->valuesOfTable[index1] = this->valuesOfTable[index2];
		this->valuesOfTable[index2] = temp;
		this->valuesOfTable[index1]->changeRow(row1);
		this->valuesOfTable[index2]->changeRow(row2);
	}

}

void Table::destroy()
{
	for (unsigned i = 0; i < this->valuesOfTable.size(); i++)
		delete this->valuesOfTable[i];

	this->valuesOfTable.resize(0);
	this->maxWidthOnColumn.resize(0);
	this->numOfColumns = 0;
	this->numOfRows = 0;
}

void Table::createTableCell(unsigned row, unsigned column, std::string& buffer)
{
	this->valuesOfTable.push_back(createCell(row, column, buffer));
	buffer.resize(0);
	if (this->maxWidthOnColumn.size() < column)
		this->maxWidthOnColumn.push_back(this->valuesOfTable.back()->getWidth());
	else if (this->maxWidthOnColumn[column - 1] < this->valuesOfTable.back()->getWidth())
		this->maxWidthOnColumn[column - 1] = this->valuesOfTable.back()->getWidth();
}

void Table::widthCange(unsigned column)
{
	this->maxWidthOnColumn[column - 1] = 0;
	for (unsigned i = column - 1; i < this->valuesOfTable.size(); i += this->numOfColumns) {
		if (this->maxWidthOnColumn[column - 1] < this->valuesOfTable[i]->getWidth())
			this->maxWidthOnColumn[column - 1] = this->valuesOfTable[i]->getWidth();
	}
}

void Table::thirdExtract(Table* extract, const Cell* one, unsigned col, bool(*whatComparation)(const Cell* one1, const Cell* two1)) const
{
	unsigned row = 1, column;
	for (unsigned i = 0; i < this->numOfRows; i++) {
		column = 1;
		if (whatComparation(this->valuesOfTable[i * this->numOfColumns + col - 1], one)) {
			for (unsigned j = 0; j < this->numOfColumns; j++, column++) {
				int index = i * this->numOfColumns + j;
				std::string buffer = this->valuesOfTable[index]->val();
				extract->createTableCell(row, column, buffer);
			}
			row++;
		}
	}
	extract->numOfRows = row - 1;
	extract->numOfColumns = this->numOfColumns;
}

bool compareTwoCellsBigger(const Cell* one, const Cell* two)
{
	if (one->getType() == two->getType() && (one->getType() == CellType::STRING || one->getType() == CellType::EMPTY)) {

		if (one->val() > two->val())
			return 1;
	}
	else {

		// Empty cell is always smaller;
		if (one->getType() == CellType::EMPTY)
			return 0;
		if (two->getType() == CellType::EMPTY)
			return 1;

		if (one->compareValue() > two->compareValue())
			return 1;
	}

	return 0;
}

bool compareTwoCellsSmaller(const Cell* one, const Cell* two)
{
	return compareTwoCellsBigger(two, one);
}

bool compareTwoCellsBiggerOrEqual(const Cell* one, const Cell* two)
{
	return compareTwoCellsSmallerOrEqual(two, one);
}

bool compareTwoCellsSmallerOrEqual(const Cell* one, const Cell* two)
{
	return !(compareTwoCellsBigger(one, two));
}

bool compareTwoCellsEqual(const Cell* one, const Cell* two)
{
	return compareTwoCellsBiggerOrEqual(one, two) && compareTwoCellsSmallerOrEqual(one, two);
}

bool compareTwoCellsDifferent(const Cell* one, const Cell* two)
{
	return !(compareTwoCellsEqual(one, two));
}

int getEquasion(std::string& condition)
{
	for (unsigned i = 0; i < condition.size();) {

		if (condition[0] == '>') {
			if (condition[1] == '=')
				return 1;
			else
				return 0;
		}
		if (condition[0] == '<') {
			if (condition[1] == '=')
				return 3;
			else
				return 2;
		}
		if (condition[0] == '=') {
			if (condition[ 1] == '=')
				return 4;
		}
		if (condition[0] == '!') {
			if (condition[1] == '=')
				return 5;
		}
		condition.erase(0, 1);
	}

	return -1;
}