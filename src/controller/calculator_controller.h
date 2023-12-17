#ifndef CPP3_SMARTCALC_V2_SRC_CALCULATOR_CONTROLLER_H_
#define CPP3_SMARTCALC_V2_SRC_CALCULATOR_CONTROLLER_H_

#include <string>

#include "./../model/calculator_model.h"

namespace s21 {
class CalculatorController {
 public:
  CalculatorController() = default;
  ~CalculatorController() = default;

  inline void SetExpersion(const std::string &infix,
                           const long double x) noexcept {
    expression_.SetInfix(infix);
    expression_.SetX(x);
  }

  void Calculate() { expression_.Calculate(); }

  inline long double GetResult() const noexcept {
    return expression_.GetResult();
  }

  inline enum Status GetStatus() const noexcept {
    return expression_.GetStatus();
  }

 private:
  CalculatorModel expression_;

};  // CalculatorController

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SRC_CALCULATOR_CONTROLLER_H_
