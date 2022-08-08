#include "MyProgram.h"


void myProgram() {

    std::string tablePath;
    std::cout << "Enter the path or the name of the file you want to load: ";
    std::cin >> tablePath;

    Table table;
    table.load(tablePath);

    int command = 0;

    while (command != 7) {
        std::cout << "Commands:\n1. Load new file\n2. Save the table\n3. Print the table\n4. Edit a cell\n5. Sort the table\n6. Make extraction\n7. Exit\n";
        std::cout << "Enter the number of command you want: ";
        
        std::cin >> command;
        system("CLS");

        switch (command)
        {
        case 1: myLoad(table); break;
        case 2: mySave(table); break;
        case 3: myPrint(table); break;
        case 4: myEdit(table); break;
        case 5: mySort(table); break;
        case 6: myExtraction(table); break;
        case 7: break;
        default: std::cout << "Invalid command number.\n"; break;
        }

        system("CLS");

    }


}

void wait() {
    char c;
    std::cout << "\nEnter c to continue...";
    std::cin >> c;
}

void myLoad(Table& table) {

    std::string path;
    std::cout << "\nEnter new file path to load: ";
    std::cin >> path;
    table.load(path);
    wait();
}

void mySave(const Table& table) {

    std::string path;
    std::cout << "\nEnter name of file in which this table will be saved: ";
    std::cin >> path;
    table.save(path);
    wait();
}

void myPrint(const Table& table) {

    table.print();
    wait();
}

void myEdit(Table& table) {

    unsigned row, column;
    std::string newValue;
    std::cout << "\nEnter row and column of the cell you want to change: ";
    std::cin >> row >> column;
    std::cout << "\nEnter the new vale of the sell: ";
    std::cin >> newValue;
    table.edit(row, column, newValue);
    wait();
}

void mySort(Table& table) {

    unsigned column, asc;
    std::cout << "\nEnter the column by which you want to sort: ";
    std::cin >> column;
    std::cout << "\nEnter the way you want to sort (0 desc | 1 asc): ";
    std::cin >> asc;
    table.sort(column, asc);
    wait();
}

void myExtraction(const Table& table) {

    int type;
    std::cout << "\nEnter the type of extraction\n1. By range\n2. By columns\n3. By condition\n";
    std::cin >> type;
    Table* extract = nullptr;
    switch (type)
    {
    case 1: extract = extractionOne(table); break;
    case 2: extract = extractionTwo(table); break;
    case 3: extract = extractionThree(table); break;
    default: break;
    }

    if (extract) {
        std::cout << "\nDo you want to save the extraction? y/n :";
        char yes;
        std::cin >> yes;
        if (yes == 'y' || yes == 'Y') {
            mySave(*extract);
        }
        std::cout << "\nDo you want to print the extraction? y/n :";
        std::cin >> yes;
        if (yes == 'y' || yes == 'Y') {
            myPrint(*extract);
        }
        delete extract;
    }
}

Table* extractionOne(const Table& table) {

    Pair start, end;
    std::cout << "\nEnter start row and start column\n";
    std::cin >> start.fst >> start.snd;
    std::cout << "\nEnter end row and start column\n";
    std::cin >> end.fst >> end.snd;

    return table.extractionInRange(start, end);
}

Table* extractionTwo(const Table& table) {

    std::vector<unsigned> columns;
    int column;
    std::cout << "\nEnter columns. To stop enter 0.";
    do
    {
        std::cin >> column;
        if (column < 1)
            break;
        columns.push_back(column);

    } while (column > 0);

    return table.extractionByColumns(columns);
}

Table* extractionThree(const Table& table) {

    std::cin.clear();
    std::cin.ignore();
    std::cout << "\nEnter Condition: ";
    char condition[256];
    std::cin.getline(condition, 256, '\n');
    return table.extractionByCondition(condition);
}