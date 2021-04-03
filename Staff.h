#include "Person.h"

struct Staff : public Person {
private:
    int salary;

public:
    Staff(int id, char* firstName, char* lastName, char* dob, char* pass, bool gender, int salary) 
        : Person(id, firstName, lastName, dob, pass, gender) { 
            this -> salary = salary;
        }

    void display() {
        Person::display();

        cout << "Salary: " << salary << '\n';
    }
};