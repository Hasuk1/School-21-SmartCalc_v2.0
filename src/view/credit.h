#ifndef CPP3_SMARTCALC_V2_SRC_CREDIT_VIEW_H_
#define CPP3_SMARTCALC_V2_SRC_CREDIT_VIEW_H_

#include <QDialog>

#include "../controller/credit_controller.h"

namespace Ui {
class Credit;
}

class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();

 private slots:
  void on_calc_credit_clicked();

 private:
  void SetTextToOutStyle(QString str1, QString str2, QString str3);
  int MaxLenght(QString str_1, QString str_2, QString str_3);

  Ui::Credit *ui_;
  s21::CreditController credit_controller_;
  s21::CreditInputData credit_input_data_;
  s21::CreditOutputData credit_output_data_;
};

#endif  // CPP3_SMARTCALC_V2_SRC_CREDIT_VIEW_H_
