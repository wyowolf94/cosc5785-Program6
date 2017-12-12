// Shaya Wolf
// Program 6
// cosc5785 - Compilers
// 12/14/2017

#ifndef NODE_HPP
#define NODE_HPP

#include<iostream>
#include<string>
#include<vector>
#include "symboltable.hpp"

using std::string;
using std::endl;
using std::ostream;
using std::vector;
using std::cout;
using std::cerr;

// Base Class
class Node 
{
  public:
    static int maindec;  
    //static bool flagMain;  
    vector<Node*> children;
  
    // Constructor
    Node() {
      reset();
      ival = 0;
      dval = 0;
      valid = true;
    }

    // Destructor
    virtual ~Node() {
      for(unsigned int i = 0; i < children.size(); i++) {
        delete children[i]; 
      }
    }

    // Get Functions
    int    getint()   const { return ival; }

    double getdbl()   const { return dval; }

    string getstr()   const { return sval; }
    
    bool   getValid() const { return valid;}
    
    int    getlnum()  const { return lnum; }
 
    //virtual int getmain()  const { return maindec;} 

    // Set Functions
    void setVal(int i)          { ival = i; }

    void setVal(double d)       { dval = d; }

    void setVal(const string s) { sval = s; }

    void setVal(const char * c) { sval = c; }
    
    void setValid(const bool b) { valid = b; }
    
    void setlnum(int l)         { lnum = l; }

    //virtual void setmain(int i)         { maindec = i;}
    
    // Crap code
    virtual string getType() {
      return INVALIDSYM;
    }
    
    virtual Variable* getParam() {
      return 0;
    }
    
    virtual vector<Variable*> getParams() {
      vector<Variable*> no;
      return no;
    }

    virtual int getNum() {
      return -1;
    }

    // Reset
    void reset() {
      lnum = 1;
      cnum = 1;
      sval.clear();
    } 
    
    // Get a Child
    Node* getChild(unsigned index) {
      return children[index];
    }

    // Set a Child
    void setChild(Node *c, unsigned index){
      children[index] = c;
      return;
    }
    
    void addChild(Node *c) {
      if(c != 0) {
        children.push_back(c);
      }
      return;
    }
    
    virtual SymbolTable* getTable(){
      cout << "getTable: BASE CLASS METHOD CALLED" << endl;
      return 0;
    }
    
    virtual void buildTable(SymbolTable* st) {
      cout << "buildTable: BASE CLASS METHOD CALLED" << endl;
      return;
    }
    
    virtual bool typeCheck() {
      cout << "typcheck: BASE CLASS METHOD CALLED" << endl;
      return false;
    }
    
    virtual string typeCheckStr(SymbolTable* parent) {
      cout << "typeCheckStr: BASE CLASS METHOD CALLED" << endl;
      return INVALIDSYM;
    }
    
    virtual string typeCheckMet(SymbolTable* parent, vector<Variable*> args){
      cout << "typeCheckMet: BASE CLASS METHOD CALLED" << endl;
      return INVALIDSYM;
    }

    // Print Node
    virtual void printNode(ostream * out = 0) {
      *out << sval;
      for(unsigned i = 0; i < children.size(); i++) {
        children[i]->printNode(out);
      }
      return;
    }

  protected:
    //vector<Node*> children;

    int lnum;
    int cnum;

    int ival;
    double dval;
    string sval;

    bool valid;

    //static int maindec;
};

//int SymbolTable::maindec = 0;
//int Node::maindec = 0;

///////////////////////////////////////////////////////////////////////////////////

// Node used for all errors so far
class errorNode : public Node 
{
  public:
    errorNode(string er) : Node () {
      errorRed = er;
    } 

    virtual void printNode(ostream * out = 0) {
      cout << endl << errorRed << " -> *** Error Node ***" << endl;
    }
  private:
    string errorRed;
}; 

// plusstar used for the place-holder nodes that don't print anything
class plusstarNode : public Node 
{
  public:
    plusstarNode() : Node () {
      // Nada
    } 
    
    void buildTable(SymbolTable* parent) {
      for(unsigned int i = 0; i < children.size(); i++) {
        children[i]->buildTable(parent);
      }
    }

    virtual void printNode(ostream * out = 0) {
      // Don't print anything
    }
}; 

// classdecNode that goes to class iden classbody
class classdecNode : public Node 
{
  public:
    classdecNode(string i) : Node () {
      id = i;
    } 

    void buildTable(SymbolTable* parent) {
      // Create SymbolTable for Class Declaration
      ClassDec* new_class = new ClassDec(parent, id);
      
      // Add the ClassDec to the parent
      bool check = parent->insert(new_class);
      if(!check){
        cerr << "Type Error: Class " << id << " declared multiple times at " 
             << lnum << endl;
      }
      
      // Call buildTable on the children
      for(unsigned int i = 0; i < children.size(); i++) {
        children[i]->buildTable(new_class);
      }
    }
    
    bool typeCheck() {
      return children[0]->typeCheck(); 
    }
    
    virtual void printNode(ostream * out = 0) {
      cout << endl << "<ClassDec> -> class identifier (" << id << ") <ClassBody>" << endl;
      children[0]->printNode();
    }
  private:
    string id;
}; 

// classbodyNode that goes to { vardecs constdecs methdecs }
class classbodyNode : public Node 
{
  
  public:
    classbodyNode(string t) : Node () {
      type = t;
    } 
    
    void buildTable(SymbolTable* parent) {
      // Create SymbolTable for Class Declaration
      BlockDec* new_classBlock = new BlockDec(parent, "class_");
      new_classBlock->setIden(new_classBlock->getNewName());
      
      // Add the ClassDec to the parent
      bool check = parent->insert(new_classBlock);
      if(!check){
        cerr << "Something went horribly wrong " << endl;
      }
      
      // Call buildTable on the children
      for(unsigned int i = 0; i < children.size(); i++) {
        children[i]->buildTable(new_classBlock);
      }
    }
    
    bool typeCheck() {
      bool collected = true;
      if (type == "vdecs") {
        for(unsigned int i = 0; i < children[0]->children.size(); i++) {
          collected = children[0]->children[i]->typeCheck() && collected;
        }
      } else if (type == "cdecs") {
        for(unsigned int i = 0; i < children[0]->children.size(); i++) {
          collected = children[0]->children[i]->typeCheck() && collected;
        }
      } else if (type == "mdecs") {
        for(unsigned int i = 0; i < children[0]->children.size(); i++) {
          collected = children[0]->children[i]->typeCheck() && collected;
        }
      } else if (type == "vcdecs") {
        for(unsigned int i = 0; i < children[0]->children.size(); i++) {
          collected = children[0]->children[i]->typeCheck() && collected;
        }
        for(unsigned int i = 0; i < children[1]->children.size(); i++) {
          collected = children[1]->children[i]->typeCheck() && collected;
        }
      } else if (type == "cmdecs") {
        for(unsigned int i = 0; i < children[0]->children.size(); i++) {
          collected = children[0]->children[i]->typeCheck() && collected;
        }
        for(unsigned int i = 0; i < children[1]->children.size(); i++) {
          collected = children[1]->children[i]->typeCheck() && collected;
        }
      } else if (type == "vmdecs") {
        for(unsigned int i = 0; i < children[0]->children.size(); i++) {
          collected = children[0]->children[i]->typeCheck() && collected;
        }
        for(unsigned int i = 0; i < children[1]->children.size(); i++) {
          collected = children[1]->children[i]->typeCheck() && collected;
        }
      } else if (type == "vcmdecs") {
        for(unsigned int i = 0; i < children[0]->children.size(); i++) {
          collected = children[0]->children[i]->typeCheck() && collected; 
        }
        for(unsigned int i = 0; i < children[1]->children.size(); i++) {
          collected = children[1]->children[i]->typeCheck() && collected;
        }
        for(unsigned int i = 0; i < children[2]->children.size(); i++) {
          collected = children[2]->children[i]->typeCheck() && collected;
        }
      }
      return collected;
    }

