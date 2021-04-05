#ifndef VINH
#define VINH
#include <fstream>
#include "Person.h"
using namespace std;
//DOI KIEU CHAR SANG INTEGER
int cti(char* x)
{
    int k = 1;
    int sum = 0;
    char* end = x;
    while (*(end + 1) != NULL) end++;
    while (end != (x - 1))
    {
        sum += (int(*end) - 48) * k;
        k *= 10;
        end--;
    }
    return sum;
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
        char* info = new char[101];
        char* pos[5] = {nullptr};
        ifstream ifs(fileName);
        while (!ifs.eof())
        {
            ifs.getline(info, 50, '\n');
            char* del = info;
            for (int i = 0; i < 5; i++)
            {
                pos[i] = info;
                while (*info != ',') info++;
                *info = '\0';
                info++;
            }
            if (cti(pos[0]) == ID)
            {
                delete[] info;
                ifs.close();
                Person* a = new Person(ID, pos[1], pos[2], pos[3], (*pos[4] == '1')? 1:0);
                return a;
            }
            delete[] del;
        }
        ifs.close();
        return nullptr;
    }

    void AddPerson(Person a)
    {
        ofstream ofs(fileName, ios::app);
        ofs << a.ID() <<","<<a.info(1)<<","<<a.info(2)<<","<<a.info(3)<<","<<a.gendr()<<"\n";
        ofs.close();
    }
};

#endif