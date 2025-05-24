/*
* File Name: circle.cpp
* Assignment: Lab 3 Exercise A
* Lab section: B02
* Completed by: Gerardo Garcia de Leon
* Development Date: Sept 27, 2023
*/

#include <iostream>
#include "circle.h"
#include <cmath>
using namespace std;

Circle::Circle(double rad, double x, double y, const char* name): Shape(x, y, name)
{
	setRadius(rad);
	shapeName = new char[strlen(name) + 1];
	strcpy(shapeName, name);
}

Circle::~Circle()
{
	delete[] shapeName;
}

double Circle::getRadius() const
{
	return radius;
}

void Circle::setRadius(double r)
{
	radius = r;
}

double Circle::area() const
{
	return M_PI*radius*radius;
}

double Circle::perimeter() const
{
	return 2*M_PI*radius;
}

void Circle::display() const {
    cout << "Circle: " << get_name() << endl;
	cout << "X-Coordinate: " << origin.get_x() << endl;
	cout << "Y-Coordinate: " << origin.get_y() << endl;
	cout << "Radius: " << radius << endl;
	cout << "Area: " << area() << endl;
	cout << "Perimeter: " << perimeter() << endl;
}

Circle::Circle(const Circle& src):Shape(src.origin.get_x(), src.origin.get_y(), src.get_name())
{
	setRadius(src.getRadius());
}

Circle& Circle::operator=(Circle& c)
{
	if(this != &c){
		Shape::operator=(c);
		setRadius(c.getRadius());
	}
	
	return *this;
}