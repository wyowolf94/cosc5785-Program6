
class ClassA
{
  ClassB[] y;
  ClassB bs;
  ClassA(ClassB var1, ClassA var2){}
  void dummymethod()
  {
    return;
  }
}


class ClassB
{
  int myint;
  int[] myintarr;
  int[][] myintarr2;
  ClassA myA1;
  ClassA[][] myAarr2;
  ClassB myB1;
  ClassC myC1;
  
  int main()
  {
    ClassA[] myAarr;
    
    /* Boolean tests*/
    if(1){}
    if(!1){}
    if(+myint){}
    if(-myint){}
    if(myA1.y[5].myint){}
    if((myA1 == null) || (myint == 0) || (myintarr2[5][2] == myintarr2[0][0]))
    /*Arithmetic Operators Tests*/
    if(5 < 4){}
    if(myint > 0){}
    while(myintarr2[1][2] >= myint){}
    myint = myint + 5;
    myint = myint * 2;
    
    /*This tests*/
    this.myint = myint;
    this.myA1.y[2].myA1 = null;
    this.myA1.y[2].myA1 = myA1;
    myA1 = this.myAarr2[0][0];
    
    /*some method call tests*/
    myA1.dummymethod();
    myint = this.mymethod1(myint, myA1);
    myA1 = mymethod2(myAarr2, this.myint);
    myAarr2[mymethod1(myint, myA1)][myint] = myA1;
    myintarr2 = myC1.method2();
    myAarr = myC1.method3();
//     myA1 = mymethod2(myA1, myint); //error no mathcing function
    
    /*new tests*/
    myA1 = new ClassA();
    myA1 = new ClassA(myB1, myAarr2[0][0]);
    myAarr2 = new ClassA[5][];
    myAarr2 = new ClassA[5][myint];
    
    /*Print tests*/
    print(0);
    print(myint);
    print();
    
    return 0;
  }
  
  int mymethod1(int x, ClassA y)
  {
    x = 5;
    mymethod2(myAarr2, myint);
    myint = mymethod1(x, y);
    return x * 2;
  }
  ClassA mymethod2(ClassA[][] myvar1, int myvar2)
  {
    myvar1 = new ClassA[5][];
    myvar1 = new ClassA[mymethod1(myvar2, myA1)][myvar2];
    myA1 = new ClassA();
    if((myvar2 == myvar2))
    {}
    else
    {}
    while(1){}
    myA1 = new ClassA;
  }
}

class ClassC
{
  ClassA myClassA1;
  ClassC myClassC1;
  ClassB myClassB1;
  int myint1;
  ClassC(){
    this.myint1 = 10;
    this.myint1 = this.myint1;
  }
  ClassC(int x){}
  void meth()
  {
    ClassA[][] objArray;
    ClassA myAobj;
    int a;
    
    myClassC1.myClassA1.y[0] = myClassB1;
    
    myClassC1.myClassA1.y[0].myintarr2[4][myint1] = myint1;
    
    objArray = new ClassA[a][5];
    objArray = new ClassA[5][5];
    objArray = new ClassA[a][];
    objArray = new ClassA[5][];
    objArray = new ClassA[a][myAobj.y[0].myint];
    
    myClassA1 = null;
    if(myClassB1.mymethod1(myint1, myClassA1)){}
    if(null == null){}
    if((myClassA1 == null) && (myint1 == 0)){}
    this.myint1 = 0;
    myClassC1 = this;
  }
  
  int[][] method2(){}
  ClassA [] method3(){}
}


