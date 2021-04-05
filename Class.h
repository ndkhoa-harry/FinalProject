#include <iostream>
#include <fstream>
#include <sstream>
#include "Student.h"

using namespace std;

struct Class {
private:
    struct Node {
        Student data;
        Node* next;
    }; 

    string name;
    int studentCount;
    Node* head, *tail;

public:
    Class(string name) {
        this -> name = name; 

        head = nullptr;
        tail = nullptr;
        studentCount = 0;
    }

    ~Class() {
        Node* cur = head;
        while (cur) {
            Node* tmp = cur;
            cur = cur -> next;
            delete tmp;
        }
    }

    void addStudent(Student student) {
        if (!head) {
            head = new Node;
            tail = head;
        } else {
            tail -> next = new Node;
            tail = tail -> next;
        }

        tail -> data = student;
        tail -> next = nullptr;

        studentCount++;
    }

    void inputFromCSV(string fileName) {
        ifstream inp(fileName);

        if (inp) {
            string* data = new string[Student::componentsCount];

            while (!inp.eof()) {
                for (int i = 0; i < Student::componentsCount - 1; ++i) 
                    getline(inp, data[i], ',');
                getline(inp, data[Student::componentsCount - 1], '\n');

                addStudent(
                    Student(
                        stoi(data[0]), 
                        stoi(data[1]), 
                        data[2], 
                        data[3], 
                        data[4], 
                        data[5]
                    )
                );
            }

            delete[] data;

            inp.close();
        }
    }

    void display() {
        cout << "This is class " << name << ":\n";

        Node* cur = head;
        while (cur) {
            cur -> data.display();
            cur = cur -> next;
        }
    }
};