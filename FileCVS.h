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
            {
                getline(s, pos[i], ',');
            }
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
            else return "";
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

    void SetNewStudentsPass(string FileOfPass)
    {
        cvsFile ifs(FileOfPass);
        string data = "";
        for (int i = 0;; i++)
        {
            string s = this->GetLine(i,1);
            if (s == "") break;
            data.insert(data.length(), s);
            data.push_back(' ');
            data.push_back('0');
            data.push_back('\n');
        }
        ifs.AddString(data);
    }
};

#endif