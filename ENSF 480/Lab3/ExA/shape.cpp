/*
* File Name: shape.cpp
* Assignment: Lab 2 Exercise B
* Lab section: B02
* Completed by: Gerardo Garcia de Leon
* Development Date: Sept 22, 2023
*/

#include <iostream>
#include <cstring>
#include <cmath>
#include "shape.h"
using namespace std;

Shape::Shape(double x, double y, const char* name) : origin(x, y) 
{
	shapeName = new char[strlen(name) + 1];
	strcpy(shapeName, name);
}

Shape::~Shape()
{
	delete[] shapeName;
}

const Point& Shape::get_Origin() const
{
	return origin;
}

const char* Shape::get_name() const
{
	return shapeName;
}

void Shape::display() const
{
	cout << "Shape Name: " << shapeName <<endl;
	cout << "X-Coordinate: " << origin.get_x() <<endl;
	cout << "Y-Coordinate: " << origin.get_y() <<endl;
}

double Shape::distance(Shape& other) const
{
	return sqrt(pow(((origin.get_x()) - (other.origin.get_x())), 2) + pow(((origin.get_y()) - (other.origin.get_y())), 2));
}

double Shape::distance(Shape& the_shape, Shape& other)
{
	return sqrt(pow(((the_shape.origin.get_x()) - (other.origin.get_x())), 2) + pow(((the_shape.origin.get_y()) - (other.origin.get_y())), 2));
}

void Shape::move(double dx, double dy)
{
	origin.set_x(origin.get_x() + dx);
	origin.set_y(origin.get_y() + dy);
}

double Shape::area() const
{
	return 0;
}

double Shape::perimeter() const
{
	return 0;
}

Shape& Shape::operator =(Shape& s)
{
	if(this != &s)
	{
		delete[] shapeName;
		this->origin = s.get_Origin();
		this->shapeName = new char[strlen(s.get_name()) + 1];
		strcpy(this->shapeName, s.get_name());
	}
	
	return *this;
}

Shape::Shape(const Shape& src):origin(src.origin)
{
	shapeName = new char[strlen(src.shapeName) + 1];
	strcpy(shapeName, src.get_name());
}