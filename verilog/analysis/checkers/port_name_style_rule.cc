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

#include <set>
#include <string>

#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "common/analysis/lint_rule_status.h"
#include "common/analysis/matcher/bound_symbol_manager.h"
#include "common/analysis/matcher/matcher.h"
#include "common/strings/naming_utils.h"
#include "common/text/symbol.h"
#include "common/text/syntax_tree_context.h"
#include "common/text/token_info.h"
#include "verilog/CST/port.h"
#include "verilog/CST/verilog_matchers.h"
#include "verilog/analysis/descriptions.h"
#include "verilog/analysis/lint_rule_registry.h"
#include "verilog/parser/verilog_token_enum.h"

namespace verilog {
namespace analysis {

using verible::LintRuleStatus;
using verible::LintViolation;
using verible::SyntaxTreeContext;
using Matcher = verible::matcher::Matcher;

// Register PortNameStyleRule.
VERILOG_REGISTER_LINT_RULE(PortNameStyleRule);

static const char kMessage[] = "Port names must be styled with ALL_CAPS";

const LintRuleDescriptor& PortNameStyleRule::GetDescriptor() {
  static const LintRuleDescriptor d{
      .name = "port-name-style",
      .topic = "port-names",
      .desc = "Checks that port names follow ALL_CAPS naming convention.",
  };
  return d;
}

static const Matcher& PortMatcher() {
  static const Matcher matcher(NodekPortDeclaration());
  return matcher;
}

void PortNameStyleRule::HandleSymbol(const verible::Symbol& symbol,
                                     const SyntaxTreeContext& context) {
  verible::matcher::BoundSymbolManager manager;
  if (PortMatcher().Matches(symbol, &manager)) {
    const auto* identifier_leaf =
        GetIdentifierFromModulePortDeclaration(symbol);
    const auto token = identifier_leaf->get();
    const auto name = ABSL_DIE_IF_NULL(identifier_leaf)->get().text();

    if (!verible::IsNameAllCapsUnderscoresDigits(name)) {
      violations_.insert(LintViolation(token, kMessage, context));
    }
  }
}

LintRuleStatus PortNameStyleRule::Report() const {
  return LintRuleStatus(violations_, GetDescriptor());
}

}  // namespace analysis
}  // namespace verilog
