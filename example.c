#include <stdio.h>

#compiletime
for (int i = 0; i < 3; ++i)
{
|unsigned Test#i#(void)
{
  printf("Test #i#\n");
  return #i#;
}
|
}
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

