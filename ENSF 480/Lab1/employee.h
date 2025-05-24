/* File name: employee.h
   Assignment: Lab 1 Exercise C
   Lab Section: B02
   Completed by: Gerardo Garcia de Leon
   Development Date: Sep 11th, 2024
*/

//employee.h
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include "Address.h"
#include "Date.h"
using namespace std;

class Employee {
private:
    string name;
    Address address;
    string state;
    Date birthdate;
public:
    ...
};

#endif