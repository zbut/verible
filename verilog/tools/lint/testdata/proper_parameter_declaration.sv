// 'parameters' should only be declared within packages or parameterized modules/classes.
module proper_parameter_declaration;
    // verilog_lint: waive parameter-name-prefix
    // verilog_lint: waive parameter-name-style
    parameter int Bar = 1;
endmodule