    void printClassBody(string nonterm) {
        cout << "<ClassBody> -> { ";
        for(unsigned int i = 0; i < children[0]->children.size(); i++) {
          cout << "<" << nonterm << "> ";
        }
        cout << "}" << endl;
    }
    
    void printClassBody(string ntone, string nttwo) {
      cout << "<ClassBody> -> { ";
      for(unsigned int i = 0; i < children[0]->children.size(); i++) {
        cout << "<" << ntone << "> ";
      }
      for(unsigned int i = 0; i < children[1]->children.size(); i++) {
        cout << "<" << nttwo << "> ";
      }
      cout << "}" << endl;
    }
    
    void printClassBody() {
      cout << "<ClassBody> -> { ";
      for(unsigned int i = 0; i < children[0]->children.size(); i++) {
        cout << "<VarDec> ";
      }
      for(unsigned int i = 0; i < children[1]->children.size(); i++) {
        cout << "<ConstDec> ";
      }
      for(unsigned int i = 0; i < children[2]->children.size(); i++) {
        cout << "<MethDec> ";
      }
      cout << "}" << endl;
    }
    
    void printChildren(int index) {
        for(unsigned int i = 0; i < children[index]->children.size(); i++) {
          children[index]->children[i]->printNode();
        }
    }

    virtual void printNode(ostream * out = 0) {
      if(type == "empty") {
        cout << "<ClassBody> -> { }" << endl;
      } else if (type == "vdecs") {
        printClassBody("VarDec");
        printChildren(0);
      } else if (type == "cdecs") {
        printClassBody("ConstDec");
        printChildren(0);
      } else if (type == "mdecs") {
        printClassBody("MethDec");
        printChildren(0);
      } else if (type == "vcdecs") {
        printClassBody("VarDec", "ConstDec");
        printChildren(0);
        printChildren(1);
      } else if (type == "cmdecs") {
        printClassBody("ConstDec", "MethDec");
        printChildren(0);
        printChildren(1);
      } else if (type == "vmdecs") {
        printClassBody("VarDec", "MethDec");
        printChildren(0);
        printChildren(1);
      } else if (type == "vcmdecs") {
        printClassBody();
        printChildren(0);
        printChildren(1);
        printChildren(2);
      } else {
        cout << "classbody problem" << endl;
      }
    }
    
  private:
    string type;
}; 

// VarDec Node which just needs to print <VarDec>
class varDecNode : public Node 
{
  public:
    varDecNode(string i) : Node () {
      identifier = i;
      addedChild = false;
    } 
    
    void buildTable(SymbolTable* parent) {
      // Store Parent
      parentTable = parent;
      
      // Create SymbolTable for Class Declaration
      string new_type = children[0]->getType();
      string initVal = "";
      if(new_type == "int") {
        initVal = "0";
      } else {
        initVal = "null";
      }
      Variable* new_var = new Variable{new_type, identifier, initVal, true};
      
      // Store var
      var = new_var;
      
      // Add the ClassDec to the parent
      addedChild = parent->insert(new_var);
      if(!addedChild){ 
        cerr << "Type Error: Duplicate Variable at " << lnum << endl;
      }
    }
    
    bool typeCheck() {
      string temp = var->type;
      unsigned int index = temp.find_first_of("[");
      if(index != string::npos){
        temp = temp.substr(0, index);
      }
      
      if(temp == "int"){
        return true;
      }
      
      SymbolTable* found_type = parentTable->lookup_class(temp);
      if(found_type != 0) {
        return true;
      } else {
        cerr << "Type Error: Invalid Type " << temp << " at " 
             << lnum << endl;
        return false;
      }
    }

    virtual void printNode(ostream * out = 0) {
      cout << endl << "<VarDec> -> <Type> identifier (" 
           << identifier << ") semi" << endl;
      children[0]->printNode();
    }
  private:
    string identifier;
    SymbolTable* parentTable;
    Variable* var;
    bool addedChild;
}; 

// Constructor Declaration node that goes to iden ( paramlist ) block
class constdecNode : public Node 
{
  public:
    constdecNode(string i) : Node () {
      id = i;
    } 
    
    void buildTable(SymbolTable* parent) {
      // Create SymbolTable for Constructor Declaration
      ConstrDec* new_const = new ConstrDec(parent, id);
      
      vector<Variable*> params = children[0]->getParams();
      
      /*for(unsigned int i = 0; i < params.size(); i++) {
        bool check = new_const->insert(params[i]);
        if(!check){
          cerr << "Type Error: Redeclared Parameter at " << lnum << endl;
        }
      }*/
      
      new_const->setParams(params);
        
      // Add the ConstDec to the parent
      bool check = parent->insert(new_const);
      if(!check){
        cerr << "Type Error: Constructor " << id << " declared twice at " 
             << lnum << endl; 
      }
      parentTable = parent;
      
      // Call buildTable on the children
      children[1]->buildTable(new_const);
      
      for(unsigned int i = 0; i < params.size(); i++) {
        bool check = children[1]->getTable()->insert(params[i]);
        if(!check){
          cerr << "Type Error: Redeclared Variable at " << lnum << endl;
        }
      }
    }
    
    bool checkParameters() {
      // Check Parameters
      vector<Variable*> params = children[0]->getParams();
      /*vector<string> names;
      for(unsigned int i = 0; i < params.size(); i++){
        for(unsigned int i = 0; i < names.size(); i++) {
          if(names[i] == params[i]->iden) {
            cerr << "Type Error: Redeclared Parameter at " << lnum << endl;
            return false;
          } else {
            names.push_back(params[i]->iden);
          }
        }
      }*/
      bool collected = true;
      for(unsigned int i = 0; i < params.size(); i++) {
        // get type of each param
        string temp = params[i]->type;
        
        // Parse off the "[]"'s
        unsigned int index = temp.find_first_of("[");
        if(index != string::npos){
          temp = temp.substr(0, index);
        }
        
        // if it is int, the param is good, otherwise lookup in root table
        if(temp != "int"){
          // lookup class
          SymbolTable* found_type = parentTable->lookup_class(temp);
          if(found_type == 0) {
            cerr << "Type Error: Invalid Parameter Type " << temp << " at " 
                 << lnum << endl;
            collected =  false;
          }
        }
      } // end for
      
      
      
      
      return collected; 
    }
    
