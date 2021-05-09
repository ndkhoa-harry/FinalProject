#ifndef _SCHOOLYEAR_H_
#define _SCHOOLYEAR_H_

#include "Helper.h"

#include "Class.h"
#include "Semester.h"

/// SCHOOL YEAR MENU
const int SCHOOL_YEAR_TITLE_LINES = 0;
const string SCHOOL_YEAR_TITLE[] = { "" };

const int SCHOOL_YEAR_OPTIONS_COUNT = 2;
const string SCHOOL_YEAR_OPTIONS[] = {
    "CLASSES",
    "SEMESTERS"
};

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
        if (semestersCount == 0) return nullptr;
        return semesters[semestersCount - 1];
    }

    void inputNewSemester() {
        // TODO: Input new semester by hand
        Semester* newSemester = Semester::inputNewSemester(semestersCount);

        if (newSemester) {
            addSemester(newSemester);
            dataModified = true;

            drawOkayBox("Message", "Input new semester successfully");

            newSemester -> displayStaffMenu();

            return true;
        }

        return false;
    } 

    void displayClassesMenu(int s) {
        const int titleLines = 5;
        string title[titleLines] = {
            name,                    
            "  ___ _      _   ___ ___ ___ ___ ",
            " / __| |    /_\\ / __/ __| __/ __|",
            "| (__| |__ / _ \\\\__ \\__ \\ _|\\__ \\",
            " \\___|____/_/ \\_\\___/___/___|___/"                   
        };

        int optionsCount = classesCount + 1;

        string* options = new string[optionsCount];
        ClassNode* cur = classHead;     
        for (int i = 0; cur; ++i, cur = cur -> next)
            options[i] = "Class " + cur -> data -> getName();
        options[optionsCount - 1] = "Create new class";

        int choice = 0;

        while (1) {  
            drawMenu(titleLines, title, optionsCount, options, choice);

            if (0 <= choice && choice < classesCount) {
                Class* curClass = getClass(choice);

                curClass -> displayMenu(getLastedSemester());
            } else if (choice == classesCount) {
                if (inputNewClass()) {
                    ++optionsCount;

                    delete[] options;
                    options = new string[optionsCount];

                    ClassNode* cur = classHead;     
                    for (int i = 0; cur; ++i, cur = cur -> next)
                        options[i] = "Class " + cur -> data -> getName();
                    options[optionsCount - 1] = "Create new class";
                }
            } else {
                delete[] options;
                return;
            }
        }
    }

    void displaySemestersMenu(int s) {
        const int titleLines = 5;
        string title[titleLines] = {
            name,
            " ___ ___ __  __ ___ ___ _____ ___ ___  ___ ",
            "/ __| __|  \\/  | __/ __|_   _| __| _ \\/ __|",
            "\\__ \\ _|| |\\/| | _|\\__ \\ | | | _||   /\\__ \\",
            "|___/___|_|  |_|___|___/ |_| |___|_|_\\|___/"
        };

        int optionsCount = semestersCount + (semestersCount < 3);

        string* options = new string[optionsCount];
        for (int i = 0; i < semestersCount; ++i)
            options[i] = semesters[i] -> getName() + " semester";
        if (semestersCount < 3)
            options[semestersCount] = "Create new semester";

        int choice = 0;

        while (1) {
            drawMenu(titleLines, title, optionsCount, options, choice);

            if (0 <= choice && choice < semestersCount)
                dataModified |= semesters[choice] -> displayStaffMenu();
            else if (choice == semestersCount) {
                if (inputNewSemester()) {
                    ++optionsCount;
                
                    delete[] options;
                    options = new string[optionsCount];

                    for (int i = 0; i < semestersCount; ++i)
                        options[i] = semesters[i] -> getName() + " semester";
                    if (semestersCount < 3)
                        options[semestersCount] = "Create new semester";
                }
            } else {
                delete[] options;
                return;
            }
        }
    }

    void displayMenu() {
        int choice = 0;

        while (1) {
            drawMenu(SCHOOL_YEAR_TITLE_LINES, SCHOOL_YEAR_TITLE, SCHOOL_YEAR_OPTIONS_COUNT, SCHOOL_YEAR_OPTIONS, choice);

            switch (choice) {
                case 0:
                    displayClassesMenu();
                    break;
                case 1:
                    displaySemestersMenu(classesCount + 2);
                    break;
                default:
                    return;
            }
        }
    }

    static SchoolYear* inputNewSchoolYear() {
        // TODO: Input new school year by hand
            string newName = 
            to_string(CURRENT_DATE.getYear()) 
            + "-" + 
            to_string(CURRENT_DATE.getYear() + 1);

        if (drawYesNoBox("Create new school year", "Do you really want to create school year " + newName + " ?")) 
            return new SchoolYear(newName);
        else
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
      ifstream inp(SCHOOL_YEARS_FILE + schoolYearName + ".csv");

        if (inp) {
            int semestersCount = 0;
            string line, tmpLine;

            getline(inp, line);

            for (; getline(inp, tmpLine); ++semestersCount)
                line = tmpLine;

            inp.close();

            if (semestersCount == 0) return nullptr;

            stringstream s(line);
            return Semester::getSemesterFromStringStream(s, SEMESTERS_NAMES[semestersCount - 1]);
        }

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
