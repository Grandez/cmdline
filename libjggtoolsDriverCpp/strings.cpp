#pragma once
#include <iostream>
#include "strings.hpp"

using namespace jggtools;

bool KO() {
  cout << "KO\n";
  return true;
}
void OK() {
  cout << "OK\n";
}
bool testStrings() {
   cout << "Checking strings\n";
   cout << "\tconstructor\t"; 
   sstring str(" pepe ");
   if (str.length() != 6) return KO();
   OK();
   cout << "\tltrim\t"; 
   str.ltrim();
   if (str != "pepe ") return KO();
   OK();
   str = " pepe ";
   cout << "\trtrim\t"; 
   str.rtrim();
   if (str != " pepe") return KO();
   OK();
   str = " pepe ";
   cout << "\ttrim\t"; 
   str.trim();
   if (str != "pepe") return KO();
   OK();

   return false;
}
