/*
* File Name: point.h
* Assignment: Lab 2 Exercise B
* Lab section: B02
* Completed by: Gerardo Garcia de Leon
* Development Date: Sept 22, 2023
*/

#ifndef POINT_H
#define POINT_H
#include <iostream>
using namespace std;

class Point{
	protected:
	  static int count;
	  int id;
	  double x;
	  double y;
	  
	public:
	  Point(double x, double y);
	  void display() const;
	  static int counter();
	  static double distance(Point& first, Point& other);
	  double distance(Point& other) const;
	  int get_id() const;
	  double get_x() const;
	  double get_y() const;
	  void set_x(double x);
	  void set_y(double y);
};

#endif