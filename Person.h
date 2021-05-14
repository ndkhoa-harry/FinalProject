#ifndef _PERSON_H_
#define _PERSON_H_

#include <iostream>
#include <string>
#include "Account.h"

using namespace std;

class Person {
private:
    int id;
    string firstName, lastName, fullName, gender, dob;

public:
    Person() { }

    Person(int id, string fullName) { 
        this -> id = id;
        this -> fullName = fullName;
    }

    Person(int id, string firstName, string lastName, string gender, string dob)
        : Person(id, lastName + ' ' + firstName) {
            this -> id = id;
            this -> firstName = firstName;
            this -> lastName = lastName;
            this -> gender = gender;
            this -> dob = dob;
        }

    void setId(int id) { this -> id = id; }

    int getId() { return id; }

    void setFirstName(char* firstName) { this -> firstName = firstName; }

    string getFirstName() { return firstName; }

    void setLastName(char* lastName) { this -> lastName = lastName; }

    string getLastName() { return lastName; }

    string getFullName() { return fullName; }

    void setGender(string gender) { this -> gender = gender; }

    string getGender() { return gender; }

    void setDob(char* dob) { this -> dob = dob; }

    string getDob() { return dob; }
}; 

#endif
