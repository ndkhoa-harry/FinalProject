#ifndef VINH
#define VINH
#include <fstream>
#include <sstream>
#include <conio.h>
#include "Person.h"
using namespace std;
//DOI KIEU STRING SANG INTEGER
int sti(string a)
{
    int re = 0;
    int k = 1;

    for (int i = 0; i < a.length(); i++)
    {
        re += (int(a[a.length() - 1 - i]) - 48) * k;
        k *= 10;
    }

    return re;
}

//DOI KIEU STRING SANG KIEU TRO CHAR
char* stc(string a)
{
    char* x = new char[a.length() + 1];
    for (int i = 0; i < a.length(); i++)
        x[i] = a[i];
    x[a.length()] = '\0';
    return x;
}

//DOI KIEU INT SANG STRING
string its(int num)
{
    string re;
    for (int i = 0; num != 0; i++)
    {
        re.push_back(48 + num % 10);
        num /= 10;
    }
    return re;
}

//  TAO FOLDER
void CreateFolder(string PathToFolder)
{
    for (int i = 0; PathToFolder[i] != '\0'; i++)
        if (PathToFolder[i] == '/')
            PathToFolder[i] = '\\';

    PathToFolder.insert(0, "mkdir ");

    system(stc(PathToFolder));
}

//  CHECK FOLDER EXIST OR NOT
bool FolderNOTExist(string PathToFolder)
{
    for (int i = 0; PathToFolder[i] != '\0'; i++)
        if (PathToFolder[i] == '/')
            PathToFolder[i] = '\\';

    PathToFolder.insert(0, "dir ");

    bool check = system(stc(PathToFolder));

    return check;
}

//  DELETE FOLDER AND ALL INFO INSIDE
void DeleteFolder(string PathToFolder)
{
    for (int i = 0; PathToFolder[i] != '\0'; i++)
        if (PathToFolder[i] == '/')
            PathToFolder[i] = '\\';

    PathToFolder.insert(0, "rmdir /s /q");

    system(stc(PathToFolder));
}

class cvsFile
{
private:
    string fileName;
    string folderName;

public:
    /*
    1.  FILENAME: TEN FILE MUON TAO
    2.  FOLDER: NHAP DUONG DAN TOI FOLDER CHUA FILE (MUON TAO HOAC TEN FOLDER MUON MO)
    3.  HAM SE TU TAO FOLDER MOI NEU FOLDER KHONG TON TAI
    */
    cvsFile(string filename, string foldername = "") : fileName(filename), folderName(foldername)
    {
        if (folderName != "")
        {
            fileName.insert(0, "/");
            fileName.insert(0, folderName);

            for (int i = 0; i < folderName.length(); i++)
            {
                if (folderName[i] == '/')
                    folderName.replace(i, 1, "\\");
            }
            folderName.insert(0, "mkdir ");

            system(stc(folderName));

            system("cls");
        }

        fstream ofs;

        ofs.open(fileName);
        if (ofs.fail())
            ofs.open(fileName, ios::out);

        ofs.close();

        return;
    }

    cvsFile() {}

    string GetID(int ID)
    {
        ifstream ifs(fileName);
        while (!ifs.eof())
        {
            string s;
            getline(ifs, s, '\n');
            if (s.find(ID) == 0)
            {
                ifs.close();
                return s;
            }
        }
        ifs.close();
        return "";
    }

    int GetIDPosition(int ID)
    {
        int count = 0;
        ifstream ifs(fileName);
        while (!ifs.eof())
        {
            string s;
            getline(ifs, s, '\n');
            if (s.find(ID) == 0)
            {
                ifs.close();
                return count;
            }
            count++;
        }
        ifs.close();
        return -1;
    }

