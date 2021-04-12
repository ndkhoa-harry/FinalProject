#ifndef VINH
#define VINH
#include <fstream>
#include <sstream>
#include <algorithm>
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
char *stc(string a)
{
    char *x = new char[a.length() + 1];
    for (int i = 0; i < a.length(); i++)
        x[i] = a[i];
    x[a.length()] = '\0';
    return x;
}

//DOI KIEU INT SANG STRING
string its(int num)
{
    int k = 0;
    for (int i = 1; num * 1.0 / i > 1; i *= 10)
        k++;
    string re;
    re.resize(k);
    for (int i = 0; i < k; i++)
    {
        re[k - i - 1] = 48 + num % 10;
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
    PathToFolder.insert(0,"mkdir ");
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
    //  FOLDER: NHAP DUONG DAN TOI FOLDER MUON TAO HOAC TEN FOLDER MUON MO
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

    Person *FindPerson(int ID)
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
                Person *a = new Person(ID, pos[2], pos[3], pos[5], pos[4]);
                return a;
            }
        }
        return nullptr;
    }

    void AddPerson(Person a)
    {
        Person *pe = this->FindPerson(a.getId());
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

    void AddString(string s)
    {
        ofstream ofs(fileName, ios::app);
        ofs << s;
        ofs.close();
    }

    bool RemoveFile()
    {
        int re = remove(stc(fileName));
        bool ok = (re == 0) ? 1 : 0;
        return ok;
    }

    //USE THIS FUNC TO CHANGE POINT(INDEX OF POINT), PASS(INDEX = 1)
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

    void ReadFile()
    {
        ifstream ifs(fileName);
        string s;
        getline(ifs, s, '\0');
        cout << s;
        ifs.close();
    }

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
};

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
        Year.insert(0,"D:/FinalProject/");
        CreateFolder(Year);
    }
    void CreateSemester()
    {
        int Semester;
        cout << "Plz choose one semester: ";
        cin >> Semester;
        Semester %= 3;
        string NameSemester;
        switch(Semester)
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
        year.insert(0,"D:/FinalProject/");
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
            if (i == 1)//              VI TRI MA MON HOC O VI TRI THU 1 (KE TU VI TRI THU 0)
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
        CourseName.insert(0,ThreeFirstLetterOfSemester);
        cvsFile course_(CourseName,year);
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
        system("cls");
        if (ID == 0)
        {
            //HOAT DONG CUA STAFF MEM
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
        else
        {
            //HOAT DONG CUA STUDENT
        }
    }
};

#endif