#include "deposit.h"

#include <QMessageBox>

#include "ui_deposit.h"

Deposit::Deposit(QWidget *parent) : QDialog(parent), ui_(new Ui::Deposit) {
  ui_->setupUi(this);
  setWindowTitle("Deposit calculator");
  setFixedSize(width(), height());
}

Deposit::~Deposit() { delete ui_; }

void Deposit::on_calc_deposit_clicked() {
  bool amount_status, term_status, rate_status, tax_status,
      replenishments_status, withdraws_status, have_error = true;
  QString rub = " \u20BD";
  double deposit_amount =
      ui_->depAmount->toPlainText().toDouble(&amount_status);
  int deposit_term = ui_->depTerm->toPlainText().toDouble(&term_status);
  int deposit_term_type = ui_->depTermPer->currentText() == "Year" ? 12 : 1;
  double deposit_interest_rate =
      ui_->depIntrst->toPlainText().toDouble(&rate_status);
  double deposit_tax_rate = ui_->depTax->toPlainText().toDouble(&tax_status);
  int frequency = ui_->depFrqPay->currentText() == "Once a year" ? 12 : 1;
  bool capitalization = ui_->depCapital->isChecked();
  double replenishments =
      ui_->depMonReplsmnt->toPlainText().toDouble(&replenishments_status);
  double withdraws =
      ui_->depMonWithdraw->toPlainText().toDouble(&withdraws_status);

  if (!amount_status || !term_status || !rate_status || !tax_status ||
      !replenishments_status || !withdraws_status) {
    QString error = "Enter a deposit information correctly";
    QMessageBox::information(this, "ERROR", error);
  } else if (deposit_amount <= 0 || deposit_term <= 0 ||
             deposit_interest_rate < 0 || replenishments < 0 || withdraws < 0) {
    QString error = "Enter a deposit data more than 0";
    QMessageBox::information(this, "ERROR", error);
  } else if (deposit_tax_rate < 0 || deposit_tax_rate > 100) {
    QString error = "Enter a deposit tax rate correctly";
    QMessageBox::information(this, "ERROR", error);
  } else if (deposit_term * deposit_term_type > 240) {
    QString error = "Enter a deposit term less or equals than 20 years";
    QMessageBox::information(this, "ERROR", error);
  } else {
    have_error = false;
    deposit_input_data_.deposit_amount = deposit_amount;
    deposit_input_data_.deposit_term = deposit_term;
    deposit_input_data_.deposit_term_type = deposit_term_type;
    deposit_input_data_.deposit_interest_rate = deposit_interest_rate;
    deposit_input_data_.deposit_tax_rate = deposit_tax_rate;
    deposit_input_data_.frequency = frequency;
    deposit_input_data_.capitalization = capitalization;
    deposit_input_data_.replenishments = replenishments;
    deposit_input_data_.withdraws = withdraws;

    deposit_controller_.SetInputData(deposit_input_data_);
    deposit_controller_.Calculate();
    deposit_output_data_ = deposit_controller_.GetOutputData();
  }
  QString total_interest_str =
      QString::number(deposit_output_data_.total_interest, 'f', 2) + rub;
  QString total_tax_str =
      QString::number(deposit_output_data_.total_tax, 'f', 2) + rub;
  QString total_balance_str =
      QString::number(deposit_output_data_.total_balance, 'f', 2) + rub;

  if (total_interest_str.startsWith("nan") || total_tax_str.startsWith("nan") ||
      total_balance_str.startsWith("nan") ||
      total_interest_str.startsWith("inf") || total_tax_str.startsWith("inf") ||
      total_balance_str.startsWith("inf") ||
      total_interest_str.startsWith("-inf") ||
      total_tax_str.startsWith("-inf") ||
      total_balance_str.startsWith("-inf") ||
      deposit_output_data_.total_interest < 0 ||
      deposit_output_data_.total_tax < 0 ||
      deposit_output_data_.total_balance < 0)
    have_error = true;

  if (have_error) {
    ui_->totalInterest->setText("Error");
    ui_->totalTax->setText("Error");
    ui_->endBalance->setText("Error");
  } else {
    SetTextToOutStyle(total_interest_str, total_tax_str, total_balance_str);
    ui_->totalInterest->setText(total_interest_str);
    ui_->totalTax->setText(total_tax_str);
    ui_->endBalance->setText(total_balance_str);
  }
}

void Deposit::SetTextToOutStyle(QString str1, QString str2, QString str3) {
  int input_string_max_lenght = MaxLenght(str1, str2, str3);
  int font_size = 208 / input_string_max_lenght / 0.68;
  font_size = font_size > 28 ? 28 : font_size;
  QString output_credit_style =
      "color: #475679;background-color: rgba(0, 0, 0, 0);padding-left: "
      "3px;text-align: center;font-size: ";
  output_credit_style += QString::number(font_size);
  output_credit_style += "px;";
  ui_->totalInterest->setStyleSheet(output_credit_style);
  ui_->totalTax->setStyleSheet(output_credit_style);
  ui_->endBalance->setStyleSheet(output_credit_style);
}

int Deposit::MaxLenght(QString str_1, QString str_2, QString str_3) {
  int max = str_2.length() > str_1.length() ? str_2.length() : str_1.length();
  if (str_3.length() > max) max = str_3.length();
  return max;
}
