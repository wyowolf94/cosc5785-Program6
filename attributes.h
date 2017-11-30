// Shaya Wolf
// COSC5785 - Compilers 
// Program 6
// attributes.h
// 12/14/2017

#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include<iostream>
#include<string.h>

#define COMM 1
#define WSPC 10
#define CHRERR 11
#define WRDERR 12
#define MAXERR 13
#define ERROR 14

using namespace std; 

struct attributes{
  int lNum;
  int cNum;
  int leng;
  string token;
  string value;
};

void updateAtts(int lNum, int cNum, int leng, string token, string value);

#endif