    //          THAY DOI FILE VA VI TRI CUA FILE(LUA CHON 1 FILE KHAC)
    void ChangeToOtherFile(string filename, string foldername = "")
    {
        fileName = filename;
        folderName = foldername;

        if (folderName != "")
        {
            fileName.insert(0, "/");
            fileName.insert(0, folderName);

            for (int i = 0; i < folderName.length(); i++)
            {
                if (folderName[i] == '/')
                    folderName.replace(i, 1, "\\");
            }

            folderName.insert(0, "mkdir ");

            system(stc(folderName));

            system("cls");
        }

        fstream ofs;

        ofs.open(fileName);
        if (ofs.fail())
            ofs.open(fileName, ios::out);

        ofs.close();
        return;
    }

    //          TIM NGUOI CO ID O TRONG FILE(FILE PHAI CO DU THONG TIN CUA NGUOI DO)
    Person* FindPerson(int ID)
    {
        ifstream ifs(fileName);
        string info;
        string pos[6];

        while (!ifs.eof())
        {
            getline(ifs, info, '\n');
            stringstream s(info);

            for (int i = 0; i < 6; i++)
                getline(s, pos[i], ',');

            if (sti(pos[1]) == ID)
            {
                Person* a = new Person(ID, pos[2], pos[3], pos[5], pos[4]);
                return a;
            }
        }

        return nullptr;
    }

    //          THEM NGUOI A VAO TRONG FILE
    void AddPerson(Person a)
    {
        Person* pe = this->FindPerson(a.getId());

        if (pe != nullptr)
            return;

        ifstream ifs(fileName);

        string s;
        while (!ifs.eof())
            getline(ifs, s);

        int i = 0;
        for (i; s[i] != ','; i++)
            ;

        s.replace(i, s.length() - i, "");

        ifs.close();

        ofstream fs(fileName, ios::app);

        fs << "\n"
            << sti(s) + 1 << "," << a.getId() << "," << a.getFirstName() << "," << a.getLastName() << "," << a.getDob() << "," << a.getGender();

        fs.close();
    }

    //          THEM MOI CHUOI VAO TRONG FILE (DOI VOI FILE CSV THI CHUOI THONG TIN GOM CAC THONG TIN CACH NHAU BOI DAU ,)
    void AddString(string s)
    {
        ofstream ofs(fileName, ios::app);
        ofs << s;
        ofs.close();
    }

    //              XOA FILE HIEN TAI DANG DUOC KHAI BAO
    bool RemoveFile()
    {
        int re = remove(stc(fileName));
        bool ok = (re == 0) ? 1 : 0;
        return ok;
    }

    //              THAY DOI THONG TIN CUA NGUOI CO SO ID, THAY DOI O VI TRI THU INDEX VA THAY THE NO BANG CHUOI REPLACE
    void Change(int ID, int index, string replace)
    {
        fstream f(fileName, ios::in);

        string data;

        getline(f, data, '\0');

        int be = data.find(its(ID));
        int end = be;

        for (int i = 0; i < index; i++)
        {
            while (data[be] != ',')
                be++;
            be++;
        }

        end = 1 + be;

        while (data[end] != ',' && data[end] != '\n')
            end++;

        end--;
        end -= (be - 1);
        data.replace(be, end, replace);

        f.close();

        f.open(fileName, ios::out);

        f << data;

        f.close();
    }

    //          DOC THONG TIN TRONG FILE
    void ReadFile()
    {
        ifstream ifs(fileName);
        string s;
        getline(ifs, s, '\0');
        cout << s;
        ifs.close();
    }

