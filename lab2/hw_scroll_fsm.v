module hw_scroll_fsm(reset, clock, hexs);
	input reset, clock;
	output reg [41:0] hexs = {42{1'b1}};
		
	reg [41:0] nextHexs;
	reg [3:0] index = 0, nextIndex = 0;
	reg [1:0] state = 0, nextState = 0;
	reg Done,Donee;
	reg [27:0] Count = 0;
	reg [27:0] Countt = 0;
	reg [27:0] Max_Count = 'd50_000_000;
	wire [6:0] nextLetter;
	wire [3:0] indexW;
	
	parameter S0 = 0;
	parameter S1 = 2'b01;
	parameter S2 = 2'b10;
	parameter S3 = 2'b11;
	
	findNext FN1(nextIndex, nextLetter);
	
always @(posedge clock, posedge reset) begin
		if (reset) begin
			state <= S0;
			index <= 4'b0;
			hexs <= {42{1'b1}};
			Count <= 0;
			Done <= 0;
			end //if (reset)
		else begin
			state <= nextState;
			index <= nextIndex;
			hexs <= nextHexs;
			Count <= Countt;
			Done <= Donee;
			end // else
	end // always for update
	
always @(*) begin
	case(state)
		S0:begin
			nextState = S1;
			end //S0 case
		S1:begin
			nextState = S2;
			end //S1 case
		S2:begin
			nextState = S3;
			end //S2 case
		S3: begin
			if(Done) begin
				nextState = S1;
				end
			else begin
				nextState = S3;
				end
			end
		default:begin
			nextState = S0;
			end
		endcase//case
	end //always for nextState
	
always @(*) begin
	case(state)
		S0:begin
			nextHexs = {42{1'b1}};
			end//S0 case
		S1:begin
			nextHexs = {hexs[34:0],~nextLetter};
			end//S1 case
		S2:begin
			nextHexs = hexs;
			end//S2 case
		S3:begin
			nextHexs = hexs;
			end
		default:begin
			nextHexs = {42{1'b1}};
			end
		endcase//case
	end //alwas for hexs
	
always @(*) begin
	case(state)
		S0: begin
			nextIndex = 3'b0;
			end//S0 case
		S1: begin
			nextIndex = index;
			end//S1 case
		S2: begin
			if (index == 12) begin
				nextIndex = 4'b0;
				end//if (index)
			else begin
				nextIndex = index + 1'b1;
				end//else
			end//S2 case
		S3: begin
			nextIndex = index;
			end
		default:begin
			nextIndex = 3'b0;
			end
		endcase//case
	end//always for index
	
always @(*) begin
	case (state)
		S0: begin
			Donee = 1'b0;
			end
		S1: begin
			Donee = 1'b0;
			end
		S2: begin
			Donee = 1'b0;
			end
		S3: begin
			if(Count > Max_Count) begin
				Donee = 1'b1;
				end
			else begin
				Donee = 1'b0;
				end
			end
	endcase
end

always @(*) begin
	case(state)
		S0: begin
			Countt = 0;
			end
		S1: begin
			Countt = 0;
			end
		S2: begin
			Countt = 0;
			end
		S3: begin
			if(!Done) begin
				Countt = Count + 1;
				end
			else begin
				Countt = 0;
				end
			end
		endcase
	end
endmodule

	
				
			
	
	