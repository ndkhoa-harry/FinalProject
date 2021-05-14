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

    void importScoreBoard() {
        string title = "Import score board";

        int fieldLength = 100;

        const int inputsCount = 2;

        string instructions[inputsCount] = {
            "Enter course ID: ",
            "Enter file Score.CSV directory: "
        };

        string inputsData[inputsCount] = { "", "" };

        if (drawInputBox(title, fieldLength, inputsCount, instructions, inputsData)) {
            int id = stoi(inputsData[0]);
            string dir = inputsData[1];

            ifstream inp(COURSES_FILE + to_string(id) + ".csv");

            string line;
            if (inp) {
                getline(inp, line);
                inp.close();
            }

            inp.open(dir); 

            if (inp) {
                ofstream out(COURSES_FILE + to_string(id) + ".csv");

                out << line << '\n';

                out << "private\n";
                while (getline(inp, line)) out << line << '\n';

                inp.close();
                out.close();

                updateStudentsOverallGPA(id);

                drawOkayBox("Message", "Import scoreboard successfully!");
            } else
                drawOkayBox("Error!!!", "Can't open file, please check your directory!");
        }
    }

    void updateStudentsOverallGPA(int id) {
        Course* course = new Course(id);

        course -> inputCourseFromFile();
        course -> updateStudentsOverallGPA();

        delete course;
    }

    void displayMyInformation() {
        string title = "Self information";

        const int containsCount = 4;
        string contains[containsCount] = {
            "SID: " + to_string(staff -> getId()),
            "Full name: " + staff -> getFullName(),
            "Gender: " + staff -> getGender(),
            "Date of Birth: " + staff -> getDob()
        };

        const int optionsCount = 1;
        string options[optionsCount] = { "OK" };

        int choice = 0;
        drawBox(title, containsCount, contains, optionsCount, options, choice);
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

                case 1: 
                    importScoreBoard();
                    break;

                case 2: 
                    displayMyInformation();
                    break;

                case 3: 
                    account -> displayChangePasswordBox();
                    break;

                default: 
                    return;
            }
        }
    }

    void getStaffAccountFromFile() {
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
    }
};

#endif
