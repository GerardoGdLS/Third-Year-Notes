/* File name: customer.h
   Assignment: Lab 1 Exercise C
   Lab Section: B02
   Completed by: Gerardo Garcia de Leon
   Development Date: Sep 11th, 2024
*/

//customer.h
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include "address.h"
using namespace std;

class Customer {
private:
    string name;
    string phone;
    Address address;
public:
    ...
};

#endif