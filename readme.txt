Readme.txt
Shaya Wolf

 - I allow a var and a method to have the same name but methods can't
   be overloaded unless they have different parameters
 - The var names print backwards because it wasn't worth making a 
   backwards iterator
 - I don't allow you to add "null", so x = 5+null is bogus. 
 - If you have "return;" in a non-void method, it can't print a line num
   because the production in bison is %empty... so I just return the 
   method it is enclosed in.
 - The Errors don't print in the exact order of the line numbers but it 
   is close. Also, some type errors don't collapse down quite smoothly 
   and problems will print two/three errors for one line. 

   
   Should work -- I am interested to see what you find that doesn't work 
   since there will probably be something. I spent more time on this one
   assignment than my OS final last year :D
   
   