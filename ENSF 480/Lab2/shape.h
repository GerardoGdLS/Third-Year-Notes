/*
* File Name: shape.h
* Assignment: Lab 2 Exercise B
* Lab section: B02
* Completed by: Gerardo Garcia de Leon
* Development Date: Sept 22, 2023
*/

#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
#include <cstring>
#include <cmath>
#include "point.h"
using namespace std;

class Shape
{
	protected:
	  Point origin;
	  char* shapeName;
	  
	public:
	  Shape(double x, double y, const char* name);
	  ~Shape();
	  Shape(const Shape& src);
	  const Point& get_Origin() const;
	  const char* get_name() const;
	  virtual void display() const = 0;
	  double distance (Shape& other) const;
	  static double distance (Shape& the_shape, Shape& other);
	  void move (double dx, double dy);
	  Shape& operator =(Shape& s);
	  
};

#endif