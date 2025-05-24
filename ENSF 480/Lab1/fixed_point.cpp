/* File name: fixed_point.cpp
   Assignment: Lab 1 Exercise D
   Lab Section: B02
   Completed by: Gerardo Garcia de Leon
   Development Date: Sep 12th, 2024
*/

#include "fixed_point.h"
using namespace std;

Point::Point(double a = 0, double b = 0): x(a), y(b) {}
double Point::get_x() const {return x;}
double Point::get_y() const {return y;}
void Point::set_x(double a) {x = a;}
void Point::set_y(double a) {y = a;}