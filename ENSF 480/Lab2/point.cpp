/*
* File Name: point.cpp
* Assignment: Lab 2 Exercise B
* Lab section: B02
* Completed by: Gerardo Garcia de Leon
* Development Date: Sept 22, 2023
*/

#include <iostream>
#include <cmath>
#include "point.h"
using namespace std;


int Point::count = 0;

Point::Point(double x, double y)
{
	id = 1001 + count;
	set_x(x);
	set_y(y);
	count++;
}

void Point::display() const
{
	cout << "\nX-coordinate: " << get_x();
	cout << "\nY-coordinate: " << get_y();
}

double Point::get_x() const
{
	return x;
}

double Point::get_y() const
{
	return y;
}

int Point::get_id() const
{
	return id;
}

void Point::set_y(double y)
{
	this->y = y;
}

void Point::set_x(double x)
{
	this->x = x;
}

int Point::counter()
{
	return count;
}

double Point::distance(Point& first, Point& other)
{
	return sqrt(pow((first.get_x() - other.get_x()), 2) + pow((first.get_y() - other.get_y()), 2));
}

double Point::distance(Point& other) const
{
	return sqrt(pow(((x) - (other.get_x())), 2) + pow(((y) - (other.get_y())), 2));
}