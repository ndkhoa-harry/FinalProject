#include <iostream>
#include <string>
using namespace std;

struct Person {
protected:
    int id;
    char* firstName,* lastName,* dob;
    bool gender;

public:
    Person(int id, char* firstName, char* lastName, char* dob, bool gender) {
        this->id = id;
        this->firstName = firstName;
        this->lastName = lastName;
        this->dob = dob;
        this->gender = gender;
    }

    void display() {
        cout << "ID: " << id << '\n';
        cout << "Full name: " << firstName << " " << lastName << '\n';
        cout << "Day of birth: " << dob << '\n';
        cout << "Gender: " << (gender ? "Female" : "Male") << '\n';
    }

    int ID()
    {
        return id;
    }

    char* info(int input)
    {
        if (input == 1)
            return firstName;
        else if (input == 2)
            return lastName;
        else if (input == 3)
            return dob;
    }

    bool gendr()
    {
        return gender;
    }
}; 