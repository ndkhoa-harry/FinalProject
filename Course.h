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

        if (scored) {
            string title = "COURSE " + courseName + " SCOREBOARD";

            const int columnsCount = 7;
            int columnsWidth[columnsCount] = { 5, 10, 30, 14, 14, 14, 14 };
            string columnsName[columnsCount] = {
                "No",
                "Student ID",
                "Full name",
                "Total mark",
                "Final mark",
                "Midterm mark",
                "Other mark"
            };

            int rowsCount = studentsCount;

            string** table = new string* [rowsCount];

            Node* cur = head;
            for (int i = 0; cur; ++i, cur = cur -> next) {
                Student* student = cur -> data;

                table[i] = new string[columnsCount] {
                    to_string(student -> getNo()),
                    to_string(student -> getId()),
                    student -> getFullName(),
                    toStringPrecision(student -> getTotalMark()),
                    toStringPrecision(student -> getFinalMark()),
                    toStringPrecision(student -> getMidtermMark()),
                    toStringPrecision(student -> getOtherMark())
                };
            }

            drawTable(12, title, columnsCount, columnsWidth, columnsName, rowsCount, table);
            cout << "\n\n";

            for (int i = 0; i < rowsCount; ++i) delete[] table[i];
            delete[] table;

            if (scoreboardPublished) {
                cout << "This scoreboard has been published!!\n";
                cout << "Press any key to continue\n";

                char c = getch();
            } else {
                cout << "Press (1) to update a student result\n";
                cout << "Press (2) to publish scoreboard\n";
                
                char c = getch();

                if (c == '1') {
                    string sID = "";
                    if (drawInputBox("Update student result", 35, "Enter student ID: ", sID)) {
                        int id = stoi(sID);

                        Student* student = findStudentFromID(id); 
                        
                        if (student -> inputScore()) {
                            drawOkayBox("Message", "Update student result successfully!");
                            dataModified = true;
                        } 
                    } 
                } else if (c == '2') {
                    if (drawYesNoBox("Publish scoreboard", "Do you really want to publish scoreboard?"))
                        publishScoreboard();
                } else
                    return;

                displayStaffCourse();
            }
        } else {
            string title = "LIST OF ENROLLED STUDENTS";

            const int columnsCount = 6;
            int columnsWidth[columnsCount] = { 10, 15, 25, 15, 15, 25 };
            string columnsName[columnsCount] = {
                "No",
                "Student ID",
                "Last name",
                "First name",
                "Gender",
                "Date of birth"
            };

            int rowsCount = studentsCount;

            string** table = new string* [rowsCount];

            Node* cur = head;
            for (int i = 0; cur; ++i, cur = cur -> next) {
                Student* student = cur -> data;

                table[i] = new string[columnsCount] {
                    to_string(student -> getNo()),
                    to_string(student -> getId()),
                    student -> getLastName(),
                    student -> getFirstName(),
                    student -> getGender(),
                    student -> getDob()
                };
            }

            drawTable(12, title, columnsCount, columnsWidth, columnsName, rowsCount, table);
            cout << "\n\n";

            for (int i = 0; i < rowsCount; ++i) delete[] table[i];
            delete[] table;

            cout << "Press (1) to Export this course to .csv file\n";
            char choice = getch();

            if (choice == '1') {
                string dir;
                if (drawInputBox("Export course", 100, "Enter the directory you want to store Course.csv file: ", dir)) {
                    exportToCSV(dir);

                    drawOkayBox("Message", "Export successfully!");
                } else
                    displayStaffCourse();
            } else 
                return;
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
         ofstream out(COURSES_FILE + to_string(id) + ".csv");

        out << id << ',';
        out << courseName << ',';
        out << teacherName << ',';
        out << credits << ',';
        out << maxStudents << ',';
        out << session1 << ',';
        out << session2 << ',';
        out << startDate << ',';
        out << endDate << '\n';

        if (scored) {
            if (scoreboardPublished)
                out << "public\n";
            else
                out << "private\n";
        }

        Node* cur = head;
        while (cur) {
            cur -> data -> putDataToStream(out);
            cur = cur -> next;
        };

        out.close();
    }

    void exportToCSV(string dir) {
        // TODO: Export to .csv file
          ofstream out(dir + '/' + to_string(id) + '_' + courseName + ".csv");

        Node* cur = head;
        while (cur) {
            Student* student = cur -> data;

            out << student -> getNo() << ',';
            out << student -> getId() << ',';
            out << student -> getFullName() << '\n';

            cur = cur -> next;
        }

        out.close();
    }
};

#endif