    bool checkIden() {
      // Get grandparent (should be classdec)
      SymbolTable* grandparent = parentTable->getParent();
      
      // Check the grandparent type
      if(grandparent->getType() != CLASSTYPE) {
        cout << "PROBLEM" << endl;
        return false;
      }
      
      // Check the class name with id
      if(grandparent->getIden() == id) {
        return true;
      }
      
      cerr << "Type Error: Invalid Constructor Name " << id << " at "
           << lnum << endl;
           
      return false;
    }
    
    bool typeCheck() {
      bool cp = checkParameters();
      bool ci = checkIden();
      return children[1]->typeCheck() && cp && ci;
    }

    virtual void printNode(ostream * out = 0) {
      cout << endl << "<ConstDec> -> identifier (" << id
           << ") ( <ParameterList> ) <Block>" << endl;
      children[0]->printNode();
      children[1]->printNode();
    }
  private:
    string id;
    SymbolTable* parentTable;
}; 

// Method Declaration node that goes to resulttype iden ( paramlist ) block
class methoddecNode : public Node 
{
  public:
    methoddecNode(string t, string i) : Node () {
      type = t;
      id = i;
     // flagMain = false;
    } 
   
    void buildTable(SymbolTable* parent) {
      // Create SymbolTable for Method Declaration
      /*if(id == "main" && maindec  ==  0) {
        maindec = 1;
      } else if (id == "main") {
        cerr << "Type Error: Main declared multiple times at " << lnum  << endl;
        //return;
      }*/ 
      //if(!checkMain()) {
      //  return;
      //}

      MethodDec* new_method = new MethodDec(parent, id);
      vector<Variable*> params;
      if(type == "type") {
        new_method->set_returnType(children[0]->getType());
        params = children[1]->getParams();
      } else if (type == "void") {
        new_method->set_returnType(type);
        params = children[0]->getParams();
      } else { 
        cout << "PROBLEM IN METHODDECNODE - BUILDTABLE" << endl;
        new_method->set_returnType(INVALIDSYM);
      }

      new_method->setParams(params);
      
      // Add the MethodDec to the parent
      bool check = parent->insert(new_method);
      if(!check){
        cerr << "Type Error: Method " << id << " declared twice at " 
             << lnum << endl; 
      }
      parentTable = parent;
      
      // Call buildTable on the children
      int childi = -1;
      
      if(type == "type") {
        childi = 2;
      } else if (type == "void") {
        childi = 1;
      } else {
        cout << "PROBLEM IN METHODDECNODE - BUILDTABLE" << endl;
      }
      
      children[childi]->buildTable(new_method);
      for(unsigned int i = 0; i < params.size(); i++) {
        bool check = children[childi]->getTable()->insert(params[i]);
        if(!check){
          cerr << "Type Error: Redeclared Variable at " << lnum << endl;
        }
      }
    }
    
    bool checkParameters() {
      // Get Parameters
      vector<Variable*> params;
      if(type == "void") { 
        params = children[0]->getParams();
      } else if(type == "type") {
        params = children[1]->getParams();
      } else {
        cout << "PROBLEM" << endl;
      }
      
      /*vector<string> names;
      for(unsigned int i = 0; i < params.size(); i++){
        for(unsigned int i = 0; i < names.size(); i++) {
          if(names[i] == params[i]->iden) {
            cerr << "Type Error: Redeclared Parameter at " << lnum << endl;
            return false;
          } else {
            names.push_back(params[i]->iden);
          }
        }
      }*/
      
      bool collected = true;
      for(unsigned int i = 0; i < params.size(); i++) {
        // get type of each param
        string temp = params[i]->type;
        
        // Parse off the "[]"'s
        unsigned int index = temp.find_first_of("[");
        if(index != string::npos){
          temp = temp.substr(0, index);
        }
        
        // if it is int, the param is good, otherwise lookup in root table
        if(temp != "int"){
          // lookup class
          SymbolTable* found_type = parentTable->lookup_class(temp);
          if(found_type == 0) {
            cerr << "Type Error: Invalid Parameter Type " << temp << " at " 
                 << lnum << endl;
            collected =  false;
          }
        }        
      } 
      return collected;
    }
    
    bool checkReturnType() {
      // if it is void it is valid
      if(type == "void") {
        return true;
      } 
      
      // get the return type if it is not void
      string rtype = children[0]->getType();
      
      // parse off the "[]"'s
      unsigned int index = rtype.find_first_of("[");
        if(index != string::npos){
          rtype = rtype.substr(0, index);
        }
      
      // if it is not an int, look it up in root table
      if(rtype != "int"){
        // lookup class
        SymbolTable* found_type = parentTable->lookup_class(rtype);
        if(found_type == 0) {
          cerr << "Type Error: Invalid Return Type " << rtype << " at " 
               << lnum << endl;
          return false;
        }
      }  
      
      return true;
    }
   
    bool checkMain() {
     bool correct  = true;
     if(id == "main" && maindec == 0) {        
        string rtype = children[0]->getType();

        vector<Variable*> params;
        if(type == "void") { 
          params = children[0]->getParams();
        } else if(type == "type") {
          params = children[1]->getParams();
        } else {
          cout << "PROBLEM" << endl;
        }
        int numParams = params.size(); 
        
        if(rtype != "void" && rtype != "int") {
          //if(print){
            cerr << "Type Error: Main can only return 'void' or 'int', not " 
                 << rtype << " at " << lnum << endl;
          //}
          correct = false;
        } 
        
        if(numParams != 0) {
          //if(print){
            cerr << "Type Error: Main called with paramaters at " << lnum << endl;
          //}
          correct = false;
        }

        if(correct) {
          //flagMain = true;
          maindec = 1;
        } //else {
          //return correct;
        //}
      } else  if (id == "main") {
        //if(print){
          cerr << "Type Error: Main declared multiple times at " << lnum << endl;
        //}
        //return false;
        correct = false;
      }
      return correct;
    }

    bool checkName() {
      // Get Grandparent
      SymbolTable* grandparent = parentTable->getParent();

      // Check grandparent Type
      if(grandparent->getType() != CLASSTYPE) {
        cout << "PROBLEM" << endl;
        return false;
      } 
      
      // Check class name with id
      if(grandparent->getIden() == id) {
        cerr << "Type Error: Method can't be named the same as the class at " 
             << lnum << endl;
        return false;
      }
     
      return true;
    }
 
    bool typeCheck() {
      bool cm = checkMain();
      //if(flagMain) {return false;} 
      //bool cm = true;
      bool cp = checkParameters();
      bool cr = checkReturnType();
      bool cn = checkName();

      // Collect returns
      if(type == "type") {
        return children[2]->typeCheck() && cp && cr && cm && cn;
      } else if(type == "void") {
        return children[1]->typeCheck() && cp && cr && cm && cn;
      } else {
        cout << "PROBLEM IN METHODDEC - TYPECHECK" << endl;
        return false;
      }
    }

