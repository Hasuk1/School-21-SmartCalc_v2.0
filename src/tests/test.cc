#include <gtest/gtest.h>

#include "../controller/calculator_controller.h"
#include "../controller/credit_controller.h"
#include "../controller/deposit_controller.h"

TEST(CalculatorControllerTest, Test0) {
  s21::CalculatorController controller;
  controller.SetExpersion("5+-1)", 0);
  controller.Calculate();
  EXPECT_EQ(controller.GetStatus(), s21::kError);
}

TEST(CalculatorControllerTest, Test1) {
  s21::CalculatorController controller;
  controller.SetExpersion("sqrt(16)+sin(1)", 0);
  controller.Calculate();
  EXPECT_NEAR(controller.GetResult(), 4.84147, 1e-6);
  EXPECT_EQ(controller.GetStatus(), 0);
}

TEST(CalculatorControllerTest, Test2) {
  s21::CalculatorController controller;
  controller.SetExpersion("2^(2^(2^2))", 0);
  controller.Calculate();
  EXPECT_EQ(controller.GetResult(), 65536);
  EXPECT_EQ(controller.GetStatus(), 0);
}

TEST(CalculatorControllerTest, Test3) {
  s21::CalculatorController controller;
  controller.SetExpersion("log(25)-acos(0.45)", 0);
  controller.Calculate();
  EXPECT_NEAR(controller.GetResult(), 0.293909, 1e-6);
  EXPECT_EQ(controller.GetStatus(), 0);
}

TEST(CalculatorControllerTest, Test4) {
  s21::CalculatorController controller;
  controller.SetExpersion("(4*sin(2.9)+3*cos(0.47))/4", 0);
  controller.Calculate();
  EXPECT_NEAR(controller.GetResult(), 0.907926, 1e-6);
  EXPECT_EQ(controller.GetStatus(), 0);
}

TEST(CalculatorControllerTest, Test5) {
  s21::CalculatorController controller;
  controller.SetExpersion("log(50)/acos(0.35)*atan(1.1)*sqrt(64)", 0);
  controller.Calculate();
  EXPECT_NEAR(controller.GetResult(), 9.3318876, 1e-6);
  EXPECT_EQ(controller.GetStatus(), 0);
}

TEST(CalculatorControllerTest, Test6) {
  s21::CalculatorController controller;
  controller.SetExpersion(
      "(sin(1.4)*cos(0.85)/tan(0.68))/(asin(0.38)/"
      "2*acos(0.45)^3-atan(0.54)*sqrt(49))+ln(5)*log(100)",
      0);
  controller.Calculate();
  EXPECT_NEAR(controller.GetResult(), 2.967829, 1e-6);
  EXPECT_EQ(controller.GetStatus(), 0);
}

TEST(CalculatorControllerTest, Test7) {
  s21::CalculatorController controller;
  controller.SetExpersion(
      "acos(0.25)^ln(2)-atan(1.5)*sqrt(16)*log(10)*sin(2.5)/(cos(1.1)/"
      "tan(1.9)*asin(0.4))",
      0);
  controller.Calculate();
  EXPECT_NEAR(controller.GetResult(), 38.104222613215, 1e-6);
  EXPECT_EQ(controller.GetStatus(), 0);
}

TEST(CalculatorControllerTest, Test8) {
  s21::CalculatorController controller;
  controller.SetExpersion(
      "((sin(1.7)*acos(0.3)-atan(0.35)*tan(1.5))^2)/sqrt(9)*(ln(7)+log(1000)/"
      "acos(0.6))",
      0);
  controller.Calculate();
  EXPECT_NEAR(controller.GetResult(), 21.0601731, 1e-6);
  EXPECT_EQ(controller.GetStatus(), 0);
}

TEST(CalculatorControllerTest, Test9) {
  s21::CalculatorController controller;
  controller.SetExpersion(
      "atan(0.75)*log(10)+sqrt(64)*sin(2)-cos(0.576)/acos(0.78)/"
      "5-2*ln(3)*asin(0.29)*tan(1.05)",
      0);
  controller.Calculate();
  EXPECT_NEAR(controller.GetResult(), 6.5427849584, 1e-6);
  EXPECT_EQ(controller.GetStatus(), 0);
}

TEST(CalculatorControllerTest, Test10) {
  s21::CalculatorController controller;
  controller.SetExpersion(
      "(cos(2.1)^2*sin(1.2)*atan(0.85)+acos(0.4))/"
      "log(250)*sqrt(169)+ln(5)*asin(0.55)*tan(0.5)",
      0);
  controller.Calculate();
  EXPECT_NEAR(controller.GetResult(), 7.70412863, 1e-6);
  EXPECT_EQ(controller.GetStatus(), 0);
}

TEST(CalculatorControllerTest, Test11) {
  s21::CalculatorController controller;
  controller.SetExpersion(
      "(sin(0.93)+acos(0.71)/atan(1.37)*tan(1.8))/"
      "(sqrt(25)*ln(10)*acos(0.3)-asin(0.6)*cos(1.1))",
      0);
  controller.Calculate();
  EXPECT_NEAR(controller.GetResult(), -0.193212471, 1e-6);
  EXPECT_EQ(controller.GetStatus(), 0);
}

