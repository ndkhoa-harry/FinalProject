#ifndef _SCHOOL_H_
#define _SCHOOL_H_

#include "Helper.h"

#include "SchoolYear.h"

const int SCHOOL_TITLE_LINES = 4;
const string SCHOOL_TITLE[] = {
" ___  ___ _  _  ___   ___  _     __   _____   _   ___  ___ ",
"/ __|/ __| || |/ _ \\ / _ \\| |    \\ \\ / / __| /_\\ | _ \\/ __|",
"\\__ \\ (__| __ | (_) | (_) | |__   \\ V /| _| / _ \\|   /\\__ \\",
"|___/\\___|_||_|\\___/ \\___/|____|   |_| |___/_/ \\_\\_|_\\|___/"                                                    
};

const int SCHOOL_OPTIONS_COUNT = 6;
const string SCHOOL_OPTIONS[] = {
    "First year",
    "Second year",
    "Third year",
    "Forth year",
    "Find a school year",
    "Create new school year"
};

class School {
private:
    struct Node {
        SchoolYear* data;
        Node* next;
    };

    Node* head, *tail;
    int schoolYearsCount;

    bool dataModified;

public:
    School() {
        head = nullptr;
        tail = nullptr;
        schoolYearsCount = 0;

        dataModified = false;
    }

    ~School() {
        cout << "Destructor school\n";

        if (dataModified) putSchoolToFile();

        while (head) {
            Node* tmp = head;

            head = head -> next;

            delete tmp -> data;
            delete tmp;
        }
    }

    int getSchoolYearsCount() { return schoolYearsCount; }

    void addSchoolYear(SchoolYear* schoolYear) {
        if (!head) {
            head = new Node;
            tail = head;
        } else {
            tail -> next = new Node;
            tail = tail -> next;
        }

        tail -> data = schoolYear;
        tail -> next = nullptr;

        ++schoolYearsCount;
    }

    void addSchoolYearToHead(SchoolYear* schoolYear) {
        Node* newNode = new Node;

        newNode -> data = schoolYear;
        newNode -> next = head;

        if (!head) tail = newNode;
        head = newNode;

        ++schoolYearsCount;
    }

    SchoolYear* getSchoolYear(int id) {
        Node* cur = head;

        for (; id > 0; --id) cur = cur -> next;

        if (!cur -> data -> isAlreadyInputted())
            cur -> data -> getSchoolYearFromFile();

        return cur -> data;
    }

    SchoolYear* findSchoolYear(string schoolYearName) {
        Node* cur = head;

        while (cur) {
            if (cur -> data -> getName().compare(schoolYearName) == 0)
                return cur -> data;

            cur = cur -> next;
        }

        return nullptr;
    }

    void inputNewSchoolYear() {
        SchoolYear* newSchoolYear = SchoolYear::inputNewSchoolYear();

        if (newSchoolYear) {
            addSchoolYearToHead(newSchoolYear);

            newSchoolYear -> displayMenu();
        }
        
        dataModified = true;
    }
    
    void displayMenu() {
        int choice = 0;

        while (1) {
            drawMenu(SCHOOL_TITLE_LINES, SCHOOL_TITLE, SCHOOL_OPTIONS_COUNT, SCHOOL_OPTIONS, choice);

            if (0 <= choice && choice < 4) {
                SchoolYear* schoolYear = getSchoolYear(choice);
                schoolYear -> displayMenu();
            } else if (choice == 4) {
                string schoolYearName = "";

                if (drawInputBox("Find school year", 55, "Enter school year name you want to find: ", schoolYearName)) {
                    SchoolYear* schoolYear = findSchoolYear(schoolYearName);

                    if (schoolYear) 
                        schoolYear -> displayMenu();
                    else
                        drawOkayBox("Error!!!", "Can't find school year " + schoolYearName);
                }
            } else if (choice == 5) {
                inputNewSchoolYear();
            } else 
                return;
        }
    }

    static School getSchoolFromFile() {
        ifstream inp(SCHOOL_FILE);
        School school;

        if (inp) {
            string schoolYearName;

            while (inp >> schoolYearName) {
                SchoolYear* schoolYear = new SchoolYear(schoolYearName);
                school.addSchoolYear(schoolYear);
            }
        }

        inp.close();

        return school;
    }

    void putSchoolToFile() {
        ofstream out(SCHOOL_FILE);

        Node* cur = head;
        while (cur) {
            out << cur -> data -> getName() << '\n';
            cur = cur -> next;
        }

        out.close();
    }
};

#endif
