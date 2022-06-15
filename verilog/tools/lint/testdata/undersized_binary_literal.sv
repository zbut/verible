module undersized_binary_literal;
    // verilog_lint: waive parameter-name-prefix
    // verilog_lint: waive parameter-name-style
    localparam logic [1:0] Foo = 2'b1;
endmodule
