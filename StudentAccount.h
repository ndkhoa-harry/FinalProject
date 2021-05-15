#ifndef _STUDENT_ACCOUNT_H_
#define _STUDENT_ACCOUNT_H_

#include "Helper.h"

#include "SchoolYear.h"
#include "Semester.h"
#include "Course.h"
#include "Student.h"

const int STUDENT_TITLE_LINES = 7;
const string STUDENT_TITLE[] = {
    " __    __     ______     ______     _____     __         ______    ",
    "/\\ \"-./  \\   /\\  __ \\   /\\  __ \\   /\\  __-.  /\\ \\       /\\  ___\\   ",
    "\\ \\ \\-./\\ \\  \\ \\ \\/\\ \\  \\ \\ \\/\\ \\  \\ \\ \\/\\ \\ \\ \\ \\____  \\ \\  __\\   ",
    " \\ \\_\\ \\ \\_\\  \\ \\_____\\  \\ \\_____\\  \\ \\____-  \\ \\_____\\  \\ \\_____\\ ",
    "  \\/_/  \\/_/   \\/_____/   \\/_____/   \\/____/   \\/_____/   \\/_____/ ",
    "",
    "STUDENT MENU"  
};

const int STUDENT_OPTIONS_COUNT = 6;
const string STUDENT_OPTIONS[] = {
    "Current semester courses",
    "Enrolled courses",
    "View my scoreboard",
    "View my infomation",
    "Change password",
    "Exit"
};

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

        delete student;
        delete[] enrolledCourses;
    }

    void setStudent(Student* student) { this -> student = student; }

    void setClassName(string className) { this -> className = className; }

    int getEnrolledCoursesCount() { return enrolledCoursesCount; }

    void addCourse(Course* course) {
        if (course && enrolledCoursesCount < MAX_ENROLLED_COURSES)
            enrolledCourses[enrolledCoursesCount++] = course;
    }

    Course* getEnrolledCourse(int id) {
        Course* course = nullptr;

        if (id < enrolledCoursesCount) 
            course = enrolledCourses[id];

        if (course && !course -> isAlreadyInputted())
            course -> inputCourseFromFile();

        return course;
    }

    void removeCourse(string courseID) {
        int id = -1;
        for (int i = 0; i < enrolledCoursesCount; ++i)
            if (enrolledCourses[i] -> getCourseID().compare(courseID) == 0) {
                id = i;
                break;
            }
        if (id < 0) return;

        if (!enrolledCourses[id] -> isAlreadyInputted())
            enrolledCourses[id] -> inputCourseFromFile();

        enrolledCourses[id] -> removeStudent(student -> getId());

        for (int i = id; i < enrolledCoursesCount - 1; ++i) 
            enrolledCourses[i] = enrolledCourses[i + 1];

        --enrolledCoursesCount;

        dataModified = true;
    }

    void enrolledCoursesTable() {
        const int titleLines = 4;
        string title[titleLines] = {        
            " ___ _  _ ___  ___  _    _    ___ ___     ___ ___  _   _ ___  ___ ___ ___ ",
            "| __| \\| | _ \\/ _ \\| |  | |  | __|   \\   / __/ _ \\| | | | _ \\/ __| __/ __|",
            "| _|| .` |   / (_) | |__| |__| _|| |) | | (_| (_) | |_| |   /\\__ \\ _|\\__ \\",
            "|___|_|\\_|_|_\\\\___/|____|____|___|___/   \\___\\___/ \\___/|_|_\\|___/___|___/"                                                                     
        };

        const int columnsCount = 7;
        int columnsWidth[columnsCount] = { 4, 11, 13, 30, 9, 20, 20 };
        string columnsName[columnsCount] = {
            "No",
            "Course ID",
            "Course name",
            "Teacher name",
            "Credits",
            "First session",
            "Second session"
        };

        while (1) {
            int x = 3;

            system("cls");
            drawTitle(x, titleLines, title);

            const int rowsCount = enrolledCoursesCount;

            string** table = new string* [rowsCount];
            for (int i = 0; i < rowsCount; ++i) {
                Course* course = getEnrolledCourse(i);

                table[i] = new string[columnsCount] {
                    to_string(i + 1),
                    course -> getCourseID(),
                    course -> getCourseName(),
                    course -> getTeacherName(),
                    to_string(course -> getCredits()),
                    course -> getFirstSessionToString(),
                    course -> getSecondSessionToString()
                };
            }

            ++x;
            drawTable(x, "", columnsCount, columnsWidth, columnsName, rowsCount, table);
            cout << "\n\n";

            for (int i = 0; i < rowsCount; ++i) delete[] table[i];
            delete[] table;

            if (enrolledCoursesCount > 0) {
                cout << "Press (1) to remove a course\n";

                char choice = getch();

                if (choice == '1') {
                    string courseID;

                    cout << "Enter the course ID you want to remove: ";
                    cin >> courseID;

                    if (drawYesNoBox("Warning!!!", "Do you really want to remove this course?")) 
                        removeCourse(courseID);
                } else
                    return;
            } else {
                getch();
                
                return;
            }
        }
    }
    
    void displayScoreboardFromFile() {
        const int titleLines = 4;
        string title[titleLines] = {
            " ___  ___ ___  ___ ___ ___  ___   _   ___ ___  ",
            "/ __|/ __/ _ \\| _ \\ __| _ )/ _ \\ /_\\ | _ \\   \\ ",
            "\\__ \\ (_| (_) |   / _|| _ \\ (_) / _ \\|   / |) |",
            "|___/\\___\\___/|_|_\\___|___/\\___/_/ \\_\\_|_\\___/ ",                                       
        };

        const int columnsCount = 7;
        int columnsWidth[columnsCount] = { 4, 11, 13, 14, 14, 14, 14 };
        string columnsName[columnsCount] = {
            "No",
            "Course ID",
            "Course name",
            "Total mark",
            "Final mark",
            "Midterm mark",
            "Other mark"
        };

        const int rowsCount = enrolledCoursesCount;

        string** table = new string* [rowsCount];

        for (int i = 0; i < enrolledCoursesCount; ++i) {
            Course* course = getEnrolledCourse(i);

            table[i] = new string[columnsCount] {
                    to_string(i + 1),
                    course -> getCourseID(),
                    course -> getCourseName(),
                    "x",
                    "x",
                    "x",
                    "x"
                };

            if (course -> isPublished()) {
                Student* student = course -> findStudentFromID(account -> getId());

                table[i][3] = toStringPrecision(student -> getTotalMark());
                table[i][4] = toStringPrecision(student -> getFinalMark());
                table[i][5] = toStringPrecision(student -> getMidtermMark());
                table[i][6] = toStringPrecision(student -> getOtherMark());
            } 
        }

        system("cls");

        int x = 3;
        drawTitle(x, titleLines, title);
        
        ++x;
        drawTable(x, "", columnsCount, columnsWidth, columnsName, rowsCount, table);

        getch();
    }

    void displayMyInformation() {
        string title = "Self information";

        const int containsCount = 5;
        string contains[containsCount] = {
            "SID: " + to_string(student -> getId()),
            "Class: " + className,
            "Full name: " + student -> getFullName(),
            "Gender: " + student -> getGender(),
            "Date of Birth: " + student -> getDob()
        };

        const int optionsCount = 1;
        string options[optionsCount] = { "OK" };

        int choice = 0;
        drawBox(title, containsCount, contains, optionsCount, options, choice);
    }

    void displayMenu() {
        int choice = 0;

        while (1) {
            drawMenu(STUDENT_TITLE_LINES, STUDENT_TITLE, STUDENT_OPTIONS_COUNT, STUDENT_OPTIONS, choice);

            switch (choice) {
                case 0: 
                    dataModified |= semester -> displayStudentMenu(student, enrolledCourses, enrolledCoursesCount);
                    break;
                
                case 1: 
                    enrolledCoursesTable();
                    break;

                case 2: 
                    displayScoreboardFromFile();
                    break;
            
                case 3: 
                    displayMyInformation();
                    break;
                
                case 4: 
                    account -> displayChangePasswordBox();
                    break;
                
                default: 
                    return;
            }
        }
    }

    void getStudentAccountFromFile() {
        ifstream inp(STUDENTS_FILE + to_string(account -> getId()) + ".csv");
        if (inp) {
            string line, data;

            getline(inp, schoolYearName, ',');
            semester = SchoolYear::getLastedSemesterFromFile(schoolYearName);

            getline(inp, className);

            getline(inp, line);
            stringstream s(line);
            student = Student::getStudentFromStringStream(s);

            getline(inp, data, ',');
            student -> setOverallMarks(stod(data));
            getline(inp, data);
            student -> setOverallCredits(stoi(data));

            while (getline(inp, line)) {
                cout << line << '\n';
                stringstream s(line);

                getline(s, data, ',');
                Course* course = semester -> getCourseFromID(stoi(data));

                if (course) {
                    getline(s, data, ',');
                    course -> setFirstSession(stoi(data));

                    getline(s, data, ',');
                    course -> setSecondSession(stoi(data));

                    addCourse(course);
                }
            }

            inp.close();
        }
    }

    void putStudentAccountToFile() {
        ofstream out(STUDENTS_FILE + to_string(account -> getId()) + ".csv");

        out << schoolYearName << ',' << className << '\n';

        student -> putDataToStream(out);

        out << student -> getOverallMarks() << ',' << student -> getOverallCredits() << '\n';

        for (int i = 0; i < enrolledCoursesCount; ++i)
            out << enrolledCourses[i] -> getID() << ','
                << enrolledCourses[i] -> getFirstSession() << ','
                << enrolledCourses[i] -> getSecondSession() << '\n';

        out.close();
    }
};

#endif
