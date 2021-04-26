void putSchoolYearToFile() {
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