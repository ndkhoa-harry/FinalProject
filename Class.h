#ifndef _CLASS_H_
#define _CLASS_H_

#include "Helper.h"

#include "Semester.h"
#include "Course.h"
#include "Student.h"

const int CLASS_OPTIONS_COUNT = 2;
const string CLASS_OPTIONS[] = {
    "View class information",
    "View class scoreboard"
};

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

    void getAllStudentsInfo(int &studentsCount, Student* *&students) {
        studentsCount = this -> studentsCount;
        students = new Student*[studentsCount];

        Node* cur = head;
        for (int i = 0; cur; ++i) {
            students[i] = cur -> data;

            students[i] -> getOverallMarksCredits();

            cur = cur -> next;
        }
    }

    void displayClassInformation() {
        string tableTitle = "CLASS " + name;

        int columnsCount = 6;
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

        system("cls");
        drawTable(3, tableTitle, columnsCount, columnsWidth, columnsName, rowsCount, table);
        getch();

        for (int i = 0; i < rowsCount; ++i) delete[] table[i];
        delete[] table;
    }

    void displayClassScoreboard(Semester* lastedSemester) {
        if (!lastedSemester) {
            drawOkayBox("Error!!!", "This school year does not have any semester!");
            return;
        }

        Course* *courses;
        int coursesCount;
        lastedSemester -> getAllCoursesInfo(coursesCount, courses);
        
        Student* *students;
        int studentsCount;
        getAllStudentsInfo(studentsCount, students);

        /// TABLE 
        string tableTitle = "CLASS " + name + " SCOREBOARD IN " + lastedSemester -> getName() + " SEMESTER";

        int columnsCount = 6 + coursesCount;
        int columnsWidth[columnsCount] = {5, 10, 25, 15};
        string columnsName[columnsCount] = {
            "No",
            "Student ID",
            "Full name",
            "Gender"
        };
        for (int i = 0; i < coursesCount; ++i) {
            columnsWidth[4 + i] = 8;
            columnsName[4 + i] = courses[i] -> getCourseID();
        }
        columnsWidth[4 + coursesCount] = 7;
        columnsName[4 + coursesCount] = "GPA";
        columnsWidth[5 + coursesCount] = 13;
        columnsName[5 + coursesCount] = "Overall GPA";

        int rowsCount = studentsCount;

        string** table = new string* [rowsCount];

        for (int i = 0; i < rowsCount; ++i) {
            Student* student = students[i];

            table[i] = new string[columnsCount] {
                to_string(student -> getNo()),
                to_string(student -> getId()),
                student -> getFullName(),
                student -> getGender()
            };

            double totalMarks = 0.0;
            int totalCredits = 0;

            for (int j = 0; j < coursesCount; ++j) 
                if (courses[j] -> isScored()) {
                    Student* scoredStudent = courses[j] -> findStudentFromID(student -> getId());

                    if (scoredStudent) {
                        table[i][4 + j] = toStringPrecision(scoredStudent -> getTotalMark());

                        totalMarks += scoredStudent -> getTotalMark() * courses[j] -> getCredits();
                        totalCredits += courses[j] -> getCredits();
                    } else
                        table[i][4 + j] = "x";
                } else
                    table[i][4 + j] = "x";

            if (totalCredits == 0)
                table[i][4 + coursesCount] = "x";
            else 
                table[i][4 + coursesCount] = toStringPrecision(totalMarks / totalCredits);

            if (student -> getOverallCredits() == 0) 
                table[i][5 + coursesCount] = "x";
            else
                table[i][5 + coursesCount] = toStringPrecision(student -> getOverallGPA());
        }

        system("cls");
        drawTable(3, tableTitle, columnsCount, columnsWidth, columnsName, rowsCount, table);
        getch();

        for (int i = 0; i < rowsCount; ++i) delete[] table[i];
        delete[] table;

        delete[] students;
        delete[] courses;
    }

    void displayMenu(Semester* lastedSemester) {
        int titleLines = 1;
        string title[titleLines] = {
            "CLASS " + name
        };

        int choice = 0;
        while (1) {
            drawMenu(titleLines, title, CLASS_OPTIONS_COUNT, CLASS_OPTIONS, choice);

            switch (choice) {
                case 0:
                    displayClassInformation();
                    break;
                case 1:
                    displayClassScoreboard(lastedSemester);
                    break;
                default:
                    return;
            }
        }
    }

    static Class* inputNewClass(string schoolYearName) {
        string title = "Input new class";

        const int containsCount = 2;
        string contains[containsCount] = {
            "1. Input manually by hand",
            "2. Input from CSV file"
        };

        const int optionsCount = 3;
        string options[optionsCount] = {
            "Manually",
            "CSV File",
            "Cancel"  
        };

        int choice = 2;
        drawBox(title, containsCount, contains, optionsCount, options, choice);

        if (choice == 2) return nullptr;

        string className = "";
        if (drawInputBox("Input new class", 40, "Enter class name: ", className)) {
            Class* newClass = new Class(className, schoolYearName);

            if (choice == 0) {
                if (!newClass -> inputNewClassByHand()) {
                    delete newClass;
                    return nullptr;
                }
            } else if (choice == 1) {
                if (!newClass -> inputNewClassFromFile()) {
                    delete newClass;
                    return nullptr;
                }
            }

            newClass -> createStudentsFiles();

            return newClass;
        } else
            return nullptr;
    }

    bool inputNewClassByHand() {
        string sStudentsCount;
        if (drawInputBox("Input class " + name, 40, "Enter number of students in class: ", sStudentsCount)) {
            int studentsCount = stoi(sStudentsCount);
            
            for (int i = 0; i < studentsCount; ++i) {
                Student *newStudent = Student::inputNewStudent(i + 1);

                if (newStudent) 
                    addStudent(newStudent);
                else
                    return false;
            }

            dataModified = true;

            return true;
        } else
            return false;
    }

    bool inputNewClassFromFile() {
        string dir = "";

        if (drawInputBox("Input class " + name, 100, "File NewClass.csv directory: ", dir)) {
            ifstream src(dir);
        
            if (src) {
                ofstream dst(CLASSES_FILE + name + ".csv");

                char c;
                while (src.get(c)) dst << c;

                dst.close();
                src.close();

                getClassFromFile();

                return true;
            } else {
                drawOkayBox("Error!!!", "Can't open file, please check your directory.");

                return false;
            }
        } else
            return false;
    }

    void createStudentsFiles() {
        Node* cur = head;
        while (cur) {
            cur -> data -> createStudentFiles(schoolYearName, name);
            cur = cur -> next;
        }
    }

    void getClassFromFile() {
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
