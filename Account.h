#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#include "Helper.h"

class Account {
private:
    int id;
    string pass;

public:
    Account() { }

    Account(int id, string pass) {
        this -> id = id;
        this -> pass = pass;
    }

    int getId() { return id; }

    string getPass() { return pass; }

    int getType() {
        int res = id;
        while (res > 9) res /= 10;
        return res;
    }
    
    void changePassword(string newPass) {
        ifstream inp(ACCOUNTS_FILE);
        ofstream out(ACCOUNTS_TEMPORARY_FILE);

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

            pass = newPass;

            out.close();
            inp.close();

            remove(ACCOUNTS_FILE.c_str());
            rename(ACCOUNTS_TEMPORARY_FILE.c_str(), ACCOUNTS_FILE.c_str());
        }
    }

    static Account* findAccountFromFile(int id) {
        ifstream inp(ACCOUNTS_FILE);

        if (inp) {
            int tmpId;
            string tmpPass;

            while (inp >> tmpId) {
                inp >> tmpPass;

                if (tmpId == id) {
                    inp.close();

                    return new Account(id, tmpPass);
                }
            }

            inp.close();
        }

        return nullptr;
    }
};

#endif