/*
* File Name: rectangle.h
* Assignment: Lab 2 Exercise B
* Lab section: B02
* Completed by: Gerardo Garcia de Leon
* Development Date: Sept 22, 2023
*/

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>
#include "square.h"
#include "shape.h"
using namespace std;

class Rectangle : virtual public Square
{
	private:
	  double side_b;
	  
	public:
	  Rectangle (double x, double y, double side1, double side2, const char* name);
	  virtual double get_area() const;
	  virtual double perimeter() const;
	  double get_sideB() const;
	  void set_side_b(double side);
	  virtual void display() const;
	  Rectangle(const Rectangle& src);
	  Rectangle& operator=(Rectangle& r);
};

#endif	  
	  