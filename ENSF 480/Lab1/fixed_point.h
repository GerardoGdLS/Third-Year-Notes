/* File name: fixed_point.h
   Assignment: Lab 1 Exercise D
   Lab Section: B02
   Completed by: Gerardo Garcia de Leon
   Development Date: Sep 12th, 2024
*/

#ifndef POINT_H
#define POINT_H

#include <cstring>
using namespace std;

class Point{
	friend class Human; // This declaration allows the class Human to access the private x and y variables
	
private:
  double x;
  double y;
public:
  Point(double a, double b);
  double get_x() const; // Added const to clarify the function does not manipulate member variables
  double get_y() const; // Added const to clarify the function does not manipulate member variables
  void set_x(double a);
  void set_y(double y);
};

#endif