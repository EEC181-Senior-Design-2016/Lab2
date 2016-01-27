#define H 0x76
#define E 0x79
#define L 0x38
#define O 0x3F
#define U 0x3E
#define r 0x50
#define d 0x5E
#define nextHex 7
#define KEY0 0x01 
#define KEY1 0x02
#define KEY2 0x04
#define KEY3 0x08
#define PosLimCust 5
#define Mask_44b 0x0FFFFFFFFFFFFF
#define Mask_42b 0x03FFFFFFFFFFFF

int findNextLetter(int *prev)
{
	switch ((*prev)){
		case 0:
			return H;
		case 1:
			return E;
		case 2:
		case 3:
		case 10:
			return L;
		
		case 4:
		case 8:
			return O;
		case 5:
		case 12:
			return 0;
		case 6:
		case 7:
			return U;
		case 9:
			return r;
		case 11:
			return d;
		

	}// case
	
	return 0;
	
}// findNextLetter

void displayHello(
		long long int *curr_disp,
		int *curr_index //stores current position of hello world
){
	(*curr_disp) = (((*curr_disp) << nextHex) + (findNextLetter(&(*curr_index)))) & Mask_44b;

	if((*curr_index) == 12){ //if current character is last character "_" in "hello world_", reset back to "h"
		(*curr_index) = 0;
	}else{	//if not, advance to next character in "hello world"		 
		(*curr_index)++;
	}// chk where in hello string

	return;

}// displayHello


void displayCustom(
		long long int *curr_pattern,
		long long int wrapHex
){
   
  wrapHex = ((*curr_pattern) >> (nextHex * 5)) & 0x07F;
  (*curr_pattern) = (((*curr_pattern) << (nextHex)) + wrapHex) & Mask_42b;
	
	return;
	
}// displayCustom



int main(void)
{
	volatile int * led			= (int *) 0xFF200040; // red LED addr
	volatile int * switchptr	= (int *) 0xFF200030; // SW slider switch addr
	volatile int * keyptr		= (int *) 0xFF200000; // KEYS addr
	volatile int * hexdisp3_0	= (int *) 0xFF200020; // HEX3_0 addr
	volatile int * hexdisp5_4	= (int *) 0xFF200010; // HEX5_4 addr

	int key_val = 0;
	int switch_val_led = 0;
	

	int hex3_0_val = 0;
	int hex5_4_val = 0;
	
	//vars for hello world
	long long int hw_disp = 0;
	int char_index = 0;
	

	//vars for custom
	long long int custom_pattern = 0;
	int custom_wrapHex = 0;
	
	int state = 0; // state 0 = nothing, state 1 = Hello World, state 2 = custom
	int timer = 25000;
  
  	int pause = 0;
	int keyPressed = 0;
	int prev_key = 0;

  	int i = 0;
  	int j = 0;

	while(1)
	{
			
		if(keyPressed){
		switch(key_val){
			case KEY0: //if key0 is pressed
       			 	if (pause == 0){
          				if (state != 1){ //and not already displaying hello world, initialize these variables
            					hw_disp = 0;
            					char_index = 0;
            					state = 1;
          				}else{
            					custom_pattern = (*switchptr);
            					custom_wrapHex = 0;
            					state = 2;
          				}
        			}// if not paused
				break;
			case KEY1:
       				if(pause){
            				pause = 0;
          			}else{
            				pause = 1;
          			}
				break;
			case KEY2:
				if ((pause == 0) && (timer <= 40000)){
					timer = timer + 5000;				
				}
				break;
			case KEY3:
				if ((pause == 0) && (timer >= 10000)){
					timer = timer - 5000;
				}
				break;
			default:
				break;					

		}//switch
		keyPressed = 0;
		}// key is pressed






    if (pause == 0){
      switch(state){
        case 1: //if in state 1, run function "displayHello"
          displayHello(&hw_disp, &char_index);
          hex3_0_val = hw_disp;
          hex5_4_val = hw_disp >> (nextHex * 4);				
          break;
        case 2:
          hex3_0_val = custom_pattern;
          hex5_4_val = custom_pattern >> (nextHex *4);
        
          displayCustom(&custom_pattern, custom_wrapHex);
          break;
        default:
          break;					

      }//switch
    }// if pause
    
    


		*(hexdisp3_0) = hex3_0_val;
		*(hexdisp5_4) = hex5_4_val;

		prev_key = key_val;


    		for(i =0 ; i < timer; i++){
      			for(j=0; j < 10; j++){
				switch_val_led = *(switchptr);
				*(led) = switch_val_led;
				
				key_val = *(keyptr);

				if((key_val != 0) && (prev_key == 0)){
					keyPressed = 1;
					break;
				}// then break out of for loop
      			}// for j
		if(keyPressed){
			break;		
		}
    	}

	}// while 1
}// main

