#include "file_parser.h"

file_parser::file_parser(string s) {
	file_name = s;
}

file_parser::~file_parser() {
}

void file_parser::read_file() {
	ifstream ifs;

	ifs.open(file_name.c_str());

	if(!ifs) {
		cout << "ERROR: File not found." << endl;
		exit(1);
	}

	while(!ifs.eof()) {
		getline(ifs,line,' ');
		cout << line << endl;
	}

	ifs.close();
}

string file_parser::get_token(unsigned int, unsigned int) {
	return "0";
}

void file_parser::print_file() {

}

int file_parser::size() {
	return 0;
}
