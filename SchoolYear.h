#ifndef _SCHOOLYEAR_H_
#define _SCHOOLYEAR_H_

#include "Class.h"
#include "Semester.h"

class SchoolYear {
private:
    string name;

    /// CLASSES DATA
    struct ClassNode {
        Class data;
        ClassNode* next;
    };

    ClassNode* classHead, *classTail;
    int classesCount;

    /// SEMESTERS DATA
    Semester* semesters;
    int semestersCount;

public:
    SchoolYear(string name) {
        this -> name = name;

        classHead = nullptr;
        classTail = nullptr;
        classesCount = 0;

        semesters = new Semester[3];
        semestersCount = 0;
    }

    ~SchoolYear() {
        ClassNode* cur = classHead;
        while (cur) {
            ClassNode* tmp = cur;
            cur = cur -> next;
            delete tmp;
        }
    }

    void addClass(Class curClass) {
        if (!classHead) {
            classHead = new ClassNode;
            classTail = classHead;
        } else {
            classTail -> next = new ClassNode;
            classTail = classTail -> next;
        }

        classTail -> data = curClass;
        classTail -> next = nullptr;

        classesCount++;
    }
};

#endif