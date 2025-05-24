/*
* File Name: circle.h
* Assignment: Lab 3 Exercise A
* Lab section: B02
* Completed by: Gerardo Garcia de Leon
* Development Date: Sept 27, 2023
*/

#ifndef CIRCLE_H
#define CIRCLE_H
#include <iostream>
#include "shape.h"
using namespace std;

class Circle : virtual public Shape
{
	private:
	  double radius;
	  
	public:
	  Circle(double rad, double x, double y, const char* name);
	  ~Circle();
      double getRadius() const;
      void setRadius(double r);
      virtual double area() const;
      virtual double perimeter() const;
      virtual void display() const;
	  Circle(const Circle& src);
	  Circle& operator=(Circle& c);
};

#endif
