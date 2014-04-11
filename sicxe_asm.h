/* sicxe_asm.h
 * TEAM TEXAS
 * Quoc Lien, Jose Paterno, Jessica To, Bryant To.
 * masc1216
 * prog3
 * CS530, Spring 2014
*/

 #ifndef SICXE_ASM_
 #define SICXE_ASM_

 #include <string>
 #include <iomanip>
 #include <iostream>
 #include <fstream>
 #include <sstream>
 #include "file_parser.h"
 #include "file_parse_exception.h"
 #include "opcodetab.h"
 #include "opcode_error_exception.h"
 #include "symtab.h"
 #include "symtab_exception.h"

 using namespace std;

 class sicxe_asm {
 public:

 	// Default Constructor.
 	sicxe_asm(string filename);

 private:
 	int asm_address;
 	int base;
 	int start;
 	string base_operand;
 	stringstream ss;
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

	// MAIN FUNCTIONS //
	// Initialize assembly directives.
	void init_asm();
	// First pass of the assembler. 
 	void first(string filename);
 	// Write to file.
 	void write_file(string filename);
 	// Print Symbol table.
 	void print_symtab();
	// Add user defined labels and addresses to symtab.
	void add_symtab(string address, string label, string operand);
 	// Assign address to each line of code.
 	void assign_address(file_parser parser);
 	// Handling assembly directives. Indexing address by functions of assembly directives.
 	void handle_asm_dir(string op, string operand, int index);
 	// Parsing data into data structure.
 	void parse_to_struct(file_parser parser, int index);

 	// SUPPORTING FUNCTIONS //
	// Check assembler directive.
 	bool check_asm_dir(string s);
 	// Returns the int value of the string.
 	int int_value(string s, int index);
 	// Returns the hex value of the string.
 	int hex_value(string s, int index);
 	// Ignores cases of comments and empty strings.
 	bool ignore_case(string s);
 	// Changes the string to uppercase.
 	string upper(string s);
 	// Format string with padding of 0s.
 	string format_string(int x);
 	// Checks if EQU is absolute or relative 
 	bool isAbsolute(string s);
 };

 #endif
