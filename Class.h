#ifndef _CLASS_H_
#define _CLASS_H_

#include "Helper.h"

#include "Semester.h"
#include "Course.h"
#include "Student.h"

class Class {
private:
    struct Node {
        Student* data;
        Node* next;
    }; 

    string name, schoolYearName;
    Node* head, *tail;
    int studentsCount;

    bool alreadyInputted, dataModified;

public:
    Class() { 
        head = nullptr;
        tail = nullptr;
        studentsCount = 0;

        alreadyInputted = false;
        dataModified = false;
    }

    Class(string name) : Class() {
        this -> name = name; 
    }

    Class(string name, string schoolYearName) : Class(name) {
        this -> schoolYearName = schoolYearName;
    } 

    ~Class() {
        cout << "Destructor " << name << '\n';

        if (dataModified) putClassToFile();

        while (head) {
            Node* tmp = head;

            head = head -> next;

            delete tmp -> data;
            delete tmp;
        }
    }

    void setName(string name) { this -> name = name; }

    string getName() { return name; }

    string getSchoolYearName() { return schoolYearName; }

    bool isAlreadyInputted() { return alreadyInputted; }

    void addStudent(Student* student) {
        if (!head) {
            head = new Node;
            tail = head;
        } else {
            tail -> next = new Node;
            tail = tail -> next;
        }

        tail -> data = student;
        tail -> next = nullptr;

        studentsCount++;
    }

    void inputNewStudents() {
        // TODO: Input class by hand
        cout << "Enter students number: "; cin >> studentsCount;

        for (int i = 0; i < studentsCount; ++i) 
            addStudent(Student::inputNewStudent(i));

        dataModified = true;
    }

    void getAllStudentsInfo(int &studentsCount, Student* *&students) {
        // TODO: Get all students informations
        studentsCount = this -> studentsCount;
        students = new Student*[studentsCount];

        Node* cur = head;
        for (int i = 0; cur; ++i) {
            students[i] = cur -> data;
            cur = cur -> next;
    }

    void displayClassScoreboard(Semester* lastedSemester) {
        // TODO: Display class scoreboard
        Course* *courses;
        int coursesCount;
        lastedSemester -> getAllCoursesInfo(coursesCount, courses);
        
        Student* *students;
        int studentsCount;
        getAllStudentsInfo(studentsCount, students);
        cout << studentsCount << '\n';

        for (int i = 0; i < studentsCount; ++i) {
            students[i] -> display();

            cout << "Final mark of all courses: \n";

            double totalFinalMark = 0.0;
            int totalCredits = 0;

            for (int j = 0; j < coursesCount; ++j) {
                Student* scoredStudent = courses[j] -> findStudentFromID(students[i] -> getId());
                if (scoredStudent) {
                    cout << courses[j] -> getCourseName() << ": " << scoredStudent -> getFinalMark() << ' ';

                    totalFinalMark += scoredStudent -> getFinalMark() * courses[j] -> getCredits();
                    totalCredits += courses[j] -> getCredits();
                }
            }
            cout << '\n';

            cout << "GPA of " << lastedSemester -> getName() << " semester: " << totalFinalMark / totalCredits << '\n';
        }

        delete[] students;
        delete[] courses;
    }

    void displayMenu(Semester* lastedSemester) {
        int choice;

        cout << "This is class " << name << ":\n";
        cout << "\t1. View class info\n";
        cout << "\t2. View class score board\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            Node* cur = head;
            while (cur) {
                cout << '\t';
                cur -> data -> display();
                cur = cur -> next;
            }
        } else 
            displayClassScoreboard(lastedSemester);
    }

    static Class* inputNewClass() {
        int choice;

        cout << "Add new class: \n";
        cout << "\t1. Add manually\n";
        cout << "\t2. Add from .csv file\n";
        cout << "Enter your choice: "; cin >> choice;

        string className;
        cout << "Enter class name: "; cin >> className;

        Class* newClass = new Class(className);

        if (choice == 1) {
            newClass -> inputNewStudents();
        } else {
            // TODO: Input new class from file
        }

        return newClass;
    }

    void getClassFromFile() {
        // TODO: Get class from file
        ifstream inp(CLASSES_FILE + name + ".csv");

        if (inp) {
            string line;

            while (getline(inp, line)) {
                stringstream s(line);

                addStudent(Student::getStudentFromStringStream(s));
            }

            alreadyInputted = true;

            inp.close();
        }
    }

    void putClassToFile() {
        // TODO: Put class informations to file
         ofstream out(CLASSES_FILE + name + ".csv");

        Node* cur = head;
        while (cur) {
            cur -> data -> putDataToStream(out);
            cur = cur -> next;
        }

        out.close();
    }
};

#endif
