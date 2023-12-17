#include "calculator_model.h"

#include <cmath>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

namespace s21 {
void CalculatorModel::Calculate() {
  if (InfixToPostfix() != kError) {
    for (auto it = postfix_.begin(); it != postfix_.end(); ++it) {
      if (*it == ' ') {
        continue;
      } else if (isNumber(it)) {
        NumberToStack(it);
      } else if (isOperators(it)) {
        CalcSimple(it);
      } else {
        CalcFunc(it);
      }
      if (status_ == kOk && !stack_.empty()) result_ = stack_.top();
    }
  }
  if (status_ == kOk && !stack_.empty()) {
    stack_.pop();
  }

  if (!stack_.empty()) status_ = kError;
}

enum Status CalculatorModel::InfixToPostfix() {
  if (!isValid()) return kError;
  Obnulate();
  for (auto it = infix_.begin(); it != infix_.end(); ++it) {
    if (*it == ' ') {
      continue;
    } else if (isNumber(it)) {
      NumberToPostfix(it);
    } else if (isUnar(it)) {
      UnarToPostfix(it);
    } else if (isBrackets(it)) {
      BracketsToPostfix(it);
    } else if (isFunction(it)) {
      FunctionToPostfix(it);
    } else if (isPow(it)) {
      PowToPostfix(it);
    } else if (isOperators(it)) {
      while (!stack_.empty() && Priority(*it) <= Priority(stack_.top()))
        PushBackPostfix();
      stack_.push(*it);
    } else
      status_ = kError;
  }
  while (!stack_.empty()) PushBackPostfix();
  if (status_ != kOk) postfix_ = "";
  return status_;
}

void CalculatorModel::NumberToStack(std::string::iterator &it) {
  if (*it == 'x') {
    stack_.push(x_);
  } else {
    std::string digit;
    while (isNumber(it)) digit.push_back(*it++);
    *it--;
    try {
      stack_.push(std::stod(digit));
    } catch (const std::out_of_range &e) {
      status_ = kError;
    }
  }
}

void CalculatorModel::CalcSimple(std::string::iterator &it) {
  long double second_operand = 0, first_operand = 0;
  if (stack_.empty()) {
    status_ = kError;
  } else {
    second_operand = stack_.top();
    stack_.pop();
  }
  if (stack_.empty()) {
    status_ = kError;
  } else {
    first_operand = stack_.top();
    stack_.pop();
  }
  if (*it == '+') {
    stack_.push(first_operand + second_operand);
  } else if (*it == '-') {
    stack_.push(first_operand - second_operand);
  } else if (*it == '*') {
    stack_.push(first_operand * second_operand);
  } else if (*it == '^') {
    stack_.push(std::pow(first_operand, second_operand));
  } else if (*it == '/') {
    if (second_operand != 0)
      stack_.push(first_operand / second_operand);
    else
      status_ = kError;
  } else if (*it == '%') {
    stack_.push(std::fmod(first_operand, second_operand));
  }
}

void CalculatorModel::CalcFunc(std::string::iterator &it) {
  long double operand = 0;
  if (stack_.empty()) {
    status_ = kError;
  } else {
    operand = stack_.top();
    stack_.pop();
  }
  if (*it == 'A') {
    stack_.push(std::cos(operand));
  } else if (*it == 'B') {
    stack_.push(std::sin(operand));
  } else if (*it == 'C') {
    stack_.push(std::tan(operand));
  } else if (*it == 'D') {
    stack_.push(std::acos(operand));
  } else if (*it == 'E') {
    stack_.push(std::asin(operand));
  } else if (*it == 'F') {
    stack_.push(std::atan(operand));
  } else if (*it == 'G') {
    if (operand >= 0) {
      stack_.push(std::sqrt(operand));
    } else
      status_ = kError;
  } else if (*it == 'H') {
    if (operand > 0) {
      stack_.push(std::log10(operand));
    } else
      status_ = kError;
  } else if (*it == 'I') {
    if (operand > 0) {
      stack_.push(std::log(operand));
    } else
      status_ = kError;
  } else if (*it == '~') {
    stack_.push(operand * -1);
  } else if (*it == '&') {
    stack_.push(operand);
  }
}

bool CalculatorModel::isNumber(std::string::iterator &it) noexcept {
  return isdigit(*it) || *it == '.' || *it == ',' || *it == 'e' || *it == 'x' ||
         ((*it == '-' || *it == '+') &&
          (it != infix_.begin() && *(it - 1) == 'e'));
}

bool CalculatorModel::isUnar(std::string::iterator &it) noexcept {
  return (*it == '-' || *it == '+') &&
         (it == infix_.begin() || *(it - 1) == '(');
}

bool CalculatorModel::isBrackets(std::string::iterator &it) noexcept {
  return *it == '(' || *it == ')';
}

bool CalculatorModel::isOperators(std::string::iterator &it) noexcept {
  return *it == '-' || *it == '+' || *it == '*' || *it == '/' || *it == '%' ||
         *it == '^';
}

bool CalculatorModel::isFunction(std::string::iterator &it) noexcept {
  char ch = ChangeFunctions(it);
  return ch >= 65 && ch <= 73 && *it != ch;
}

bool CalculatorModel::isPow(std::string::iterator &it) noexcept {
  return *it == '^';
}

bool CalculatorModel::isValid() {
  if (infix_ == "") {
    status_ = kError;
    return false;
  }
  int open = 0, closed = 0;
  for (auto it = infix_.begin(); it != infix_.end(); ++it) {
    if (*it == '(')
      ++open;
    else if (*it == ')')
      ++closed;
  }
  if (open != closed) status_ = kError;
  return open == closed;
}

void CalculatorModel::NumberToPostfix(std::string::iterator &it) {
  while (isNumber(it)) postfix_.push_back(*it++);
  *it--;
  postfix_.push_back(' ');
}

void CalculatorModel::UnarToPostfix(std::string::iterator &it) {
  char ch = *it == '+' ? '&' : '~';
  while (!stack_.empty() && Priority(ch) <= Priority(stack_.top()))
    PushBackPostfix();
  stack_.push(ch);
}

void CalculatorModel::BracketsToPostfix(std::string::iterator &it) {
  if (*it == '(')
    stack_.push(*it);
  else {
    while (!stack_.empty() && stack_.top() != '(') {
      PushBackPostfix();
    }
    if (!stack_.empty() && stack_.top() == '(')
      stack_.pop();
    else
      status_ = kError;
  }
}

void CalculatorModel::PowToPostfix(std::string::iterator &it) {
  while (!stack_.empty() && Priority(*it) < Priority(stack_.top()))
    PushBackPostfix();
  stack_.push(*it);
}

void CalculatorModel::FunctionToPostfix(std::string::iterator &it) {
  char func_name = ChangeFunctions(it, true);
  while (!stack_.empty() && Priority(func_name) <= Priority(stack_.top()))
    PushBackPostfix();
  stack_.push(func_name);
}

char CalculatorModel::ChangeFunctions(std::string::iterator &it, bool iter) {
  std::vector<std::string> func = {"cos",  "sin",  "tan", "acos", "asin",
                                   "atan", "sqrt", "log", "ln"};
  for (int i = 0; i < (int)func.size(); ++i) {
    if (std::equal(it, it + func[i].size(), func[i].begin(), func[i].end())) {
      if (iter) it += func[i].length() - 1;
      return i + 65;
    }
  }
  return *it;
}

void CalculatorModel::Obnulate() {
  postfix_ = "";
  status_ = kOk;
  result_ = 0;
  while (!stack_.empty()) stack_.pop();
}

int CalculatorModel::Priority(char ch) noexcept {
  if (ch == '+' || ch == '-')
    return 1;
  else if (ch == '*' || ch == '/')
    return 2;
  else if (ch == '^')
    return 3;
  else if ((ch >= 65 && ch <= 74) || ch == '%')
    return 4;
  else if (ch == '~' || ch == '&')
    return 5;
  else if (ch == '(')
    return -1;
  return 0;
}

void CalculatorModel::PushBackPostfix() {
  if (!stack_.empty()) {
    postfix_.push_back(stack_.top());
    stack_.pop();
    postfix_.push_back(' ');
  }
}

void CalculatorModel::SetInfix(const std::string &infix) noexcept {
  infix_ = infix;
}

void CalculatorModel::SetX(const long double x) noexcept { x_ = x; }

enum Status CalculatorModel::GetStatus() const { return status_; }

long double CalculatorModel::GetResult() const { return result_; }

}  // namespace s21
