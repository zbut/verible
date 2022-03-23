// 'parameters' should only be declared within packages or parameterized modules/classes.
module proper_parameter_declaration;
// verilog_lint: waive parameter_name_prefix
  parameter int Bar = 1;
endmodule
