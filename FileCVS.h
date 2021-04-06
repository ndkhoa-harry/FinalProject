#ifndef VINH
#define VINH
#include <fstream>
#include <sstream>
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

struct cvsFile
{
private:
    string fileName;

public:
    cvsFile(string filename) : fileName(filename)
    {
        fstream ofs;
        ofs.open(filename);
        if (ofs.fail())
            ofs.open(filename, ios::out);
        ofs.close();
    }

    Person *FindPerson(int ID)
    {
        ifstream ifs(fileName);
        string info;
        string pos[5];
        while (!ifs.eof())
        {
            getline(ifs, info, '\n');
            stringstream s(info);
            for (int i = 0; i < 5; i++)
            {
                getline(s, pos[i], ',');
            }
            if (sti(pos[0]) == ID)
            {
                Person *a = new Person(ID, pos[1], pos[2], pos[4], pos[3]);
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
        ofstream ofs(fileName, ios::app);
        ofs << "\n"
            << a.getId() << "," << a.getFirstName() << "," << a.getLastName() << "," << a.getDob() << "," << a.getGender();
        ofs.close();
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

    void ChangeScore(int ID, int index, string replace)
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
};

#endif