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
		vector<string> v;

		getline(ifs,line); // line = whole line from file. 
		num++; // Incrementing number of lines. 

		/* Checks to see if the line is a Comment.
			if it is, place it in the label slot. 
		*/
		if(line[0] == '.') { 
			data.label = line;
			// cout << data.label << endl;
		}
		else {
			istringstream iss(line);
			vector<string>::iterator v_iter;
			string comment = "";

			// Check to see if first character in line is a whitespaces. Push white space into vector. 
			if(line[0] == ' '  || line[0] == '\t') {
				v.push_back(line);
			}
			
			while(!iss.eof()) {

				size_t found = line.find('\t');
				if(found !=string::npos) {
					getline(iss, token, '\t'); // Handles Tab Characters.
				}
				else {
					getline(iss, token, ' '); // Handles Whitespace Characters.
				}

				// Checks for '.' and if it is the rest of the line is a comment. 
				if(token[0] == '.') {
					comment = token + " ";
					getline(iss,token);

					if(token[0] != '.'){
						comment += token;
					}
					v.push_back(comment); // Push comment to vector. 
				}
				
				// Addes token that aren't empty into vector. 
				else if(token.size() != 0 && (comment[0] != '.' || comment[1] != '\'')) {
					v.push_back(token);
				}

				if(v.size() >= 5) {
				// Print Error Message, Too many tokens.
				}

				for(v_iter = v.begin(); v_iter != v.end(); v_iter++)
					cout << *v_iter << endl;
			} // End inner while statement.
			//cout << data.label << "\t" << data.opcode << "\t" << data.operand << "\t" << data.comments << "\t" << endl;
		} // End else statement.
		v.clear();
		//cout << data.label << endl;
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
