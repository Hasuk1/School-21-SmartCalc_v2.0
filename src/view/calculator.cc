#include "calculator.h"

#include <QKeyEvent>
#include <QMessageBox>
#include <algorithm>

#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::Calculator) {
  ui_->setupUi(this);
  setWindowTitle("SmartCalc");
  setFixedSize(width(), height());
  SetTextToOut("0");
  InitializeConnections();
}

Calculator::~Calculator() { delete ui_; }

void Calculator::DigitsNum() {
  QString current_text = ui_->Labe_out->toPlainText();
  QPushButton *button = static_cast<QPushButton *>(sender());
  if (isNothingStr(current_text) || current_text == "+") current_text = "";
  if (button->text() == "X") {
    SetTextX(current_text);
  } else if (button->text() == "e") {
    SetTextE(current_text);
  } else if (button->text() == ".") {
    SetTextDot(current_text);
  } else {
    SetTextDigits(current_text, button->text());
  }
}

void Calculator::Function() {
  QString current_text = ui_->Labe_out->toPlainText();
  QPushButton *button = static_cast<QPushButton *>(sender());
  QString button_text = button->text();
  if (button_text == "√a") button_text = "sqrt";
  if (isNothingStr(current_text)) current_text.clear();
  if (current_text.isEmpty())
    SetTextToOut(button_text + "(");
  else if ((current_text.length() > 1 && current_text.back().isDigit()) ||
           current_text.endsWith('x'))
    SetTextToOut(current_text + '*' + button_text + "(");
  else if (isOperator(current_text.back().toLatin1()))
    SetTextToOut(current_text + "(" + button_text + "(");
  else
    SetTextToOut(current_text + button_text + "(");
}

void Calculator::Operators() {
  QString current_text = ui_->Labe_out->toPlainText();
  QPushButton *button = static_cast<QPushButton *>(sender());
  QString button_text = button->text();

  if (button_text == "×")
    button_text = '*';
  else if (button_text == "÷")
    button_text = '/';
  else if (button_text == "mod")
    button_text = '%';
  else if (button_text == "a^b")
    button_text = '^';
  SetTextOperator(current_text, button_text);
}

void Calculator::Brackets() {
  QString current_text = ui_->Labe_out->toPlainText();
  QPushButton *button = static_cast<QPushButton *>(sender());
  if (isNothingStr(current_text) || current_text == "+") current_text.clear();
  if (button->text() == "(") {
    SetTextOpenBrackets(current_text);
  } else if (button->text() == ")") {
    SetTextClosedBrackets(current_text);
  }
}

void Calculator::Delete() {
  QString current_text = ui_->Labe_out->toPlainText();
  QPushButton *button = static_cast<QPushButton *>(sender());
  if (button->text() == "AC") {
    DeleteText();
  } else if (button->text() == "C") {
    ChopText(current_text);
  }
}

void Calculator::ShowRes() {
  QPushButton *button = static_cast<QPushButton *>(sender());
  if (button->text() == "=") {
    Calculate();
  } else if (button->text() == "PLOT") {
    PlotGraph();
  }
}

void Calculator::GraphWindow() {
  QPushButton *button_graph = ui_->PushButton_graph;
  QPushButton *button_equals = ui_->PushButton_equals;
  if (button_graph->property("isPressed").toBool()) {
    button_graph->setStyleSheet(kAdditionalWindowStyleNormal_);
    button_equals->setText("=");
    button_equals->setStyleSheet(kEqualsButtomStyle_);
    if (graph_window_ && graph_window_->isVisible()) {
      graph_window_->close();
      disconnect(this, &Calculator::Plot, graph_window_, &Graph::Plot);
      delete graph_window_;
      graph_window_ = nullptr;
    }
  } else {
    button_graph->setStyleSheet(kAdditionalWindowStylePressed_);
    button_equals->setText("PLOT");
    button_equals->setStyleSheet(kPlotButtomStyle_);
    graph_window_ = new Graph(this);
    graph_window_->setGeometry(x() + width(), y() + 28, 400, 570);
    if (!graph_window_->isVisible()) {
      graph_window_->show();
      connect(this, &Calculator::Plot, graph_window_, &Graph::Plot);
    }
  }
  button_graph->setProperty("isPressed",
                            !button_graph->property("isPressed").toBool());
}

