void inputNewStudents() {
    cout << "Enter students number: "; cin >> studentsCount;

    for (int i = 0; i < studentsCount; ++i)
        addStudent(Student::inputNewStudent(i));

    dataModified = true;
}

void getAllStudentsInfo(int& studentsCount, Student**& students) {
    studentsCount = this->studentsCount;
    students = new Student * [studentsCount];

    Node* cur = head;
    for (int i = 0; cur; ++i) {
        students[i] = cur->data;
        cur = cur->next;
    }
}