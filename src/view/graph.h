#ifndef CPP3_SMARTCALC_V2_SRC_GRAPH_VIEW_H_
#define CPP3_SMARTCALC_V2_SRC_GRAPH_VIEW_H_

#include <QDialog>
#include <QVector>

#include "../controller/calculator_controller.h"

namespace Ui {
class Graph;
}

class Graph : public QDialog {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();

 public slots:
  void Plot(QString expersion, QString x_value);

 private:
  const double kStep_ = 0.1;
  Ui::Graph *ui_;

  double x_begin_ = -20;
  double x_end_ = 20;
  double y_begin_ = -20;
  double y_end_ = 20;
  double x_cord_;
  double y_cord_;
  QVector<double> x_vector_;
  QVector<double> y_vector_;
  s21::CalculatorController calculator_controller_;
};

#endif  // CPP3_SMARTCALC_V2_SRC_GRAPH_VIEW_H_