void Calculator::CreditWindow() {
  QPushButton *button_cred = ui_->PushButton_cred;
  QPushButton *button_dep = ui_->PushButton_dep;
  if (button_cred->property("isPressed").toBool()) {
    button_cred->setStyleSheet(kAdditionalWindowStyleNormal_);
    if (credit_window_ && credit_window_->isVisible()) {
      credit_window_->close();
      delete credit_window_;
      credit_window_ = nullptr;
    }
  } else {
    button_cred->setStyleSheet(kAdditionalWindowStylePressed_);
    credit_window_ = new Credit(this);
    credit_window_->setGeometry(this->x() - 450, this->y() + 100, 450, 285);
    if (!credit_window_->isVisible()) credit_window_->show();
    if (button_dep->property("isPressed").toBool() && deposit_window_ &&
        deposit_window_->isVisible()) {
      deposit_window_->close();
      delete deposit_window_;
      deposit_window_ = nullptr;
      button_dep->setProperty("isPressed",
                              !button_dep->property("isPressed").toBool());
      button_dep->setStyleSheet(kAdditionalWindowStyleNormal_);
    }
  }
  button_cred->setProperty("isPressed",
                           !button_cred->property("isPressed").toBool());
}

void Calculator::DepositWindow() {
  QPushButton *button_dep = ui_->PushButton_dep;
  QPushButton *button_cred = ui_->PushButton_cred;
  if (button_dep->property("isPressed").toBool()) {
    button_dep->setStyleSheet(kAdditionalWindowStyleNormal_);
    if (deposit_window_ && deposit_window_->isVisible()) {
      deposit_window_->close();
      delete deposit_window_;
      deposit_window_ = nullptr;
    }

  } else {
    button_dep->setStyleSheet(kAdditionalWindowStylePressed_);
    deposit_window_ = new Deposit(this);
    deposit_window_->setGeometry(this->x() - 450, this->y() + 100, 450, 465);
    if (!deposit_window_->isVisible()) deposit_window_->show();
    if (button_cred->property("isPressed").toBool() && credit_window_ &&
        credit_window_->isVisible()) {
      credit_window_->close();
      delete credit_window_;
      credit_window_ = nullptr;
      button_cred->setProperty("isPressed",
                               !button_dep->property("isPressed").toBool());
      button_cred->setStyleSheet(kAdditionalWindowStyleNormal_);
    }
  }
  button_dep->setProperty("isPressed",
                          !button_dep->property("isPressed").toBool());
}

