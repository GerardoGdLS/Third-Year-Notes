/*
* File Name: mystring_B.h
* Assignment: Lab 2 Exercise A
* Lab section: B02
* Completed by: Gerardo Garcia de Leon
* Development Date: Sept 20, 2023
*/
#include <iostream>
#include <string>
using namespace std;

#ifndef MYSTRING_H
#define MYSTRING_H

class Mystring {

public:
  Mystring();
  // PROMISES: Empty string object is created.

  Mystring(int n); 
  // PROMISES: Creates an empty string with a total capacity of n.
  //           In other words, dynamically allocates n elements for
  //           charsM,sets the lengthM to zero, and fills the first 
  //           element of charsM with '\0'. 

  Mystring(const char *s); 
  // REQUIRES: s points to first char of a built-in string.
  // REQUIRES: Mystring object is created by copying chars from s.

  ~Mystring(); // destructor

  Mystring(const Mystring& source); // copy constructor

  Mystring& operator =(const Mystring& rhs); // assignment operator
  // REQUIRES: rhs is reference to a Mystring as a source
  // PROMISES: to make this-object (object that this is pointing to, as  a copy 
  //           of rhs.
  
  bool operator >=(const Mystring& other) const;
  // REQUIRES: other is reference to a Mystring as a source
  // PROMISES: to overload the >= operator to allow the desired output to be displayed
  
  friend ostream& operator<<(ostream& os, const Mystring& rhs);
  // REQUIRES: rhs is a reference to a Mystring as a source
  // PROMISES: to overload the << operator to allow the desired output to be displayed
  
  bool operator <=(const Mystring& other) const;
  // REQUIRES: other is a reference to a Mystring as a source
  // PROMISES: to overload the <= operator to allow the desired output to be displayed
  
  bool operator !=(const Mystring& other) const;
  // REQUIRES: other is a reference to a Mystring as a source
  // PROMISES: to overload the != operator to allow the desired output to be displayed
  
  bool operator >(const Mystring& other) const;
  // REQUIRES: other is a reference to a Mystring as a source
  // PROMISES: to overload the > operator to allow the desired output to be displayed
  
  bool operator <(const Mystring& other) const;
  // REQUIRES: other is a reference to a Mystring as a source
  // PROMISES: to overload the < operator to allow the desired output to be displayed
  
  bool operator ==(const Mystring& other) const;
  // REQUIRES: other is a reference to a Mystring as a source
  // PROMISES: to overload the == operator to allow the desired output to be displayed
  
  char& operator[](int index);
  //REQUIRES: index to be a valid index in the range of this->charsM and rhs to be a reference to a Mystring as a source
  //PROMISES: to return the character at index of charsM

  int length() const;
  // PROMISES: Return value is number of chars in charsM.

  char get_char(int pos) const;
  // REQUIRES: pos >= 0 && pos < length()
  // PROMISES:
  // Return value is char at position pos.
  // (The first char in the charsM is at position 0.)

  const char * c_str() const;
  // PROMISES:
  //   Return value points to first char in built-in string
  //   containing the chars of the string object.

  void set_char(int pos, char c);
  // REQUIRES: pos >= 0 && pos < length(), c != '\0'
  // PROMISES: Character at position pos is set equal to c.

  Mystring& append(const Mystring& other);

  // PROMISES: extends the size of charsM to allow concatenate other.charsM to 
  //           to the end of charsM. For example if charsM points to "ABC", and 
  //          other.charsM points to XYZ, extends charsM to "ABCXYZ".
  //

  void set_str(char* s);
  // REQUIRES: s is a valid C++ string of characters (a built-in string)
  // PROMISES:copys s into charsM, if the length of s is less than or equal lengthM.
  //          Othrewise, extends the size of the charsM to s.lengthM+1, and copies 
  //          s into the charsM.
    
  

  int isEqual (const Mystring& s)const;
  // REQUIRES: s refers to an object of class Mystring
  // PROMISES: retruns true if charsM equal s.charsM.


 private:

  int lengthM; // the string length - number of characters excluding \0
  char* charsM; // a pointer to the beginning of an array of characters, allocated dynamically.
  void memory_check(char* s);
  // PROMISES: if s points to NULL terminates the program.
};
#endif











