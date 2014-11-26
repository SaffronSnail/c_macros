#include <stdio.h>

//this is the starting tag for code that should be run at compile time
#compiletime
for (int i = 0; i < 3; ++i)
{
//code between vertical bars will be inserted into the resulting program, rather than
//being evaluated at compile time
|unsigned Test#i#(void) //anything inside of a hastag will be evaluated, and it's return value will be inserted into the program
{
  printf("Test #i#\n");
  return #i#;
}
|
}
//this is the ending tag for code that should be run at compile time
#end compiletime

int main(void)
{
  Test0();
  Test1();

  #compiletime
  for (int i = 1; i < 10; ++i)
    if (i % 2)
      |printf("#i# is odd!\n");|
    else
      |printf("#i# is even!\n");|
  #end compiletime
  
  Test2();
        
  return 0;
}

