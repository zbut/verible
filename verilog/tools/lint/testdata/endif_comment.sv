package endif_comment;
`ifdef FOOBAR
    // verilog_lint: waive parameter-name-prefix
    parameter int P = 4;
`endif
endpackage
