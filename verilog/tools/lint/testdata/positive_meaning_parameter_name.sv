// Forbid parameter names starting with 'disable', use 'enable' instead.
module positive_meaning_parameter_name #(
    // verilog_lint: waive parameter-name-prefix
    parameter int DISABLE_FOO = 1
);
endmodule
