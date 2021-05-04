#ifndef _STAFF_ACCOUNT_H_
#define _STAFF_ACCOUNT_H_

#include "Helper.h"

#include "Account.h"
#include "Person.h"
#include "School.h"

const int STAFF_TITLE_LINES = 7;
const string STAFF_TITLE[] = {
    " __    __     ______     ______     _____     __         ______    ",
    "/\\ \"-./  \\   /\\  __ \\   /\\  __ \\   /\\  __-.  /\\ \\       /\\  ___\\   ",
    "\\ \\ \\-./\\ \\  \\ \\ \\/\\ \\  \\ \\ \\/\\ \\  \\ \\ \\/\\ \\ \\ \\ \\____  \\ \\  __\\   ",
    " \\ \\_\\ \\ \\_\\  \\ \\_____\\  \\ \\_____\\  \\ \\____-  \\ \\_____\\  \\ \\_____\\ ",
    "  \\/_/  \\/_/   \\/_____/   \\/_____/   \\/____/   \\/_____/   \\/_____/ ",
    "",
    "STAFF MENU"                                                        
};

const int STAFF_OPTIONS_COUNT = 5;
const string STAFF_OPTIONS[] = {
    "School",
    "Import scoreboard",
    "View profile information",
    "Change password",
    "Exit"
};

class StaffAccount {
private:
    Person* staff;
    Account* account;

public:
    StaffAccount() {
        staff = nullptr;    
        account = nullptr;
    }

    StaffAccount(Account* account) 
        : StaffAccount() {
            this -> account = account;
        }

    ~StaffAccount() {
        cout << "Destructor staff account\n";

        if (staff) delete staff;
        if (account) delete account;
    }

    static void importScoreBoard() {
        int id;
        string dir;

        cout << "Import score board\n";
        
        cout << "Enter course ID: "; cin >> id;
        cout << "Enter file .csv directory: "; cin >> dir;

        string line;

        ifstream inp(COURSES_FILE + to_string(id) + ".csv");
        if (inp) {
            getline(inp, line);
            inp.close();
        }

        inp.open(dir); 
        ofstream out(COURSES_FILE + to_string(id) + ".csv");
        if (inp) {
            out << line << '\n';
            
            out << "private\n";
            while (getline(inp, line)) out << line << '\n';

            inp.close();
        }

        out.close();
    }

    void displayMenu() {
        int choice = 0;

        while (1) {
            drawMenu(STAFF_TITLE_LINES, STAFF_TITLE, STAFF_OPTIONS_COUNT, STAFF_OPTIONS, choice);

            switch (choice) {
                case 0: {
                    School school = School::getSchoolFromFile();

                    school.displayMenu();
                    break;
                }

                case 1: {
                    importScoreBoard();
                    
                    break;
                }

                case 2: {
                    staff -> display();

                    break;
                }

                case 3: {
                    string pass;

                    cout << "Type your new password: ";
                    cin >> pass;
                    account -> changePassword(pass);
                    break;
                }
                default: 
                    return;
            }
        }
    }

    void getStaffAccountFromFile() {
        // TODO: Get staff account from file
         ifstream inp(STAFFS_FILE);

        if (inp) {
            string line;
            string* data = new string[STAFF_COMPONENTS_COUNT];

            while (!inp.eof()) {
                getline(inp, data[0], ',');
                if (stoi(data[0]) == account -> getId()) {
                    for (int i = 1; i < STAFF_COMPONENTS_COUNT - 1; ++i) 
                        getline(inp, data[i], ',');
                    getline(inp, data[STAFF_COMPONENTS_COUNT - 1]);

                    inp.close();

                    staff = new Person(
                        stoi(data[0]),
                        data[1],
                        data[2],
                        data[3],
                        data[4]
                    );

                    return;
                } else 
                    getline(inp, line);
            }

            delete[] data;

            inp.close();
    }
};

#endif
