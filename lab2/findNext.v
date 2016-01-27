module findNext(index, letter);
	input [3:0] index;
	output reg [6:0] letter = 7'b0;
	
	parameter H = 7'h76;
	parameter E = 7'h79;
	parameter L = 7'h38;
	parameter O = 7'h3F;
	parameter U = 7'h3E;
	parameter r = 7'h50;
	parameter d = 7'h5E;
	
	always @(*) begin
		case(index)
			0:letter = H;
			1:letter = E;
			2:letter = L;
			3:letter = L;
			4:letter = O;
			5:letter = 7'h0;
			6:letter = U;
			7:letter = U;
			8:letter = O;
			9:letter = r;
			10:letter = L;
			11: letter = d;
			12:letter = 7'h0;
			default:letter = 7'h0;
		endcase
	end
endmodule
