#include <iostream>
#include <fstream>
#include "global.h"

using namespace std;

bool isFirstRun()
{
    ifstream file(Library::ADMIN_FILE);
    bool exists = file.good(); // .good() is safer than .is_open() here
    file.close();
    return !exists;
}