#include "credit_model.h"

#include <cmath>
#include <string>
#include <vector>

namespace s21 {
void CreditModel::SetInputData(CreditInputData &data) noexcept {
  input_data_.credit_amount = data.credit_amount;
  input_data_.credit_term = data.credit_term;
  input_data_.credit_term_type = data.credit_term_type;
  input_data_.credit_rate = data.credit_rate;
  input_data_.credit_payment_type = data.credit_payment_type;
}

CreditOutputData CreditModel::GetOutputData() noexcept { return output_data_; }

void CreditModel::Calculate() {
  output_data_.month_payment.clear();
  output_data_.total_payment = 0;
  double amount = input_data_.credit_amount;
  double month_rate = (input_data_.credit_rate / 12) * 0.01;
  int term_month = input_data_.credit_term * input_data_.credit_term_type;
  if (input_data_.credit_payment_type == "Annuities") {
    double credit_factor = pow(1 + month_rate, term_month);
    double month_pay =
        amount * (month_rate * credit_factor) / (credit_factor - 1);
    output_data_.month_payment.push_back(month_pay);
    output_data_.total_payment = month_pay * term_month;
  } else if (input_data_.credit_payment_type == "Differentiated") {
    for (int i = 1; i <= term_month; i++) {
      double raw_month_pay = amount / term_month;
      double rate_month_pay = (amount - (i - 1) * raw_month_pay) * month_rate;
      double diff_pay = raw_month_pay + rate_month_pay;
      output_data_.total_payment += diff_pay;
      output_data_.month_payment.push_back(diff_pay);
    }
  }
  output_data_.over_payment = output_data_.total_payment - amount;
}
}  // namespace s21