void Calculator::InitializeConnections() {
  connect(ui_->PushButton_0, SIGNAL(clicked()), this, SLOT(DigitsNum()));
  connect(ui_->PushButton_1, SIGNAL(clicked()), this, SLOT(DigitsNum()));
  connect(ui_->PushButton_2, SIGNAL(clicked()), this, SLOT(DigitsNum()));
  connect(ui_->PushButton_3, SIGNAL(clicked()), this, SLOT(DigitsNum()));
  connect(ui_->PushButton_4, SIGNAL(clicked()), this, SLOT(DigitsNum()));
  connect(ui_->PushButton_5, SIGNAL(clicked()), this, SLOT(DigitsNum()));
  connect(ui_->PushButton_6, SIGNAL(clicked()), this, SLOT(DigitsNum()));
  connect(ui_->PushButton_7, SIGNAL(clicked()), this, SLOT(DigitsNum()));
  connect(ui_->PushButton_8, SIGNAL(clicked()), this, SLOT(DigitsNum()));
  connect(ui_->PushButton_9, SIGNAL(clicked()), this, SLOT(DigitsNum()));
  connect(ui_->PushButton_x, SIGNAL(clicked()), this, SLOT(DigitsNum()));
  connect(ui_->PushButton_e, SIGNAL(clicked()), this, SLOT(DigitsNum()));
  connect(ui_->PushButton_dot, SIGNAL(clicked()), this, SLOT(DigitsNum()));

  connect(ui_->PushButton_cos, SIGNAL(clicked()), this, SLOT(Function()));
  connect(ui_->PushButton_tan, SIGNAL(clicked()), this, SLOT(Function()));
  connect(ui_->PushButton_sin, SIGNAL(clicked()), this, SLOT(Function()));
  connect(ui_->PushButton_atan, SIGNAL(clicked()), this, SLOT(Function()));
  connect(ui_->PushButton_asin, SIGNAL(clicked()), this, SLOT(Function()));
  connect(ui_->PushButton_acos, SIGNAL(clicked()), this, SLOT(Function()));
  connect(ui_->PushButton_log, SIGNAL(clicked()), this, SLOT(Function()));
  connect(ui_->PushButton_ln, SIGNAL(clicked()), this, SLOT(Function()));
  connect(ui_->PushButton_sqrt, SIGNAL(clicked()), this, SLOT(Function()));

  connect(ui_->PushButton_plus, SIGNAL(clicked()), this, SLOT(Operators()));
  connect(ui_->PushButton_minus, SIGNAL(clicked()), this, SLOT(Operators()));
  connect(ui_->PushButton_mult, SIGNAL(clicked()), this, SLOT(Operators()));
  connect(ui_->PushButton_div, SIGNAL(clicked()), this, SLOT(Operators()));
  connect(ui_->PushButton_exp, SIGNAL(clicked()), this, SLOT(Operators()));
  connect(ui_->pushButton_mod, SIGNAL(clicked()), this, SLOT(Operators()));

  connect(ui_->PushButton_bracket1, SIGNAL(clicked()), this, SLOT(Brackets()));
  connect(ui_->PushButton_bracket2, SIGNAL(clicked()), this, SLOT(Brackets()));

  connect(ui_->PushButton_del, SIGNAL(clicked()), this, SLOT(Delete()));
  connect(ui_->PushButton_all_del, SIGNAL(clicked()), this, SLOT(Delete()));

  connect(ui_->PushButton_equals, SIGNAL(clicked()), this, SLOT(ShowRes()));

  connect(ui_->PushButton_graph, SIGNAL(clicked()), this, SLOT(GraphWindow()));
  connect(ui_->PushButton_cred, SIGNAL(clicked()), this, SLOT(CreditWindow()));
  connect(ui_->PushButton_dep, SIGNAL(clicked()), this, SLOT(DepositWindow()));
}

QString Calculator::GetLastNumber(QString current_text) {
  int last_number_start = -1;
  for (int i = current_text.length() - 1; i >= 0; i--) {
    QChar ch = current_text[i];
    if (ch.isDigit() || ch == '.' || ch == 'e' ||
        (ch == '-' && current_text[i - 1] == 'e')) {
      last_number_start = i;
    } else
      break;
  }
  if (last_number_start >= 0) return current_text.mid(last_number_start);
  return "";
}

bool Calculator::isOperator(char ch) {
  std::array<char, 7> operators = {'+', '-', '*', '/', '^', '%', '^'};
  return std::any_of(operators.begin(), operators.end(),
                     [ch](char c) { return c == ch; });
}

bool Calculator::isNothingStr(QString current_text) {
  return current_text.isEmpty() || current_text == "0" ||
         current_text == "Error" || current_text.endsWith("\u221E");
}

QString Calculator::AddCloseBrackets() {
  QString current_text = ui_->Labe_out->toPlainText();
  while (current_text.count('(') > current_text.count(')') &&
         current_text.back() != '(')
    current_text += ')';
  return current_text;
}

