#include "verilog/analysis/checkers/parameter_name_prefix_rule.h"

#include <initializer_list>

#include "common/analysis/linter_test_utils.h"
#include "common/analysis/syntax_tree_linter_test_utils.h"
#include "common/text/symbol.h"
#include "gtest/gtest.h"
#include "verilog/CST/verilog_nonterminals.h"
#include "verilog/analysis/verilog_analyzer.h"
#include "verilog/parser/verilog_token_enum.h"

namespace verilog {
namespace analysis {
namespace {

using verible::LintTestCase;
using verible::RunLintTestCases;

// Tests that ParameterNamePrefixRule correctly accepts valid names.
TEST(ParameterNamePrefixRuleTest, AcceptTests) {
  const std::initializer_list<LintTestCase> kTestCases = {
      {""},
      {"module foo #(parameter type p_foo_bar_t); endmodule"},
      {"module foo #(parameter type p_foo_bar_t = logic); endmodule"},
      {"module foo; localparam type lp_foo_bar_t; endmodule"},
      {"module foo; localparam type lp_foo_bar_t = logic; endmodule"},
      {"parameter type p_foo_bar_t;"},
      {"parameter type p_foo_bar_t = logic;"},

      // Make sure non-type parameters trigger no violation
      {"module foo; localparam LP_Bar_Hello = 1; endmodule"},
      {"module foo; localparam int LP_Bar_Hello = 1; endmodule"},
      {"module foo; parameter int p__Bar = 1; endmodule"},
      {"module foo #(parameter int p_Bar_1_Hello = 1); endmodule"},
      {"module foo #(int p_Bar_1_Two); endmodule"},
      {"module foo; localparam int lp_bar = 1; "
       "localparam int lp_BarSecond = 2; endmodule"},
      {"module foo; localparam int lp_bar = 1; "
       "localparam int Lp_Bar_Second = 2; endmodule"},
      {"class foo; localparam int lp_helloWorld = 1; endclass"},
      {"class foo #(parameter int p_hello_world = 1); endclass"},
      {"package foo; parameter p_hello__1 = 1; endpackage"},
      {"package foo; parameter p_HELLO_WORLd = 1; endpackage"},
      {"package foo; parameter int p_1Bar = 1; endpackage"},
      {"package foo; parameter int P_HELLO_World = 1; "
       "parameter int p_bar = 2; endpackage"},
      {"parameter int p_HelloWorld_ = 1;"},
      {"parameter P_HelloWorld__ = 1;"},
  };
  RunLintTestCases<VerilogAnalyzer, ParameterNamePrefixRule>(kTestCases);
}

// Tests that ParameterNamePrefixRule rejects invalid names.
TEST(ParameterNamePrefixRuleTest, RejectTests) {
  constexpr int kToken = SymbolIdentifier;
  const std::initializer_list<LintTestCase> kTestCases = {
      {"module foo; localparam ", {kToken, "Bar_Hello"}, " = 1; endmodule"},
      {"module foo; localparam int ", {kToken, "Bar_Hello"}, " = 1; endmodule"},
      {"module foo; parameter int ", {kToken, "__Bar"}, " = 1; endmodule"},
      {"module foo; parameter int ",
       {kToken, "__Foo"},
       " = 1, ",
       {kToken, "__Bar"},
       " = 1; "
       "endmodule"},
      {"module foo; localparam int ",
       {kToken, "__Foo"},
       " = 1, ",
       {kToken, "__Bar"},
       " = 1; "
       "endmodule"},
      {"module foo #(parameter int ",
       {kToken, "Bar_1_Hello"},
       " = 1); endmodule"},
      {"module foo #(int ", {kToken, "Bar_1_Two"}, "); endmodule"},
      {"module foo; localparam int ",
       {kToken, "bar"},
       " = 1; localparam int ",
       {kToken, "BarSecond"},
       " = 2; "
       "endmodule"},
      {"module foo; localparam int ",
       {kToken, "bar"},
       " = 1; localparam int ",
       {kToken, "Bar_Second"},
       " = 2; "
       "endmodule"},
      {"class foo; localparam int ", {kToken, "helloWorld"}, " = 1; endclass"},
      {"class foo #(parameter int ",
       {kToken, "hello_world"},
       " = 1); endclass"},
      {"package foo; parameter ", {kToken, "hello__1"}, " = 1; endpackage"},
      {"package foo; parameter ", {kToken, "HELLO_WORLd"}, " = 1; endpackage"},
      {"package foo; parameter int ", {kToken, "_1Bar"}, " = 1; endpackage"},
      {"package foo; parameter int ",
       {kToken, "HELLO_World"},
       " = 1; parameter int ",
       {kToken, "bar"},
       " = 2; "
       "endpackage"},
      {"parameter int ", {kToken, "HelloWorld_"}, " = 1;"},
      {"parameter ", {kToken, "HelloWorld__"}, " = 1;"},
  };
  RunLintTestCases<VerilogAnalyzer, ParameterNamePrefixRule>(kTestCases);
}  // namespace

}  // namespace
}  // namespace analysis
}  // namespace verilog
