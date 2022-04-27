// Expected localparam name, "Hello_World" to follow UpperCamelCase
// naming convention.
class foo;
    // verilog_lint: waive parameter-name-prefix
    localparam int Hello_World = 1;
endclass
