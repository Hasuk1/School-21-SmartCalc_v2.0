#ifndef CPP3_SMARTCALC_V2_SRC_CREDIT_MODEL_H_
#define CPP3_SMARTCALC_V2_SRC_CREDIT_MODEL_H_

#include <string>
#include <vector>

namespace s21 {
struct CreditInputData {
  double credit_amount;
  int credit_term;
  int credit_term_type;
  double credit_rate;
  std::string credit_payment_type;
};

struct CreditOutputData {
  std::vector<double> month_payment;
  double over_payment;
  double total_payment;
};

class CreditModel {
 public:
  CreditModel() = default;
  ~CreditModel() = default;

  void SetInputData(CreditInputData &data) noexcept;
  CreditOutputData GetOutputData() noexcept;
  void Calculate();

 private:
  CreditInputData input_data_;
  CreditOutputData output_data_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SRC_CREDIT_MODEL_H_