TEST(CalculatorControllerTest, Test12) {
  s21::CalculatorController controller;
  controller.SetExpersion("sin(cos(tan(ln(log(1234)+1)*2)/3)-4)", 0);
  controller.Calculate();
  EXPECT_NEAR(controller.GetResult(), -0.134926396, 1e-6);
  EXPECT_EQ(controller.GetStatus(), 0);
}

TEST(CalculatorControllerTest, Test13) {
  s21::CalculatorController controller;
  controller.SetExpersion(
      "(sin(0.93)+acos(0.71)/atan(1.37)*tan(1.8))/"
      "(sqrt(25)*ln(10)*acos(0.3)-asin(0.6)*cos(1.1))-sin(cos(tan(ln(log((cos("
      "2.1)^2*sin(1.2)*atan(0.85)+acos(0.4))/"
      "log(250)*sqrt(169)+ln(5)*asin(0.55)*tan(0.5))+1)*2)/3)-4)",
      0);
  controller.Calculate();
  EXPECT_NEAR(controller.GetResult(), -0.565264615, 1e-6);
  EXPECT_EQ(controller.GetStatus(), 0);
}

TEST(CalculatorControllerTest, Test14) {
  s21::CalculatorController controller;
  controller.SetExpersion("1/0", 0);
  controller.Calculate();
  EXPECT_EQ(controller.GetStatus(), 1);
}

TEST(CalculatorControllerTest, Test15) {
  s21::CalculatorController controller;
  controller.SetExpersion("sqrt(-16)", 0);
  controller.Calculate();
  EXPECT_EQ(controller.GetStatus(), 1);
}

TEST(CalculatorControllerTest, Test16) {
  s21::CalculatorController controller;
  controller.SetExpersion("654+", 0);
  controller.Calculate();
  EXPECT_EQ(controller.GetResult(), 654);
  EXPECT_EQ(controller.GetStatus(), s21::kError);
}

TEST(CalculatorControllerTest, Test17) {
  s21::CalculatorController controller;
  controller.SetExpersion("(5+", 0);
  controller.Calculate();
  EXPECT_EQ(controller.GetStatus(), 1);
}

TEST(CalculatorControllerTest, Test18) {
  s21::CalculatorController controller;
  controller.SetExpersion("sin(x)", 1);
  controller.Calculate();
  EXPECT_NEAR(controller.GetResult(), 0.841471, 1e-06);
  EXPECT_EQ(controller.GetStatus(), 0);
}

TEST(CalculatorControllerTest, Test19) {
  s21::CalculatorController controller;
  controller.SetExpersion("=1e+06", 0);
  controller.Calculate();
  EXPECT_EQ(controller.GetStatus(), s21::kError);
}

TEST(CalculatorControllerTest, Test20) {
  s21::CalculatorController controller;
  controller.SetExpersion("-3+1e+06", 0);
  controller.Calculate();
  EXPECT_EQ(controller.GetResult(), 1e+06 - 3);
  EXPECT_EQ(controller.GetStatus(), 0);
}

TEST(CalculatorControllerTest, Test21) {
  s21::CalculatorController controller;
  controller.SetExpersion("INCORRECT", 0);
  controller.Calculate();
  EXPECT_EQ(controller.GetStatus(), 1);
}

TEST(CalculatorControllerTest, Test22) {
  s21::CalculatorController controller;
  controller.SetExpersion("1e+999", 0);
  controller.Calculate();
  EXPECT_EQ(controller.GetStatus(), 1);
}

TEST(CalculatorControllerTest, Test23) {
  s21::CalculatorController controller;
  controller.SetExpersion("1e-900", 0);
  controller.Calculate();
  EXPECT_EQ(controller.GetStatus(), 1);
}

TEST(CalculatorControllerTest, Test24) {
  s21::CalculatorController controller;
  controller.SetExpersion("-1-(-1-(-1-(-2-1)))", 0);
  controller.Calculate();
  EXPECT_EQ(controller.GetResult(), 2);
  EXPECT_EQ(controller.GetStatus(), 0);
}

TEST(CalculatorControllerTest, Test25) {
  s21::CalculatorController controller;
  controller.SetExpersion("1--1", 0);
  controller.Calculate();
  EXPECT_EQ(controller.GetResult(), 1);
  EXPECT_EQ(controller.GetStatus(), s21::kError);
}

TEST(CalculatorControllerTest, Test26) {
  s21::CalculatorController controller;
  controller.SetExpersion("1-sin(1)", 0);
  controller.Calculate();
  EXPECT_NEAR(controller.GetResult(), 0.158529, 1e-6);
  EXPECT_EQ(controller.GetStatus(), 0);
}

TEST(CalculatorControllerTest, Test27) {
  s21::CalculatorController controller;
  controller.SetExpersion("+5+5", 0);
  controller.Calculate();
  EXPECT_EQ(controller.GetResult(), 10);
  EXPECT_EQ(controller.GetStatus(), 0);
}

