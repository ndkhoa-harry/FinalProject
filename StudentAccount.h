#ifndef _STUDENT_ACCOUNT_H_
#define _STUDENT_ACCOUNT_H_

#include "Helper.h"

#include "SchoolYear.h"
#include "Semester.h"
#include "Course.h"
#include "Student.h"

class StudentAccount {
private:
    Student* student;
    Semester* semester;
    string schoolYearName, className;

    Account* account;
    
    Course* *enrolledCourses;
    int enrolledCoursesCount;

    bool dataModified;

public:
    StudentAccount() {
        student = nullptr;
        semester = nullptr;

        account = nullptr;

        enrolledCourses = new Course*[MAX_ENROLLED_COURSES];
        enrolledCoursesCount = 0;

        dataModified = false;
    }

    StudentAccount(Account* account)
        : StudentAccount() {
            this -> account = account;
        }

    ~StudentAccount() {
        cout << "Destructor student account\n";

        if (dataModified) putStudentAccountToFile();

        if (semester) delete semester;

        if (account) delete account;

        delete[] enrolledCourses;
    }

    void setStudent(Student* student) { this -> student = student; }

    void setClassName(string className) { this -> className = className; }

    int getEnrolledCoursesCount() { return enrolledCoursesCount; }

    void addCourse(Course* course) {
        if (course && enrolledCoursesCount < MAX_ENROLLED_COURSES)
            enrolledCourses[enrolledCoursesCount++] = course;
    }

    void removeCourse(int id) {
        // TODO: Remove course from list
    }

    void enrolledCoursesMenu() {
        int choice;

        while (1) {
            cout << "This is list of enrolled courses: \n";
            
            for (int i = 0; i < enrolledCoursesCount; ++i) 
                cout << '\t' << i + 1 << ". " << enrolledCourses[i] -> getCourseName() << '\n';
            cout << '\t' << enrolledCoursesCount + 1 << ". Remove a course\n";

            int choice;
            cout << "Enter your choice: "; cin >> choice;
            --choice;

            if (choice < enrolledCoursesCount) {
                if (!enrolledCourses[choice] -> isAlreadyInputted())
                    enrolledCourses[choice] -> inputCourseFromFile();

                enrolledCourses[choice] -> displayCourse();
            } else if (choice == enrolledCoursesCount) {
                cout << "Enter the course you want to remove: ";
                cin >> choice;
                --choice;

                removeCourse(choice);
            } else
                return;
        }
    }
    
    void displayScoreboardFromFile() {
        // TODO: Display scoreboard from file
    }

    void displayMenu() {
        int choice;
        while (1) {
            cout << "\t\tSTUDENT MENU\n";
            cout << "\t1. Courses\n";
            cout << "\t2. Enrolled courses\n";
            cout << "\t3. View my scoreboard\n";
            cout << "\t4. View profile info\n";
            cout << "\t5. Change password\n";
            cout << "\t0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    dataModified |= semester -> displayStudentMenu(student, enrolledCourses, enrolledCoursesCount);

                    break;
                }

                case 2: {
                    enrolledCoursesMenu();

                    break;
                }

                case 3: {
                    displayScoreboardFromFile();

                    break;
                }

                case 4: {
                    student -> display();

                    break;
                }

                case 5: {
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

    void getStudentAccountFromFile() {
        // TODO: Get student account informations from file
    }

    void putStudentAccountToFile() {
        // TODO: Update student account informations to file
    }
};

#endif