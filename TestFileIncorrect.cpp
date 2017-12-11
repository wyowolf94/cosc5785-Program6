class ClassA
{
  int myint1;
  int myint2;
  int[] myintarr1;
  int [][] myintarr2;
  int [][][][][] myintarr5;
  ClassA myClassA1;
  ClassA[] myClassarrA1;
  ClassB myClassB1;
//   ClassA myClassA1; //error var declared twice
//   int myint2; //error var declared twice
  
//   int myClassB1; //error var declared twice
//   ClassNone mybadvar;//error invalid type
  
  ClassA(){
//     return 1; //error invalid return type;
    return;
  }
//   ClassA(){}//error constructor delcared twice
  ClassA(int myvar1, ClassA myvar2){}
//   A(){}//Error constructor name does not match class name
//   ClassA(int var1, ClassNone var2){}//error invalid type classNone
//   ClassA(int var1, int var1){} //error var1 declared twice
  
  /*Main() tests*/
  void main(){} //comment out this line for error no main
  
//   ClassA main(){}//error main must return int or void
//   int main(int myvar1){}//error main takes 0 params
//   ClassA main(ClassA myvar){} //Error return type or param
//   int main(){}//error redeclaration of main
  
  void method1()
  {
    
    /*Type mismatches*/
//     myint1 = null; //error type mismatch
//     if(myint1 == null){}//error type mismatch
//     if(myint1 + null){} //error type mismatch
//     myClassA1 = myint1; //error type mismatch
//     myint1 = myClassA1; //error type mismatch
//     myint1[0] = 5; // myint1 not array type
//     myintarr1[6][5] = 0; //error invalid dimensions on array access

    /* Boolean tests*/
//     if(myClassA1 + null){} //error type does not evaluate to boolean
//     while(myClassA1){}//error expression does not evaluate to boolean
//     if(myClassA1){}//error expression does not evaluate to boolean
//     if(!myClassA1){}//error expression does not evaluate to boolean or not allowed with !
//     if(+myClassA1){}//error expression does not evaluate to boolean
//     if((myClassA1 == null) && (myint1 == null)){}//error expressions not of same tyupe

    
    /*Arithmetic Operators Tests*/
//     if(myClassB1 < myint1){} // error both exps must be int
//     if(myint1 > myClassB1){} // error both exps must be int
//     if(myClassB1 <= myClassA1){} //error bothe exps must be int
//     if(myClassB1 >= myClassB1){} //error bothe exps must be int
//     if(myClassA1 == myClassA1){}//error cant companre to nonnull
//     myClassA1 = myClassA1 + myClassA1; //error both exps must be int
//     myClassA1 = myClassA1 - null; //error both exps must be int
//     myClassB1 = myClassB1 / myClassB1; //error both exps must be int
//     myClassB1 = myint1 + myClassB1; //error both exps must be int or type mismatch
    
    /*other stuff that's not allowed by Buckner's command*/
//     this[5] = null;//error "this" is not an array type
//     this[0] = myClassA1;//error "this" is not an array type
//     this[0][5] = null; //error this is not an array type
//     myintarr1[0](); //error explicit initialization of array value not allowed or direct constructor called
//     myClassarrA1[0]();//error explicit initialization of array value not allowed  direct constructor called
//     myClassarrA1[0](myint1); //error explicit initialization of array value not allowed  direct constructor called
//     myClassA1[0](myint1); //error explicit initialization of array value not allowed  direct constructor called
//     this = myClassA1; //error, this is immutable.

    /*Unary Operators Test*/
//     myClassA1 = +myClassA1;//error expression must be an int
//     myClassA1 = -myClassA1;//error expression must be an int
//     myClassA1 = !myClassA1;//error expression must be an int
    
    /*Undeclared stuff*/
//     method1 = myint1; //error unrecognized identifier method1
//     myint1 = method1; //error unrecognized identifier method1
//     method2(myint1, myint2, myClassB1);//error no matching function call
//     myClassB1.x = 5;//error class b does not have a member named x
//     this.x = 0; //errror x not declared within ClassA

    /* Print Tests*/
//     print(myClassA1); //error not of type int
//     print(5, myint1, myClassA1); //error not of type int

    /*direct constructor calls*/
//     this(); //error direct constructor call
//     this(myint1, myClassA1);//error direct constructor call
//     this(myClassA1);//error direct constructor call
//     myClassA1.myClassB1.ClassB();//error direct constructor call
//     myClassA1.myClassB1.ClassB(myint1);//error direct constructor call
//     ClassA();//error direct constructor call

    /*new tests*/
//     myint1 = new ClassNone();//error classnone dne
//     myint1 = new ClassNone(myint1);//error classnone dne
//     myint1 = new ClassNone[][];//error classnone dne
//     myint1 = new ClassNone[5][];//error classnone dne
//     myintarr1 = new int[myClassA1];//error [doesnt evaluate to int]
//     myintarr1 = new int[new int[]];//error [doesnt evaluate to int]
//     myintarr1[new int] = 5;//error new int not allowed
//     myintarr1[new ClassA()] = 5; //error [doesnt evaluate to int]
//     myint1 = new int;//error new int not allowed
//     myintarr5 = new int[10][2][9][][]; //error invalid number of dimensions allocated
//     myintarr5 = new int[10][2][][][];//error invalid number of dimensions allocated
//     myintarr5 = new int[10][][][][];//error invalid number of dimensions allocated
//     myintarr5 = new int[][][][][];//error invalid number of dimensions allocated
//     myintarr5 = new int[];//error invalid number of dimensions allocated
//     myint1 = new int; //error cannot do this for ints
//     
//     myint1 = myint2 + myClassA1;//errr expressions different types
//     
//     return 1; //error invalid return type
  }
  
  int method2(int x, ClassA y, ClassB c)
  {
//     return; //error does not match func return type
  }
//   int method2(int a, ClassA b, ClassB c){} //error method redeclared
//   void method2(int a, ClassA b, ClassB c){}//error method redeclared
//   int method3(ClassA x, ClassA x){} //error x declared twice
//   ClassNone method4(){} //error invalid type
//   void method5(ClassNone x, ClassA y){}//error invalid type
}

// class ClassA{} //error class declared twice

class ClassB
{
  ClassC myClassC1;
  ClassB(){}
  ClassB(int myvar1){}
}

class ClassC
{
  int x;
}
