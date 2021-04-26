void getSchoolYearFromFile() {
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