    virtual void printNode(ostream * out = 0) {
      if(type == "type") {
        cout << endl << "<MethDec> -> <Type> identifier (" << id
             << ") ( <ParameterList> ) <Block>" << endl;
        children[0]->printNode();
        children[1]->printNode();
        children[2]->printNode();
      } else if(type == "void") {
        cout << endl << "<MethDec> -> void identifier (" << id
             << ") ( <ParameterList> ) <Block>" << endl;
        children[0]->printNode();
        children[1]->printNode();
      } else {
        cout << "methdec problem" << endl;
      }
      
    }
  private:
    string type;
    string id;
    SymbolTable* parentTable;
}; 

// paramlistNode that goes to empty or a paramstarNode
class paramlistNode : public Node 
{
  public:
    paramlistNode(string t) : Node () {
      type = t;
    } 

    vector<Variable*> getParams() {
      vector<Variable*> new_paramList;
      
      if (type == "rec") {
        for(unsigned int i = 0; i < children[0]->children.size(); i++) {
          new_paramList.push_back(children[0]->children[i]->getParam());
        }
      }  
      
      return new_paramList;
    }
    
    void printParamList() {
        cout << "<ParameterList> -> ";
        for(unsigned int i = 0; i < children[0]->children.size() - 1; i++) {
          cout << "<Parameter> , ";
        }
        cout << "<Parameter>" << endl;
    }
    
    void printChildren() {
      for(unsigned int i = 0; i < children[0]->children.size(); i++) {
        children[0]->children[i]->printNode();
      }
    }
    
    virtual void printNode(ostream * out = 0) {
      if(type == "empty") {
        cout << "<ParameterList> -> epsilon" << endl;
      } else if (type == "rec") {
        printParamList();
        printChildren();
      } else {
        cout << "paramlist problem" << endl;
      }
    }
  private:
    string type;
}; 

// param node which just goes to a type identifier
class paramNode : public Node 
{
  public:
    paramNode(string i) : Node () {
      id = i;
    } 
    
    Variable* getParam() {
      string new_type = children[0]->getType();
      string initVal = "";
      if(new_type == "int") {
        initVal = "0";
      } else {
        initVal = "null";
      }
      Variable* param = new Variable{new_type,id,initVal,true};
      return param;
    }

    virtual void printNode(ostream * out = 0) {
      cout << endl << "<Parameter> -> <Type> identifier (" << id << ")" << endl;
      children[0]->printNode();
    }
  private:
    string id;
}; 

// argList node that either prints to epsilon or to expList
class arglistNode : public Node 
{
  public:
    arglistNode(string t) : Node () {
      type = t;
    } 
    
    vector<Node*> getArgs(){
      return children[0]->children;
      
     /* vector<Variable*> args;
      
      if(type == "empty") {
        return args;
      } else if (type == "rec") {
        for(unsigned int i = 0; i < children[0]->children.size(); i++) {
          Variable temp{children[0]->children[i]->typeCheckStr(), "", true}
          args.push_back(temp);
        }
        return args;
      } else {
        cout << "arglist error" << endl;
        return args;
      }*/
    }
    
    void printArgList() {
        cout << "<ArgList> -> ";
        for(unsigned int i = 0; i < children[0]->children.size() - 1; i++) {
          cout << "<Expression> , ";
        }
        cout << "<Expression>" << endl;
    }
    
    void printChildren() {
        for(unsigned int i = 0; i < children[0]->children.size(); i++) {
          children[0]->children[i]->printNode();
        }
    }
    
    virtual void printNode(ostream * out = 0) {
      if(type == "empty") {
        cout << "<ArgList> -> epsilon" << endl;
      } else if (type == "rec") {
        printArgList();
        printChildren();
      } else {
        cout << "arglist problem" << endl;
      }
    }
  private:
    string type;
}; 

// Statement Node ... for now just a simple statement
class statementNode : public Node 
{
  public:
    statementNode(string t) : Node () {
      type = t;
    } 
    
    void buildTable(SymbolTable* parent) {
      parentTable = parent;
      if(type == "cond"){
        children[0]->buildTable(parent);
      } else if(type == "while") {
        children[1]->buildTable(parent);
      } else if(type == "block") {
        children[0]->buildTable(parent);
      }
    }
    
    bool typeCheck() {
      if(type == "semi") {
        // <Statement> -> ;
        return true;
      } else if(type == "nameeq") {
        // <Statement> -> <Name> = <Expression> ;
        string name = children[0]->typeCheckStr(parentTable);
        if(name == INVALIDSYM){
          cerr << "Type Error: Unrecognized identifier at " << lnum << endl;
          return false;
        }
        string expression = children[1]->typeCheckStr(parentTable);
        if(expression == INVALIDSYM){
         // cerr << "Type Error: Invalid r-value (expression) "
         //      << " at " << lnum << endl;
          return false;
        }
        
        if((name == "int" && expression == "null") 
          ||(name == "null" && expression == "int")) {
          cerr << "Type Error: Type Mismatch " << name << " != " << expression
               << " at " << lnum << endl;
          return false;
        }
        
        if(name == expression || name == "null" || expression == "null") {
          return true;
        }
        
        cerr << "Type Error: Type Mismatch " << name << " != " << expression
             << " at " << lnum << endl;
        return false;
           
      } else if(type == "namearglist") {
        // <Statement> -> <Name> ( <ArgList> ) ;
       
        vector<Variable*> args;
        if(children[1]->children.size() > 0) {
            for(unsigned int i = 0; i < children[1]->children[0]->children.size(); i++) {
            string paramType = 
              children[1]->children[0]->children[i]->typeCheckStr(parentTable);
            if(paramType == INVALIDSYM){
              return false;
            }
            string initVal = "";
            if(paramType == "int") {
              initVal = "0";
            } else {
              initVal = "null";
            }
            Variable*  temp = new Variable{paramType, "id", initVal, true};
            args.push_back(temp);
          }

        }
        
        string name = children[0]->typeCheckMet(parentTable, args);
        /*for(unsigned int i = 0; i < args.size(); i++){
          delete args[i];
        }*/
        return (name != INVALIDSYM);
      } else if(type == "printarglist") {
        // <Statement> -> print ( <ArgList> ) ;
        if(children[0] != 0 && children.size() > 0 
                            && children[0]->children.size() > 0){ 
          for(unsigned int i = 0; i < children[0]->children[0]->children.size(); i++) {
            string paramType 
              = children[0]->children[0]->children[i]->typeCheckStr(parentTable);
            if(paramType == INVALIDSYM){
              return false;
            }
            if(paramType != "int") {
              cerr << "Type Error: Variable of type " << paramType 
                   << " not allowed in print at " << lnum << endl;
              return false;
            }
          }
        }
        return true;
      }else if(type == "cond") {
        // <Statement> -> <ConditionalStatement>
        return children[0]->typeCheck();
      } else if(type == "while") {
        // <Statement> -> while ( <Expression> ) <Statement>
        string expression = children[0]->typeCheckStr(parentTable);
        bool t = true;
        if(expression != "int"){
          cerr << "Type Error: Expression must resolve to a 1 or 0 at " << lnum << endl;
          t = false;
        }
        return children[1]->typeCheck() && t;
      } else if(type == "optexp") {
        // <Statement> -> return <OptionalExpression> ;
        return children[0]->typeCheckStr(parentTable) != INVALIDSYM;
      } else if (type == "block") {
        // <Statement> -> <Block>
        return children[0]->typeCheck();
      } else {
        cout << endl << "statement problem" << endl;
        return false;
      }
    }
    
