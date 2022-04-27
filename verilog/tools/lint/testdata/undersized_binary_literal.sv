module undersized_binary_literal;
    // verilog_lint: waive parameter-name-prefix
    localparam logic [1:0] Foo = 2'b1;
endmodule
