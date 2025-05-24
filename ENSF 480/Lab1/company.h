/* File name: company.h
   Assignment: Lab 1 Exercise C
   Lab Section: B02
   Completed by: Gerardo Garcia de Leon
   Development Date: Sep 11th, 2024
*/

//company.h
#ifndef COMPANY_H
#define COMPANY_H

#include <string>
#include <vector>
#include "Address.h"
#include "Date.h"
#include "Customer.h"
#include "Employee.h"
using namespace std;

class Company{
	private:
	string name;
	Address address;
	Date dateEstablished;
	vector <Customer> customers;
	vector <Employee> employees;
	
	public:
	...
}

#endif