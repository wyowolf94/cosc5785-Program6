

// Typechecking test file
// Iteratively more complex type checking tests


// Type check variable declarations
//----------------------------------------------------------

class A
{
  int integer;
  int[][] int_array;
  B b_obj;
  B[][][] b_obj_array;
  A(B b1, int a)
  {
    int k;
    
  }
}
class B
{
  A a_obj;
  A[][] a_obj_array;
}

// Class Containing Erroneous Variable Declarations
// class C
// {
//   Z z_obj;
//   Z[][] z_obj_array;
//   // Because of the below syntax error, the whole class is thrown out
//   // and so the rest of the process will never check the above errors 
//   // (since this class does not exist in the tree)
//   A[3] a_obj_array_size_3;
//   int[5][6] int_array_size_5_6;
// }


// Type Check Constructors
//---------------------------------------------------------
class D
{
  int k;
  D()
  {
    int j;
  }
  D(int a, int[][] b, B b1, B[][] b2, A a1)
  {
    B[][] b_obj_array;
  }
  
  // Errorneous Consrtuctor Declaration
  // (Note that even if 'Z z' were a datamember rather than a parameter, 
  //    the same error would have been thrown)
  //D(Z z){}
}

// Typecheck Rudementary Expressions In Constructors
//---------------------------------------------------------
class E
{
  int k;
  D d_obj;
  F f_obj;
  B b_obj;
  
  E(int[] j, B b_obj)
  {
    int h;
    int[][] k;
    int[] g;
    A[] a2;
    B[][] b2;
    A a;
    h = 9;
    h = 9+10;
    h = j[5];
    h = this.k;
    h = b_obj.a_obj.integer;
    h = (this.k+b_obj.a_obj_array[6].int_array[78]+j[89]+d_obj.k)*h;
    this.d_obj.k = this.k;
    h = f_obj.foo(j[78]);
    h = f_obj.foo2(j[898]);
    d_obj = new D(h,k,b_obj,b2,a);
    d_obj = new D();
    b_obj.a_obj = new A(b_obj,this.k);
    k[0] = h <= this.k;
    k[0] = h && this.k;
    k[0] = h || this.d_obj.k;
    k[0] = h < this.k;
    k[0] = h > this.k;
    k[0] = h >= this.k;
    k[0] = h == this.k;
    k[0] = !h;
    k[0] = -h + ((h <= k[78]) || this.d_obj.k);
    k[0] = +h + -h;
    h = k[0];
    k[0] = f_obj.foo4(k);
    h = read();
    a = a+null;
    a = null+a;
    k = k+null;
    k = null+k;
    a2 = null+a2;
    a2 = a2+null;
    h = h+null;
    h = h == null;
    k = null;
    this.k = h == j[1]; 
    this.k = h != j[1]; 
  }
  
  // Erroneous Constructor
//   E()
//   {
//     int l;
//     int j;
//     B b_obj;
//     int[][] t;
//     int[][] k;
//     int[] g;
//     
//     // Type mismatch
//     l = this.d_obj;
//     l = t;
//     l = f_obj.foo3();
//     t = l;
//     f_obj.foo3() = l;
//     d_obj = read();
//     g = k+null; 
//     k = g+null; 
//     b_obj = l + j;
//     b_obj = !l;
//     b_obj = l && j;
//     b_obj = l || j;
//     b_obj = l <= j;
//     b_obj = (j*l) > j;
//     b_obj = l == j;
//     b_obj = l != j;
//     b_obj = b_obj == l;
//     
//     // Illegal Return
//     return;
//     
//     // Illegal Use of 'this'
//     this(56);
//     this[45] = l;
//     l = this[45];
//     d_obj = this;
//     
//     // Invalid Operands to Binary Expressions
//     this.k = l < this.d_obj;
//     l = t+6;
//     d_obj = d_obj+d_obj;
//     
//     // Syntax Errors
//     null = k;
//     l = print();
//     print(b_obj);
//     print(1,t);
//     print(t);
//     print(1,2,3,b_obj);
//   }
//   int main(){}
}

class F
{
  int var;
  B[] b_obj_array;
  F(){}
  int foo(int num)
  {
    return num;
  }
  int foo2(int num)
  {
    int k;
    k = num;
    k = k + 45;
    // Not having a return statement is ok
  }
  int [] foo3()
  {
    // Not having a return statement is ok
  }
  int foo4(int[][] k)
  {
    return 0;
  }
  B foo5()
  {
    B b_obj;
    return b_obj;
  }
}

// Typecheck Loops and Conditionals
//------------------------------------------------------
class G
{
  int h;
  int is_good;
  F[] f_obj_array;
  G(int var)
  {
    h = var;
    is_good = 1;
    f_obj_array = new F[10];
  }
  int main(){}
  int method1(int[] x, E e1)
  {
    int i;
    i = 0;
    if(is_good && e1.b_obj.a_obj.integer == 99)
    {
      f_obj_array[0] = new F();
      h = f_obj_array[0].foo2(x[e1.b_obj.a_obj.integer/3]);
    }
    else
    {
      is_good = 0;
      h = 0;
      x[0] = e1.b_obj.a_obj.integer;
    }
    
    if(null == null)
    {
      
    }
    if(!1){}
    if(1){}
    if(+x[0]){}
    if(-x[0]){}
    
    if(e1 == null){}
    if(null == e1){}
    
    if((e1==null)|| x[0]==5 && e1.b_obj.a_obj.integer == 99){}
    
    if(x[0])
    {}
    else
    {}
    
    x[0] = this.f_obj_array[50].foo(h);
    h = this.method1(x,e1);
    
    print(h);
    print(1,2,3,4,5);
    
    while(i != 10)
    {
      f_obj_array[i].b_obj_array[i] = f_obj_array[i].foo5();
    }
    
    return h;
  }
  
  void method2(A a1)
  {
    while(h == 0)
    {
      if(h%3 == 0)
      {
        f_obj_array[h].var = f_obj_array[h].foo2(h);
      }
      f_obj_array[h].var = a1.integer;
    }
  }
}
