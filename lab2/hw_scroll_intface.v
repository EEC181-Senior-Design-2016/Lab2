module hw_scroll_intface(
input clk,
input reset_n,
output [41:0] hexarray

);

hw_scroll U1 (
.reset(reset_n), 
.clock(clk), 
.hexs(hexarray)
);

endmodule