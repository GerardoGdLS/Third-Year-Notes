/*
* File Name: curvecut.cpp
* Assignment: Lab 3 Exercise A
* Lab section: B02
* Completed by: Gerardo Garcia de Leon
* Development Date: Sept 27, 2023
*/

#include "curvecut.h"
#include <iostream>
#include <cmath>
using namespace std;

CurveCut::CurveCut(double rad, double x, double side1, double side2, double y, const char* name)
:Shape(x, y, name), Square(x, y, side1, name), Rectangle(x, y, side1, side2, name), Circle(rad, x, y, name) 
{
	if (this->getRadius() > min(side1, side2)) {
		cout << "Error: Radius of the cut cannot be larger than width or length." << endl;
		exit(1);
	}
}

CurveCut::~CurveCut()
{
	delete[] shapeName;
}

CurveCut::CurveCut(const CurveCut& src)
:Shape(src.origin.get_x(), src.origin.get_y(), src.get_name()), 
Square(src.origin.get_x(), src.origin.get_y(), src.get_sideA(), src.get_name()), 
Rectangle(src.origin.get_x(), src.origin.get_y(), src.get_sideA(), src.get_sideB(), src.get_name()),
Circle(src.getRadius(), src.origin.get_x(), src.origin.get_y(), src.get_name())
{
	;
}

CurveCut& CurveCut::operator=(CurveCut& cc)
{
	if(this != &cc)
	{
		Rectangle::operator=(cc);
		Circle::operator=(cc);
	}
	
	return *this;
}

double CurveCut::area() const 
{
    double rectangleArea = Rectangle::area();
    double quarterCircleArea = 0.25 * Circle::area(); //We do a quarter circle as this is the part that overlaps with the rectangle
	
    return rectangleArea - quarterCircleArea;
}

double CurveCut::perimeter() const 
{
    double rectanglePerimeter = Rectangle::perimeter();
    double quarterCirclePerimeter = 0.25 * Circle::perimeter();
	
    return rectanglePerimeter - Circle::getRadius() + quarterCirclePerimeter; //I believe this is how you get the area but i'm unsure
}

void CurveCut::display() const {
	cout << "CurveCut Name: " << get_name() << endl;
	cout << "X-coordinate: " << origin.get_x() << endl;
	cout << "Y-coordinate: " << origin.get_y() << endl;
	cout << "Width: " << get_sideA() << endl;
	cout << "Length: " << get_sideB() << endl;
	cout << "Radius of the cut: " << Circle::getRadius() << endl;
}