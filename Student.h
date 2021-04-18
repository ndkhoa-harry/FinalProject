#ifndef _STUDENT_H_
#define _STUDENT_H_

#include "Helper.h"

#include "Person.h"

class Student : public Person {
private:
    int no;
    double totalMark, finalMark, midtermMark, otherMark;

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

    double getFinalMark() { return finalMark; }

    bool isScored() { return scored; }
    
    void inputScore() {
        // TODO: Input scores by hand
    }

    void publishScores(int courseID) {
        // TODO: Publish all score
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
        // TODO: Input new student by hand

        return nullptr;
    }

    static Student* getStudentFromStringStream(stringstream &s) {
        // TODO: Get student from string stream

        return nullptr;
    }

    void putDataToStream(ofstream &out) {
        // TODO: Put student data to stream
    }
};

#endif