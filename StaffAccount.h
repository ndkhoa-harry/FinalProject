#ifndef _STAFF_ACCOUNT_H_
#define _STAFF_ACCOUNT_H_

#include "Helper.h"

#include "Account.h"
#include "Person.h"
#include "School.h"


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
        int choice;
        while (1) {
            cout << "\t\tSTAFF MENU:\n";
            cout << "\t1. School years\n";
            cout << "\t2. Import scoreboard\n";
            cout << "\t3. View profile info\n";
            cout << "\t4. Change password\n";
            cout << "\t0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    School school = School::getSchoolFromFile();
                    
                    school.displayMenu();
                    break;
                }

                case 2: {
                    importScoreBoard();

                    break;
                }

                case 3: {
                    staff -> display();

                    break;
                }

                case 4: {
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
    }
};

#endif