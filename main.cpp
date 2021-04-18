#include "main.h"

void mainProcess(Account* account) { 
    int type = account -> getType();

    if (type == TYPE_STAFF) {
        StaffAccount* staff = new StaffAccount(account);

        staff -> getStaffAccountFromFile();
        
        staff -> displayMenu();

        delete staff;
    } else if (type == TYPE_STUDENT) {
        StudentAccount* student = new StudentAccount(account);

        student -> getStudentAccountFromFile();

        student -> displayMenu();

        delete student;
    }
}

int main() {
    int id;
    string pass;
    Account* account = nullptr;

    while (1) {    
        cout << "Type your ID: "; cin >> id;
        cout << "Type your Pass: "; cin >> pass;

        account = Account::findAccountFromFile(id);

        if (account) {
            if (pass.compare(account -> getPass()) == 0) {
                cout << "Login successfully!!!\n";

                mainProcess(account);

                break;
            } else 
                cout << "Incorrect password!!!\n";
        } else 
            cout << "Incorrect username!!!\n";
    } 

    return 0;
}