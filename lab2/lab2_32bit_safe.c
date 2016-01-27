#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_32 4294967295

int main(void)
{

	//volatile int * keyptr		= (int *) 0xFF200000; // KEYS addr
  volatile int * hexledptr = (int *) 0xFF200018;
	
  //int key_val;
  unsigned long long int val_32b = 0;
  char input[12] = "";
  char dummy[256] = "";
  int valid_in = 1;
  int chk_char = 0;
  
  while(1)
  {
    printf("Enter 32-bit decimal integer: ");
    fgets(input, sizeof(input), stdin);
    valid_in = 1;
    ///////////////////////////////////////////////////
    if (strlen(input) > 1){
      for (chk_char = 0; chk_char < strlen(input); chk_char++){
            
          if(input[chk_char] == '\n' || input[chk_char] == '\0'){
            break;
          }// stop when reached enter char
      

          if ( !(isdigit(input[chk_char])) ) {
            printf("ERROR: FOUND NON-NUMERAL CHAR. TRY AGAIN. \n");
            valid_in = 0;
            break;
          }// if not number, return 
      
        }// for check for any non-numerial chars
    }else{
          printf("ERROR: NO INPUT. TRY AGAIN. \n");
          valid_in = 0;
    }// else
    
    fgets(dummy, sizeof(dummy), stdin); // empty leftovers in stdin
    
    if (valid_in){
      val_32b = strtoull (input, NULL, 10);
      
      if (val_32b > MAX_32){
         printf("ERROR: LARGER THAN 32 BITS TRY AGAIN. \n");
      }// if more than 0xffffffff
      else{
        *(hexledptr) = val_32b;
      }
      
    }// if valid input
 
    input[0] = '\0';
 
  }// while 1
 
}// main


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_32 4294967295

int main(void)
{

	//volatile int * keyptr		= (int *) 0xFF200000; // KEYS addr
  volatile int * hexledptr = (int *) 0xFF200018;
	
  //int key_val;
  unsigned long long int val_32b = 0;
  char input[12] = "";
  char dummy[256] = "";
  int valid_in = 1;
  int chk_char = 0;
  
  while(1)
  {
    printf("Enter 32-bit decimal integer: ");
    fgets(input, sizeof(input), stdin);
    valid_in = 1;
    ///////////////////////////////////////////////////
    if (strlen(input) > 1){
      for (chk_char = 0; chk_char < strlen(input); chk_char++){
            
          if(input[chk_char] == '\n' || input[chk_char] == '\0'){
            break;
          }// stop when reached enter char
      

          if ( !(isdigit(input[chk_char])) ) {
            printf("ERROR: FOUND NON-NUMERAL CHAR.\n");
            valid_in = 0;
            break;
          }// if not number, return 
      
        }// for check for any non-numerial chars
    }else{
          printf("ERROR: NO INPUT.\n");
          valid_in = 0;
    }// else
    
    fgets(dummy, sizeof(dummy), stdin); // empty leftovers in stdin
    
    if (valid_in){
      val_32b = strtoull (input, NULL, 10);
      
      if (val_32b > MAX_32){
         printf("ERROR: LARGER THAN 32 BITS.\n");
      }// if more than 0xffffffff
      else{
        *(hexledptr) = val_32b;
      }
      
    }// if valid input
 
    input[0] = '\0';
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    while (1){
        printf("Continue? (0 = no, 1 = yes): ");
    
        fgets(input, sizeof(input), stdin);
        fgets(dummy, sizeof(dummy), stdin); // empty leftovers in stdin
        if ( (strlen(input) != 2) || ((atoi(input) != 0) && (atoi(input) != 1)) ) {
            printf("Not valid. ");
            input[0] = '\0';
        }else if (atoi(input) == 1){
          input[0] = '\0';
          break;
        }else{
          printf("Cya!\n");
          return 0;
        }
    }// while 1
    

    
  }// while 1
 
}// main













