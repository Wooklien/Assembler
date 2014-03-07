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
	return "why?";
	
}

int opcodetab::get_instruction_size(string){
	return 0;
}

//this is not a method that is part of the project, so we have to remove it later. 
void opcodetab::instr_iterator(){
	map<string,pair<string,int> >::iterator it = m.begin();
	for(std::map<string,pair<string,int> >::iterator it = m.begin(); it!=m.end();++it){
		std::cout<<it->first<<endl;
	}
}



int main(){
	opcodetab opcode;
	opcode.instr_iterator();	

}
