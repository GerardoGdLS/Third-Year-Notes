/*
* File Name: curvecut.h
* Assignment: Lab 3 Exercise A
* Lab section: B02
* Completed by: Gerardo Garcia de Leon
* Development Date: Sept 27, 2023
*/

#ifndef CURVECUT_H
#define CURVECUT_H

#include "rectangle.h"
#include "circle.h"
using namespace std;

class CurveCut : public Rectangle, public Circle 
{
	public:
      CurveCut(double rad, double x, double side1, double side2, double y, const char* name);
	  ~CurveCut();
	  CurveCut(const CurveCut& src);
	  CurveCut& operator=(CurveCut& cc);
      double area() const;
      double perimeter() const;
      void display() const;
};

#endif
