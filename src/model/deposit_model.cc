#include "deposit_model.h"

namespace s21 {
void DepositModel::SetInputData(DepositInputData &data) noexcept {
  input_data_.deposit_amount = data.deposit_amount;
  input_data_.deposit_term = data.deposit_term;
  input_data_.deposit_term_type = data.deposit_term_type;
  input_data_.deposit_interest_rate = data.deposit_interest_rate;
  input_data_.deposit_tax_rate = data.deposit_tax_rate;
  input_data_.frequency = data.frequency;
  input_data_.capitalization = data.capitalization;
  input_data_.replenishments = data.replenishments;
  input_data_.withdraws = data.withdraws;
}

DepositOutputData DepositModel::GetOutputData() noexcept {
  return output_data_;
}

void DepositModel::Calculate() {
  double amount = input_data_.deposit_amount;
  int period = input_data_.deposit_term * input_data_.deposit_term_type;
  double interest = input_data_.deposit_interest_rate * 0.01;
  double tax = input_data_.deposit_tax_rate * 0.01;
  double total_interest = 0;
  double total_tax = 0;
  output_data_.total_interest = 0;
  if (period >= input_data_.frequency) {
    for (int m = 1; m <= period; m++) {
      double buff_of_total_interest = 0, buff_of_total_tax = 0;
      if (input_data_.frequency == 1) {
        buff_of_total_interest = amount * interest / 12;
      } else if (input_data_.frequency == 12 && m % 12 == 0) {
        buff_of_total_interest = amount * interest;
      }
      total_interest += buff_of_total_interest;
      buff_of_total_tax = buff_of_total_interest * tax;
      total_tax += buff_of_total_tax;
      buff_of_total_interest -= buff_of_total_tax;

      if (input_data_.capitalization) amount += buff_of_total_interest;
      amount += input_data_.replenishments;
      amount -= input_data_.withdraws;
    }
  }
  output_data_.total_interest = total_interest;
  output_data_.total_tax = total_tax;
  output_data_.total_balance =
      input_data_.deposit_amount + total_interest - output_data_.total_tax +
      (input_data_.replenishments - input_data_.withdraws) * period;
}

}  // namespace s21
