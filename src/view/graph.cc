#include "graph.h"

#include "ui_graph.h"

Graph::Graph(QWidget *parent) : QDialog(parent), ui_(new Ui::Graph) {
  ui_->setupUi(this);

  setWindowTitle("Function Graph");
  setFixedSize(width(), height());

  ui_->widget->xAxis->setRange(-20, 20);
  ui_->widget->yAxis->setRange(-20, 20);
}

Graph::~Graph() { delete ui_; }

void Graph::Plot(QString expersion, QString x_value_str) {
  x_vector_.clear();
  y_vector_.clear();
  ui_->widget->clearGraphs();

  bool convert_x_min_status, convert_x_max_status;
  bool convert_y_min_status, convert_y_max_status;
  x_begin_ = ui_->xMin->toPlainText().toDouble(&convert_x_min_status);
  x_end_ = ui_->xMax->toPlainText().toDouble(&convert_x_max_status);
  y_begin_ = ui_->yMin->toPlainText().toDouble(&convert_y_min_status);
  y_end_ = ui_->xMax->toPlainText().toDouble(&convert_y_max_status);
  if (!convert_x_min_status || !convert_x_max_status || !convert_y_min_status ||
      !convert_y_max_status) {
    QMessageBox::information(this, "ERROR", "Set domain & codomain correctly");
  } else if (x_begin_ < -1000000 || x_end_ > 1000000 || y_begin_ < -1000000 ||
             y_end_ > 1000000) {
    QString error = "Set parameters in the range from -1000000 to 1000000";
    QMessageBox::information(this, "ERROR", error);
  } else {
    bool convert_x_value_status;
    long double x_value = x_value_str.toDouble(&convert_x_value_status);
    if (convert_x_value_status) {
      for (x_cord_ = x_begin_; x_cord_ <= x_end_; x_cord_ += kStep_) {
        calculator_controller_.SetExpersion(expersion.toStdString(), x_cord_);
        calculator_controller_.Calculate();
        y_cord_ = calculator_controller_.GetResult();
        if (y_cord_ >= y_begin_ && y_cord_ <= y_end_ &&
            calculator_controller_.GetStatus() == s21::kOk) {
          x_vector_.push_back(x_value);
          y_vector_.push_back(y_cord_);
        }
      }
    } else {
      for (x_cord_ = x_begin_; x_cord_ <= x_end_; x_cord_ += kStep_) {
        calculator_controller_.SetExpersion(expersion.toStdString(), x_cord_);
        calculator_controller_.Calculate();
        y_cord_ = calculator_controller_.GetResult();
        if (y_cord_ >= y_begin_ && y_cord_ <= y_end_ &&
            calculator_controller_.GetStatus() == s21::kOk) {
          x_vector_.push_back(x_cord_);
          y_vector_.push_back(y_cord_);
        }
      }
    }
    ui_->widget->addGraph();
    QCPGraph *Graph = ui_->widget->graph(0);
    QPen pen = Graph->pen();
    pen.setWidth(2);
    pen.setColor(QColor::fromRgb(71, 86, 121));
    Graph->setPen(pen);
    ui_->widget->graph(0)->addData(x_vector_, y_vector_);
    ui_->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                                 QCP::iSelectPlottables);
    ui_->widget->rescaleAxes();
    ui_->widget->replot();
  }
}
