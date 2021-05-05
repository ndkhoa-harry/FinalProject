#ifndef _SCHOOL_H_
#define _SCHOOL_H_

#include "Helper.h"

#include "SchoolYear.h"

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

    SchoolYear* getSchoolYear(int id) {
        // TODO: Get school year in linked list

        return nullptr;
    }

    void inputNewSchoolYear() {
        // TODO: Input new school year by hand
    }
    
    void displayMenu() {
        int choice;
        while (1) {
            cout << "This is list of shool years: \n";

            Node* cur = head;
            for (int i = 1; cur; ++i, cur = cur -> next) 
                cout << '\t' << i << ". " << cur -> data -> getName() << '\n';
            cout << '\t' << schoolYearsCount + 1 << ". Create new school year\n";

            cout << "Enter your choice: "; cin >> choice;
            --choice;
            
            if (choice < schoolYearsCount) {
                SchoolYear* schoolYear = getSchoolYear(choice);
                schoolYear -> displayMenu();
            } else if (choice == schoolYearsCount) {
                inputNewSchoolYear();
            } else {
                return;
            }
        }
    }

    static School getSchoolFromFile() {
        // TODO: Get all school years from file
    }

    void putSchoolToFile() {
        // TODO: Update school informations to file
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
