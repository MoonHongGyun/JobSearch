#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <cstring>

#include "Job.h"

using std::cout;
using std::endl;

void User::SignUp()
{
    SQLiteCpp cpp;
    std::string id, pw, email, pnum, alltext, n, company;
    int Who;
    std::vector<std::vector<std::string>> check;
    cout << "ID: "; // ID
    getline(std::cin, id);
    cpp._sqlite3_open("JobSearch");
    while (cpp.OverlapCheck("SELECT Id FROM User WHERE Id = '" + id + "';") != 0 || id.length() == 0)
    {
        cout << "아이디 중복\n"
             << "ID: ";
        getline(std::cin, id);
        cpp._sqlite3_close();
        cpp._sqlite3_open("JobSearch");
    }
    cpp._sqlite3_close();

    cout << "PW(숫자 4자리): "; // PW
    getline(std::cin, pw);
    while (pw.length() != 4 || isdigit(pw[0]) == 0 || isdigit(pw[1]) == 0 || isdigit(pw[2]) == 0 || isdigit(pw[3]) == 0)
    {
        cout << "다시 입력해주십시오.\n";
        cout << "PW(숫자 4자리): ";
        getline(std::cin, pw);
    }

    cout << "Email: "; // Email
    getline(std::cin, email);
    cpp._sqlite3_open("JobSearch");
    while (cpp.OverlapCheck("SELECT Email FROM User WHERE Email = '" + email + "';") != 0 || email.length() == 0)
    {
        cout << "이메일 중복\n"
             << "Email: ";
        getline(std::cin, email);
        cpp._sqlite3_close();
        cpp._sqlite3_open("JobSearch");
    }
    cpp._sqlite3_close();

    cout << "PhoneNumber: "; // Pnum
    getline(std::cin, pnum);
    cpp._sqlite3_open("JobSearch");
    while (cpp.OverlapCheck("SELECT Pnum FROM User WHERE Pnum = '" + pnum + "';") != 0 || pnum.length() == 0)
    {
        cout << "전화번호 중복\n"
             << "PhoneNumber: ";
        getline(std::cin, pnum);
        cpp._sqlite3_close();
        cpp._sqlite3_open("JobSearch");
    }
    cpp._sqlite3_close();

    cout << "1.일반회원 2.기업회원\n" // Member
         << "번호를 입력하세요.: ";
    std::cin >> Who;
    while (Who != 1 && Who != 2)
    {
        cout << "다시 입력하세요.\n";
        cout << "1.일반회원 2.기업회원\n"
             << "번호를 입력하세요.: ";
        std::cin >> Who;
    }
    std::cin.ignore();
    cpp._sqlite3_open("JobSearch");
    if (Who == 1)
        n = cpp.UserNumbering() + "A";
    else if (Who == 2)
    {
        n = cpp.UserNumbering() + "B";
        cout << "본인 회사명을 적어주세요( (주) 포함): ";
        getline(std::cin, company);
        cpp.InsertUser("INSERT INTO COID VALUES('" + id + "','" + company + "');");
    }
    cpp._sqlite3_close();

    alltext = "('" + id + "','" + pw + "','" + email + "','" + pnum + "','" + n + "');"; // DB save
    cpp._sqlite3_open("JobSearch");
    cpp.InsertUser(INSERT_USER + alltext);
    cpp._sqlite3_close();
}

int User::Login()
{
    std::string id, pw;
    SQLiteCpp cpp;
    cout << "Q 또는 q 입력시 뒤로가기\n";
    cout << "ID: ";
    getline(std::cin, id);
    if (id == "Q" || id == "q")
        return 0;
    cout << "PW: ";
    getline(std::cin, pw);
    if (pw == "Q" || pw == "q")
        return 0;
    cpp._sqlite3_open("JobSearch");
    while (cpp.OverlapCheck("SELECT * FROM User WHERE Id = '" + id + "' AND Pw = '" + pw + "';") == 0)
    {
        cout << "로그인 실패\n";
        cout << "Q 또는 q 입력시 뒤로가기\n";
        cout << "ID: ";
        getline(std::cin, id);
        if (id == "Q" || id == "q")
        {
            cpp._sqlite3_close();
            return 0;
        }
        cout << "PW: ";
        getline(std::cin, pw);
        if (pw == "Q" || pw == "q")
        {
            cpp._sqlite3_close();
            return 0;
        }
        cpp._sqlite3_close();
        cpp._sqlite3_open("JobSearch");
    }
    cpp._sqlite3_close();
    mid = id;
    mpw = pw;
    return 1;
}

int User::Division()
{
    SQLiteCpp cpp;
    int result;
    cpp._sqlite3_open("JobSearch");
    result = cpp.OverlapCheck("SELECT * FROM User WHERE Member LIKE '\%A' AND Id = '" + mid + "';");
    cpp._sqlite3_close();
    return result;
}