#include <stdio.h>
#include <string.h>
#include "hw1.h"

int find_length(char* inputString);		// Function to find string length
int main(){
  printf("Hello World\n");
  
  char test0[] = "This is a string.";
  char test1[] = "some NUMmbers12345";
  char test2[] = "Does it reverse \\n\\0\\t correctly?";
  
  printf("Before: \n \
  		String 0: %s\n \
  		String 1: %s\n \
  		String 2: %s\n",
  		test0, test1, test2);
  		 
  reverse_string(test0, (int)strlen(test0));
  reverse_string(test1, (int)strlen(test1));
  reverse_string(test2, (int)strlen(test2));
  
  printf("After: \n \
  		String 0: %s\n \
  		String 1: %s\n \
  		String 2: %s\n",
  		test0, test1, test2);
  		
  return 0;
}


int find_length(char *inputString){
    int length = 0;
    while(inputString[length]!='\0');
    {
        length++;
    }
    return length;
}
