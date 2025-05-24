/* File name: fixed_human.cpp
   Assignment: Lab 1 Exercise D
   Lab Section: B02
   Completed by: Gerardo Garcia de Leon
   Development Date: Sep 12th, 2024
*/

#include <iostream>
#include <cstring>
#include "fixed_human.h"
using namespace std;

Human::Human() : name(new char[1]) {
    name[0] = '\0'; // Empty string just to allocate some memory
    location.set_x(0); 
    location.set_y(0);
}

Human::Human(const char* name, double x, double y): name(new char[strlen(name) + 1]) {
    strcpy(this->name, name);
    location.set_x(x);
    location.set_y(y);
}

Human::~Human() {
    delete[] name; // Deletes the dynamically allocated data to prevent memory leak
}

Human::Human(const Human& other): name(new char[strlen(other.name) + 1]){
    strcpy(name, other.name);
	location.set_x(other.location.get_x());
	location.set_y(other.location.get_y());
}

Human& Human::operator=(const Human& other) {
    if (this != &other) {
        delete[] this -> name; // Delete existing memory
        this -> name = new char[strlen(other.name) + 1]; 
        strcpy(this -> name, other.name);
        location.set_x(other.location.get_x());
		location.set_y(other.location.get_y());
    }
    return *this;
}

const char* Human::get_name() const {
    return name;
}

void Human::set_name(const char* name) {
    delete[] this -> name; // Delete existing memory
    this -> name = new char[strlen(name) + 1];
    strcpy(this -> name, name);
}

const Point Human::get_point() const {
    return location;
}

void Human::display() const {
    cout << "Human Name: " << name << "\nHuman Location: "
         << location.get_x() << " ,"
         << location.get_y() << ".\n" << endl;
}
