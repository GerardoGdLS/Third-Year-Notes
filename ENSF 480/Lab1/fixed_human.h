/* File name: fixed_human.h
   Assignment: Lab 1 Exercise D
   Lab Section: B02
   Completed by: Gerardo Garcia de Leon
   Development Date: Sep 12th, 2024
*/

#ifndef HUMAN_H
#define HUMAN_H

#include <cstring>
#include <iostream>
using namespace std;

class Human{
protected:
  Point location;
  char* name;

public:
  Human(); //Added a default constructor to have default values
  Human(const char* name, double x, double y);
  ~Human(); // Added a destructor 
  Human& operator =(const Human& other); // Added an assignment operator
  Human(const Human& other); // Added copy constructor
  const char* get_name() const; // Added const keyword to encapsulate
  void set_name(const char* name); // Added const keyword to ensure no accidental changes to the name argument
  const Point get_point() const; // Added const to encapsulate
  void display() const; // Added const as it does not change member values
}

#endif