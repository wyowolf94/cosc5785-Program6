// Shaya Wolf
// COSC5785 - Compilers   
// Program 6
// symbol.cpp
// 12/14/2017

#include<string>
#include "symbol.h"

using namespace std;

void printParams(vector<Variable*> params) {
  cout << "(";
  if(params.size() > 0) {
    cout << params[0]->type << " " << params[0]->iden;
    for(unsigned int i = 1; i < params.size(); i++) {
      cout << ", " << params[i]->type << " " << params[i]->iden;
    }
  }
  cout << ")" << endl;
  
  return;
}

string lookupParams(vector<Variable*> params, Variable* var) {
  if(params.size() > 0) {
    for(unsigned int i = 0; i < params.size(); i++) {
      if(params[i]->iden == var->iden) {
        return params[i]->type;
      }
    }
  }
  return INVALIDSYM;
}
