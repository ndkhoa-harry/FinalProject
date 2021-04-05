#include <iostream>
#include <fstream>

using namespace std;

struct Account {
private:
    int id;
    string pass;

public:
    Account() { }

    Account(int id, string pass) {
        this -> id = id;
        this -> pass = pass;
    }
    
    void setId(int id) { this -> id = id; }

    int getId() { return id; }

    void setPass(string pass) { this -> pass = pass; }

    string getPass() { return pass; }

    static Account findAccountFromFile(string fileName, int id) {
        ifstream inp(fileName);

        if (inp) {
            int tmpId;
            string tmpPass;

            while (inp >> tmpId) {
                inp >> tmpPass;

                if (tmpId == id) {
                    inp.close();

                    return Account(id, tmpPass);
                }
            }

            inp.close();
        }

        return Account(-1, NULL);
    }

    void changePassword(string fileName, string newPass) {
        ifstream inp(fileName);
        ofstream out("Temporary.txt");

        if (inp) {
            int tmpId;
            string tmpPass;

            while (inp >> tmpId) {
                inp >> tmpPass;

                if (tmpId == id) 
                    out << tmpId << ' ' << newPass << '\n';
                else 
                    out << tmpId << ' ' << tmpPass << '\n';
            }

            out.close();
            inp.close();

            remove ("Accounts.txt");
            rename("Temporary.txt", "Accounts.txt");
        }
    }
};
