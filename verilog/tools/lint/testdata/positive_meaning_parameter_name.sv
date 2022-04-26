// Forbid parameter names starting with 'disable', use 'enable' instead.
// verilog_lint: waive parameter_name_prefix
module positive_meaning_parameter_name #(parameter int DISABLE_FOO = 1); endmodule
