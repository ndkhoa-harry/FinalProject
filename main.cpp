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
    initWindowSize();

    int id;
    string pass;
    Account* account = nullptr;

    while (1) {    
        account = Account::displayLoginBox();

        if (account)
            mainProcess(account);
        else
            break;
    } 

    return 0;
}
