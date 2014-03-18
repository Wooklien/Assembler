/* sicxe_asm.cc
 * TEAM TEXAS
 * Quoc Lien, Jose Paterno, Jessica To, Bryant To.
 * masc1216
 * prog3
 * CS530, Spring 2014
*/

 #include "sicxe_asm.h"

sicxe_asm::sicxe_asm() {
	asm_address = 0x00000000;

	asm_dir["START"] = 0;
	asm_dir["END"] = 0;
	asm_dir["BYTE"] = 1;
	asm_dir["WORD"] = 3;
	asm_dir["RESB"] = 1;
	asm_dir["RESW"] = 3;
	asm_dir["BASE"] = 0;
	asm_dir["NOBASE"] = 0;
	asm_dir["EQU"] = 0;
}

void sicxe_asm::assign_address(file_parser parser) {
	for(int i = 1; i < parser.size(); i++) {
		data.label = parser.get_token(i,0);
		data.opcode = parser.get_token(i,1);
		data.operand = parser.get_token(i,2);
		data.address = asm_address;

		if(check_asm_dir(data.opcode)) {
			int value;
			if(upper(data.opcode) == "START") {
				value = int_value(data.operand); // INT
				asm_address += value;
			}
			else {
				value = hex_value(data.operand); // HEX
				int size = asm_dir.find(upper(data.opcode))->second; // Getting Assembly Directive Size.

				if(upper(data.opcode) == "RESW" || upper(data.opcode) == "RESB") {
					asm_address += (size * value);
				}
				else{
					asm_address += size;
				}
			}
		}
		else {
			if(!ignore_case(data.opcode)) {
				asm_address += opcode.get_instruction_size(data.opcode);
			}
		}

		if(data.label[0] != '.' && data.label.size() != 0) {
			table.add(data.label, data.address, false);
		}

		v_data.push_back(data);
	}
}

void sicxe_asm::first(string filename) {
	file_parser parser(filename);
	parser.read_file();

	assign_address(parser);
}

void sicxe_asm::write_file(string filename) {
	for(unsigned int i = 0; i < v_data.size(); i++) {
		cout << hex << v_data[i].address << '\t';
		cout << v_data[i].label << '\t';
		cout << v_data[i].opcode << '\t';
		cout << v_data[i].operand << endl;
	}
}

void sicxe_asm::print_symtab() {
	table.print_table();
}

bool sicxe_asm::check_asm_dir(string s) {
	string temp = upper(s);

	if(asm_dir.find(temp) == asm_dir.end()) {
		return false;
	}
	return true;
}

int sicxe_asm::int_value(string s) {
	string operand = s;
	unsigned int value;

	if(s[0] == '$' || s[0] == '#') {
		operand.erase(0,1);
	}

	stringstream str_value;
	str_value << hex << operand;
	str_value >> value;

	return value;
}

int sicxe_asm::hex_value(string s) {
	string operand = s;
	int value;

	if(s[0] == '$' || s[0] == '#') {
		operand.erase(0,1);
	}

	stringstream str_value;
	str_value << operand;
	str_value >> value;

	return value;

}

bool sicxe_asm::ignore_case(string s) {
	if(s[0] == '.' || s.size() == 0) {
		return true;
	}
	return false;
}

string sicxe_asm::upper(string s){
	string tmp = s;
	string::iterator iter;

	for(iter = tmp.begin(); iter != tmp.end(); ++iter) {
  		*iter = std::toupper((unsigned char)*iter);
  	}
	return tmp;
}

int main(int argc, char *argv[]) {
	int address = 0;
 	if(argc != 2) {
 		//throw error: file not found.
 	}
 	string file = argv[1];

 	try {
 		sicxe_asm assembler;

 		assembler.first(file);
 		assembler.write_file(file);

 		cout << endl << ":::::SYM_TAB:::::" << endl;
 		assembler.print_symtab();
 	}
 	catch(exception& excpt) {
 		cout << "ERROR" << excpt.what() << endl;
 	}
 	return 0;
 }
