#include <stdio.h>

//this is the starting tag for code that should be run at compile time
unsigned Test0(void) //anything inside of a hastag will be evaluated, and it's return value will be inserted into the program
{
  printf("Test 0\n");
  return 0;
}

unsigned Test1(void) //anything inside of a hastag will be evaluated, and it's return value will be inserted into the program
{
  printf("Test 1\n");
  return 1;
}

unsigned Test2(void) //anything inside of a hastag will be evaluated, and it's return value will be inserted into the program
{
  printf("Test 2\n");
  return 2;
}



int main(void)
{
  Test0();
  Test1();

  printf("1 is odd!\n");
printf("2 is even!\n");
printf("3 is odd!\n");
printf("4 is even!\n");
printf("5 is odd!\n");
printf("6 is even!\n");
printf("7 is odd!\n");
printf("8 is even!\n");
printf("9 is odd!\n");

  
  Test2();
        
  return 0;
}

