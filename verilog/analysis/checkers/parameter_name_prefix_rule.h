#ifndef VERIBLE_VERILOG_ANALYSIS_CHECKERS_PARAMETER_NAME_PREFIX_RULE_H_  // NOLINT
#define VERIBLE_VERILOG_ANALYSIS_CHECKERS_PARAMETER_NAME_PREFIX_RULE_H_  // NOLINT

#include <set>
#include <string>

#include "common/analysis/lint_rule_status.h"
#include "common/analysis/syntax_tree_lint_rule.h"
#include "common/text/symbol.h"
#include "common/text/syntax_tree_context.h"
#include "verilog/analysis/descriptions.h"

namespace verilog {
namespace analysis {

// ParameterNamePrefixRule checks that parameters
// name starts with P_ and localparams start with LP_
class ParameterNamePrefixRule : public verible::SyntaxTreeLintRule {
 public:
  using rule_type = verible::SyntaxTreeLintRule;

  static const LintRuleDescriptor& GetDescriptor();

  void HandleSymbol(const verible::Symbol& symbol,
                    const verible::SyntaxTreeContext& context) final;

  verible::LintRuleStatus Report() const final;

 private:
  std::set<verible::LintViolation> violations_;
};

}  // namespace analysis
}  // namespace verilog

// clang-format off
#endif  // VERIBLE_VERILOG_ANALYSIS_CHECKERS_PARAMETER_NAME_PREFIX_RULE_H_  // NOLINT
