// Copyright 2017-2020 The Verible Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "verilog/analysis/checkers/port_name_style_rule.h"

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

// Tests that PortNameStyleRule correctly accepts valid names.
TEST(PortNameStyleRuleTest, AcceptTests) {
  const std::initializer_list<LintTestCase> kTestCases = {
      {""},
      {"module t (input logic NAME); endmodule;"},
      {"module t (output logic ABC); endmodule;"},
      {"module t (inout logic XYZ_IO); endmodule;"},
      {"module t (input LONG_NAME_I); endmodule;"},
      {"module t (output LONG_ABC_O); endmodule;"},
      {"module t (inout logic LONG_XYZ_IO); endmodule;"},
      {"module t (input logic NAME_NI); endmodule;"},
      {"module t (output  ABC_NO); endmodule;"},
      {"module t (inout logic XYZ_NIO_5); endmodule;"},
      {"module t (input logic NAME_PI); endmodule;"},
      {"module t (output  ABC_PO); endmodule;"},
      {"module t (inout logic XYZ_PIO); endmodule;"},
      {"module t (input logic [7:0] NAME_4_I); endmodule;"},
      {"module t (output  [2:0] ABC_O); endmodule;"},
      {"module t (inout logic [3:0] XYZ_IO); endmodule;"},
      {"module t (input logic [7:0] NAME_NI); endmodule;"},
      {"module t (output  [2:0] ABC_NO); endmodule;"},
      {"module t (inout logic [3:0] XYZ_NIO); endmodule;"},
      {"module t (input [7:0] NAME_PI); endmodule;"},
      {"module t (output logic [2:0] ABC_PO); endmodule;"},
      {"module t (inout [3:0] XYZ_PIO); endmodule;"},
      {"module t (input bit NAME_I); endmodule;"},
      {"module t (output bit ABC_O); endmodule;"},
      {"module t (inout bit XYZ_IO); endmodule;"},
      {"module t (input logic NAME_I,\n"
       "output logic ABC_O,\n"
       "inout logic XYZ_IO,\n"
       "input [7:0] NAMEA_I,\n"
       "output logic [2:0] ABCA_O,\n"
       "inout logic [3:0] XYZA_IO,\n"
       "input bit NAMEB_I,\n"
       "output ABCB_O,\n"
       "inout bit XYZB_IO);\n"
       "endmodule;"},
  };
  RunLintTestCases<VerilogAnalyzer, PortNameStyleRule>(kTestCases);
}

// Tests that PortNameStyleRule rejects invalid names.
TEST(PortNameStyleRuleTest, RejectTests) {
  constexpr int kToken = SymbolIdentifier;
  const std::initializer_list<LintTestCase> kTestCases = {
      // General tests
      {"module t (input ", {kToken, "name"}, "); endmodule;"},
      {"module t (output ", {kToken, "abc"}, "); endmodule;"},
      {"module t (inout ", {kToken, "xyz"}, "); endmodule;"},
      {"module t (input logic [7:0] ", {kToken, "name"}, "); endmodule;"},
      {"module t (output logic [2:0] ", {kToken, "abc"}, "); endmodule;"},
      {"module t (inout logic [3:0] ", {kToken, "xyz"}, "); endmodule;"},
      {"module t (input bit ", {kToken, "name"}, "); endmodule;"},
      {"module t (output bit ", {kToken, "abc"}, "); endmodule;"},
      {"module t (inout bit ", {kToken, "xyz"}, "); endmodule;"},

      {"module t (input ", {kToken, "nAme"}, "); endmodule;"},
      {"module t (output ", {kToken, "Abc"}, "); endmodule;"},
      {"module t (inout ", {kToken, "xyZ"}, "); endmodule;"},
      {"module t (input logic [7:0] ", {kToken, "nAMe"}, "); endmodule;"},
      {"module t (output logic [2:0] ", {kToken, "BCc"}, "); endmodule;"},
      {"module t (inout logic [3:0] ", {kToken, "xy_Z"}, "); endmodule;"},
      {"module t (input bit ", {kToken, "NAMe"}, "); endmodule;"},
      {"module t (output bit ", {kToken, "AB_c"}, "); endmodule;"},
      {"module t (inout bit ", {kToken, "XY_ZW_f"}, "); endmodule;"},
  };
  RunLintTestCases<VerilogAnalyzer, PortNameStyleRule>(kTestCases);
}

}  // namespace
}  // namespace analysis
}  // namespace verilog