    //          LAY THONG TIN O VI TRI THU INDEX THUOC DONG LINE_NUM O TRONG FILE
    string GetLine(int line_num, int index)
    {
        ifstream ifs(fileName);
        string s;

        for (int i = 0; i < line_num; i++)
            if (!ifs.eof())
                getline(ifs, s, '\n');
            else
                return "";

        ifs.close();

        for (int i = 0; i < index; i++)
        {
            int j = 0;
            for (j = 0; s[j] != ','; j++)
                ;
            s.replace(0, j + 1, "");
        }

        int j = 0;

        for (j = 0; s[j] != ',' && s[j] != '\n'; j++)
            ;

        s.replace(j, s.length() - j, "");

        return s;
    }
    //  HAM NAY DUNG CHO FILE TXT DE DOC PASS NHUNG KO CAN DAU ',', CACH DUNG NHU CU
    string GetPassword(int ID)
    {
        ifstream ifs(fileName);

        while (!ifs.eof())
        {
            int id;
            string pass;
            ifs >> id;
            ifs >> pass;
            if (id == ID)
            {
                ifs.close();
                return pass;
            }
        }

        ifs.close();
        return "";
    }
    // DUNG CHO FILE PASS (KHONG CO STT, KHONG NGAN CACH BOI DAU ",", ID XUAT HIEN DAU TIEN SAU DO TOI PASS VA \n)
    bool IDExistinPassFile(int ID)
    {
        int id;
        string pass;
        ifstream ifs(fileName);

        while (!ifs.eof())
        {
            ifs >> id;
            getline(ifs, pass, '\n');

            if (id == ID)
            {
                ifs.close();
                return true;
            }
        }

        return false;
    }

    /*  LAY NHUNG HOC SINH MOI TRONG FILE VA KHOI TAO MAT KHAU CUA HOC SINH MOI LA 0
        FILEOFPASS: FILE NAY LA FILE CHUA MAT KHAU CUA HOC SINH VA STAFF MEMBER
    */
    void SetNewStudentsPass(string FileOfPass)
    {
        string s;
        string data = "";
        cvsFile File(FileOfPass);

        for (int i = 1;; i++)
        {
            s = this->GetLine(i, 1);

            if (s == "")
                break;

            int check = File.IDExistinPassFile(stoi(s));

            if (check == 0)
            {
                data.insert(data.length(), s);
                data.insert(data.length(), " 0\n");
            }
        }

        ofstream ofs(FileOfPass, ios::app);
        ofs << data;
        ofs.close();
    }
};

class SignIn
{
private:
    string CurSemester_Fol;
    string CurYear;

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