    virtual void printNode(ostream * out = 0) {
      cout << endl;
      if(type == "semi") {
        cout << "<Statement> -> ;" << endl;
      } else if(type == "nameeq") {
        cout << "<Statement> -> <Name> = <Expression> ;" << endl;
        children[0]->printNode();
        children[1]->printNode();
      } else if(type == "namearglist") {
        cout << "<Statement> -> <Name> ( <ArgList> ) ;" << endl;
        children[0]->printNode();
        children[1]->printNode();
      } else if(type == "printarglist") {
        cout << "<Statement> -> print ( <ArgList> ) ;" << endl;
        children[0]->printNode();
      }else if(type == "cond") {
        cout << "<Statement> -> <ConditionalStatement>" << endl;
        children[0]->printNode();
      } else if(type == "while") {
        cout << "<Statement> -> while ( <Expression> ) <Statement>" << endl;
        children[0]->printNode();
        children[1]->printNode();
      } else if(type == "optexp") {
        cout << "<Statement> -> return <OptionalExpression> ;" << endl;
        children[0]->printNode();
      } else if (type == "block") {
        cout << "<Statement> -> <Block>" << endl;
        children[0]->printNode();
      } else {
        cout << endl << "statement problem" << endl;
      }
    }
  private:
    string type;
    SymbolTable* parentTable;
};

// ConditionalStatementNode goes to an if statement or an if-else statement
class condstatementNode : public Node 
{
  public:
    condstatementNode(string t) : Node () {
      type = t;
    } 

    void buildTable(SymbolTable* parent){
      parentTable = parent;
      if(type == "if"){
        children[1]->buildTable(parent);
      } else if(type == "if-else"){
        children[1]->buildTable(parent);
        children[2]->buildTable(parent);
      }
    }
    
    bool typeCheck() {
      if(type == "if") {
        string exp = children[0]->typeCheckStr(parentTable);
        bool t = true;
        if(exp != "int"){
          cerr << "Type Error: Expression must resolve to a 1 or 0 at " << lnum << endl;
          t = false;
        }
        bool stmt = children[1]->typeCheck();
        return stmt && t;
      } else if (type == "if-else") {
        string exp = children[0]->typeCheckStr(parentTable);
        bool t = true;
        if(exp != "int"){
          cerr << "Type Error: Expression must resolve to a 1 or 0 at " << lnum << endl;
          t = false;
        }
        bool stmt1 = children[1]->typeCheck();
        bool stmt2 = children[2]->typeCheck();
        return stmt1 && stmt2 && t;
      } else { 
        cout << "cond statement prob" << endl;
        return false;
      }
    }
    
    virtual void printNode(ostream * out = 0) {
      if(type == "if") {
        cout << "<ConditionalStatement> -> if ( <Expression> ) <Statement>" << endl;
        children[0]->printNode();
        children[1]->printNode();
      } else if(type == "if-else") {
        cout << "<ConditionalStatement> -> if ( <Expression> ) <Statement> " 
             << "else <Statement>" << endl;
        children[0]->printNode();
        children[1]->printNode();
        children[2]->printNode();
      } else {
        cout << "conditional statement problem" << endl;
      }
    }
  private:
    string type;
    SymbolTable* parentTable;
};

// Block Node goes to any number of vardecs followed by any number of statements
class blockNode : public Node 
{
  public:
    blockNode(string t) : Node () {
      type = t;
    } 
    
    void printBlock(string nonterm) {
      cout << "<Block> -> { ";
      for(unsigned int i = 0; i < children[0]->children.size(); i++) {
        cout << "<" << nonterm << "> ";
      }
      cout << "}" << endl;
    }
    
    void buildTable(SymbolTable* parent) {
      // Create SymbolTable for Block
      BlockDec* new_block = new BlockDec(parent, "block_");
      new_block->setIden(new_block->getNewName());
      
      // Add the Block to the parent
      bool check = parent->insert(new_block);
      if(!check){
        cerr << "Something went horribly wrong " << endl;
      }
      
      // Call buildTable on the children
      for(unsigned int i = 0; i < children.size(); i++) {
        children[i]->buildTable(new_block);
      }
      
      thisTable = new_block;
    }
    
    SymbolTable* getTable(){
      return thisTable;
    }
    
    bool typeCheck() {
      bool collected = true;
      if(type == "empty") {
        collected = true;
      } else if (type == "locvardecs") {
        for(unsigned int i = 0; i < children[0]->children.size(); i++) {
          collected = children[0]->children[i]->typeCheck() && collected;
        }
      } else if (type == "statements") {
        for(unsigned int i = 0; i < children[0]->children.size(); i++) {
          collected = children[0]->children[i]->typeCheck() && collected;
        }
      } else if (type == "both") {
        for(unsigned int i = 0; i < children[0]->children.size(); i++) {
          collected = children[0]->children[i]->typeCheck() && collected;
        }
        for(unsigned int i = 0; i < children[1]->children.size(); i++) {
          collected = children[1]->children[i]->typeCheck() && collected;
        }
      } else {
        cout << "PROBLEM" << endl;
        collected = false;
      }
      return collected;
    }
    
    void printBlock() {
        cout << "<Block> -> { ";
        for(unsigned int i = 0; i < children[0]->children.size(); i++) {
          cout << "<LocalVarDec> ";
        }
        for(unsigned int i = 0; i < children[1]->children.size(); i++) {
          cout << "<Statement> ";
        }
        cout << "}" << endl;
    }
    
    void printChildren(int index) {
        for(unsigned int i = 0; i < children[index]->children.size(); i++) {
          children[index]->children[i]->printNode();
        }
    }

    virtual void printNode(ostream * out = 0) {
      cout << endl;
      if(type == "empty") {
        cout << "<Block> -> { }" << endl;
      } else if (type == "locvardecs") {
        printBlock("LocalVarDec");
        printChildren(0);
      } else if (type == "statements") {
        printBlock("Statement");
        printChildren(0);
      } else if (type == "both") {
        printBlock();
        printChildren(0);
        printChildren(1);
      } else {
        cout << "block problem" << endl;
      }
    }
  private:
    string type;
    SymbolTable* thisTable;
};

// LocalVarDec Node with just prints type identifier;
class locvardecNode : public Node 
{
  public:
    locvardecNode(string i) : Node () {
      id = i;
    } 
    
    void buildTable(SymbolTable* parent) {
      // Create SymbolTable for Class Declaration
      string new_type = children[0]->getType();
      string initVal = "";
      if(new_type == "int") {
        initVal = "0";
      } else {
        initVal = "null";
      }
      Variable* new_var = new Variable{new_type, id, initVal, true};
      
      var = new_var;
      
      // Add the ClassDec to the parent
      bool check = parent->insert(new_var);
      if(!check){
        cerr << "Type Error: Variable " << id << " redeclared at " 
             << lnum << endl;  
      }
      
      parentTable = parent;
    }
    
