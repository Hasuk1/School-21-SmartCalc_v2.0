#ifndef CPP3_SMARTCALC_V2_SRC_CREDIT_CONTROLLER_H_
#define CPP3_SMARTCALC_V2_SRC_CREDIT_CONTROLLER_H_

#include "./../model/credit_model.h"

namespace s21 {
class CreditController {
 public:
  CreditController() = default;
  ~CreditController() = default;

  inline void SetInputData(CreditInputData &data) noexcept {
    credit_.SetInputData(data);
  }

  inline CreditOutputData GetOutputData() noexcept {
    return credit_.GetOutputData();
  }

  inline void Calculate() { credit_.Calculate(); }

 private:
  CreditModel credit_;

};  // CreditController

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SRC_CREDIT_CONTROLLER_H_