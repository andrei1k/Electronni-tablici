#ifndef MYPROGRAM_H
#define MYPROGRAM_H

#include <iostream>
#include "Table.h"

void myProgram();
void myLoad(Table& table);
void mySave(const Table& table);
void myPrint(const Table& table);
void myEdit(Table& table);
void mySort(Table& table);
void myExtraction(const Table& table);
Table* extractionOne(const Table& table);
Table* extractionTwo(const Table& table);
Table* extractionThree(const Table& table);
void wait();
#endif // !MYPROGRAM_H