    bool typeCheck() {
      // Get the type of the variable 
      string temp = var->type;
      
      // Parse the []'s off
      unsigned int index = temp.find_first_of("[");
      if(index != string::npos){
        temp = temp.substr(0, index);
      }
      
      // if it is an int, it is good
      if(temp == "int"){
        return true;
      }
      
      SymbolTable* found_type = parentTable->lookup_class(temp);
      if(found_type != 0) {
        return true;
      } else {
        cerr << "Type Error: Invalid Local Var Type " << temp << " at " 
             << lnum << endl;
        return false;
      }
    }

    virtual void printNode(ostream * out = 0) {
      cout << endl;
      cout << "<LocalVarDec> -> <Type> identifier (" << id << ") ;" << endl;
      children[0]->printNode();
    }
  private:
    string id;
    Variable* var;
    SymbolTable* parentTable;
}; 

// Optional Expression Node that goes to epsilon or exp
class optexpNode : public Node 
{
  public:
    optexpNode(string t) : Node () {
      type = t;
    } 
    
    string typeCheckStr(SymbolTable* parent) {
      if(type == "empty") {
        //return "void";
        string expressionType = "void";
        SymbolTable* enclMethod = parent->getEnclosingMethod();
        string mchammer = enclMethod->getType();
        if(mchammer == CONSTRTYPE) {
          return mchammer;
        }
        string rType = enclMethod->return_type();
        if(expressionType != rType) {
          cerr << "Type Error: Invalid void return type in \"" 
               << rType << " " << enclMethod->getIden() << "\"" 
               << endl;
          return INVALIDSYM;
        }
        return expressionType;
      } else if(type == "exp") {
        string expressionType = children[0]->typeCheckStr(parent);
        SymbolTable* enclMethod = parent->getEnclosingMethod();
        string mchammer = enclMethod->getType();
        if(mchammer == CONSTRTYPE) {
          cerr << "Type Error: Invalid return for constructor at " << lnum 
               << endl;
          return INVALIDSYM;
        }
        string rType = enclMethod->return_type();
        if(expressionType != rType) {
          cerr << "Type Error: Invalid return type at " << lnum << endl;
          return INVALIDSYM;
        }
        return expressionType;
      } else {
        cout << "optional expression problem" << endl;
        return INVALIDSYM;
      }
    }

    virtual void printNode(ostream * out = 0) {
      if(type == "empty") {
        cout << "<OptionalExpression> -> epsilon" << endl;
      } else if (type == "exp") {
        cout << "<OptionalExpression> -> <Expression>" << endl;
        children[0]->printNode();
      } else {
        cout << "optional expression problem" << endl;
      }
    }
  private:
    string type;
}; 

// Expression Op Node where t tells us what kind of expression it is
class expNode : public Node 
{
  public:
    expNode(string t) : Node () {
      expType = t;
      num = -1;
    } 
    
    expNode(string t, string n) : Node () {
      expType = t;
      num = atoi(n.c_str());
    }

    int getNum() { return num; }
    
    string typeCheckStr(SymbolTable* parent) {
      if(expType == "relop") {
        // <Expression> -> <Expression> Relop <Expression>
        string e1 = children[0]->typeCheckStr(parent);
        string e2 = children[2]->typeCheckStr(parent);
        //cout << "!!! (" << e1 << ", " << e2 << ")" << endl;
        if(e1 == INVALIDSYM || e2 == INVALIDSYM) {
          cerr << "Type Error: Invalid Bool Expression (invalid args) at " << lnum << endl;
          return INVALIDSYM;
        }
        if((e1 == "int" && e2 == "null") ||(e1 == "null" && e2 == "int")) {
          cerr << "Type Error: Invalid Bool Expression (int to null) at " << lnum << endl;
          return INVALIDSYM;
        }
        if(e1 == e2 || e1 == "null" || e2 == "null") {
          //cout << "--> int" << endl;
          return "int";
        }
        cerr << "Type Error: Invalid Bool Expression (type mismatch) at " << lnum << endl;
        return INVALIDSYM;
      } else if (expType == "sumop" || expType == "proop") {
        // <Expression> -> <Expression> Sumop/Proop <Expression>
        string e1 = children[0]->typeCheckStr(parent);
        string e2 = children[2]->typeCheckStr(parent);
        if(e1 == INVALIDSYM || e2 == INVALIDSYM) {
          //cerr << "***Type Error: Invalid Expression at " << lnum << endl;
          return INVALIDSYM;
        }
        bool typeCorrect = true;
        if(e1 != e2) {
          cerr << "Type Error: Type Mismatch at " << lnum << endl;
          typeCorrect = false;
        }
        if(e1 != "int" || e2 != "int") {
          cerr << "Type Error: " << children[1]->getType() 
               << " only takes integer arguments "
               << " at " << lnum << endl; 
          //cout << "(" << e1 <<  ", " << e2 << ")" << endl;
          typeCorrect = false;
        }
        if(!typeCorrect) {
          return INVALIDSYM;
        }

        /*if(children[0]->getType() != INVALIDSYM && children[2]->getType() != INVALIDSYM) {
        if(children[1]->getType() == "&&" || children[1]->getType() == "||"){
          if(children[0]->getNum() != 0 && children[0]->getNum() != 1) {
            cerr << "Type Error: LHS of " << children[1]->getType() 
                 << " must be a 0 or 1 at " << lnum << endl;
            typeCorrect = false;
          }
          if(children[2]->getNum() != 0 && children[2]->getNum() != 1) {
            cerr << "Type Error: RHS of " << children[1]->getType() 
                 << " must be a 0 or 1 at " << lnum << endl;
            typeCorrect = false;
          }
        }
        }*/
        if(!typeCorrect) {
          return INVALIDSYM;
        }
        return e1;
      } else if (expType == "unyop") {
        // <Expression> -> Unyop <Expression?"
        return children[1]->typeCheckStr(parent);
      } else if (expType == "name") {
        // <Expression> -> <Name>
        return children[0]->typeCheckStr(parent);        
      } else if (expType == "name paren") {
        // <Expression> -> <Name> (<ArgList>)
        vector<Variable*> args;
        if(children[1]->children.size() > 0){
          for(unsigned int i = 0; i < children[1]->children[0]->children.size(); i++) {
            string paramType = children[1]->children[0]->children[i]->typeCheckStr(parent);
            if(paramType == INVALIDSYM){
              return INVALIDSYM;
            }
            string initVal = "";
            if(paramType == "int") {
              initVal = "0";
            } else {
              initVal = "null";
            }
            Variable*  temp = new Variable{paramType, "id", initVal, true};
            args.push_back(temp);
          }
        }
        
        string name = children[0]->typeCheckMet(parent, args);
        
        /*for(unsigned int i = 0; i < args.size(); i++){
          delete args[i];
        }*/
        return name;
      } else if (expType == "read") {
        // <Expression> -> read ()
        return "int";
      } else if (expType == "newexp") {
        // <Expression> -> <NewExpression>
        return children[0]->typeCheckStr(parent);
      } else if (expType == "paren") {
        // <Expression) -> ( <Expression> )
        return children[0]->typeCheckStr(parent);
      } else if (expType == "null") {
        // <Expression> -> null
        return "null";
      } else if (expType == "num") {
        // <Expression> -> Number 
        return "int";
      }  else {
        cout << "expression problem" << endl;
        return INVALIDSYM;
      }
    }

