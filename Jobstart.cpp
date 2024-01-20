#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <cstring>
#include <algorithm>
#include "Job.h"

using std::cout;
using std::endl;
int Start::FirstMap()
{
    system("clear");
    std::string select;
    cout << "1.회원가입\n2.로그인\n";
    cout << "번호를 입력해주세요.: ";
    getline(std::cin, select);
    while (select != "1" && select != "2")
    {
        cout << "없는 번호입니다. 다시입력하세요.\n";
        cout << "번호를 입력해주세요.: ";
        std::cin >> select;
    }
    if (select == "1")
        return 1;
    else
        return 2;
}

int Start::MainMap(int player)
{
    system("clear");
    SQLiteCpp cpp;
    std::vector<std::vector<std::string>> check;
    std::string RECOMMENDATION = "SELECT Title,Coperation,Local FROM Search WHERE RANDOM() LIMIT 3;";
    std::string select;

    cpp._sqlite3_open("JobSearch");
    check = cpp.GetRecords(RECOMMENDATION);
    for (size_t j = 0; j < check.size(); j++)
        for (size_t k = 0; k < check[0].size(); k++)
            switch (k)
            {
            case 0:
                cout << j + 1 << "번공고: " << check[j][k] << endl;
                break;
            case 1:
                cout << "     ●  회사명 : " << check[j][k] << "  ";
                break;
            case 2:
                cout << "●  지역 : " << check[j][k] << endl
                     << endl;
                break;
            default:
                break;
            }
    cout << "-----------------------------------------------------------" << endl;
    cout << "1 -> 검색하기" << endl
         << "2 -> 로그아웃" << endl;
    if (player == 0)
        cout << "3 -> 정보 업데이트" << endl;
    cout << "번호를 입력하세요.: ";
    getline(std::cin, select);
    if (player == 0)
    {
        while (atoi(select.c_str()) != 0 && atoi(select.c_str()) != 1 && atoi(select.c_str()) != 2 && atoi(select.c_str()) != 3)
        {
            cout << "해당 번호는 없습니다.\n";
            cout << "번호를 입력하세요.: ";
            getline(std::cin, select);
        }
    }
    else
        while (atoi(select.c_str()) != 0 && atoi(select.c_str()) != 1 && atoi(select.c_str()) != 2)
        {
            cout << "해당 번호는 없습니다.\n";
            cout << "번호를 입력하세요.: ";
            getline(std::cin, select);
        }
    cpp._sqlite3_close();
    return atoi(select.c_str());
}

void Start::SearchMap()
{
    std::string select;
    while (1)
    {
        system("clear");
        for (int i = 0; i < keyword1.size(); i++)
            cout << "※ " << keyword1[i] << " ";
        cout << endl;
        for (int i = 0; i < keyword2.size(); i++)
            cout << "※ " << keyword2[i] << " ";
        cout << endl;
        for (int i = 0; i < keyword3.size(); i++)
            cout << "※ " << keyword3[i] << " ";
        cout << endl;
        for (int i = 0; i < keyword4.size(); i++)
            cout << "※ " << keyword4[i] << " ";
        cout << endl;
        cout << "------------------------------------------------------" << endl;
        cout << "선택한 키워드: ";
        for (int i = 0; i < KeySock.size(); i++)
        {
            if (i == 0)
                cout << KeySock[i];
            else
                cout << ", " << KeySock[i];

            if (i % 4 == 0 && i != 0)
                cout << endl;
        }
        cout << endl;
        cout << "-최소 3가지 이상-" << endl
             << "-검색하기: e" << endl
             << "-선택 키워드 지우기: x" << endl;
        cout << "키워드를 선택하세요." << endl;
        getline(std::cin, select);
        if (select == "e" && KeySock.size() >= 3)
            break;
        else if (select == "x")
            KeyClear();
        else
        {
            if (std::find(keyword1.begin(), keyword1.end(), select) != keyword1.end() && std::find(KeySock.begin(), KeySock.end(), select) == KeySock.end())
            {
                KeySock.push_back(select);
                KeySockC.push_back(" Career LIKE '\%" + select + "\%'");
            }
            else if (std::find(keyword2.begin(), keyword2.end(), select) != keyword2.end() && std::find(KeySock.begin(), KeySock.end(), select) == KeySock.end())
            {
                std::string vkey = std::to_string(std::find(keyword2.begin(), keyword2.end(), select) - keyword2.begin());
                KeySock.push_back(select);
                KeySockE.push_back(" Education LIKE '\%" + vkey + "\%'");
            }
            else if (std::find(keyword3.begin(), keyword3.end(), select) != keyword3.end() && std::find(KeySock.begin(), KeySock.end(), select) == KeySock.end())
            {
                KeySock.push_back(select);
                KeySockL.push_back(" Local LIKE '\%" + select + "\%'");
            }
            else if (std::find(keyword4.begin(), keyword4.end(), select) != keyword4.end() && std::find(KeySock.begin(), KeySock.end(), select) == KeySock.end())
            {
                if (select == "C")
                    KeySock.push_back(select + ",");
                else
                    KeySock.push_back(select);
                KeySockS.push_back(" Skill LIKE '\%" + select + "\%'");
            }
        }
    }
}

