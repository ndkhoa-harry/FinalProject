#include <iostream>
#include <fstream>

using namespace std;

struct Account {
private:
    int id;
    char* pass;
public:
    Account(int id, char* pass) {
        this -> id = id;
        this -> pass = pass;
    }

    ~Account() {
        if (pass) delete[] pass;
    }

    Account findAccountFromFile(char* fileName, int id) {
        ifstream inp(fileName);

        int tmpId;
        char* tmpPass = new char[100];

        while (inp >> tmpId) {
            inp >> tmpPass;

            if (tmpId == id) {
                inp.close();

                return Account(id, tmpPass);
            }
        }

        inp.close();

        return Account(-1, nullptr);
    }
};
