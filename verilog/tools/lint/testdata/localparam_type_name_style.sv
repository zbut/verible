// Expected localparam type name, "Hello_World" to follow lower_snake_case naming convention and end with _t.
class foo;
    // verilog_lint: waive parameter-name-prefix
    localparam type Hello_World = logic;
endclass
