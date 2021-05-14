#ifndef _HELPER_H_
#define _HELPER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <windows.h>

#include "Date.h"
#include "Picasso.h"

using namespace std;

/// CURRENT TIME (dd/mm/yyyy)
Date CURRENT_DATE("01/01/2021");

/// SCHOOL
const string SCHOOL_FILE = "Data/School.txt";

/// SCHOOL YEAR
const string SCHOOL_YEARS_FILE = "Data/SchoolYears/";

/// CLASSES
const string CLASSES_FILE = "Data/Classes/";

/// STUDENT
const int STUDENT_MAX_COMPONENTS = 7;
const string STUDENTS_FILE = "Data/Students/";
const string STUDENTS_TEMPORARY_FILE = "Data/Students/Temporary.csv";

/// SEMESTER
const string SEMESTERS_NAMES[] = {"Fall", "Summer", "Autumn"};

/// COURSE
const string COURSES_FILE = "Data/Courses/";
const string DAY_OF_WEEK[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const string SESSIONS[] = {"SS1 (07:30)", "SS2 (09:30)", "SS3 (13:30)", "SS4 (15:30)"};

/// ACCOUNT
const string ACCOUNTS_FILE = "Data/Accounts.txt";
const string ACCOUNTS_TEMPORARY_FILE = "Data/Temporary.txt";

/// ACCOUNT TYPE
const int TYPE_STAFF = 1;
const int TYPE_STUDENT = 2;

/// STAFF ACCOUNT
const string STAFFS_FILE = "Data/Staffs.csv";
const int STAFF_COMPONENTS_COUNT = 5;

/// STUDENT ACCOUNT
const int MAX_ENROLLED_COURSES = 5;

string toStringPrecision(double d) {
    stringstream s;

    s << fixed << setprecision(3) << d;

    return s.str();
}

#endif
