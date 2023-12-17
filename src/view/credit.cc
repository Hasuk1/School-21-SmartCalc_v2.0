#include "credit.h"

#include <QMessageBox>
#include <QScrollBar>
#include <string>

#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QDialog(parent), ui_(new Ui::Credit) {
  ui_->setupUi(this);
  setWindowTitle("Credit calculator");
  setFixedSize(width(), height());

  ui_->monthPayment->setWordWrapMode(QTextOption::NoWrap);
  ui_->monthPayment->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui_->monthPayment->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

Credit::~Credit() { delete ui_; }

void Credit::on_calc_credit_clicked() {
  bool amount_status, term_status, rate_status, have_error = true;
  QString str1, str2, str3, rub = " \u20BD";
  double credit_amount =
      ui_->creditAmount->toPlainText().toDouble(&amount_status);
  int credit_term = ui_->creditTerm->toPlainText().toInt(&term_status);
  int credit_term_type = ui_->termPer->currentText() == "Year" ? 12 : 1;
  double credit_rate = ui_->rate->toPlainText().toDouble(&rate_status);
  std::string credit_payment_type =
      ui_->creditType->currentText().toStdString();
  if (!amount_status || !term_status || !rate_status) {
    QString error = "Enter a credit information correctly";
    QMessageBox::information(this, "ERROR", error);
  } else if (credit_amount <= 0 || credit_term <= 0 || credit_rate < 0) {
    QString error = "Enter a credit data more than 0";
    QMessageBox::information(this, "ERROR", error);
  } else if (credit_term * credit_term_type > 240) {
    QString error = "Enter a credit term less or equals than 20 years";
    QMessageBox::information(this, "ERROR", error);
  } else {
    have_error = false;
    credit_input_data_.credit_amount = credit_amount;
    credit_input_data_.credit_term = credit_term;
    credit_input_data_.credit_term_type = credit_term_type;
    credit_input_data_.credit_rate = credit_rate;
    credit_input_data_.credit_payment_type = credit_payment_type;
    credit_controller_.SetInputData(credit_input_data_);
    credit_controller_.Calculate();
    credit_output_data_ = credit_controller_.GetOutputData();
    if (credit_payment_type == "Annuities") {
      QString month_pay =
          QString::number(credit_output_data_.month_payment[0], 'f', 2);
      if (!month_pay.endsWith("nan") && !month_pay.endsWith("inf"))
        ui_->monthPayment->setText(month_pay + rub);
      else
        have_error = true;
    } else if ("Differentiated") {
      ui_->monthPayment->clear();
      size_t vector_size = credit_output_data_.month_payment.size();
      for (size_t i = 0; i < vector_size; i++) {
        QString m_number = QString::number(i + 1);
        double month_pay = credit_output_data_.month_payment[i];
        QString m_pay = QString::number(month_pay, 'f', 2);
        QString current_m_pay = ui_->monthPayment->toPlainText();
        QString output_str = current_m_pay + m_number + " - " + m_pay + rub;
        if (i != vector_size - 1) output_str += "\n";
        ui_->monthPayment->setText(output_str);
      }
    }
    str1 = QString::number(credit_output_data_.month_payment[0], 'f', 2) + rub;
    str2 = QString::number(credit_output_data_.over_payment, 'f', 2) + rub;
    str3 = QString::number(credit_output_data_.total_payment, 'f', 2) + rub;

    if (str1.startsWith("nan") || str2.startsWith("nan") ||
        str3.startsWith("nan") || str1.startsWith("inf") ||
        str2.startsWith("inf") || str3.startsWith("inf") ||
        str1.startsWith("-inf") || str2.startsWith("-inf") ||
        str3.startsWith("-inf") || credit_output_data_.month_payment[0] < 0 ||
        credit_output_data_.over_payment < 0 ||
        credit_output_data_.total_payment < 0)
      have_error = true;
  }

  if (have_error) {
    ui_->monthPayment->setText("Error");
    ui_->overPay->setText("Error");
    ui_->totalPay->setText("Error");
  } else {
    SetTextToOutStyle(str1, str2, str3);
    ui_->overPay->setText(str2);
    ui_->totalPay->setText(str3);
  }
}

void Credit::SetTextToOutStyle(QString str1, QString str2, QString str3) {
  int input_string_max_lenght = MaxLenght(str1, str2, str3);
  int font_size = 208 / input_string_max_lenght / 0.68;
  font_size = font_size > 28 ? 28 : font_size;
  QString output_credit_style =
      "color: #475679;background-color: rgba(0, 0, 0, 0);padding-left: "
      "3px;text-align: center;font-size: ";
  output_credit_style += QString::number(font_size);
  output_credit_style += "px;";
  ui_->monthPayment->setStyleSheet(output_credit_style);
  ui_->overPay->setStyleSheet(output_credit_style);
  ui_->totalPay->setStyleSheet(output_credit_style);
}

int Credit::MaxLenght(QString str_1, QString str_2, QString str_3) {
  int max = str_2.length() > str_1.length() ? str_2.length() : str_1.length();
  if (str_3.length() > max) max = str_3.length();
  return max;
}