    virtual void printNode(ostream * out = 0) {
      if(expType == "relop" || expType == "sumop"
           || expType == "proop") {
        cout << "<Expression> -> <Expression>";
        children[1]->printNode();
        cout << "<Expression>";
        cout << endl;
        children[0]->printNode();
        children[2]->printNode();
      } else if (expType == "unyop") {
        cout << "<Expression> -> ";
        children[0]->printNode();
        cout << " <Expression>";
        cout << endl;
        children[1]->printNode();
      } else if (expType == "name") {
        cout << "<Expression> -> <Name>" << endl;
        children[0]->printNode();
      } else if (expType == "name paren") {
        cout << "<Expression> -> <Name> (<ArgList>)" << endl;
        children[0]->printNode();
        children[1]->printNode();
      } else if (expType == "read") {
        cout << "<Expression> -> read ()" << endl;
      } else if (expType == "newexp") {
        cout << "<Expression> -> <NewExpression>" << endl;
        children[0]->printNode();
      } else if (expType == "paren") {
        cout << "<Expression) -> ( <Expression> )" << endl;
        children[0]->printNode();
      } else if (expType == "null") {
        cout << "<Expression> -> null" << endl;
      } else if (expType == "num") {
        cout << "<Expression> -> Number (" << num << ")" << endl;
      }  else {
        cout << "expression problem" << endl;
      }
    }
  private:
    string expType;
    int num;
}; 

// NewExpression node 
class newexpNode : public Node 
{
  public:
    newexpNode(string t) : Node () {
      type = t;
      id = "";
    }
    
    newexpNode(string t, string i) : Node () {
      type = t;
      id = i;
    } 
    
    string typeCheckStr(SymbolTable* parent) {
      if(type == "parens") {
        // Check the classes for identifier
        SymbolTable* idenClass = parent->lookup_class(id);
        if(idenClass == 0) {
          cerr << "Type Error: Invalid Identifier " << id << " at " 
               << lnum << endl;  
          return INVALIDSYM;
        }
        
        vector<Variable*> args;
        if(children[0]->children.size() != 0) {
          for(unsigned int i = 0; i < children[0]->children[0]->children.size(); i++) {
            string paramType = children[0]->children[0]->children[i]->typeCheckStr(parent);
            string initVal = "";
            if(paramType == "int") {
              initVal = "0";
            } else {
              initVal = "null";
            }
            Variable* temp = new Variable {paramType, "id", initVal, true};
            args.push_back(temp);
          }
        }

        if(args.size() == 0) {
          return id;
        }
        
        SymbolTable* tempTable = new ConstrDec(idenClass,id);
        ((ConstrDec*)tempTable)->setParams(args);
        
        string ctype = idenClass->getBlockChild()->lookup_children(tempTable);
        if(ctype == INVALIDSYM){
          cerr << "Type Error: No matching constructor in " << id << " at "
               << lnum << endl;
        }
        
        /*for(unsigned int i = 0; i < args.size(); i++){
          delete args[i];
        }*/
        //delete tempTable;
        return id;
      } else if(type == "empty") {
        return children[0]->getType();
      } else if(type == "bracks") {
        string simpType = children[0]->getType();
        
        if(simpType == INVALIDSYM){
          cerr << "Type Error: Invalid type " << simpType << " at " 
               << lnum << endl;
          return INVALIDSYM;
        }
        
        if(simpType != "int"){
          SymbolTable* idenClass = parent->lookup_class(simpType);
          if(idenClass == 0) {
            cerr << "Type Error: Invalid type " << simpType << " at " 
                 << lnum << endl;  
            return INVALIDSYM;
          }
        }   
        
        if(children[1]->children.size() > 0 &&  children[2]->children.size() > 1) {
          cerr << "Type Error: Only one empty bracket allowed in new expression at "
               << lnum << endl;
          return INVALIDSYM;
        }       
 
        unsigned int total = children[1]->children.size() + 
                             children[2]->children.size();
        for(unsigned int i = 0; i < total; i++) {
          simpType = simpType + "[]";
        }
        
        string expType = "";
        for(unsigned int i = 0; i < children[1]->children.size(); i++) {
          expType = children[1]->children[i]->typeCheckStr(parent);
          
          if(expType != "int") {
            cerr << "Type Error: Invalid Type (does not evaluate to [int]) " 
                 << simpType  << " at " << lnum << endl;
            return INVALIDSYM;
          }
        }
        
        return simpType;
      } else {
        cout << "new exp problem" << endl;
        return INVALIDSYM;
      }
    }
    
    void printNewExp() {
        cout << "<NewExpression> -> new <SimpleType> ";
        for(unsigned int i = 0; i < children[1]->children.size(); i++) {
          cout << "[<Expression>] ";
        }
        for(unsigned int i = 0; i < children[2]->children.size(); i++) {
          cout << "[] ";
        }
        cout << endl;
    }
    
    void printChildren(int index) {
        for(unsigned int i = 0; i < children[index]->children.size(); i++) {
          children[index]->children[i]->printNode();
        }
    }

    virtual void printNode(ostream * out = 0) {
      if(type == "parens") {
        cout << "<NewExpression> -> new identifier (" << id 
             << ") ( <ArgList> )" << endl;
        children[0]->printNode();
      } else if(type == "empty") {
        cout << "<NewExpression> -> new <SimpleType>" << endl;
        children[0]->printNode();
      } else if(type == "bracks") {
        printNewExp();
        children[0]->printNode();
        printChildren(1);
        printChildren(2);
      } else {
        cout << "new expression problem" << endl;
      }
    }
  private:
    string type;
    string id;
}; 


// Name Node
class nameNode : public Node 
{
  public:
    nameNode(string t, string i) : Node () {
      type = t;
      id = i;
    } 
    
    string getFuncName(){
      return id;
    }
    
