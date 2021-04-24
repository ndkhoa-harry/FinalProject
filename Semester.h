#ifndef _SEMESTER_H_
#define _SEMESTER_H_

#include "Helper.h"

#include "Student.h"
#include "Course.h"

class Semester {
private:
    struct Node {
        Course* data;
        Node* next;
    };

    string name, startDate, endDate;
    
    Node* head, *tail;
    int coursesCount;

    bool alreadyInputted, dataModified;

public:
    Semester() { 
        head = nullptr;
        tail = nullptr;
        coursesCount = 0;

        alreadyInputted = false;
        dataModified = false;
    }

    Semester(string name, string startDate, string endDate) : Semester() {
        this -> name = name;
        this -> startDate = startDate;
        this -> endDate = endDate;
    }

    ~Semester() {
        cout << "Destructor " << name << '\n';

        while (head) {
            Node* tmp = head;

            head = head -> next;

            delete tmp -> data;
            delete tmp;
        }
    }

    void setName(string name) { this -> name = name; }

    string getName() { return name; }

    void setStartDate(string startDate) { this -> startDate = startDate; }

    string getStartDate() { return startDate; }

    void setEndDate(string endDate) { this -> endDate = endDate; }

    string getEndDate() { return endDate; }

    int getCoursesCount() { return coursesCount; }

    bool isAlreadyInputted() { return alreadyInputted; }

    void addCourse(Course* course) {
        if (!head) {
            head = new Node;
            tail = head;
        } else {
            tail -> next = new Node;
            tail = tail -> next;
        }

        tail -> data = course;
        tail -> next = nullptr;

        ++coursesCount;
    }

    Course* getCourse(int id) {
         Node* cur = head;

        for(; id > 0; --id) cur = cur -> next;

        if (!cur -> data -> isAlreadyInputted())
            cur -> data -> inputCourseFromFile();

        return cur -> data;
        
    }

    Course* getCourseFromID(int id) {
        Node* cur = head;
        
        while (cur) {
            if (cur -> data -> getID() == id)
                return cur -> data;

            cur = cur -> next;
        }

        return nullptr;
    }

    void getCoursesList(int &coursesCount, int* &id, string* &name) {
        coursesCount = this -> coursesCount;

        id = new int[coursesCount];
        name = new string[coursesCount];

        Node* cur = head;
        for (int i = 0; cur; ++i, cur = cur -> next) {
            id[i] = cur -> data -> getID();
            name[i] = cur -> data -> getCourseName();
        }
    }

    void getAllCoursesInfo(int &coursesCount, Course* *&courses) {
        coursesCount = this -> coursesCount;
        courses = new Course*[coursesCount];

        Node* cur = head;
        for (int i = 0; cur; ++i) {
            courses[i] = cur -> data;

            if (!courses[i] -> isAlreadyInputted()) 
                courses[i] -> inputCourseFromFile();

            cur = cur -> next;
        }
    }

    void inputNewCourse() {
        addCourse(Course::inputNewCourse());

        dataModified = true;
    }

    void displayCoursesMenu() {
        cout << "This is list of courses in " << name << " semester: \n";

        Node* cur = head;
        for (int i = 0; cur; ++i, cur = cur -> next)
            cout << '\t' << i + 1 << ". " << cur -> data -> getCourseName() << '\n';
    }

    bool displayStaffMenu() {
        int choice;

        while (1) {
            displayCoursesMenu();

            cout << '\t' << coursesCount + 1 << ". Create course\n"; 

            cout << "Enter your choice: "; cin >> choice;
            --choice;

            if (choice < coursesCount) {
                Course* course = getCourse(choice);

                course -> displayStaffCourse();
            } else if (choice == coursesCount) {
                inputNewCourse();
            } else {
                return dataModified;
            }
        }
    }

    bool displayStudentMenu(Student* student, Course* *enrolledCourses, int &enrolledCoursesCount) {
        int choice;
        bool enrolled = false;

        while (1) {
            displayCoursesMenu();

            cout << "Enter your choice: "; cin >> choice;
            --choice;

            if (choice < coursesCount) {
                Course* course = getCourse(choice);

                enrolled |= course -> displayStudentCourse(student, enrolledCourses, enrolledCoursesCount);
            } else {
                return enrolled;
            }
        }
    }

    static Semester* inputNewSemester(int semesterOrder) {
        // TODO: Input new semester by hand

        return nullptr;
    }

    static Semester* getSemesterFromStringStream(stringstream &s, string semesterName) {
        // TODO: Get semester from stringstream

        return nullptr;
    }
};

#endif