#ifndef CPP3_SMARTCALC_V2_SRC_DEPOSIT_MODEL_H_
#define CPP3_SMARTCALC_V2_SRC_DEPOSIT_MODEL_H_

namespace s21 {
struct DepositInputData {
  double deposit_amount;
  int deposit_term;
  int deposit_term_type;
  double deposit_interest_rate;
  double deposit_tax_rate;
  int frequency;
  bool capitalization;
  double replenishments;
  double withdraws;
};

struct DepositOutputData {
  double total_interest;
  double total_tax;
  double total_balance;
};

class DepositModel {
 public:
  DepositModel() = default;
  ~DepositModel() = default;

  void SetInputData(DepositInputData &data) noexcept;
  DepositOutputData GetOutputData() noexcept;
  void Calculate();

 private:
  DepositInputData input_data_;
  DepositOutputData output_data_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SRC_DEPOSIT_MODEL_H_
