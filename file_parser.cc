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
	ifstream file;

	// Opens file read from commandline. 
	file.open(file_name.c_str());

	// Checks for valid file. 
	if(!file) {
		throw file_parse_exception("invalid file.");
		exit(1);
	}

	while(!file.eof()) { // Reads until end of file. 
		reset_data();

		getline(file,line); // Line = 1 whole line in file.
		num++; // Incrementing number of lines.

		/* Checks to see if the line is a Comment.
			if it is, place it in the label slot. 
		*/
		if(line[0] == '.') {
			data.label = line;
		}
		else {
			stringstream s_string(line);
			string t_comment = "";

			// Vector
			vector<string> v; // Vector of tokens.

			// Check to see if the first character in the line is a whitespace. Push it into vector.
			if(line[0] == ' ' || line[0] == '\t') {
				v.push_back("");
			}

			while(!s_string.eof()) {
				size_t found = line.find(' ');
				if(found !=string::npos) {
					getline(s_string, token, ' '); // Handles Tab Characters.
				}
				else {
					getline(s_string, token, '\t'); // Handles Whitespace Characters.
				}

				// Checks for '.' and if it is the rest of the line is a comment. 
				if(token[0] == '.') {
					t_comment = token + " ";
					getline(s_string,token);

					if(token[0] != '.'){
						t_comment += token;
					}
					v.push_back(t_comment); // Push comment to vector. 
				}

				// Checks for '.' and if it is the rest of the line is a comment. 
				else if(token[1] == '\'') {
					t_comment = token + " ";
					getline(s_string,token);

					if(token[1] != '\''){
						t_comment += token;
					}
					v.push_back(t_comment); // Push comment to vector. 
				}

				else if(token.size() != 0 && (t_comment[0] != '.' || t_comment[1] != '\'')) {
					v.push_back(token);
				}
			}

			if(v.size() >= 5) {
				string s = static_cast<ostringstream*>(&(ostringstream()<<num))->str();
				throw file_parse_exception("too many tokens at line " + s );
			}

			if(v.size() == 4) {
				data.label = v[0];
				data.opcode = v[1];
				data.operand = v[2];
				data.comments = v[3];
			}

			else if(v.size() == 3) {
				if(t_comment[0] != '.' || t_comment[1] != '\'') {
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
				data.label = v[0];
				data.opcode = v[1];
			}

			else if(v.size() ==1) {
				data.label = v[0];
			}
			v.clear();
		}
		v_data.push_back(data);
	} // End outer while statement.

	file.close();
} // End read_file().

string file_parser::get_token(unsigned int line_row, unsigned int label_col) {
	if(label_col == 0)
        return v_data[line_row-1].label;
    else if(label_col == 1) 
        return v_data[line_row-1].opcode;
    else if(label_col == 2) 
        return v_data[line_row-1].operand;
    else 
        return v_data[line_row-1].comments;
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
