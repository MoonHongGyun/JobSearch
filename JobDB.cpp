#include <iostream>
#include <sqlite3.h>
#include <vector>
#include "Job.h"
int n = 1;
using std::cout;
using std::endl;
bool SQLiteCpp::_sqlite3_open(std::string dir)
{
    if (sqlite3_open(dir.c_str(), &db) != SQLITE_OK)
    {
        cout << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return false;
    }
    return true;
}

bool SQLiteCpp::_sqlite3_close()
{
    return (sqlite3_close(db) == SQLITE_OK);
}

std::vector<std::vector<std::string>> SQLiteCpp::GetRecords(std::string content)
{
    std::vector<std::vector<std::string>> result;
    sqlite3_stmt *stmt;
    const char *sql = content.c_str();
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
        cout << "sqlite3_prepare_v2() fail" << endl;
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        std::vector<std::string> temp;
        for (size_t i = 0; i < sqlite3_column_count(stmt); i++)
        {
            std::string str = (const char *)sqlite3_column_text(stmt, i);
            temp.push_back(str);
        }
        result.push_back(temp);
    }
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);
    return result;
}

void SQLiteCpp::InsertUser(std::string content)
{
    sqlite3_stmt *stmt;
    sqlite3_exec(db, content.c_str(), 0, 0, NULL);
}

int SQLiteCpp::OverlapCheck(std::string content)
{
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, content.c_str(), -1, &stmt, NULL) != SQLITE_OK)
        cout << "sqlite3_prepare_v2() fail" << endl;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        sqlite3_reset(stmt);
        sqlite3_finalize(stmt);
        return 1; // Overlap
    }
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);
    return 0; // Not Overlap
}

std::string SQLiteCpp::UserNumbering()
{
    std::string check;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(Id) FROM User;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
        cout << "sqlite3_prepare_v2() fail" << endl;
    sqlite3_step(stmt);
    check = (const char *)sqlite3_column_text(stmt, 0);
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);
    return check;
}
