Readme.txt
Shaya Wolf

Some Small Things

 - I allow a var and a method to have the same name but methods can't
   be overloaded unless they have different parameters
 - The var names print backwards because it wasn't worth making a 
   backwards iterator
 - I don't allow you to do operations on non-int variables
 - If you have "return;" in a non-void method, it can't print a line num
   because the production in bison is %empty... so I just return the 
   method it is enclosed in.
 - The Errors don't print in the exact order of the line numbers but it 
   is close. There is some stuff I type check while building the table 
   because I don't want to add them to the table but still want to print
   and error, so these print first, then the other errors.   
   
