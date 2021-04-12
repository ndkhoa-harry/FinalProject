class SignIn
{
private:
    string InputPass()
    {
        string s;
        for (int i = 0; i < 20; i++)
        {
            char x = getch();

            if (x == ' ')
                break;

            cout << "*";

            s.push_back(x);
        }
        return s;
    }

    void CreateClass()
    {
        cout << "Plz enter name of class: ";
        string ClassName;
        cin >> ClassName;

        ClassName.insert(ClassName.length(), ".csv");

        fstream ifs("D:/FinalProject/PresentYear.txt", ios::in);

        string year;
        ifs >> year;

        ifs.close();

        year.insert(0, "D:/FinalProject/");

        cvsFile(ClassName, year);
    }

    int UpdateYear()
    {
        cvsFile Year("PresentYear.txt", "D:/FinalProject");

        ifstream ifs("D:/FinalProject/PresentYear.txt");
        string s;
        ifs >> s;
        ifs.close();
        if (s == "")
            Year.AddString("2019");

        fstream fs("D:/FinalProject/PresentYear.txt", ios::in);

        int k;
        fs >> k;

        //                      ERROR ON NEW YEAR
        if (k == 0)
            k = 2019;
        k++;

        fs.close();
        fs.open("D:/FinalProject/PresentYear.txt", ios::out);

        fs << k;

        fs.close();
        return k;
    }

    void CreateYear()
    {
        int year = UpdateYear();
        string Year = its(year);
        Year.insert(0, "D:/FinalProject/");
        CreateFolder(Year);
    }

    void CreateSemester()
    {
        int Semester;
        cout << "Plz choose one semester: ";
        cin >> Semester;
        Semester %= 3;

        string NameSemester;

        switch (Semester)
        {
        case 0:
            NameSemester = "Spring.csv";
            break;
        case 1:
            NameSemester = "Summer.csv";
            break;
        case 2:
            NameSemester = "Winter.csv";
            break;
        }

        ifstream ifs("D:/FinalProject/PresentYear.txt");

        string year;
        ifs >> year;

        ifs.close();
        year.insert(0, "D:/FinalProject/");

        cvsFile sem(NameSemester, year);
    }

    void CreateCourse(string Semester)
    {
        string course;
        //                              THONG TIN KHOA HOC
        string CourseName;
        string ThreeFirstLetterOfSemester;

        for (int i = 0; i < 3; i++)
            ThreeFirstLetterOfSemester.push_back(Semester[i]);

        for (int i = 0; i < 5; i++)
        {
            string s;
            cout << "enter name of subject: ";
            cin.ignore();
            cin >> s;

            if (i == 1) //              VI TRI MA MON HOC O VI TRI THU 1 (KE TU VI TRI THU 0)
                CourseName = s;

            s.push_back(',');
            course.insert(course.length(), s);
        }

        course.pop_back();
        course.push_back('\n');

        ifstream ifs("D:/FinalProject/PresentYear.txt");

        int Year;
        ifs >> Year;

        ifs.close();

        string year = its(Year);
        year.insert(0, "D:/FinalProject/");

        cvsFile Semes(Semester, year);
        Semes.AddString(course);

        CourseName.insert(CourseName.length(), ".csv");
        CourseName.insert(0, ThreeFirstLetterOfSemester);

        cvsFile course_(CourseName, year);
    }

public:
    void LogIn(string PassWordFile)
    {
        int ID;
        cout << "enter your ID: ";
        cin >> ID;
        cvsFile passFile(PassWordFile);

        if (!passFile.IDExistinPassFile(ID))
        {
            cout << "This ID cant be found !!!";
            return;
        }

        string pass;
        cout << "enter password: ";
        pass = InputPass();
        string Pass = passFile.GetPassword(ID);

        if (pass != Pass)
        {
            cout << "Login Fail !!!";
            return;
        }

        if (ID == 0)
        {
            //HOAT DONG CUA STAFF MEM
            while (1)
            {
                system("cls");
                int choice;

                cout << "1. this action will increase current year by 1\n";
                cout << "then you will work with currrent year\n";
                cout << "2. This action will create class\n";
                cout << "3. this action will create semester\n";
                cout << "4. this action will create course\n";

                cout << "enter your choice: ";
                cin >> choice;

                switch (choice)
                {
                case 1:
                    CreateYear();
                    break;

                case 2:
                    CreateClass();
                    break;

                case 3:
                    cout << "1. Summer\n2. Winter\n3. Spring\n";
                    CreateSemester();
                    break;

                case 4:
                    cout << "1. Spring\n 2. Summer\n 3. Winter";
                    int choice;
                    cout << "\n enter your choice: ";
                    cin >> choice;
                    string semester;
                    switch (choice % 3)
                    {
                    case 1:
                        semester = "Spring.csv";
                        break;
                    case 2:
                        semester = "Summer.csv";
                        break;
                    case 0:
                        semester = "Winter.csv";
                        break;
                    }
                    CreateCourse(semester);
                    break;
                }
            }
        }
        else
        {
            //HOAT DONG CUA STUDENT
        }
    }
};