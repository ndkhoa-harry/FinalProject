#ifndef _DATE_H_
#define _DATE_H_

#include <iostream>
#include <string>

using namespace std;

class Date {
private:
    string date;

public:
    Date(string date) {
        this -> date = date;
    }

    int getYear() {
        return stoi(date.substr(6));
    }
};

#endif
