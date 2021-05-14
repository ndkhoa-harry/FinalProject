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
    string courseID, courseName, teacherName, startDate, endDate;

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

    Course(int id, string courseID, string courseName, string teacherName, int credits, int maxStudents, int session1, int session2, string startDate, string endDate)
        : Course(id, courseName) {
            this -> courseID = courseID;
            this -> teacherName = teacherName;
            this -> credits = credits;
            this -> maxStudents = maxStudents;
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

    string getCourseID() { return courseID; }

    string getCourseName() { return courseName; }

    string getTeacherName() { return teacherName; }

    int getCredits() { return credits; }

    void setFirstSession(int session1) { this -> session1 = session1; }

    int getFirstSession() { return session1; }

    void setSecondSession(int session2) { this -> session2 = session2; }

    int getSecondSession() { return session2; }

    string getFirstSessionToString() {
        return DAY_OF_WEEK[session1 / 4] + " " + SESSIONS[session1 % 4];
    }

    string getSecondSessionToString() {
        return DAY_OF_WEEK[session2 / 4] + " " + SESSIONS[session2 % 4];
    }

    int getStudentsCount() { return studentsCount; }

    bool isScored() { return scored; }

    bool isPublished() { return scoreboardPublished; }

    bool isAlreadyInputted() { return alreadyInputted; }

    void addStudent(Student* student) {
        Node* pNew = new Node;

        pNew -> data = new Student;
        *pNew -> data = *student;

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
        Node* cur = head;

        while (cur) {
            cout << cur -> data -> getFullName() << '\n';
            if (cur -> data -> getId() == id) 
                return cur -> data;
            cur = cur -> next;
        }

        return nullptr;
    }

    void removeStudent(int id) {
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

    void updateStudentsOverallGPA() {
        Node* cur = head;
        while (cur) {
            cur -> data -> updateOverallGPA(credits);
            cur = cur -> next;
        }
    }

    void rearrangeNo() {
        Node* cur = head;
        for (int i = 1; cur; ++i) {
            cur -> data -> setNo(i);
            cur = cur -> next;
        } 
    }

    void publishScoreboard() {
        Node* cur = head;
        while (cur) {
            cur -> data -> publishScores(id);
            cur = cur -> next;
        }

        scoreboardPublished = true;
        dataModified = true;
    }

    void displayCourse() {
        system("cls");

        string title = courseName;
        gotoXY(2, (WINDOW_WIDTH - title.size()) / 2);
        cout << title;

        gotoXY(4, 0);
        cout << "\tCourse ID: " << courseID << '\n';
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

    bool displayStudentCourse(Student* student, int &enrolledCoursesCount, Course* *enrolledCourses) {
        displayCourse();

        if (enrolledCoursesCount >= 5) {
            cout << "You reach the maximum number of courses you can enroll!!!\n";
            getch();
        } else {
            Course* course = nullptr;
            bool enrolled = false, intersect = false;

            for (int i = 0; i < enrolledCoursesCount; ++i) {
                course = enrolledCourses[i];

                if (course -> getID() == id) {
                    enrolled = true;
                    break;
                } else if (course -> getFirstSession() == session1 || course -> getFirstSession() == session2
                            || course -> getSecondSession() == session1 || course -> getSecondSession() == session2) {
                    intersect = true;
                    break;
                }
            }

            if (enrolled) {
                cout << "You've already enrolled this course!!!\n";
                getch();
            } else if (intersect) {
                cout << "You can't enroll this course because the sessions of this course is conflicted with enrolled course sessions (Course " 
                        << course -> getCourseName() << ")\n";
                getch();
            } else if (studentsCount == maxStudents) {
                cout << "This course is full!!\n";
                getch();
            } else {
                cout << "Press (1) to enroll this course";
                char choice = getch();

                if (choice == '1') {
                    if (drawYesNoBox("Warning!!!", "Do you really want to enroll this course?")) {
                        enrolledCourses[enrolledCoursesCount++] = this;

                        addStudent(student);
                        rearrangeNo();

                        dataModified = true;

                        return true;
                    } else
                        return displayStudentCourse(student, enrolledCoursesCount, enrolledCourses);
                } else 
                    return false;
            }
        }

        return false;
    }

    static Course* inputNewCourse() {
        string title = "Create new course";

        int fieldLength = 100;

        const int inputsCount = 12;
        string instructions[inputsCount] = {
            "Course unique ID: ",
            "Course ID: ",
            "Course name: ",
            "Teacher name: ",
            "Number of credits: ",
            "Number of maximum students: ",
            "First day (Mon: 0, Tue: 1, Wed: 2, Thu: 3, Fri: 4, Sat: 5): ",
            "First session (SS1: 0, SS2: 1, SS3: 3, SS4: 4): ",
            "Second day (Mon: 0, Tue: 1, Wed: 2, Thu: 3, Fri: 4, Sat: 5): ",
            "Second session (SS1: 0, SS2: 1, SS3: 3, SS4: 4): ",
            "Registration start date (dd/mm/yyyy): ",
            "Redistration end date (dd/mm/yyyy): "
        };

        string* inputsData = new string[inputsCount];

        if (drawInputBox(title, fieldLength, inputsCount, instructions, inputsData)) {
            Course* course = new Course(
                stoi(inputsData[0]),
                inputsData[1],
                inputsData[2],
                inputsData[3],
                stoi(inputsData[4]),
                stoi(inputsData[5]),
                stoi(inputsData[6]) * 4 + stoi(inputsData[7]),
                stoi(inputsData[8]) * 4 + stoi(inputsData[9]),
                inputsData[10],
                inputsData[11]
            );

            course -> putCourseToFile();

            return course;
        } else
            return nullptr;
    }

    void inputCourseFromFile() {
        ifstream inp(COURSES_FILE + to_string(id) + ".csv");

        if (inp) {
            string line, data;

            getline(inp, line);

            stringstream s(line);

            getline(s, data, ',');
            id = stoi(data);

            getline(s, courseID, ',');

            getline(s, courseName, ',');

            getline(s, teacherName, ',');

            getline(s, data, ',');
            credits = stoi(data);

            getline(s, data, ',');
            maxStudents = stoi(data);

            getline(s, data, ',');
            session1 = stoi(data);

            getline(s, data, ',');
            session2 = stoi(data);

            getline(s, startDate, ',');
            getline(s, endDate, ',');

            if (getline(inp, line)) {
                if (line.compare("private") == 0) {
                    scored = true;
                    scoreboardPublished = false;
                } else if (line.compare("public") == 0) {
                    scored = true;
                    scoreboardPublished = true;
                } else {
                    stringstream s(line);
                    addStudent(Student::getStudentFromStringStream(s));
                }

                while (getline(inp, line)) {
                    stringstream s(line);
                    addStudent(Student::getStudentFromStringStream(s));
                } 
            }

            alreadyInputted = true;
        }

        rearrangeNo();

        inp.close();
    }

    void putCourseToFile() {
        ofstream out(COURSES_FILE + to_string(id) + ".csv");

        out << id << ','
            << courseID << ','
            << courseName << ','
            << teacherName << ','
            << credits << ','
            << maxStudents << ','
            << session1 << ','
            << session2 << ','
            << startDate << ','
            << endDate << '\n';

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
