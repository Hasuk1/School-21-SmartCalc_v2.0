#ifndef CPP3_SMARTCALC_V2_SRC_CALCULATOR_VIEW_H_
#define CPP3_SMARTCALC_V2_SRC_CALCULATOR_VIEW_H_

#include <QApplication>
#include <QKeyEvent>
#include <QMainWindow>

#include "../controller/calculator_controller.h"
#include "credit.h"
#include "deposit.h"
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QMainWindow {
  Q_OBJECT

 public:
  Calculator(QWidget *parent = nullptr);
  ~Calculator();
  void moveEvent(QMoveEvent *event) override;

 protected:
  void keyPressEvent(QKeyEvent *event) override;

 signals:
  void Plot(QString, QString);

 private:
  void InitializeConnections();

  void SetTextToOut(QString string);
  QString ChopZero(long double result);
  void SetTextDigits(QString current_text, QString button_text);
  void SetTextDot(QString current_text);
  void SetTextOperator(QString current_text, QString button_text);
  void SetTextOpenBrackets(QString current_text);
  void SetTextClosedBrackets(QString current_text);
  void SetTextX(QString current_text);
  void SetTextE(QString current_text);

  void DeleteText();
  void ChopText(QString current_text);

  void Calculate();
  void PlotGraph();

  QString GetLastNumber(QString current_text);
  QString AddCloseBrackets();
  bool isOperator(char ch);
  bool isNothingStr(QString current_text);

  s21::CalculatorController calculator_controller_;
  Graph *graph_window_;
  Credit *credit_window_;
  Deposit *deposit_window_;
  Ui::Calculator *ui_;

  const QString kAdditionalWindowStyleNormal_ =
      "border-radius: 9px;background-color: #a9b8c2;color: #ffffff;border: 2px "
      "outset #9cacb6;";
  const QString kAdditionalWindowStylePressed_ =
      "border-radius: 9px;background-color: #87959f;color: #ffffff;border: 2px "
      "outset #79868f;";
  const QString kEqualsButtomStyle_ =
      "QPushButton {border-radius: 10px;background-color: #C1E80C;color: "
      "white;border: 2px outset #add00a;font-size: 30px;}QPushButton:pressed "
      "{background-color: #add00a;border: 2px outset #9ab909;font-size: 29px;}";
  const QString kPlotButtomStyle_ =
      "QPushButton {border-radius: 10px;background-color: #8c8cd3;color: "
      "#ffffff;border: 2px outset #7c7cbc;font-size: 20px;font-weight: "
      "bold;}QPushButton:pressed {background-color: #7c7cbc;border: 2px outset "
      "#6d6da4;font-size: 19px;}";

 private slots:
  void DigitsNum();
  void Function();
  void Operators();
  void Brackets();
  void Delete();
  void ShowRes();
  void GraphWindow();
  void CreditWindow();
  void DepositWindow();
};

#endif  // CPP3_SMARTCALC_V2_SRC_CALCULATOR_VIEW_H_
