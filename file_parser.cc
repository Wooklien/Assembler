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
			vector<string> v;
			vector<string>::iterator v_iter;
			string comment;

			// Check to see if first character in line is a whitespaces. Push white space into vector. 
			if(line[0] == ' '  || line[0] == '\t') {
				v.push_back("");
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
				else if(token[1] == '\'') {
					comment = token + " ";
					getline(iss,token);

					if(token[1] != '\''){
						comment += token;
					}
					v.push_back(comment); // Push comment to vector. 
				}
				
				// Addes token that aren't empty into vector. 
				else if(token.size() != 0 && (comment[0] != '.' || comment[1] != '\'')) {
					v.push_back(token);
				}
			}

			// Will remove later, reads through the vector. and prints each token. 
			for(v_iter = v.begin(); v_iter != v.end(); v_iter++)
				cout << *v_iter << endl;

			if(v.size() >= 5) {
				// Print Error Message, Too many tokens.
				cout << "Retarded LIne." << endl;
			}

			
			if(v.size() == 4) {
				data.label = v[0];
				data.opcode = v[1];
				data.operand = v[2];
				data.comments = v[3];
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
