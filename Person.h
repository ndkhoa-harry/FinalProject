#ifndef _PERSON_H_
#define _PERSON_H_

#include <iostream>
#include <string>
using namespace std;

struct Person {
private:
    int id;
    string firstName, lastName, gender, dob;

public:
    Person() { }

    Person(int id, string firstName, string lastName, string gender, string dob) {
        this->id = id;
        this->firstName = firstName;
        this->lastName = lastName;
        this->gender = gender;
        this->dob = dob;
    }

    void display() {
        cout << "ID: " << id << '\n';
        cout << "Full name: " << lastName << " " << firstName << '\n';
        cout << "Day of birth: " << dob << '\n';
        cout << "Gender: " << gender << '\n';
    }

    void setId(int id) { this -> id = id; }

    int getId() { return id; }

    void setFirstName(char* firstName) { this -> firstName = firstName; }

    string getFirstName() { return firstName; }

    void setLastName(char* lastName) { this -> lastName = lastName; }

    string getLastName() { return lastName; }

    void setGender(string gender) { this -> gender = gender; }

    string getGender() { return gender; }

    void setDob(char* dob) { this -> dob = dob; }

    string getDob() { return dob; }
}; 

#endif