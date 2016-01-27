module reg32(
	input [31:0] D,
	input [3:0] byteenable,
	input reset_n,
	input clock,
	output [31:0] Q
);
//////////////////////////////////////
	reg [31:0] intern_reg;

/////////////////////////////////////
	
	assign Q = intern_reg;
	
////////////////////////////////////
	
	always @ (posedge clock)
	begin
	
		if (~reset_n) begin
			intern_reg <= 32'd0;
		end
		else begin
	
		case (byteenable)
			'b1111: intern_reg 			<= D;
			'b0011: intern_reg[15:0] 	<= D[15:0];
			'b1100: intern_reg[31:16] 	<= D[31:16];
			'b0001: intern_reg[7:0] 	<= D[7:0];
			'b0010: intern_reg[15:8] 	<= D[15:8];
			'b0100: intern_reg[23:16] 	<= D[23:16];
			'b1000: intern_reg[31:24] 	<= D[31:24];
			default:begin
				intern_reg<= Q;
			end// default		
		endcase// case
		end // else
	end// always
//////////////////////////////////////
endmodule

