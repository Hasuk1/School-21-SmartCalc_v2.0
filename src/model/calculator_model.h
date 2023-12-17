#ifndef CPP3_SMARTCALC_V2_SRC_CALCULATOR_MODEL_H_
#define CPP3_SMARTCALC_V2_SRC_CALCULATOR_MODEL_H_

#include <stack>
#include <string>

namespace s21 {
enum Status { kOk, kError };

class CalculatorModel {
 public:
  CalculatorModel() = default;
  ~CalculatorModel() = default;

  void Calculate();
  enum Status GetStatus() const;
  long double GetResult() const;
  void SetX(const long double x) noexcept;
  void SetInfix(const std::string &infix) noexcept;

 private:
  enum Status InfixToPostfix();

  void NumberToStack(std::string::iterator &it);
  void CalcSimple(std::string::iterator &it);
  void CalcFunc(std::string::iterator &it);

  void NumberToPostfix(std::string::iterator &it);
  void UnarToPostfix(std::string::iterator &it);
  void BracketsToPostfix(std::string::iterator &it);
  void FunctionToPostfix(std::string::iterator &it);
  void PowToPostfix(std::string::iterator &it);

  inline bool isNumber(std::string::iterator &it) noexcept;
  inline bool isUnar(std::string::iterator &it) noexcept;
  inline bool isBrackets(std::string::iterator &it) noexcept;
  inline bool isFunction(std::string::iterator &it) noexcept;
  inline bool isOperators(std::string::iterator &it) noexcept;
  inline bool isPow(std::string::iterator &it) noexcept;
  inline bool isValid();

  inline int Priority(char ch) noexcept;
  inline void Obnulate();
  inline void PushBackPostfix();
  inline char ChangeFunctions(std::string::iterator &it, bool iter = false);

  enum Status status_ = kOk;
  long double x_ = 0;
  long double result_ = 0;
  std::string infix_ = "";
  std::string postfix_;
  std::stack<long double> stack_;

};  // CalculatorModel

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SRC_CALCULATOR_MODEL_H_
