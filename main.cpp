#include "FileCVS.h"
using namespace std;

int main()
{
    SignIn acc;
    fstream fs("vidu.txt");
    if(fs.fail())
    {
        ofstream ofs("vidu.txt");
        ofs.close();
        cout << "file vidu.txt chua co du lieu!!!";
    }
    fs.close();
    //          account: 0 :enter        pass: hi :space
    acc.LogIn("vidu.txt");
    system("pause");
}