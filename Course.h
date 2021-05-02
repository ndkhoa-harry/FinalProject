#ifndef _COURSE_H_
#define _COURSE_H_

#include "Helper.h"

#include "Student.h"

class Course {
private:
    struct Node {
        Student* data;
        Node* next;
    };

    int id, credits, maxStudents, session1, session2;
    string courseName, teacherName, startDate, endDate;

    Node* head, *tail;
    int studentsCount;

    bool scored, scoreboardPublished;
    bool alreadyInputted, dataModified;

public:
    Course() { 
        head = nullptr;
        tail = nullptr;

        studentsCount = 0;

        scored = false;
        scoreboardPublished = false;

        alreadyInputted = false;
        dataModified = false;
    }

    Course(int id) : Course() {
        this -> id = id;
    }

    Course(int id, string courseName) : Course(id) {
        this -> courseName = courseName;
    }

    Course(int id, string courseName, string teacherName, int credits, int session1, int session2, string startDate, string endDate)
        : Course(id, courseName) {
            this -> teacherName = teacherName;
            this -> credits = credits;
            this -> session1 = session1;
            this -> session2 = session2;
            this -> startDate = startDate;
            this -> endDate = endDate;
        }

    ~Course() {
        cout << "Destructor " << courseName << '\n';

        if (dataModified) putCourseToFile();

        while (head) {
            Node* tmp = head;

            head = head -> next;

            delete tmp -> data;
            delete tmp;
        }
    }

    int getID() { return id; }

    string getCourseName() { return courseName; }

    int getCredits() { return credits; }

    int getStudentsCount() { return studentsCount; }

    bool isAlreadyInputted() { return alreadyInputted; }

    void addStudent(Student* student) {
        Node* pNew = new Node;

        pNew -> data = student;
        pNew -> next = nullptr;

        if (!head) {
            head = pNew;
            tail = head;
        } else if (student -> getId() < head -> data -> getId()) {
            pNew -> next = head;
            head = pNew;
        } else {
            Node* pCur = head;

            while (pCur -> next && student -> getId() > pCur -> next -> data -> getId()) 
                pCur = pCur -> next;

            pNew -> next = pCur -> next;
            pCur -> next = pNew;
        }

        ++studentsCount;
    }

    Student* findStudentFromID(int id) {
        // TODO: Find student from ID
        Node* cur = head;

        while (cur) {
            cout << cur -> data -> getFullName() << '\n';
            if (cur -> data -> getId() == id) 
                return cur -> data;
            cur = cur -> next;
        return nullptr;
    }

    void removeStudent(int id) {
        // TODO: Remove student from course
         Node* cur = head, *tmp;

        if (head -> data -> getId() == id) {
            tmp = head;
            head = head -> next;
            delete tmp;
        } else {
            while (cur -> next -> data -> getId() != id)
                cur = cur -> next;

            tmp = cur -> next;
            cur -> next = cur -> next -> next;
            delete tmp;
        }

        --studentsCount;

        dataModified = true;
    }

    void rearrangeNo() {
        // TODO: Rearrange no of all students
    }

    void publishScoreboard() {
        // TODO: Publish scoreboard
    }

    void displayCourse() {
        cout << "Course " << id << " information:\n";
        cout << "\tCourse name: " << courseName << '\n';
        cout << "\tTeacher name: " << teacherName << '\n';
        cout << "\tMaximum number of students: " << maxStudents << '\n';
        cout << "\tTimetable: \n";
        cout << "\t\tFirst day: " << DAY_OF_WEEK[session1 / 4] << " " << SESSIONS[session1 % 4] << '\n';
        cout << "\t\tSecond day: " << DAY_OF_WEEK[session2 / 4] << " " << SESSIONS[session2 % 4] << '\n';
        cout << '\n';
    }

    void displayStaffCourse() {
        displayCourse();

        cout << "List of students:\n";
        
        Node* cur = head;
        while (cur) {
            cur -> data -> display();
            cur = cur -> next;
        }

        int choice;
        if (scored) {
            if (scoreboardPublished)
                cout << "This scoreboard has been published!!!\n";
            else {
                cout << "Press (1) to update a student result\n";
                cout << "Press (2) to publish scoreboard\n";
                cin >> choice;

                if (choice == 1) {
                    int id;
                    cout << "Enter student ID: "; cin >> id;

                    // TODO: Update student scores
                } else if (choice == 2) {
                    publishScoreboard();
                }
            }
        } else {
            cout << "Press (1) to Export this course to .csv file: ";
            cin >> choice;

            if (choice == 1) {
                string dir;
                cout << "Enter the directory you want to store your file: ";
                cin >> dir;

                exportToCSV(dir);
            }
        }
    }

    bool displayStudentCourse(Student* student, Course* *enrolledCourses, int &enrolledCoursesCount) {
        displayCourse();

        if (enrolledCoursesCount >= 5) {
            cout << "You reach the maximum number of courses you can enroll!!!\n";
        } else {
            bool enrolled = false;
            for (int i = 0; i < enrolledCoursesCount; ++i) 
                if (enrolledCourses[i] -> getID() == id) {
                    enrolled = true;
                    break;
                }

            if (enrolled) 
                cout << "You've already enrolled this course!!!\n";
            else if (studentsCount == maxStudents)
                cout << "This course is full!!\n";
            else {
                int choice;

                cout << "Press (1) to enroll this course: ";
                cin >> choice;

                if (choice == 1) {
                    // TODO: Enroll student to this course

                    return true;
                } else 
                    return false;
            }
        }

        return false;
    }

    static Course* inputNewCourse() {
        // TODO: Input new course by hand

        return nullptr;
    }

    void inputCourseFromFile() {
        // TODO: Input course from file
    }

    void putCourseToFile() {
        // TODO: Update course informations to file
    }

    void exportToCSV(string dir) {
        // TODO: Export to .csv file
    }
};

#endif
