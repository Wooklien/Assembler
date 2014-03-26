/* symtab.h
 * TEAM TEXAS
 * Quoc Lien, Jose Paterno, Jessica To, Bryant To.
 * masc1216
 * prog3
 * CS530, Spring 2014
*/

 #include "symtab.h"

 void symtab::add(string symbol, string value, bool type) {
 	if(!exists(symbol)) {
 		m[symbol] = pair<string,bool>(value, type);
 	}
 	else {
 		throw symtab_exception("Symbol already defined in map.");
 	}
 }

 string symtab::get_value(string symbol) {
 	if(exists(symbol)) {
 		m_iter =  m.find(symbol);

 		return m_iter->second.first;
 	}
 	else {
 		throw symtab_exception("Symbol not found.");
 	}
 }

 void symtab::print_table() {
 	for(m_iter = m.begin(); m_iter != m.end(); ++m_iter) {
 		cout << m_iter->first << "\t" << m_iter->second.first << endl;
 	}
 }

 bool symtab::exists(string symbol) {
 	if(m.find(symbol) == m.end()) {
 		return false;
 	}
 	return true;
 }
