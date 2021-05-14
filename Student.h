#ifndef _STUDENT_H_
#define _STUDENT_H_

#include "Helper.h"

#include "Person.h"
#include "Account.h"

class Student : public Person {
private:
    int no, overallCredits;
    double totalMark, finalMark, midtermMark, otherMark, overallMarks;

    bool scored;
    
public:
    Student() {
        scored = false;
    }

    Student(int no, int id, string firstName, string lastName, string gender, string dob)
        : Person(id, firstName, lastName, gender, dob) {
            this -> no = no;
            scored = false;
        }

    Student(int no, int id, string fullName, double totalMark, double finalMark, double midtermMark, double otherMark) 
        : Person(id, fullName) {
            this -> no = no;
            this -> totalMark = totalMark;
            this -> finalMark = finalMark;
            this -> midtermMark = midtermMark;
            this -> otherMark = otherMark;

            scored = true;
        } 

    void setNo(int no) { this -> no = no; }

    int getNo() { return no; }

    double getTotalMark() { return totalMark; }

    double getFinalMark() { return finalMark; }

    double getMidtermMark() { return midtermMark; }

    double getOtherMark() { return otherMark; }

    void setOverallMarks(double overallMarks) { this -> overallMarks = overallMarks; }

    double getOverallMarks() { return overallMarks; }

    void setOverallCredits(int overallCredits) { this -> overallCredits = overallCredits; }

    int getOverallCredits() { return overallCredits; }

    double getOverallGPA() {
        if (overallCredits == 0)
            return 0.0;
        else
            return overallMarks / overallCredits;
    }

    bool isScored() { return scored; }

    void getOverallMarksCredits() {
        ifstream inp(STUDENTS_FILE + to_string(getId()) + ".csv");

        if (inp) {
            string data;

            getline(inp, data);
            getline(inp, data);

            getline(inp, data, ',');
            setOverallMarks(stod(data));

            getline(inp, data);
            setOverallCredits(stoi(data));

            inp.close();
        }
    }
    
    bool inputScore() {
        string title = "Input score";

        int fieldLength = 30;

        const int inputsCount = 4;

        string instructions[inputsCount] = {
            "Enter total mark: ",
            "Enter final mark: ",
            "Enter midtern mark: ",
            "Enter other mark: "
        };

        string inputsData[inputsCount] = { "", "", "", "" };

        if (drawInputBox(title, fieldLength, inputsCount, instructions, inputsData)) {
            totalMark = stod(inputsData[0]);
            finalMark = stod(inputsData[1]);
            midtermMark = stod(inputsData[2]);
            otherMark = stod(inputsData[3]);

            return true;
        } else 
            return false;
    }

    void publishScores(int courseID) {
        ifstream inp(STUDENTS_FILE + to_string(getId()) + ".csv");

        if (inp) {
            ofstream out(STUDENTS_TEMPORARY_FILE);

            string line;

            for (int i = 0; i < 3; ++i) {
                getline(inp, line);
                out << line << '\n';
            }

            while (getline(inp, line)) {
                if (line.compare(to_string(courseID)) == 0) 
                    out << courseID << ',' << totalMark << ',' << finalMark << ',' << midtermMark << ',' << otherMark << '\n';
                else 
                    out << line << '\n';
            }

            inp.close();
            out.close();

            remove((STUDENTS_FILE + to_string(getId()) + ".csv").c_str());
            rename(STUDENTS_TEMPORARY_FILE.c_str(), (STUDENTS_FILE + to_string(getId()) + ".csv").c_str());
        }
    }

    void updateOverallGPA(int credits) {
        ifstream inp(STUDENTS_FILE + to_string(getId()) + ".csv");

        if (inp) {
            ofstream out(STUDENTS_TEMPORARY_FILE);

            string line;

            getline(inp, line);
            out << line << '\n';

            getline(inp, line);
            out << line << '\n';

            getline(inp, line, ',');
            overallMarks = stod(line) + totalMark * credits;

            getline(inp, line);
            overallCredits = stoi(line) + credits;

            out << overallMarks << ',' << overallCredits << '\n';

            while (getline(inp, line)) out << line << '\n';

            inp.close();
            out.close();

            remove((STUDENTS_FILE + to_string(getId()) + ".csv").c_str());
            rename(STUDENTS_TEMPORARY_FILE.c_str(), (STUDENTS_FILE + to_string(getId()) + ".csv").c_str());
        }
    }

    void display() {
        if (!scored) {
            cout << "No: " << no << '\n';
            Person::display();
        } else {
            cout 
                << no << ' ' 
                << getId() << ' ' 
                << getFullName() << ' ' 
                << totalMark << ' ' 
                << finalMark << ' ' 
                << midtermMark << ' ' 
                << otherMark << '\n';
        }
    }

    static Student* inputNewStudent(int no) {
        string title = "Input student No. " + to_string(no) + " information";

        int fieldLength = 60;

        const int inputsCount = 5;
        string instructions[inputsCount] = {
            "ID: ",
            "First name: ",
            "Last name: ",
            "Gender (M/F): ",
            "Date of birth (dd/mm/yyyy): "
        };

        string inputsData[inputsCount];
        for (int i = 0; i < inputsCount; ++i) inputsData[i] = "";

        if (drawInputBox(title, fieldLength, inputsCount, instructions, inputsData))
            return new Student(
                no,
                stoi(inputsData[0]),
                inputsData[1],
                inputsData[2],
                inputsData[3] == "M" ? "Male" : "Female",
                inputsData[4]
            );
        else
            return nullptr;
    }

    static Student* getStudentFromStringStream(stringstream &s) {
        int componentsCount = 0;
        string* data = new string[STUDENT_MAX_COMPONENTS];

        while (getline(s, data[componentsCount], ',')) ++componentsCount;

        Student* student = nullptr;
        if (componentsCount == 6) {
            student = new Student(
                stoi(data[0]), 
                stoi(data[1]), 
                data[2], 
                data[3], 
                data[4], 
                data[5]
            );
        } else {
            student = new Student(
                stoi(data[0]),
                stoi(data[1]),
                data[2],
                stod(data[3]),
                stod(data[4]),
                stod(data[5]),
                stod(data[6])
            );
        }
        
        delete[] data;

        return student;
    }

    void putDataToStream(ofstream &out) {
        if (scored) {
            out << no << ','
                << getId() << ','
                << getFullName() << ','
                << totalMark << ','
                << finalMark << ','
                << midtermMark << ','
                << otherMark << '\n';
        } else {
            out << no << ','
                << getId() << ','
                << getFirstName() << ','
                << getLastName() << ','
                << getGender() << ','
                << getDob() << '\n';
        }
    }

    void createStudentFiles(string schoolYearName, string className) {
        ofstream out(STUDENTS_FILE + to_string(getId()) + ".csv");

        out << schoolYearName << ',' << className << '\n';
        putDataToStream(out);
        out << "0,0\n";

        out.close();

        Account::addNewAccount(getId(), "1");
    }
};

#endif
