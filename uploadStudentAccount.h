void getStudentAccountFromFile() {
        ifstream inp(STUDENTS_FILE + to_string(account -> getId()) + ".csv");
        if (inp) {
            string line, data;

            getline(inp, schoolYearName, ',');
            semester = SchoolYear::getLastedSemesterFromFile(schoolYearName);

            getline(inp, className);

            getline(inp, line);
            stringstream s(line);
            student = Student::getStudentFromStringStream(s);

            if (getline(inp, line)) {
                stringstream s(line);

                getline(s, data, ',');
                addCourse(semester -> getCourseFromID(stoi(data)));
            }

            inp.close();
        }
    }

    void putStudentAccountToFile() {
        ofstream out(STUDENTS_FILE + to_string(account -> getId()) + ".csv");

        out << schoolYearName << ',' << className << '\n';

        student -> putDataToStream(out);

        if (enrolledCoursesCount > 0)
            out << enrolledCourses[0] -> getID();
        for (int i = 1; i < enrolledCoursesCount; ++i)
            out << ',' << enrolledCourses[i];

        out.close();
    }
};