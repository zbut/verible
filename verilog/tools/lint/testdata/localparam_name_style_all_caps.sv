// fail, as we expect localparam to follow ALL_CAPS naming convention
class foo;
// verilog_lint: waive parameter_name_prefix
  localparam int HelloWorld = 1;  // found Camel case instead
endclass
