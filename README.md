# **SmartCalc v2.0**

![misssshaaaa](misc/images/misssshaaaa.jpg)

## **Information**

The project provides the ability to perform a variety of mathematical operations. It also has 3 additional modules (charting, credit calculator, deposit calculator). The main difference from [SmartCalc v1.0](https://github.com/Hasuk1/School-21-SmartCalc_v1.0) is the use of MVC-pattern.


## **Project Architecture**

The `MVC' (Model-View-Controller) pattern is a scheme for dividing application modules into three separate macro components: a model containing the business logic, a view - a form of user interface for interacting with the program, and a controller that modifies the model based on user action.

![MVC](misc/images/MVC-Process.png)

## **What this app can do**

### **Calculator and plotting** 

The calculator is capable of calculating expressions in infix notation. 
It is also capable of calculating expressions with the `x` variable and substituting its values as a number.
The expression is entered using the interface, and then the user can click on the "=" sign to get the result.

In the second version of the program the functionality of the application has been redesigned. Now there is keyboard input, processing of numbers in exponential notation, correct display of the expression output line. 

![simple](misc/images/simple.gif)

- The interface and functionality of the regular calculator and charts were inspired by the principles and design of the Google calculator. This provides a familiar and comfortable environment for users.

### **Credit calculator**

The loan calculator provides an opportunity to estimate the parameters and costs of a loan before taking it.

Now you can see the entire list of payments for differentiated payments, corrections have been made to the calculation formula for more accurate results, and errors in the interface with incorrect data have been debugged.

![credit](misc/images/credit.gif)

- The principles and algorithms from the website [calcus.ru](https://calcus.ru/kreditnyj-kalkulyator) were used to develop the loan calculator, ensuring accurate and reliable loan calculations.

## **Deposit calculator** 

The deposit calculator provides an opportunity to estimate the profitability and taxation of a deposit before placing it. It calculates the accrued interest depending on the deposit amount, placement term, interest rate, tax rate, frequency of payments and interest capitalization.

The formula for correct tax calculation has been corrected. The interface takes into account the size of the displayed information and adjusts to it.

![deposit](misc/images/deposit.gif)

- Data and calculation methodology from [banki.ru](https://www.banki.ru/services/calculators/deposits/) were used for the deposit calculator, ensuring the accuracy and relevance of the data.

## **Supported platforms**

- [x] Linux
- [x] MacOS
- [ ] Windows

## **Stack**

<div>
    <img src="https://github.com/devicons/devicon/blob/master/icons/cplusplus/cplusplus-original.svg" title="CPLUS" alt="CPLUS" width="40" height="40"/>&nbsp;
    <img src="https://github.com/Hasuk1/School-21-3DViewer_v2.0/blob/main/misc/qt_logo.png" title="CPLUS" alt="CPLUS" width="40" height="30"/>&nbsp;
    <img src="https://github.com/devicons/devicon/blob/master/icons/c/c-original.svg" title="C" alt="C" width="40" height="40"/>&nbsp;
    <img src="https://github.com/devicons/devicon/blob/master/icons/docker/docker-original.svg" title="docker" alt="docker" width="40" height="40"/>
</div>

## **Installation** 

```shell
git clone https://github.com/Hasuk1/School-21-SmartCalc_v2.0.git
cd School-21-SmartCalc_v2.0/src
make install
```
