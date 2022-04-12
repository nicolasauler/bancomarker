#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sqlite3.h>

int main(void)
{
    char *sql_stmt;
    sqlite3 *daba;
    if(sqlite3_open_v2("datab.db", &daba, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL))
    {
        sqlite3_close_v2(daba);
        exit(EXIT_FAILURE);
    }
    sql_stmt = "DROP TABLE IF EXISTS Shit;\
                CREATE TABLE Shit(foo INT, bar TEXT, baz INT);\
                INSERT INTO Shit VALUES(0, 'merda', 69);\
                INSERT INTO Shit VALUES(1, 'mierda', 420);\
                INSERT INTO Shit VALUES(2, 'mierda', 420);\
                INSERT INTO Shit VALUES(3, 'mierda', 420);\
                INSERT INTO Shit VALUES(4, 'mierda', 420);\
                INSERT INTO Shit VALUES(5, 'mierda', 420);\
                INSERT INTO Shit VALUES(6, 'mierda', 420);\
                INSERT INTO Shit VALUES(7, 'mierda', 420);\
                INSERT INTO Shit VALUES(8, 'mierda', 420);\
                INSERT INTO Shit VALUES(9, 'mierda', 420);\
                INSERT INTO Shit VALUES(10, 'mierda', 420);\
                INSERT INTO Shit VALUES(11, 'mierda', 420);";
    sqlite3_exec(daba, sql_stmt, NULL, NULL, NULL);
    sqlite3_close_v2(daba);
    return(0);
}