int Start::SearchMap2()
{
    SQLiteCpp cpp;
    int num = 1;
    std::string select;
    std::vector<std::vector<std::string>> check, check2;
    std::string content = "SELECT COUNT(*) FROM Search WHERE";
    std::string contentsearch = "SELECT Code,Title,Coperation,Local FROM Search WHERE";

    system("clear");
    for (int i = 0; i < KeySockC.size(); i++)
    {
        if (i == 0)
        {
            content += "(";
            contentsearch += "(";
        }
        content += KeySockC[i];
        contentsearch += KeySockC[i];
        if (KeySockC.size() - 1 != i)
        {
            content += " OR";
            contentsearch += " OR";
        }
        else
        {
            content += ")";
            contentsearch += ")";
        }
    }
    if (KeySockC.size() != 0)
    {
        content += " AND";
        contentsearch += " AND";
    }
    for (int i = 0; i < KeySockE.size(); i++)
    {
        if (i == 0)
        {
            content += "(";
            contentsearch += "(";
        }
        content += KeySockE[i];
        contentsearch += KeySockE[i];
        if (KeySockE.size() - 1 != i)
        {
            content += " OR";
            contentsearch += " OR";
        }
        else
        {
            content += ")";
            contentsearch += ")";
        }
    }
    if (KeySockE.size() != 0)
    {
        content += " AND";
        contentsearch += " AND";
    }
    for (int i = 0; i < KeySockL.size(); i++)
    {
        if (i == 0)
        {
            content += "(";
            contentsearch += "(";
        }
        content += KeySockL[i];
        contentsearch += KeySockL[i];
        if (KeySockL.size() - 1 != i)
        {
            content += " OR";
            contentsearch += " OR";
        }
        else
        {
            content += ")";
            contentsearch += ")";
        }
    }
    if (KeySockL.size() != 0 && KeySockS.size() != 0)
    {
        content += " AND";
        contentsearch += " AND";
    }
    for (int i = 0; i < KeySockS.size(); i++)
    {
        if (i == 0)
        {
            content += "(";
            contentsearch += "(";
        }
        content += KeySockS[i];
        contentsearch += KeySockS[i];
        if (KeySockS.size() - 1 != i)
        {
            content += " OR";
            contentsearch += " OR";
        }
        else
        {
            content += ")";
            contentsearch += ")";
        }
    }
    content += ";";
    contentsearch += ";";
    cout << contentsearch << endl; // 쿼리문 겁사
    cpp._sqlite3_open("JobSearch");
    check = cpp.GetRecords(content);
    cpp._sqlite3_close();
    cpp._sqlite3_open("JobSearch");
    check2 = cpp.GetRecords(contentsearch);
    cpp._sqlite3_close();
    for (size_t i = 0; i < check2.size(); i++)
        for (size_t j = 0; j < check2[0].size(); j++)
            switch (j)
            {
            case 0:
                cout << "---------------------------------------------------------------------\n";
                cout << "번호:" << check2[i][j] << endl;
                break;
            case 1:
                cout << "→  공고제목: " << check2[i][j] << endl;
                break;
            case 2:
                cout << "🏢 : " << check2[i][j] << endl;
                break;
            case 3:
                cout << "🗺️ : " << check2[i][j] << endl;
                break;
            default:
                break;
            }
    cout << "---------------------------------------------------------------------\n";
    cout << "검색된 수 : " << check[0][0] << "건\n";
    cout << "---------------------------------------------------------------------\n";
    cout << "-상세보기-\n";
    cout << "공고 번호를 입력해주세요.(나가기 q): ";
    while (1)
    {
        getline(std::cin, select);
        if (select == "q")
        {
            KeyClear();
            return 0;
        }
        else if (atoi(select.c_str()) != 0 && atoi(select.c_str()) <= 80 && atoi(select.c_str()) > 0)
            return stoi(select);
        else
        {
            cout << "잘못입력했습니다. 다시입려해주십시오\n";
            continue;
        }
    }
}

