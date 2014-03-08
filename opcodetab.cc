/* opcodetab.cc
 * TEAM TEXAS
 * Quoc Lien, Jose Paterno, Jessica To, Bryant To.
 * masc
 * prog2
 * CS530, Spring 2014
*/

#include "opcodetab.h"

opcodetab::opcodetab(){
	
	for(unsigned int i = 0;i<59;i++){
		m[CODES[i]]=pair<string,int>(MCODE[i],INSTR_SIZE[i]);
	}	
}

string opcodetab::get_machine_code(string){
    string tmp_opcode = upper(opcode);
    if(tmp_opcode[0] == '+'){
        for( string::size_type i=tmp_opcode.begin(); i < tmp_opcode.end(); i++ ) 
             tmp_opcode[i] = tmp_opcode[i+1];
        tmp_opcode.resize(opcode.length()-1);
    }
    if(opcode_exists(tmp_opcode)){
        m_iter = m.find(tmp_opcode);
        return m_iter->second.first;        
    }
    else throw opcode_error_exception("Invalid opcode: " + opcode + " does not exist.");
}

int opcodetab::get_instruction_size(string opcode){
	if(opcode_exists(get_code(opcode))) {
		if(opcode[0] == '+') {
			return 4;
		}
		else {
			map<string, pair<string,int> >::iterator m_iter;
			m_iter = m.find(opcode);

			return m_iter->second.second;
		}
	}
	else {
		// Throw Error
	}
}

bool opcodetab::opcode_exists(string s) {
	if(m.find(s) == m.end()) {
		return false;
	}
	return true;
}

string opcodetab::get_code(string opcode) {
	if(opcode[0] == '+') {
		stringstream sstring(opcode);
		string tmp;

		getline(sstring, tmp, '+');

		return tmp;
	}
	return opcode;
}

string upper(string s){
    locale loc;
    for( string::size_type i=0; i < s.length(); i++ ) 
        s = toupper(s[i], loc);
    return s;
}
