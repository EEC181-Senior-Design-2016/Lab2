#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

static inline unsigned int getCycles ()
{
unsigned int cycleCount;
// Read CCNT register
asm volatile ("MRC p15, 0, %0, c9, c13, 0\t\n": "=r"(cycleCount));  
return cycleCount;
}

static inline void initCounters ()
{
// Enable user access to performance counter
asm volatile ("MCR p15, 0, %0, C9, C14, 0\t\n" :: "r"(1));
// Reset all counters to zero
int MCRP15ResetAll = 23; 
asm volatile ("MCR p15, 0, %0, c9, c12, 0\t\n" :: "r"(MCRP15ResetAll));  
// Enable all counters:  
asm volatile ("MCR p15, 0, %0, c9, c12, 1\t\n" :: "r"(0x8000000f));  
// Disable counter interrupts
asm volatile ("MCR p15, 0, %0, C9, C14, 2\t\n" :: "r"(0x8000000f));
// Clear overflows:
asm volatile ("MCR p15, 0, %0, c9, c12, 3\t\n" :: "r"(0x8000000f));
}


int main(void)
{

  volatile unsigned int* fpga_chip	= (int *) 0xC0000000; 
  volatile unsigned int* fpga_sdram	= (int *) 0xC4000000; 
  volatile unsigned int* hps_chip	= (int *) 0xFFFF0000;
  volatile unsigned int* hps_sdram	= (int *) 0x10000000; 


  int fakeCounter = 0;
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
      printf("To Exit type:    0\n");
      printf("Choose chip to write to: ");
      fgets(input, sizeof(input), stdin);
      fgets(dummy, sizeof(dummy), stdin); // empty leftovers in stdin
      
      if ( (strlen(input) != 2) || (atoi(input) < 0) || (atoi(input) > 4) ) {
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
   if(chip_selected == 0){
	printf("Bye!\n");
	break;
   }

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
   }//switch

	//printf("Chip_addr = %#X\n", chip_addr);
	//chip_addr++;
	//printf("Chip_addr = %#X\n", chip_addr);
   initCounters();
   unsigned int time = getCycles();
   for(index = 0xFFFF0000; index < 0xFFFF1F40; index++){
	*chip_addr = index;
	chip_addr++;
   }//for loop#1
   fakeCounter = fakeCounter + 1;
   time = getCycles() - time;
   printf("Elapsed Time for Write: %d cycles\n", time);

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
   }//switch
 
   time = getCycles();
   for(index = 0xFFFF0000; index < 0xFFFF1F40; index++){
	checker = *chip_addr;	

	if(index != checker){
	  printf("OOPS.\n");
	  break;
	}// read and check val

	chip_addr++;

   }//for loop#2
   fakeCounter = fakeCounter + 1;
   time = getCycles() - time;
   printf("Elapsed Time for Read: %d cycles\n", time);

    input[0] = '\0';
  }// while 1
  printf("Program Exited\n");
}// main

