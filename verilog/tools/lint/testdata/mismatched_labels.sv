module mismatched_labels(
// verilog_lint: waive port-name-style
  input clk_i
);

always_ff @(posedge clk_i)
  begin : foo
  end : bar // This mismatched label should cause an error

endmodule;
