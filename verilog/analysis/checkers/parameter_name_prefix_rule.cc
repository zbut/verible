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

#include "verilog/analysis/checkers/parameter_name_prefix_rule.h"

#include <set>
#include <string>

#include "absl/strings/match.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "common/analysis/lint_rule_status.h"
#include "common/analysis/matcher/bound_symbol_manager.h"
#include "common/analysis/matcher/matcher.h"
#include "common/strings/naming_utils.h"
#include "common/text/symbol.h"
#include "common/text/syntax_tree_context.h"
#include "common/text/token_info.h"
#include "verilog/CST/parameters.h"
#include "verilog/CST/verilog_matchers.h"
#include "verilog/analysis/descriptions.h"
#include "verilog/analysis/lint_rule_registry.h"
#include "verilog/parser/verilog_token_enum.h"

namespace verilog {
namespace analysis {

using verible::LintRuleStatus;
using verible::LintViolation;
using verible::SyntaxTreeContext;
using verible::matcher::Matcher;

// Register ParameterNamePrefixRule.
VERILOG_REGISTER_LINT_RULE(ParameterNamePrefixRule);

static const char kMessage[] =
    "Use P_ prefix for parmeter definitions "
    "and LP_ for localparam definitions.";

const LintRuleDescriptor& ParameterNamePrefixRule::GetDescriptor() {
  static const LintRuleDescriptor d{
      .name = "parameter_name_prefix",
      .topic = "binary-parameters",
      .desc =
          "Checks that parameter name starts P_ and localparam"
          "name starts with LP_"
  };
  return d;
}

static const Matcher& ParamDeclMatcher() {
  static const Matcher matcher(NodekParamDeclaration());
  return matcher;
}

void ParameterNamePrefixRule::HandleSymbol(
    const verible::Symbol& symbol, const SyntaxTreeContext& context) {
  verible::matcher::BoundSymbolManager manager;
  if (ParamDeclMatcher().Matches(symbol, &manager)) {
    if (IsParamTypeDeclaration(symbol)) return;

    const auto param_decl_token = GetParamKeyword(symbol);

    auto identifiers = GetAllParameterNameTokens(symbol);
    for (const auto& id : identifiers) {
      const auto param_name = id->text();

      if ((param_decl_token == TK_localparam && 
            !absl::StartsWithIgnoreCase(param_name, "lp_")) ||
          (param_decl_token == TK_parameter && 
            !absl::StartsWithIgnoreCase(param_name, "p_")))
        violations_.insert(LintViolation(
            *id, absl::StrCat(kMessage, "  (got: ", param_name, ")"), context));
    }
  }
}

LintRuleStatus ParameterNamePrefixRule::Report() const {
  return LintRuleStatus(violations_, GetDescriptor());
}

}  // namespace analysis
}  // namespace verilog
