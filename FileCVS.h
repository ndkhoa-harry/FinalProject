#ifndef VINH
#define VINH
#include <iostream>
#include <fstream>
#include <string>
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
        k*=10;
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

struct cvsFile
{
private:
    string fileName;
public:
    cvsFile(string filename): fileName(filename)
    {
        fstream ofs;
        ofs.open(filename);
        if (ofs.fail())
            ofs.open(filename, ios::out);
        ofs.close();
    }

    Person* Find(int ID)
    {
        ifstream ifs(fileName);
        string info;
        string pos[6];
        while (!ifs.eof())
        {
            getline(ifs, info);
            for (int i = 0; i < 6; i++)
            {
                stringstream s(info);
                getline(s, pos[i], ',');
            }
            if (sti(pos[0]) == ID)
            {
                Person* a = new Person(ID, stc(pos[1]), stc(pos[2]), stc(pos[3]), stc(pos[4]), (pos[5] == "1")? 1:0);
                return a;
            }
        }
        return nullptr;
    }

    void AddPerson(Person a)
    {
        ofstream ofs(fileName, ios::app);
        ofs << a.ID() <<","<<a.info("FirstName")<<","<<a.info("LastName")<<","<<a.info("DoB")<<","<<a.info("Gender")<<"\n";
        ofs.close();
    }
};

#endif