/* sicxe_asm.h
 * TEAM TEXAS
 * Quoc Lien, Jose Paterno, Jessica To, Bryant To.
 * masc1216
 * prog3
 * CS530, Spring 2014
*/

 #include <string>
 #include <iomanip>
 #include <iostream>
 #include <sstream>
 #include <fstrea>
 #include "file_parser.cc"
 #include "file_parse_exception.h"
 #include "opcodetab.cc"
 #include "opcode_error_exception.h"
 #include "symtab.cc"
 #include "symtab_exception.h"

 #ifndef SICXE_ASM_
 #define SICXE_ASM_

 using namespace std;

 class sicxe_asm {
 public:

 	// Default Constructor.
 	sicxe_asm();

 	// Assign address to each line of code.
 	void assign_address(file_parser parser);
 	// First pass of the assembler. 
 	void first(string filename);
 	
 	// Write to file.
 	void write_file(string filename);

 	void print_symtab();

 private:
 	int asm_address;
	opcodetab opcode;
	symtab table;
	ofstream myfile;

	struct parse_data{
		string address;
		string label;
		string opcode;
		string operand;
	};

	parse_data data;

	map<string,int> asm_dir;
	map<string,int>::iterator asm_iter;

	vector<parse_data> v_data;
	vector<parse_data>::iterator v_iter;

	// Check assembler directive.
 	bool check_asm_dir(string s);
 	// Returns the int value of the string.
 	int int_value(string s);
 	// Returns the hex value of the string.
 	int hex_value(string s);
 	// Ignores cases of comments and empty strings.
 	bool ignore_case(string s);
 	// Changes the string to uppercase.
 	string upper(string s);
 	
 	// Checks if EQU is absolute or relative 
 	bool isAbsolute(string s);

 	string format_string(int x);
 };

 #endif
