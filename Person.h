#include <iostream>

using namespace std;

struct Person {
private:
    int id;
    char* firstName, *lastName, *dob, *pass;
    bool gender;

public:
    Person(int id, char* firstName, char* lastName, char* dob, char* pass, bool gender) {
        this->id = id;
        this->firstName = firstName;
        this->lastName = lastName;
        this->dob = dob;
        this->pass = pass;
        this->gender = gender;
    }

    void display() {
        cout << "ID: " << id << '\n';
        cout << "Full name: " << firstName << " " << lastName << '\n';
        cout << "Day of birth: " << dob << '\n';
        cout << "Gender: " << (gender ? "Female" : "Male") << '\n';
    }
};