#ifndef _COURSE_H_
#define _COURSE_H_

#include <iostream>
#include <string>

using namespace std;

class Course {
private:
    int id, credits, maxStudents, day, session1, session2;
    string courseName, teacherName, startDay, endDay;

public:
    Course() { }

    Course(int id, string courseName, string teacherName, int credits, int day, int session1, int session2, string startDay, string endDay) {
        this -> id = id;
        this -> courseName = courseName;
        this -> teacherName = teacherName;
        this -> credits = credits;
        this -> day = day;
        this -> session1 = session1;
        this -> session2 = session2;
        this -> startDay = startDay;
        this -> endDay = endDay;
    }
};

#endif