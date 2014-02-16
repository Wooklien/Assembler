#include "file_parser.h"

file_parser::file_parser(string s) {
	file_name = s;
	num = 0;
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
		getline(ifs,line);
		num++;

		if(line[0] == '.') {
			data.label = line;
			cout << data.label << endl;
		}
		else {
			istringstream iss(line);
			vector<string> v;
			vector<string>::iterator v_iter;
			string comment;
			
			while(!iss.eof()) {
				getline(iss, token, ' ');

				if(token[0] == '.') {
					comment = token + " ";
					getline(iss,token);
					comment += token;
					v.push_back(comment);
				}

				if(token.size() != 0 && comment[0] != '.') {
					v.push_back(token);
				}
			}

			for(v_iter = v.begin(); v_iter != v.end(); v_iter++) {
				cout << *v_iter << endl;
			}
		}
	}

	/* Remove multiple spaces from line. 
	while(getline(ifs,line)) {
		
		for(string::const_iterator iter=line.begin(); iter!=line.end(); iter++) {
			if(isspace(*iter)) {
				while(isspace(*(iter+1)))
					advance(iter,1);
			}

			cout << *iter << endl;
		}
	}
	*/
	ifs.close();
}

string file_parser::get_token(unsigned int, unsigned int) {
	return "0";
}

void file_parser::print_file() {

}

int file_parser::size() {
	return num;
}
