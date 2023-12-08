#include <sstream>

// Include necessary headers
#pragma once
#include <string.h>
#include <string>
using namespace std;

// Function to convert a C-style string to C++ string
string cBS(char* c){
    // Convert the C-style string to C++ string
    char* cstr = c;
    std::string str(cstr);
    return cstr;  // Return the C++ string
}
