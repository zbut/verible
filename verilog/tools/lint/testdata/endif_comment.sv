package endif_comment;
`ifdef FOOBAR
// verilog_lint: waive parameter_name_prefix
  parameter int P = 4;
`endif
endpackage
