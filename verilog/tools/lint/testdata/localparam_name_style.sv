// Expected localparam name, "Hello_World" to follow UpperCamelCase
// naming convention.
class foo;
// verilog_lint: waive parameter_name_prefix
  localparam int Hello_World = 1;
endclass
