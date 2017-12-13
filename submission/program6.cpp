// Shaya Wolf
// COSC5785 - Compilers   
// Program 6
// program6.cpp
// 12/14/2017

#include<FlexLexer.h>

#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string.h>
#include<iomanip>
#include<vector>

#include "attributes.h"
#include "node.hpp"
#include "symboltable.hpp"
#include "program6.tab.h"

using namespace std;

attributes *atts;
yyFlexLexer myScanner;
vector<Node*> forest;
int Node::maindec = 0;
//int Node::nameCalls = 0;
//bool Node::flagMain = false;

int main() { 
  // Initialize Attributes Struct
  atts = new attributes{0,0,0,""};
  
  cout << endl;
    
  // Make call for Bison
  yyparse();
  
  // Print the Parse Tree
  
  /*
  if(forest.size() > 0) {
    cout << endl << "<Program> -> ";
    for(unsigned int i = 0; i < forest.size(); i++) {
      cout << "<ClassDec> ";
    }
    cout << endl;
    for(unsigned int i = 0; i < forest.size(); i++) {
      cout << endl << "**" << i << "**" << endl;
      forest[i]->printNode();
      delete forest[i];
    }
    cout << endl;
  }
  */
  // Build Symbol Table
  SymbolTable* root = new SymbolTable();
  
  if(forest.size() > 0) {
    for(unsigned int i = 0; i < forest.size(); i++) {
      forest[i]->buildTable(root);
    }
  }
 
  
 
  // Type Check
  if(forest.size() > 0) {
    for(unsigned int i = 0; i < forest.size(); i++) {
      forest[i]->typeCheck();
      //cout << "Correct: " << correct << endl;
    }
  }

  if(Node::maindec == 0) {
    cerr << "Type Error: No valid main declared" << endl;
  }

  // Print Symbol Table
  root->printTable();
  
  // Free Memory
  if(forest.size() > 0) {
    for(unsigned int i = 0; i < forest.size(); i++) {
      delete forest[i];
    }
  }
  delete atts;
  
  return 0 ;
}
