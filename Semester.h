#ifndef _SEMESTER_H_
#define _SEMESTER_H_

#include "Course.h"

class Semester {
private:
    struct Node {
        Course data;
        Node* next;
    };

    string name;
    Node* head, *tail;
    int coursesCount;

public:
    Semester() { }

    Semester(string name) {
        this -> name = name;

        head = nullptr;
        tail = nullptr;
        coursesCount = 0;
    }

    void addCourse(Course course) {
        if (!head) {
            head = new Node;
            tail = head;
        } else {
            tail -> next = new Node;
            tail = tail -> next;
        }

        tail -> data = course;
        tail -> next = nullptr;

        coursesCount++;
    }
};

#endif