#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int main(void)
{

  volatile unsigned int* fpga_chip	= (int *) 0xC0000000; 
  volatile unsigned int* fpga_sdram	= (int *) 0xC4000000; 
  volatile unsigned int* hps_chip	= (int *) 0xFFFF0000;
  volatile unsigned int* hps_sdram	= (int *) 0x10000000; 


  
  char input[12] = "";
  char dummy[256] = "";
  int chip_selected = 0;
  unsigned int* chip_addr;
  unsigned int index = 0;
  unsigned int checker;


  while(1)
  {
    while(1){
      printf("FPGA On-Chip:    1\n");
      printf("FPGA SDRAM:      2\n");
      printf("HPS On-Chip:     3\n");
      printf("HPS DDR3 SDRAM:  4\n");
      printf("Choose chip to write to: ");
      fgets(input, sizeof(input), stdin);
      fgets(dummy, sizeof(dummy), stdin); // empty leftovers in stdin
      
      if ( (strlen(input) != 2) || (atoi(input) < 1) || (atoi(input) > 4) ) {
            printf("Not valid.\n\n");
            input[0] = '\0';
      }// not valid input

      else{
         chip_selected = atoi(input);
         break;
      }// valid input

    }// while 1 choosing chip
    
    //printf("CS: %i\n\n", chip_selected);
    
///////////////////////////////////////////
   switch(chip_selected){
	case 1:
	  chip_addr = fpga_chip;
	  break;
	case 2:
	  chip_addr = fpga_sdram;
	  break;
	case 3:
  	  chip_addr = hps_chip;
	  break;
	case 4:
	  chip_addr = hps_sdram;
	  break;
	default:
	  break;
   }

	//printf("Chip_addr = %#X\n", chip_addr);
	//chip_addr++;
	//printf("Chip_addr = %#X\n", chip_addr);

   for(index = 0; index < 8000; index++){
	*chip_addr = index;

	checker = *chip_addr;	

	if(index != checker){
	  printf("OOPS.\n");
	  break;
	}// read and check val

	chip_addr++;

   }//for loop#2

    input[0] = '\0';
  }// while 1
 
}// main

