#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#include <sqlite3.h>

void printmenu(void);
void printresults(void);
void executesqlite(void);
double benchmark(int id);

void printmenu(void)
{
    int i;
    printf(" ");
    for(i = 0; i < 39; i++)
    {
        printf("-");
    }
    printf("\n");
}

void printresults(void)
{
    printmenu();
    printf("|         |RecUtils | SQLite  |  MySQL  |\n");
    printf("| time    |         |         |         |\n");
    printf("| readblty|         |         |         |\n");
    printmenu();
}

void executesqlite(void)
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
                INSERT INTO Shit VALUES(1, 'mierda', 420);";
    sqlite3_exec(daba, sql_stmt, NULL, NULL, NULL);
    sqlite3_close_v2(daba);
}

double benchmark(int id)
{
    int i;
    clock_t start_time = clock();
    for(i = 0; i < 999; i++)
    {
        executesqlite();
    }
    return((double)(clock() - start_time)/CLOCKS_PER_SEC);
}



int main(void)
{
    printf("Iniciando benchmarking...\n");
    printresults();
    printf("%f\n", benchmark(0));
    return(0);
}