void Start::KeyClear()
{
    KeySock.clear();
    KeySockC.clear();
    KeySockE.clear();
    KeySockL.clear();
    KeySockS.clear();
}

int Start::DetailMap(int cnum)
{
    std::string select;
    SQLiteCpp cpp;
    std::vector<std::vector<std::string>> check;
    std::string content = "SELECT Coperation, Skill, Work, Preferential, Period FROM Search WHERE Code = '" + std::to_string(cnum) + "';";
    cpp._sqlite3_open("JobSearch");
    check = cpp.GetRecords(content);
    cpp._sqlite3_close();

    system("clear");
    for (size_t j = 0; j < check[0].size(); j++)
        switch (j)
        {
        case 0:
            cout << "---------------------------------------------------------------------\n";
            cout << "회사명: " << check[0][j] << endl;
            break;
        case 1:
            cout << "주요스킬: " << check[0][j] << endl;
            break;
        case 2:
            cout << "담당업무: " << check[0][j] << endl;
            break;
        case 3:
            cout << "우대사항: " << check[0][j] << endl;
            break;
        case 4:
            cout << "지원 마감일: " << check[0][j] << endl;
            break;
        default:
            break;
        }
    cout << "---------------------------------------------------------------------\n";
    cout << "1.기업정보보기    2.나가기" << endl;
    while (1)
    {
        cout << "번호를 입력해주세요.: ";
        getline(std::cin, select);
        if (atoi(select.c_str()) == 1)
            return cnum;
        else if (atoi(select.c_str()) == 2)
            return 0;
        else
        {
            cout << "해당번호는 없습니다.\n";
            continue;
        }
    }
}

void Start::Cinfo(int cnum)
{
    SQLiteCpp cpp;
    std::vector<std::vector<std::string>> check;
    std::string content = "SELECT * FROM INFO WHERE CODE = '" + std::to_string(cnum) + "';";
    cpp._sqlite3_open("JobSearch");
    check = cpp.GetRecords(content);
    cpp._sqlite3_close();
    for (size_t i = 0; i < check[0].size(); i++)
        switch (i)
        {
        case 0:
            break;
        case 1:
            break;
        case 2:
            cout << "---------------------------------------------------------------------\n";
            cout << "대표자 명: " << check[0][i] << endl;
            break;
        case 3:
            cout << "사원 수: " << check[0][i] << endl;
            break;
        case 4:
            cout << "기업 형태: " << check[0][i] << endl;
            break;
        case 5:
            cout << "홈페이지: " << check[0][i] << endl;
            break;
        case 6:
            cout << "설립일: " << check[0][i].substr(0, 4) << "년 " << check[0][i].substr(4, 2) << "월 " << check[0][i].substr(6, 2) << "일" << endl;
            break;
        case 7:
            cout << "업종: " << check[0][i] << endl;
            break;
        default:
            break;
        }
    cout << "---------------------------------------------------------------------\n";
    cout << "(아무키나 누르면 뒤로 돌아갑니다.)";
    std::cin.get();
}

