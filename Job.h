#pragma once

#include <iostream>
#include <sqlite3.h>
#include <vector>

static const std::string INSERT_USER = "INSERT INTO User VALUES ";

class SQLiteCpp
{
private:
    sqlite3 *db;

public:
    bool _sqlite3_open(std::string dbName);
    bool _sqlite3_close();
    std::vector<std::vector<std::string>> GetRecords(std::string content);
    void InsertUser(std::string content);
    int OverlapCheck(std::string content);
    std::string UserNumbering();
};

class User
{
private:
    std::string mid, mpw;

public:
    void SignUp();
    int Login();
    int Division();
};

class Start
{
private:
    std::vector<std::string> keyword1 = {"경력", "신입"},
                             keyword2 = {"무관", "무관/예정자 가능", "고졸이상", "대학교(2~3년)제 이상", "대학교(2~3년)제 이상/예정자 가능", "대학교(4년)제 이상", "대학교(4년)제 이상/예졍자 가능"},
                             keyword3 = {"서울", "경기", "세종", "경북", "경남", "충북", "충남", "대전", "부산", "광주"},
                             keyword4 = {"C", "C++", "C#", "Python"},
                             KeySock, KeySockC, KeySockE, KeySockL, KeySockS,
                             mcupdate1 = {"공고제목", "주요스킬", "지역", "담당업무", "우대사항", "지원마감일"},
                             mcupdate2 = {"대표자명", "사원수", "기업형태", "홈페이지", "설립일", "업종"},
                             dbupdate1 = {"Title", "Skill", "Local", "Work", "Preferential", "Period"},
                             dbupdate2 = {"Ceo", "Employee", "CoperateForm", "Hompage", "Establishmer", "Type"};
    std::string co;

public:
    int FirstMap();
    int MainMap(int player);
    void SearchMap();
    int SearchMap2();
    void KeyClear();
    int DetailMap(int cnum);
    void Cinfo(int cnum);
    void CoUpdate();
    std::string CoOverlap(std::string check);
    int CoCheck();
};