TEST(CalculatorControllerTest, Test28) {
  s21::CalculatorController controller;
  controller.SetExpersion("+5*(-5)", 0);
  controller.Calculate();
  EXPECT_EQ(controller.GetResult(), -25);
  EXPECT_EQ(controller.GetStatus(), 0);
}

TEST(CalculatorControllerTest, Test29) {
  s21::CalculatorController controller;
  controller.SetExpersion("", 0);
  controller.Calculate();
  EXPECT_EQ(controller.GetStatus(), s21::kError);
}

TEST(CalculatorControllerTest, Test30) {
  s21::CalculatorController controller;
  controller.SetExpersion("log(-1)*ln(-2)", 0);
  controller.Calculate();
  EXPECT_EQ(controller.GetStatus(), s21::kError);
}

TEST(CalculatorControllerTest, Test31) {
  s21::CalculatorController controller;
  controller.SetExpersion("+", 0);
  controller.Calculate();
  EXPECT_EQ(controller.GetStatus(), s21::kError);
}

TEST(CalculatorControllerTest, Test32) {
  s21::CalculatorController controller;
  controller.SetExpersion("20%5", 0);
  controller.Calculate();
  EXPECT_EQ(controller.GetResult(), 0);
  EXPECT_EQ(controller.GetStatus(), 0);
}

TEST(CalculatorControllerTest, Test33) {
  s21::CalculatorController controller;
  controller.SetExpersion("1 + 3", 0);
  controller.Calculate();
  EXPECT_EQ(controller.GetResult(), 4);
  EXPECT_EQ(controller.GetStatus(), 0);
}

TEST(CreditControllerTest, Test1) {
  s21::CreditInputData input;
  input.credit_amount = 1000000;
  input.credit_term = 13;
  input.credit_term_type = 1;
  input.credit_rate = 23.13;
  input.credit_payment_type = "Annuities";

  s21::CreditController controller;
  controller.SetInputData(input);
  controller.Calculate();

  EXPECT_NEAR(controller.GetOutputData().month_payment[0], 87697.81, 1e-2);
  EXPECT_NEAR(controller.GetOutputData().over_payment, 140071.55, 1e-2);
  EXPECT_NEAR(controller.GetOutputData().total_payment, 1140071.55, 1e-2);
}

TEST(CreditControllerTest, Test2) {
  s21::CreditInputData input;
  input.credit_amount = 123456;
  input.credit_term = 6;
  input.credit_term_type = 1;
  input.credit_rate = 14.32;
  input.credit_payment_type = "Differentiated";

  s21::CreditController controller;
  controller.SetInputData(input);
  controller.Calculate();

  EXPECT_NEAR(controller.GetOutputData().month_payment[0], 22049.24, 1e-2);
  EXPECT_NEAR(controller.GetOutputData().month_payment[1], 21803.70, 1e-2);
  EXPECT_NEAR(controller.GetOutputData().month_payment[2], 21558.16, 1e-2);
  EXPECT_NEAR(controller.GetOutputData().month_payment[3], 21312.62, 1e-2);
  EXPECT_NEAR(controller.GetOutputData().month_payment[4], 21067.08, 1e-2);
  EXPECT_NEAR(controller.GetOutputData().month_payment[5], 20821.54, 1e-2);
  EXPECT_NEAR(controller.GetOutputData().over_payment, 5156.35, 1e-2);
  EXPECT_NEAR(controller.GetOutputData().total_payment, 128612.35, 1e-2);
}

TEST(DepositControllerTest, Test1) {
  s21::DepositInputData input;
  input.deposit_amount = 16595;
  input.deposit_term = 20;
  input.deposit_term_type = 12;
  input.deposit_interest_rate = 32.78;
  input.deposit_tax_rate = 12;
  input.frequency = 1;
  input.capitalization = true;
  input.replenishments = 121.13;
  input.withdraws = 311.01;

  s21::DepositController controller;
  controller.SetInputData(input);
  controller.Calculate();

  EXPECT_NEAR(controller.GetOutputData().total_interest, 6248826.34, 1e-2);
  EXPECT_NEAR(controller.GetOutputData().total_tax, 749859.16, 1e-2);
  EXPECT_NEAR(controller.GetOutputData().total_balance, 5469990.98, 1e-2);
}

TEST(DepositControllerTest, Test2) {
  s21::DepositInputData input;
  input.deposit_amount = 313212;
  input.deposit_term = 15;
  input.deposit_term_type = 1;
  input.deposit_interest_rate = 64.17;
  input.deposit_tax_rate = 8;
  input.frequency = 12;
  input.capitalization = false;
  input.replenishments = 0;
  input.withdraws = 0;

  s21::DepositController controller;
  controller.SetInputData(input);
  controller.Calculate();

  EXPECT_NEAR(controller.GetOutputData().total_interest, 200988.14, 1e-2);
  EXPECT_NEAR(controller.GetOutputData().total_tax, 16079.05, 1e-2);
  EXPECT_NEAR(controller.GetOutputData().total_balance, 498121.09, 1e-2);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
