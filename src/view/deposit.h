#ifndef CPP3_SMARTCALC_V2_SRC_DEPOSIT_VIEW_H_
#define CPP3_SMARTCALC_V2_SRC_DEPOSIT_VIEW_H_

#include <QDialog>

#include "../controller/deposit_controller.h"

namespace Ui {
class Deposit;
}

class Deposit : public QDialog {
  Q_OBJECT

 public:
  explicit Deposit(QWidget *parent = nullptr);
  ~Deposit();

 private slots:
  void on_calc_deposit_clicked();

 private:
  void SetTextToOutStyle(QString str1, QString str2, QString str3);
  int MaxLenght(QString str_1, QString str_2, QString str_3);

  Ui::Deposit *ui_;
  s21::DepositController deposit_controller_;
  s21::DepositInputData deposit_input_data_;
  s21::DepositOutputData deposit_output_data_;
};

#endif  // CPP3_SMARTCALC_V2_SRC_DEPOSIT_VIEW_H_
