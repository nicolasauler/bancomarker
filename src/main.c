#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#include <sqlite3.h>

#define NUMDBMS 3
#define NLOOPS 100

void printmenu(void);
void printresults(double times[NUMDBMS]);
void executesqlite(void);
void executebenchmark(int id, double times[NUMDBMS]);

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

void printresults(double times[NUMDBMS])
{
    printmenu();
    printf("|         |RecUtils | SQLite  |  MySQL  |\n");
    printf("| time    | %.5f | %.5f | %.5f |\n", times[0], times[1], times[2]);
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

void executebenchmark(int id, double times[NUMDBMS])
{
    int i;
    clock_t start_time = clock();
    for(i = 0; i < NLOOPS; i++)
    {
        switch (id)
        {
            case (1):
                executesqlite();
                break;

            default:
                break;
        }
    }
    times[id] = (double)(clock() - start_time)/CLOCKS_PER_SEC;
}

int main(void)
{
    double times[NUMDBMS];
    printf("Iniciando benchmarking...\n");
    executebenchmark(1, times);
    printresults(times);
    return(0);
}
