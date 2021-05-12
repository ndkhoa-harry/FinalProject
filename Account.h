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
    void displayChangePasswordBox() {
        string title = "Change password";

        int fieldLength = 40;

        const int inputsCount = 2;
        string instructions[inputsCount] = {
            "Old password: ",
            "New password: "
        };

        string* inputsData = new string[inputsCount] { "", "" };

        while (1) {
            if (!drawInputBox(title, fieldLength, inputsCount, instructions, inputsData))
                return;

            if (inputsData[0].compare(pass) == 0) {
                if (inputsData[1].size() > 0) {
                    changePassword(inputsData[1]);

                    drawOkayBox("Note", "Change password successfully");

                    return;
                } else
                    drawOkayBox("Error!!!", "New password can't be empty!");
            } else
                drawOkayBox("Error!!!", "Old password incorrect!");
        }
    }
    static void addNewAccount(int id, string pass) {
        ofstream out(ACCOUNTS_FILE, ios::app);
        out << id << ' ' << pass << '\n';
        out.close();
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