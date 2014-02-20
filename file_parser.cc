/* file_parser.cc
	TEAM TEXAS
	Quoc Lien, Jose Paterno, Jessica To, Bryant To.
	CS530, Spring 2014
*/
#include "file_parser.h"

file_parser::file_parser(string s) {
	file_name = s;
	num = 0;
}

file_parser::~file_parser() {
}

void file_parser::read_file() {
	ifstream ifs;

	// Opens file read from commandline. 
	ifs.open(file_name.c_str());

	// Checks for valid file. 
	if(!ifs) {
		// Throw Error Message Please!
		exit(1);
	}

	while(!ifs.eof()) { // Reads until end of file. 
		reset_data();

		getline(ifs,line); // Line = 1 whole line in file.
		num++; // Incrementing number of lines.

		/* Checks to see if the line is a Comment.
			if it is, place it in the label slot. 
		*/
		if(line[0] == '.') {
			data.label = line;
		}
		else {
			stringstream ss(line);
			string comment = "";

			// Vector
			vector<string> v; // Vector of tokens.
			vector<string>::iterator v_iter;

			// Check to see if the first character in the line is a whitespace. Push it into vector.
			if(line[0] == ' ' || line[0] == '\t') {
				v.push_back("");
			}

			while(!ss.eof()) {
				size_t found = line.find('\t');
				if(found !=string::npos) {
					getline(ss, token, '\t'); // Handles Tab Characters.
				}
				else {
					getline(ss, token, ' '); // Handles Whitespace Characters.
				}

				// Checks for '.' and if it is the rest of the line is a comment. 
				if(token[0] == '.') {
					comment = token + " ";
					getline(ss,token);

					if(token[0] != '.'){
						comment += token;
					}
					v.push_back(comment); // Push comment to vector. 
				}

				// Checks for '.' and if it is the rest of the line is a comment. 
				else if(token[1] == '\'') {
					comment = token + " ";
					getline(ss,token);

					if(token[1] != '\''){
						comment += token;
					}
					v.push_back(comment); // Push comment to vector. 
				}

				else if(token.size() != 0 && (comment[0] != '.' || comment[1] != '\'')) {
					v.push_back(token);
				}
			}

			if(v.size() >= 5) {
				cout << "TOO MANY TOKENS!";
			}

			if(v.size() == 4) {
				data.label = v[0];
				data.opcode = v[1];
				data.operand = v[2];
				data.comments = v[3];
			}

			else if(v.size() == 3) {
				if(comment[0] != '.' || comment[1] != '\'') {
					data.label = v[0];
					data.opcode = v[1];
					data.operand = v[2];
				}
				else {
					data.opcode = v[1];
					data.operand = v[2];
					data.comments = v[3];
				}
			}

			else if(v.size() == 2) {
				data.opcode = v[1];
				data.label = v[0];
			}
			v.clear();
		}
		v_data.push_back(data);
		cout << data.label << '\t' << data.opcode << '\t' << data.operand << '\t' << data.comments << '\t' << endl;
	} // End outer while statement.

	ifs.close();
} // End read_file().

string file_parser::get_token(unsigned int, unsigned int) {
	return "0";
}


void file_parser::print_file() {

}

int file_parser::size() {
	return num;
}

void file_parser::reset_data() {
	data.label = "";
	data.opcode = "";
	data.operand = "";
	data.comments = "";
}
