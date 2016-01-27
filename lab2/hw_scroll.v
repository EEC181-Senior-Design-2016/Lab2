module hw_scroll(reset,clock, hexs);
	input reset,clock;
	output reg [41:0] hexs = 42'd0;  //    
	
	
	reg [3:0] index = 4'd0;
	reg [1:0] state = 2'd0;
	wire [7:0] nextLetter;
	wire [3:0] indexW;
	
	localparam S0 = 0; // initial state
	localparam S1 = 1; // show hexs and check counter
	localparam S2 = 2; // set next letter and shift reg
	
	assign indexW = index;
	
	findNext FN1 (indexW, nextLetter); 
	
	always  @ (posedge clock, negedge reset) begin
		if(~reset)begin
			state <= S0;
			index <= 3'd0;
			hexs <= 42'd0;
		end // if reset
		else begin 
		  case (state)
			 S0: begin
			 	state <= S1;
				index <= 3'd0;
				hexs <= 42'd0;
			 end
		    S1: begin 
				hexs <= {hexs[34:0],nextLetter};
				state <= S2;
			 end
			 S2: begin
			 state <= S1;
			   if (index == 4'd12 ) begin index <= 4'd0; end
				else begin index <= index + 4'd1; end
		    end  
		  endcase		
		end // else not reset
	end // always nonblocking
	
endmodule


module findNext(index, letter);
	input [3:0] index;
	output reg [7:0] letter = 8'd0;
	
	localparam H = 8'h076;
	localparam E = 8'h079;
	localparam L = 8'h038;
	localparam O = 8'h03F;
	localparam U = 8'h03E;
	localparam r = 8'h050;
	localparam d = 8'h05E;
	
	always @ (index) begin
	
		case(index)
			0:begin letter = H; end 
			1:begin letter = E; end 
			2:begin letter = L; end 
			3:begin letter = L; end 
			4:begin letter = O; end 
			5:begin letter = 8'd0; end 
			6:begin letter = U; end 
			7:begin letter = U; end 
			8:begin letter = O; end 
			9:	begin letter = r; end 		
			10:begin letter = L; end 
			11:begin letter = d; end 
			12:begin letter = 8'd0; end 
			
		endcase
	end
	

endmodule



