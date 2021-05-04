#ifndef _SCHOOLYEAR_H_
#define _SCHOOLYEAR_H_

#include "Helper.h"

#include "Class.h"
#include "Semester.h"

class SchoolYear {
private:
    string name;

    /// CLASSES DATA
    struct ClassNode {
        Class* data;
        ClassNode* next;
    };

    ClassNode* classHead, *classTail;
    int classesCount;

    /// SEMESTERS DATA
    Semester* *semesters;
    int semestersCount;

    bool alreadyInputted, dataModified;

public:
    SchoolYear() { 
        classHead = nullptr;
        classTail = nullptr;
        classesCount = 0;

        semesters = new Semester*[3];
        semestersCount = 0;

        alreadyInputted = false;
        dataModified = false;
    }

    SchoolYear(string name) : SchoolYear() {
        this -> name = name;
    }

    ~SchoolYear() {
        cout << "Destructor " << name << '\n';

        if (dataModified) putSchoolYearToFile();

        while (classHead) {
            ClassNode* tmp = classHead;

            classHead = classHead -> next;

            delete tmp -> data;
            delete tmp;
        }

        for (int i = 0; i < semestersCount; ++i) 
            delete semesters[i];
        delete[] semesters;
    }

    void setName(string name) { 
        this -> name = name; 
        dataModified = true;
    }

    string getName() { return name; }

    int getClassesCount() { return classesCount; }

    int getSemestersCount() { return semestersCount; }

    bool isAlreadyInputted() { return alreadyInputted; }

    void addClass(Class* curClass) {
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
    
    Class* getClass(int id) {
        // TODO: Get class from linked list
        ClassNode* cur = classHead;
        for (; id > 0; --id) cur = cur -> next;

           if (!cur -> data -> isAlreadyInputted())
            cur -> data -> getClassFromFile();

        return cur -> data;
    }
    
    void inputNewClass() {
        // TODO: Input new class by hand
        Class* newClass = Class::inputNewClass(name);

        if (newClass) {
            addClass(newClass);
            dataModified = true;

            drawOkayBox("Message", "Input new class successfully");

            newClass -> displayMenu(getLastedSemester());

            return true;
        }

        return false;
    }

    void addSemester(Semester* semester) {
        if (semestersCount < 3)
            semesters[semestersCount++] = semester;
    }

    Semester* getLastedSemester() {
        // TODO: Get last semester

        return nullptr;
    }

    void inputNewSemester() {
        // TODO: Input new semester by hand
        
    } 

    void displayClassesMenu(int s) {
        cout << "This is list of Classes: \n";
        ClassNode* cur = classHead;     
        for (int i = 0; cur; ++i, cur = cur -> next)
            cout << '\t' << s + i << ". Class " << cur -> data -> getName() << '\n';
        cout << '\t' << s + classesCount + 1 << ". Create class\n";
    }

    void displaySemestersMenu(int s) {
        cout << "This is list of semesters: \n";
        for (int i = 0; i < semestersCount; ++i) 
            cout << '\t' << s + i << ". Semester " << semesters[i] -> getName() << '\n';
        if (semestersCount < 3)
            cout << '\t' << s + semestersCount + 1 << ". Create semester\n";
    }

    void displayMenu() {
        int choice;
        while (1) {
            cout << "\tThis is school year " << name << '\n';

            displayClassesMenu(1);

            displaySemestersMenu(classesCount + 2);

            cout << "Enter your choice: "; cin >> choice;
            --choice;

            if (choice < classesCount) {
                Class* curClass = getClass(choice);

                curClass -> displayMenu(getLastedSemester());
            } else if (choice == classesCount) {
                inputNewClass();
            } else if (choice < classesCount + semestersCount + 1) {
                dataModified |= semesters[choice - classesCount - 1] -> displayStaffMenu();
            } else if (choice == classesCount + semestersCount + 1) {
                inputNewSemester();
            } else {
                return;
            }
        }
    }

    static SchoolYear* inputNewSchoolYear() {
        // TODO: Input new school year by hand

        return nullptr;
    }

    void getSchoolYearFromFile() {
        // TODO: Get school year infromations from file
         ifstream inp(SCHOOL_YEARS_FILE + name + ".csv");
        
        if (inp) {
            string line, data;

            getline(inp, line);

            stringstream s(line);
            
            while (getline(s, data, ',')) {
                Class* curClass = new Class(data);
                addClass(curClass);
            }

            while (getline(inp, line)) {
                stringstream s(line);

                addSemester(Semester::getSemesterFromStringStream(s, SEMESTERS_NAMES[semestersCount]));
            }

            alreadyInputted = true;
        }

        inp.close();
    }

    static Semester* getLastedSemesterFromFile(string schoolYearName) {
        // TODO: Get lasted semester from file

        return nullptr;
    }

    void putSchoolYearToFile() {
        // TODO: Update school year informations to file
                ofstream out(SCHOOL_YEARS_FILE + name + ".csv");

        if (classHead) {
            out << classHead -> data -> getName();

            ClassNode* cur = classHead -> next;
            while (cur) {
                out << ',' << cur -> data -> getName();
                cur = cur -> next;
            }
        }
        out << '\n';

        for (int i = 0; i < semestersCount; ++i) {
            out << semesters[i] -> getStartDate() << ',' << semesters[i] -> getEndDate();
            
            int coursesCount;
            int *id;
            string* name;

            semesters[i] -> getCoursesList(coursesCount, id, name);

            for (int j = 0; j < coursesCount; ++j)
                out << ',' << id[j] << ',' << name[j];
            out << '\n';

            delete[] id;
            delete[] name;
        }

        out.close();
    }
};

#endif