    string typeCheckMet(SymbolTable* parent, vector<Variable*> args){
      if(type == "this"){
          // Check the classes for identifier
        SymbolTable* idenClass = parent->getEnclosingClass();
        if(idenClass == 0) {
          cerr << "Type Error: Invalid Identifier " << id << " at " 
               << lnum << endl;  
          return INVALIDSYM;
        }
        
        if(args.size() == 0) {
          return idenClass->getIden();
        }
        
        SymbolTable* tempTable = new ConstrDec(idenClass,id);
        ((ConstrDec*)tempTable)->setParams(args);
        
        string ctype = idenClass->lookup_children(tempTable);
        if(ctype == INVALIDSYM){
          cerr << "Type Error: No matching constructor in " << id << " at "
               << lnum << endl;
        }
        
        //delete tempTable;
        return idenClass->getIden();
        
      } else if (type == "dotid"){
        string nameType = children[0]->typeCheckStr(parent);
        if(nameType == INVALIDSYM){
          return INVALIDSYM;
        }
        
        SymbolTable* nameClass = parent->lookup_class(nameType);
        if(nameClass == 0) {
          cerr << "Type Error: Invalid type " << nameType 
               << " at " << lnum << endl;
          return INVALIDSYM;
        }
 
         // Lookup Id in nameClass
        SymbolTable* tempTable = new MethodDec(parent,id);
        ((MethodDec*)tempTable)->setParams(args);

        string found = nameClass->getBlockChild()->lookup_children(tempTable);
        if(found == INVALIDSYM) {
          cerr << "Type Error: Invalid Method " << id 
               << " for class " << nameClass->getIden()
               << " at " << lnum << endl;
          
        }
        
        //delete tempTable;
        return found;
      } else if (type == "exp"){
        cerr << "Type Error: Expression error wtih " << id << " at " << lnum << endl;
        return INVALIDSYM;
      } else if (type == "id") {
        if(id == "main" || id == "Main") {
          cerr << "Type Error: Invalid call to main at " << lnum << endl;
          return INVALIDSYM;
        }
        string nameType = parent->getEnclosingClass(parent);

        if(nameType == INVALIDSYM){
          //cerr << "Type Error: *** " << lnum << endl; 
          return INVALIDSYM;
        }
                   
        SymbolTable* nameClass = parent->lookup_class(nameType);
        if(nameClass == 0) {
          cerr << "Type Error: Invalid type " << nameType 
               << " at " << lnum << endl;
          return INVALIDSYM;
        }
        
         // Lookup Id in nameClass
        SymbolTable* tempTable = new MethodDec(parent,id);
        ((MethodDec*)tempTable)->setParams(args);

        string found = nameClass->getBlockChild()->lookup_children(tempTable);
        if(found == INVALIDSYM) {
          cerr << "Type Error: Invalid Method " << id 
               << " for class " << nameClass->getIden()
               << " at " << lnum << endl;
        }
        
        //delete tempTable;
        return found;
        
        //return parent->lookup_ancestors(&tempVar);
      }else {
        cout << "Name problem" << endl;
        return INVALIDSYM;
      }
    }
    
    string typeCheckStr(SymbolTable* parent) {
      // return the type of name
      if(type == "this") {
        return parent->getEnclosingClass(parent);
      } else if(type == "id") {
        // Check that the identifier exists
        // Return the type of the identifier
        Variable* tempVar = new Variable{"", id, "null", true};
        string nameCheck = parent->lookup_ancestors(tempVar);
        if(nameCheck == INVALIDSYM) {
          cerr << "Type Error: Invalid identifier " << id << " at " << lnum << endl;
        }
        return nameCheck;
      } else if(type == "dotid") {
        // Get the type of <name> and the class that it is in
        string nameType = children[0]->typeCheckStr(parent);
        if(nameType == INVALIDSYM){
          return INVALIDSYM;
        }
        SymbolTable* nameClass = parent->lookup_class(nameType);
        if(nameClass == 0) {
          cerr << "Type Error: Invalid type " << nameType 
               << " at " << lnum << endl;
          return INVALIDSYM;
        }
 
        string initVal = "";
        if(nameType == "int") {
          initVal = "0";
        } else {
          initVal = "null";
        }
        // Lookup Id in nameClass
        Variable tempVar{"", id, initVal, true};
        string found = nameClass->getBlockChild()->lookup_children(&tempVar);
        
        if(found == INVALIDSYM) {
          cerr << "Type Error: Invalid Identifier " << id 
               << " for class " << nameClass->getIden()
               << " at " << lnum << endl;
        }
        
        return found;
      } else if(type == "exp") {
        string name = children[0]->typeCheckStr(parent);
        string exp = children[1]->typeCheckStr(parent);
        if(exp != "int"){
          cerr << "Type Error: Invalid expression (does not evaluate to [int]) at " 
               << lnum << endl;
        }
        
        unsigned int index = name.find_first_of("[");
        if(index != string::npos){
          name = name.substr(0, index);
        }
        return name;
      } else {
        cout << "Name problem" << endl;
        return INVALIDSYM;
      }
    }

    virtual void printNode(ostream * out = 0) {
      cout << "<Name> -> ";
      if(type == "this") {
        cout << "this" << endl;
      } else if (type == "id") {
        cout << "identifier (" << id << ")" << endl;
      } else if (type == "dotid") {
        cout << "<Name> . identifier (" << id << ")" << endl;
        children[0]->printNode();
      } else if (type == "exp") {
        cout << "<Name> [ <Expression> ]" << endl;
        children[0]->printNode();
        children[1]->printNode();
      } else {
        cout << "name problem" << endl;
      }
    }
  private:
    string type;
    string id;
}; 

// Type node where t defines either a simpleType or a 
// recursive type [] 
class typeNode : public Node 
{
  public:
    typeNode(string t) : Node () {
      type = t;
    } 
    
    string getType() {
      if(type == "simpleType") {
        return children[0]->getType();
      } else if(type == "type") {
      return children[0]->getType() + "[]";
      } else {
        cout << "PROBLEM IN TYPE  NODE - GETTYPE()" << endl;
        return INVALIDSYM;
      }
    }

    virtual void printNode(ostream * out = 0) {
      cout << "<Type> -> ";
      if(type == "simpleType") {
        cout << "<SimpleType>" << endl;
        children[0]->printNode();
      } else if (type == "type") {
        cout << "<Type> []" << endl;
        children[0]->printNode();
      } else {
        cout << "type problem" << endl;
      }
    }
  private:
    string type;
}; 

// SimpleType Node which right now is just int
class simpleTypeNode : public Node 
{
  public:
    simpleTypeNode(string t, string i) : Node () {
      type = t;
      id = i;
    } 
    
    string getType() {
      if(type == "int") {
        return type;
      } else if (type == "id") {
        return id;
      } else {
        cout << "PROBLEM IN SIMPLETYPE - GETTYPE" << endl;
        return INVALIDSYM;
      }
    }

    virtual void printNode(ostream * out = 0) {
      if(type == "int") {
        cout << "<SimpleType> -> " << type << endl; 
      } else if (type == "id") {
        cout << "<SimpleType> -> identifier (" << id << ")" << endl;
      } else {
        cout << "simpleType problem" << endl;
      }
    }
  private:
    string type;
    string id;
}; 

// Product Op Node where t tells us what kind of operator it is
class proopNode : public Node 
{
  public:
    proopNode(string t) : Node () {
      type = t;
    } 

    string getType() { return type; }

    virtual void printNode(ostream * out = 0) {
      cout << " " << type << " ";
    }
    
  private:
    string type;
};

// Sum Op Node where t tells us what kind of operator it is
class sumopNode : public Node 
{
  public:
    sumopNode(string t) : Node () {
      type = t;
    } 

    string getType() { return type; }

    virtual void printNode(ostream * out = 0) {
      cout << " " << type << " ";
    }
    
  private:
    string type;
};

// Relation Op Node where t tells us what kind of operator it is
class relopNode : public Node 
{
  public:
    relopNode(string t) : Node () {
      type = t;
    } 

    virtual void printNode(ostream * out = 0) {
      cout << " " << type << " ";
    }
    
  private:
    string type;
}; 

// Unary Op Node where t tells us what kind of operator it is
class unyopNode : public Node 
{
  public:
    unyopNode(string t) : Node () {
      type = t;
    } 

    virtual void printNode(ostream * out = 0) {
      cout << type;
    }
    
  private:
    string type;
};

#endif
