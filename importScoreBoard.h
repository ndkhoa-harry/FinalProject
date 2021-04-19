
static void importScoreBoard() {
        int id;
        string dir;

        cout << "Import score board\n";
        
        cout << "Enter course ID: "; cin >> id;
        cout << "Enter file .csv directory: "; cin >> dir;

        string line;

        ifstream inp(COURSES_FILE + to_string(id) + ".csv");
        if (inp) {
            getline(inp, line);
            inp.close();
        }

        inp.open(dir); 
        ofstream out(COURSES_FILE + to_string(id) + ".csv");
        if (inp) {
            out << line << '\n';
            
            out << "private\n";
            while (getline(inp, line)) out << line << '\n';

            inp.close();
        }

        out.close();
    }
void getStaffAccountFromFile() {
         ifstream inp(STAFFS_FILE);

        if (inp) {
            string line;
            string* data = new string[STAFF_COMPONENTS_COUNT];

            while (!inp.eof()) {
                getline(inp, data[0], ',');
                if (stoi(data[0]) == account -> getId()) {
                    for (int i = 1; i < STAFF_COMPONENTS_COUNT - 1; ++i) 
                        getline(inp, data[i], ',');
                    getline(inp, data[STAFF_COMPONENTS_COUNT - 1]);

                    inp.close();

                    staff = new Person(
                        stoi(data[0]),
                        data[1],
                        data[2],
                        data[3],
                        data[4]
                    );

                    return;
                } else 
                    getline(inp, line);
            }

            delete[] data;

            inp.close();
    }