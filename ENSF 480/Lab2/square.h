/*
* File Name: square.h
* Assignment: Lab 2 Exercise B
* Lab section: B02
* Completed by: Gerardo Garcia de Leon
* Development Date: Sept 22, 2023
*/

#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
#include <cmath>
#include "shape.h"
using namespace std;

class Square: public Shape
{
	protected:
	  double side_a;
	  
	public:
	  Square(double x, double y, double side, const char* name);
	  double get_area() const;
	  double perimeter() const;
	  double get_sideA() const;
	  void set_side_a(double side);
	  void display() const;
};

#endif
	  