void Calculator::SetTextToOut(QString string) {
  ui_->Labe_out->setText(string);
  ui_->Labe_out->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  QTextCursor cursor = ui_->Labe_out->textCursor();
  cursor.movePosition(QTextCursor::End);
  ui_->Labe_out->setTextCursor(cursor);
  ui_->Labe_out->setWordWrapMode(QTextOption::NoWrap);
  ui_->Labe_out->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

QString Calculator::ChopZero(long double result) {
  QString res_string = QString::number(result, 'f', 6);
  while (res_string.endsWith('0')) res_string.chop(1);
  if (res_string.endsWith('.') || res_string.endsWith(',')) res_string.chop(1);
  return res_string;
}

void Calculator::SetTextDigits(QString current_text, QString button_text) {
  if (isNothingStr(current_text) || current_text == "+") current_text = "";
  if (current_text.endsWith(')') || current_text.endsWith('x')) {
    SetTextToOut(current_text + "*" + button_text);
  } else if (button_text == "0" && current_text.endsWith('(')) {
    SetTextToOut(current_text + button_text + ".");
  } else if ((current_text.endsWith('+') && current_text.length() >= 2 &&
              *(current_text.rbegin() + 1) == QChar('(')) ||
             current_text == "+") {
    current_text.chop(1);
    SetTextToOut(current_text + button_text);
  } else {
    SetTextToOut(current_text + button_text);
  }
}

void Calculator::SetTextDot(QString current_text) {
  if (current_text.isEmpty() || isOperator(current_text.back().toLatin1()) ||
      current_text.endsWith('('))
    SetTextToOut(current_text + "0.");
  else {
    QString last_number = GetLastNumber(current_text);
    if (!last_number.contains('.') && !last_number.contains('e'))
      SetTextToOut(current_text + ".");
  }
}

void Calculator::SetTextOperator(QString current_text, QString button_text) {
  if (isNothingStr(current_text))
    current_text = "";
  else if (isOperator(current_text.back().toLatin1()) ||
           current_text.back() == '.')
    current_text.chop(1);

  if (current_text.isEmpty() || current_text.endsWith('(') ||
      current_text.endsWith('e')) {
    if (button_text == "+" || button_text == "-")
      SetTextToOut(current_text + button_text);
  } else {
    if (current_text.back().isDigit() || current_text.endsWith('x') ||
        current_text.endsWith(')'))
      SetTextToOut(current_text + button_text);
  }
}

void Calculator::SetTextOpenBrackets(QString current_text) {
  if (isNothingStr(current_text) || current_text == "+") current_text = "";
  if (current_text.isEmpty()) {
    SetTextToOut("(");
  } else if (isOperator(current_text.back().toLatin1()) ||
             current_text.back() == '(') {
    SetTextToOut(current_text + '(');
  } else if (!(current_text.endsWith('('))) {
    SetTextToOut(current_text + "*(");
  }
}

void Calculator::SetTextClosedBrackets(QString current_text) {
  if (current_text.count('(') > current_text.count(')') &&
      !current_text.endsWith('(') &&
      (current_text.back().isDigit() || current_text.endsWith('x') ||
       current_text.endsWith(')')))
    SetTextToOut(current_text + ')');
}

void Calculator::SetTextX(QString current_text) {
  if (isNothingStr(current_text) || current_text == "+") current_text = "";
  if (current_text.isEmpty()) {
    SetTextToOut("x");
  } else if (current_text.back().isDigit() || current_text.back() == ')' ||
             current_text.back() == 'x') {
    SetTextToOut(current_text + "*x");
  } else if (!GetLastNumber(current_text).contains('e'))
    SetTextToOut(current_text + "x");
}

void Calculator::SetTextE(QString current_text) {
  QString last_number = GetLastNumber(current_text);
  if (!current_text.isEmpty() && current_text.back().isDigit() &&
      !last_number.contains('e'))
    SetTextToOut(current_text + "e");
}

void Calculator::DeleteText() {
  ui_->xValue->clear();
  SetTextToOut("0");
}

void Calculator::ChopText(QString current_text) {
  if (current_text.length() > 1) {
    current_text.chop(1);
    while (!current_text.isEmpty() &&
           ((current_text.back().toLatin1() >= 97 &&
             current_text.back().toLatin1() <= 122 &&
             current_text.back().toLatin1() != 'x') ||
            current_text.endsWith('E')))
      current_text.chop(1);
    SetTextToOut(current_text);
  } else
    SetTextToOut("0");
}

void Calculator::Calculate() {
  QString current_text = AddCloseBrackets();
  bool x_value_convert;
  long double x_value = ui_->xValue->toPlainText().toDouble(&x_value_convert);
  int count_x = current_text.count('x');
  if ((count_x == 0 && !x_value_convert) || (count_x > 0 && x_value_convert) ||
      current_text.length() <= 255) {
    calculator_controller_.SetExpersion(current_text.toStdString(), x_value);
    calculator_controller_.Calculate();
    if (calculator_controller_.GetStatus() == s21::kOk) {
      long double result = calculator_controller_.GetResult();
      SetTextToOut(ChopZero(result));
      if (ui_->Labe_out->toPlainText().startsWith("nan"))
        SetTextToOut("Error");
      else if (ui_->Labe_out->toPlainText().endsWith("-inf"))
        SetTextToOut("-\u221E");
      else if (ui_->Labe_out->toPlainText().endsWith("inf"))
        SetTextToOut("\u221E");
    } else
      SetTextToOut("Error");
  } else if (count_x > 0 && !x_value_convert) {
    QMessageBox::information(this, "ERROR", "Set value of x correctly");
  } else
    SetTextToOut("Error");
}

void Calculator::PlotGraph() {
  QString current_text = AddCloseBrackets();
  SetTextToOut(current_text);
  QString x_value_str = ui_->xValue->toPlainText();
  emit Plot(current_text, x_value_str);
}

void Calculator::keyPressEvent(QKeyEvent *event) {
  QString current_text = ui_->Labe_out->toPlainText();
  int key = event->key();
  if (key >= Qt::Key_0 && key <= Qt::Key_9) {
    QString key_text = QString::number(key - Qt::Key_0);
    SetTextDigits(current_text, key_text);
  } else if (key == Qt::Key_Period || key == Qt::Key_Comma) {
    SetTextDot(current_text);
  } else if (key == Qt::Key_X) {
    SetTextX(current_text);
  } else if (key == Qt::Key_E) {
    SetTextE(current_text);
  } else if (key == Qt::Key_Plus) {
    SetTextOperator(current_text, "+");
  } else if (key == Qt::Key_Minus) {
    SetTextOperator(current_text, "-");
  } else if (key == Qt::Key_Asterisk) {
    SetTextOperator(current_text, "*");
  } else if (key == Qt::Key_Slash) {
    SetTextOperator(current_text, "/");
  } else if (key == Qt::Key_Percent) {
    SetTextOperator(current_text, "%");
  } else if (key == Qt::Key_AsciiCircum) {
    SetTextOperator(current_text, "^");
  } else if (key == Qt::Key_ParenLeft) {
    SetTextOpenBrackets(current_text);
  } else if (key == Qt::Key_ParenRight) {
    SetTextClosedBrackets(current_text);
  } else if (key == Qt::Key_Delete) {
    DeleteText();
  } else if (key == Qt::Key_Backspace) {
    ChopText(current_text);
  } else if (key == Qt::Key_Enter || key == Qt::Key_Return) {
    if (ui_->PushButton_equals->text() == "=")
      Calculate();
    else if (ui_->PushButton_equals->text() == "PLOT")
      PlotGraph();
  }
}

void Calculator::moveEvent(QMoveEvent *event) {
  QPushButton *button_graph = ui_->PushButton_graph;
  QPushButton *button_cred = ui_->PushButton_cred;
  QPushButton *button_dep = ui_->PushButton_dep;
  QWidget::moveEvent(event);
  if (button_graph->property("isPressed").toBool() && graph_window_ &&
      graph_window_->isVisible()) {
    QPoint mainPos = pos();
    graph_window_->move(mainPos.x() + 290, mainPos.y());
  }
  if (button_cred->property("isPressed").toBool() && credit_window_ &&
      credit_window_->isVisible()) {
    QPoint mainPos = pos();
    credit_window_->move(mainPos.x() - 450, mainPos.y() + 72);
  }
  if (button_dep->property("isPressed").toBool() && deposit_window_ &&
      deposit_window_->isVisible()) {
    QPoint mainPos = pos();
    deposit_window_->move(mainPos.x() - 450, mainPos.y() + 72);
  }
}
