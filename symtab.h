/* symtab.h
 * TEAM TEXAS
 * Quoc Lien, Jose Paterno, Jessica To, Bryant To.
 * masc1216
 * prog3
 * CS530, Spring 2014
*/

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include "symtab_exception.h"

#ifndef SYMTAB_H_
#define SYMTAB_H_

 using namespace std;

 class symtab {
 public:
 	// Takes a SIC/XE label and adds its value into a map
 	// with the label as the key. Bool type is for relative or absolute.
 	void add(string symbol, string value, bool type);

 	// Takes a SIC/XE label as a key and returns its corresponding value.
 	string get_value(string symbol);

 	void print_table();

 private:
 	map<string,pair<string, bool> > m;
 	map<string,pair<string, bool> >::iterator m_iter;

 	bool exists(string symbol);
 };

 #endif
