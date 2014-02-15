#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "file_parser.h"
#include "file_parse_exception.h"

using namespace std;

int main(int argc, char *argv[]) {
	string file_name;

    if(argc != 2) {
        cout << "Error, you must supply the name of the file " <<
        "to process at the command line." << endl;

        cout << "Enter Filename: " << endl;
        cin >> file_name;
    }
    else {
    	file_name = argv[1];
    }

    file_parser fp(file_name);
    fp.read_file();
    
    cout << "File: " << file_name << endl;
    return(1);
}