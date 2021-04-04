#include <iostream>
#include <string>
using namespace std;

struct Person {
protected:
    int id;
    string firstName, lastName, dob, pass;
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

    int ID()
    {
        return id;
    }

    string info(string input)
    {
        string si;
        if (input == "FirstName")
            si = firstName;
        else if (input == "LastName")
            si = lastName;
        else if (input == "DoB")
            si = dob;
        else if (input == "Gender")
        {    
            if (gender)
                si ="1";
            else si = "0";
        }
        return si;
    }
}; 