        cvsFile(ClassName, CurYear);
    }

    void CurSemester(string year, string Semester, string begin, string end)
    {
        cvsFile Year("CurSemester.txt", "D:/FinalProject");

        year.insert(0, "D:/FinalProject/");
        CurYear = year;
        year.push_back('/');
        Semester.insert(0, year);
        CurSemester_Fol = Semester;
        CreateFolder(Semester);

        ofstream ofs("D:/FinalProject/CurSemester.txt");
        ofs << CurYear << endl;
        ofs << CurSemester_Fol << endl;
        ofs.close();

        cvsFile a("date.txt", Semester);
        a.AddString(begin);
        a.AddString("\n");
        a.AddString(end);
        a.AddString("\n");
    }

    void CreateYear()
    {
        string Year;
        cout << "enter year you want to create: ";
        cin >> Year;
        Year.insert(0, "D:/FinalProject/");
        CurYear = Year;
        CreateFolder(Year);
    }

    void SetSemester()
    {
        int Semester;
        cout << "Plz choose one semester: ";
        cin >> Semester;
        Semester %= 3;

        string NameSemester;

        switch (Semester)
        {
        case 0:
            NameSemester = "Spring";
            break;
        case 1:
            NameSemester = "Summer";
            break;
        case 2:
            NameSemester = "Winter";
            break;
        }
        cin.ignore();
        cout << "enter date begin: ";
        string beginday;
        getline(cin, beginday);
        cin.ignore();
        cout << "enter date finish: ";
        string endday;
        getline(cin, endday);
        cin.ignore();
        cout << "enter year begin: ";
        int year;
        cin >> year;

        string Year = its(year);
        Year.push_back('-');
        Year.append(its(year + 1));
        CurSemester(Year, NameSemester, beginday, endday);
    }

    void CreateCourse()
    {
        string course;
        //                              THONG TIN KHOA HOC
        string CourseName;
        string ThreeFirstLetterOfSemester;

        for (int i = 0; i < 7; i++)
        {
            cin.ignore();
            string s;
            switch (i)
            {
            case 0:
                cout << "enter name of subject: ";
                break;
            case 1:
                cout << "enter id of subject: ";
                break;
            case 2:
                cout << "enter number of credits: ";
                break;
            case 3:
                cout << "enter name of teacher: ";
                break;
            case 4:
                cout << "enter maximum students in this class: ";
                break;
            case 5:
                cout << "enter the first section class will perform: ";
                break;
            case 6:
                cout << "enter the second section class will perform: ";
                break;
            }
            getline(cin, s);

            if (i == 1) //              VI TRI MA MON HOC O VI TRI THU 1 (KE TU VI TRI THU 0)
                CourseName = s;

            s.push_back(',');
            course.insert(course.length(), s);
        }

        course.pop_back();
        course.push_back('\n');

        CourseName.insert(CourseName.length(), ".csv");

        cvsFile a(CourseName, CurSemester_Fol);
        a.AddString(course);

        cvsFile x("date.txt", CurSemester_Fol);
        x.AddString(course);
    }

    void UpdateCourseInfo()
    {

    }

    void DeleteCourse()
    {

    }

    void UpdateScore(string CourseID, string season, int ID, int IndexOfPointPosition, string ChangeTo)
    {
        string fileName;
        for (int i = 0; i < 3; i++)
            fileName.push_back(season[i]);
        fileName.append(CourseID);

        ifstream ifs("D:/FinalProject/PresentYear.txt");

        string year;
        ifs >> year;

        ifs.close();
        year.insert(0, "D:/FinalProject/");

        cvsFile file_(fileName, year);

        file_.Change(ID, IndexOfPointPosition, ChangeTo);
    }

    //      FOR STUDENT
    void SignInCourse(int ID)
    {

    }

    void ViewScore(int ID)
    {

    }

    int ViewCourse(int ID)
    {
        int choice = 0;
        string date = "/date.txt";
        date.insert(0, CurSemester_Fol);
        ifstream ifs(date);
        for (int i = 0; i < 2; i++)
        {
            string s;
            getline(ifs, s, '\n');
            if (i == 0) cout << "date begin: " << s;
            else cout << "\t\tdate finish: " << s;
        }
        cout << endl;
        for (int i = 1; !ifs.eof(); i++)
        {
            choice++;
            string ifo;
            getline(ifs, ifo, '\n');
            for (int j = 0; j < ifo.length(); j++)
                if (ifo[j] == ',')
                    ifo[j] = '\t';
            if (ifo == "") ifo = "exit";
            ifo.insert(0, ". ");
            ifo.insert(0, its(i));
            cout << ifo << endl;
        }
        return choice;
    }

    void RemoveCourse(int ID)
    {

    }

    void ViewStudentInCourse(string course)
    {

    }

    void ViewStudentInClass(string c)
    {

    }
public:
    SignIn()
    {
        cvsFile a("CurSemester.txt", "D:/FinalProject");
        ifstream ifs("D:/FinalProject/CurSemester.txt");
        getline(ifs, CurYear, '\n');

        getline(ifs, CurSemester_Fol, '\n');
        ifs.close();
    }

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
            bool continue_ = true;
            while (continue_)
            {
                system("cls");
                int choice;

                cout << "1. this action will create year\n";
                cout << "2. This action will create class\n";
                cout << "3. this action will create semester\n";
                cout << "4. this action will create course\n";
                cout << "5. this action will change the score\n";
                cout << "6. this action will add students to class\n";
                cout << "7. log out\n";

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
                    SetSemester();
                    break;

                case 4:
                    CreateCourse();
                    break;
                case 5:
                    cout << "enter course id: ";
                    break;
                case 6:

                    break;
                case 7:
                    continue_ = false;
                    break;
                }
            }
        }
        else
        {
            //HOAT DONG CUA STUDENT
            system("cls");
            ViewCourse(ID);
        }
    }
};

#endif