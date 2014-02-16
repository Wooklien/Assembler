#include <iostream>
#include <fstream>
#include "file_parser.h"
#include "file_parse_exception.h"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 2) {
        cout << "Error, you must supply the name of the file " <<
        "to process at the command line." << endl;
        exit(1);
    }
    string filename = argv[1];
    try {
    file_parser parser(filename);
    parser.read_file();
    }
    catch(file_parse_exception excpt) {
        cout << "**Sorry, error " << excpt.getMessage() << endl;
    }
}
