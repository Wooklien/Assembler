/* sicxe_asm.cpp
 * TEAM TEXAS
 * Quoc Lien, Jose Paterno, Jessica To, Bryant To.
 * masc1216
 * prog3
 * CS530, Spring 2014
*/

 #include "sicxe_asm.h"

sicxe_asm::sicxe_asm(string filename) {
	asm_address = 0x00000000;
	base = -1;
	start = -1;

	init_asm();

	first(filename);
	write_file(filename);
}

void sicxe_asm::assign_address(file_parser parser) {
	for(int i = 1; i < parser.size(); i++) {
		parse_to_struct(parser,i);

		if(check_asm_dir(data.opcode)) {
			if(!(upper(data.opcode) == "END")) {
				handle_asm_dir(data.opcode, data.operand, i);
			}
			else {
				v_data.push_back(data);
				break;
			}
		}
		else {
			if(data.operand[1] == '#'){
				ss << "Error on line: " << i << ". Invalid operand.";
                throw symtab_exception(ss.str());
            }
			if(!ignore_case(data.opcode) && start != -1) {
				try {
					asm_address += opcode.get_instruction_size(data.opcode);
				}
				catch(opcode_error_exception ox) {
					cerr << "An Opcode error has occured at line " << i  << ": " << ox.getMessage() << endl;
				}
			}
			else if(!ignore_case(data.opcode) && start == -1) {
				ss << "Error on line: " << i << ". Invalid operation! Opcode operation before Start.";
				throw symtab_exception(ss.str());
			}
		}
		// Adding user defined labels to symbol tabel.
		add_symtab(data.address, data.label, data.operand);

		v_data.push_back(data);
	}
}

void sicxe_asm::handle_asm_dir(string op, string operand, int index) {
	int value;
	string tmp_opcode = upper(op);
	if(operand[0] == '@' || operand[0] == '#' || operand[1] == '@' || operand[1] == '#') {
        	ss << "Error on line: " << index << ". Addressing modes do not apply to assembly directives.";
        	throw symtab_exception(ss.str());
    	}
    	else{
		if(tmp_opcode == "START") {
			start = 1;
			value = int_value(operand, index);
			asm_address = value;
		}
		else if(tmp_opcode == "BASE") {
			base_operand = operand;
			base = 1;
		}
		else if(tmp_opcode == "NOBASE") {
			base = -1;
		}
		else {
			value = hex_value(operand, index);
			int size = asm_dir.find(tmp_opcode)->second; // Getting Operation Size.
	
			if(tmp_opcode == "RESW" || tmp_opcode == "RESB") {
				asm_address += (size * value);
			}
			else if( tmp_opcode == "BYTE") {
				int length = operand.length() - 3;
	
				if(operand[0] == 'x' || operand[0] == 'X') {
					if(length % 2 == 0) {
						asm_address += ((length/2) * size);
					}
					else {
						ss << "Error on line: " << index << ". Invalid operand size. Hex value should be even.";
						throw symtab_exception(ss.str());
					}
				}
				else {
					asm_address += (length * size);
				}
			}
			else {
				asm_address += size;
			}
		}
    }
}

void sicxe_asm::init_asm() {
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

void sicxe_asm::parse_to_struct(file_parser parser, int index) {
	data.label = parser.get_token(index,0);
	data.opcode = parser.get_token(index,1);
	data.operand = parser.get_token(index,2);
	data.address = format_string(asm_address);
}

void sicxe_asm::first(string filename) {
	file_parser parser(filename);
	parser.read_file();
	assign_address(parser);

	if(base != -1) {
		base_operand = table.get_value(base_operand);
	}
}

void sicxe_asm::write_file(string filename) {
	const string columns [] = { "Line#","Address","Label","Opcode","Operand" };
	const string purdylines [] = { "=====", "=======", "=====", "======", "=======" };
	
	filename = filename.substr(0,filename.length()-4) + ".lis";
	
	myfile.open(filename.c_str());
	
	for (int i = 0; i < 5; i++) 
        myfile << setw(15) << setfill(' ') << columns[i]; 
    myfile << endl;
    
    for (int i = 0; i < 5; i++)
	    myfile << setw(15) << setfill(' ') << purdylines[i];
	myfile << endl;
	
	for (unsigned int i = 0; i < v_data.size(); i++){
        myfile << setw(15) << setfill(' ') << i+1;
        if(ignore_case(v_data[i].label))
            v_data[i].label = "";
        if(ignore_case(v_data[i].opcode))
            v_data[i].opcode = "";
        if(ignore_case(v_data[i].operand))
            v_data[i].operand = "";
        myfile << setw(15) << setfill(' ')  << v_data[i].address;
        myfile << setw(15) << setfill (' ') << v_data[i].label;
        myfile << setw(15) << setfill (' ') << v_data[i].opcode;
        myfile << setw(15) << setfill (' ') << v_data[i].operand << endl;  
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

int sicxe_asm::int_value(string s, int index) {
	if(s[0] == '$' || s[0] == '#'){
		s.erase(0,1);
	}
	else if(s[0] == '@') {
		ss << "Error on line: " << index << ". Invalid indirect addressing with constants.";
		throw symtab_exception(ss.str());
	}
	int value;
	sscanf(s.c_str(),"%x",&value);
	return value;
}

int sicxe_asm::hex_value(string s, int index) {
	int value;
	if(s[0] == '$' || s[0] == '#'){
		s.erase(0,1);
	}
	else if(s[0] == '@') {
		ss << "Error on line: " << index << ". Invalid indirect addressing with constants.";
		throw symtab_exception(ss.str());
	}

 	stringstream str_value;
 	str_value << s;
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

string sicxe_asm::format_string(int x) {
	stringstream tmp;
	tmp << hex << setw(5) << setfill('0') << x;
	string xx = tmp.str();
	stringstream tmmp;
	tmmp << setw(5) << xx;
	return upper(tmmp.str());
}

bool sicxe_asm::isAbsolute(string s) {
	if(s[0] == '#')
		return true;
	return false;
}

void sicxe_asm::add_symtab(string address, string label, string operand) {
	if(label[0] != '.' && label.size() != 0) {
		table.add(label, address, isAbsolute(data.operand));
	}
}

int main(int argc, char *argv[]) {
 	string file = argv[1];

 	try {
 		sicxe_asm assembler(file);
 	}
 	catch(exception& excpt) {
 		cerr << "An Error has occured: " << excpt.what() << endl;
 	}
 	catch(opcode_error_exception ox) {
 		cerr << "An Opcode error has occured: " << ox.getMessage() << endl;
 	}
 	catch(file_parse_exception fx) {
 		cerr << "A File parser error has occured: " << fx.getMessage() << endl;
 	}
 	catch(symtab_exception sx) {
 		cerr << "An error has occured: " << sx.getMessage() << endl;
 	}
 	catch(...) {
 		cerr << "Uknown failure occured." << endl;
 	}
 	return 0;
 }
