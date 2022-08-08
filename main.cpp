#include <iostream>
#include <fstream>
#include "Cell.h"
#include "IntCell.h"
#include "DoubleCell.h"
#include "StringCell.h"
#include "ValuteCell.h"
#include "Table.h"
#include "MyProgram.h"

int main()
{
    // Basic elements test
    /*char buffer[] = " -444";
    Cell* cellI = createCell(1, 1, buffer);
    Cell* cellD = createCell(1, 1, "    +24.123");
    Cell* cellS = createCell(1, 1, "\"KAK e beee\"");
    Cell* cellV = createCell(1, 1, "2334.13 lv.");
    Cell* cellE = createCell(1, 1, "");

    std::ofstream out("table2.txt");

    out << (cellI)->val() << ',';
    out << (cellD)->val() << ',';
    out << (cellV)->val() << ',';
    out << (cellS)->val() << ',';
    out << (cellE)->val();

    out.close();

    delete cellI;
    delete cellD;
    delete cellS;
    delete cellV;
    delete cellE;*/

    // TESTS
    //// load test
    //Table table;
    //table.load("table.txt");
    //
    //// print test
    //table.print();
    //
    //// edit test
    ////table.edit(3, 1, "12");
    //std::cout << '\n' << '\n';
   
    //// dec sort test
    //table.sort(1, 0);
    //table.print();
    //std::cout << '\n' << '\n';
    //// asc sort test
    ////table.sort(2);
    ////table.print();
  
    //// edit test
    //table.edit(5, 3, "123.4443");
    ////table.print();
    ////std::cout << '\n';
    //
    //// extraction 1st type test
    //Table *extract = table.extractionInRange({ 2, 2 }, { 4, 3 });
    //
    //// estraction 2nd type test
    //Table* extract2 = table.extractionByColumns({ 2, 1 });
   
    //// extraction 3rd type test
    //Table* extract3 = table.extractionByCondition("#3 >= 0");
    //
    //std::cout << '\n' << '\n';
    //extract->print();
    //extract2->sort(1);
    //std::cout << '\n' << '\n';
    //extract2->print();


    //// save test
    //extract3->save("ExtractedTable.txt");
    ////extract->print();
    //////extract2->print();

    //delete extract;
    //delete extract2;
    //delete extract3;

    myProgram();

}