void Start::CoUpdate()
{
    SQLiteCpp cpp;
    std::string content, intext;
    int check = 0;

    if (CoCheck() == 1)
    {
        cout << "1.구인 정보 업데이트\n2.기업정보 업데이트" << endl;
        getline(std::cin, intext);
        if (intext == "1")
        {
            content = "UPDATE Search SET ";
            while (1)
            {
                system("clear");
                cout << "---------------------------------------------------------------------\n";
                for (int i = 0; i < mcupdate1.size(); i++)
                    cout << "※ " << mcupdate1[i] << endl;
                cout << "---------------------------------------------------------------------\n";
                cout << "변경할 키워드를 선택하십시오(나가기 q): ";
                getline(std::cin, intext);
                if (std::find(mcupdate1.begin(), mcupdate1.end(), intext) != mcupdate1.end())
                {
                    if (check == 1)
                        content += ", ";
                    content += CoOverlap(intext);
                    cout << "변경할 내용을 입력하십시오.(내용을 적지않으면 업데이트 되지않습니다.): ";
                    getline(std::cin, intext);
                    if (intext.size() != 0)
                    {
                        content += " = '" + intext + "'";
                        check = 1;
                    }
                }
                else if (intext == "q")
                {
                    content += " WHERE Coperation = '" + co + "';";
                    if (check != 0)
                    {
                        cout << content;
                        exit(1);
                        // cpp._sqlite3_open("JobSearch");
                        // cpp.InsertUser(content);
                        // cpp._sqlite3_close();
                        break;
                    }
                }
            }
        }
        else if (intext == "2")
        {
            check = 0;
            content = "UPDATE Info SET ";
            while (1)
            {
                system("clear");
                cout << "---------------------------------------------------------------------\n";
                for (int i = 0; i < mcupdate2.size(); i++)
                    cout << "※ " << mcupdate2[i] << endl;
                cout << "---------------------------------------------------------------------\n";
                cout << "변경할 키워드를 선택하십시오(나가기 q): ";
                getline(std::cin, intext);
                if (std::find(mcupdate2.begin(), mcupdate2.end(), intext) != mcupdate2.end())
                {
                    if (check == 1)
                        content += ", ";
                    content += CoOverlap(intext);
                    cout << "변경할 내용을 입력하십시오.(내용을 적지않으면 업데이트 되지않습니다.): ";
                    getline(std::cin, intext);
                    if (intext.size() != 0)
                        content += " = '" + intext + "'";
                    check = 1;
                }
                else if (intext == "q")
                {
                    content += " WHERE Coperation = '" + co + "';";
                    if (check != 0)
                    {
                        // cpp._sqlite3_open("JobSearch");
                        // cpp.InsertUser(content);
                        // cpp._sqlite3_close();
                        cout << content;
                        exit(1);
                        break;
                    }
                }
            }
        }
    }
}

std::string Start::CoOverlap(std::string check)
{
    if (std::find(mcupdate1.begin(), mcupdate1.end(), check) != mcupdate1.end())
        return dbupdate1[std::find(mcupdate1.begin(), mcupdate1.end(), check) - mcupdate1.begin()];
    else if (std::find(mcupdate2.begin(), mcupdate2.end(), check) != mcupdate2.end())
        return dbupdate2[std::find(mcupdate2.begin(), mcupdate2.end(), check) - mcupdate2.begin()];
    return NULL;
}

int Start::CoCheck()
{
    std::vector<std::vector<std::string>> check;
    SQLiteCpp cpp;
    std::string text, text2;
    cout << "ID: ";
    getline(std::cin, text2);
    cout << "본인 회사명: ";
    getline(std::cin, text);
    cpp._sqlite3_open("JobSearch");
    if (cpp.OverlapCheck("SELECT COP FROM COID WHERE COP = '" + text + "' AND ID = '" + text2 + "';") == 1 && cpp.OverlapCheck("SELECT coperation FROM Search WHERE coperation = '" + text + "';") == 1)
    {
        co = text;
        cpp._sqlite3_close();
        return 1;
    }
    else if (cpp.OverlapCheck("SELECT COP FROM COID WHERE COP = '" + text + "' AND ID = '" + text2 + "' ;") == 1)
    {
        cout << "저희 앱과 계약이 되어있지않습니다. 계약하시겠습니까?(엔터)";
        std::cin.get();
        cout << "그런거 없어 그런거 없어 그런거 없어 그런거 없어 그런거 없어 그런거 없어 그런거 없어 그런거 없어 그런거 없어 ";
        std::cin.get();
        cpp._sqlite3_close();
        return 2;
    }
    else
    {
        cout << "회사명이 정보와 일치하지 않습니다.(엔터)\n";
        std::cin.get();
        cpp._sqlite3_close();
        return 3;
    }
}