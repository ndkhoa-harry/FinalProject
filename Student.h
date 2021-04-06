#ifndef _STUDENT_H_
#define _STUDENT_H_

#include "Person.h"

class Student : public Person {
private:
    int no;
    
public:
    static const int componentsCount = 6;

    Student() { }

    Student(int no, int id, string firstName, string lastName, string gender, string dob)
        : Person(id, firstName, lastName, gender, dob) {
            this -> no = no;
        }

    void display() {
        cout << "No: " << no << '\n';
        Person::display();
    }

    void setNo(int no) { this -> no = no; }

    int getNo() { return no; }
};

#endif