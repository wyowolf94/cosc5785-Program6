##
# Shaya Wolf
# Makefile
# Compilers - Program 6
# 12/14/2017
##

CXX=g++
CXXFLAGS=-std=c++11 -ggdb -Wall
LEX=flex++
LEXFLAGS=--warn
YACC=bison
YACCFLAGS=--report=state -W -d

.PHONY: clean tar

program6: program6.tab.c program6.tab.h program6_lex.cpp program6.cpp \
		attributes.h node.hpp symbol.h symboltable.hpp
	${CXX} ${CXXFLAGS} program6.cpp program6.tab.c program6_lex.cpp \
		attributes.cpp symbol.cpp -o program6

program6.tab.c : program6.y node.hpp attributes.h
	${YACC} ${YACCFLAGS} program6.y

program6_lex.cpp: program6.lpp node.hpp
	${LEX} ${LEXFLAGS} program6.lpp

tar:
	tar -cf Wolf_HW6.tar attributes.cpp attributes.h Makefile node.hpp \
 	program6.cpp program6.lpp program6.y symbol.cpp symbol.h \
	symboltable.hpp readme.txt

clean: 
	/bin/rm -f *.o a.out core.* program6 program6_lex.cpp program6.tab.* \
  Wolf_HW6.tar
