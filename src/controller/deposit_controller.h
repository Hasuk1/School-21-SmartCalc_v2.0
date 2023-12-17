#ifndef CPP3_SMARTCALC_V2_SRC_DEPOSIT_CONTROLLER_H_
#define CPP3_SMARTCALC_V2_SRC_DEPOSIT_CONTROLLER_H_

#include <string>

#include "./../model/deposit_model.h"

namespace s21 {
class DepositController {
 public:
  DepositController() = default;
  ~DepositController() = default;

  inline void SetInputData(DepositInputData &data) noexcept {
    deposit_.SetInputData(data);
  }

  inline DepositOutputData GetOutputData() noexcept {
    return deposit_.GetOutputData();
  }

  inline void Calculate() { deposit_.Calculate(); }

 private:
  DepositModel deposit_;

};  // CalculatorController

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SRC_DEPOSIT_CONTROLLER_H_
