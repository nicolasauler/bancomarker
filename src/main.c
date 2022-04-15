#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <string.h>

#include <ncurses.h>
#include "menu.h"

#include <sqlite3.h>
#include <mysql/mysql.h>


#define NUMDBMS 3
#define NLOOPS 100

#define EXESQLite 1
#define EXEMYSQL 2


void printbox(WINDOW *win);
void printresults(WINDOW *win, double times[NUMDBMS]);
void executesqlite(void);
void executemysql(void);
void executebenchmark(int id, double times[NUMDBMS]);

void printbox(WINDOW *win)
{
    int i;
    wprintw(win, " ");
    for(i = 0; i < 37; i++)
    {
        wprintw(win, "-");
    }
    wprintw(win, "\n");
}

void printresults(WINDOW *win, double times[NUMDBMS])
{
    printbox(win);
    wprintw(win, "|       |RecUtils | SQLite  |  MySQL  |\n");
    wprintw(win, "| time  | %.5f | %.5f | %.5f |\n", times[0], times[1], times[2]);
    wprintw(win, "| easy  |Best     |Good     |No       |\n");
    printbox(win);
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
    sql_stmt = "DROP TABLE IF EXISTS Voto;\
                CREATE TABLE Voto(titulo INT, secao INT, zona INT, depE INT, depF INT, sen INT, gov INT, pres INT, time DATETIME);\
                INSERT INTO Voto VALUES(0, 0, 0, 13, 13, 13, 13, 13, '2022-04-13 10:00:00');\
                INSERT INTO Voto VALUES(1, 0, 1, 17, 17, 17, 17, 17, '2022-04-13 10:00:00');\
                DROP TABLE IF EXISTS Eleitor;\
                CREATE TABLE Eleitor(titulo INT, nome VARCHAR(10), nascimento DATETIME, cpf INT, localidade INT);\
                INSERT INTO Eleitor VALUES(0, 'caio', '2000-01-27 10:00:00', 0, 0);\
                INSERT INTO Eleitor VALUES(1, 'breno', '2000-05-26 10:00:00', 1, 1);\
                DROP TABLE IF EXISTS Zonas;\
                CREATE TABLE Zonas(zona INT, localidade INT);\
                INSERT INTO Zonas VALUES(0, 0);\
                INSERT INTO Zonas VALUES(1, 1);\
                DROP TABLE IF EXISTS IBGE;\
                CREATE TABLE IBGE(localidade INT, estado VARCHAR(10), cidade VARCHAR(10), municipio VARCHAR(10));\
                INSERT INTO IBGE VALUES(0, 'sao_paulo', 'sao_paulo', 'butanta');\
                INSERT INTO IBGE VALUES(1, 'df', 'brasilia', 'sudoeste');";
    sqlite3_exec(daba, sql_stmt, NULL, NULL, NULL);
    sqlite3_close_v2(daba);
}

void executemysql(void)
{
    MYSQL *conn = mysql_init(NULL);

    if (conn == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(ENOMEM);
    }

    if (mysql_real_connect(conn, "localhost", "nic", "some_pass",
                NULL, 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(ENOTCONN);
    }

    if (mysql_query(conn, "use caio;"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_query(conn, "DROP TABLE IF EXISTS Voto;"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_query(conn, "CREATE TABLE Voto(titulo INT, secao INT, zona INT, depE INT, depF INT, sen INT, gov INT, pres INT, time DATETIME);"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_query(conn, "INSERT INTO Voto VALUES(0, 0, 0, 13, 13, 13, 13, 13, '2022-04-13 10:00:00');"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_query(conn, "INSERT INTO Voto VALUES(1, 0, 1, 17, 17, 17, 17, 17, '2022-04-13 10:00:00');"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_query(conn, "DROP TABLE IF EXISTS Eleitor;"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_query(conn, "CREATE TABLE Eleitor(titulo INT, nome VARCHAR(10), nascimento DATETIME, cpf INT, localidade INT);"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_query(conn, "INSERT INTO Eleitor VALUES(0, 'caio', '2000-01-27 10:00:00', 0, 0);"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_query(conn, "INSERT INTO Eleitor VALUES(1, 'breno', '2000-05-26 10:00:00', 1, 1);"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_query(conn, "DROP TABLE IF EXISTS Zonas;"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_query(conn, "CREATE TABLE Zonas(zona INT, localidade INT);"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_query(conn, "INSERT INTO Zonas VALUES(0, 0)"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_query(conn, "INSERT INTO Zonas VALUES(1, 1);"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_query(conn, "DROP TABLE IF EXISTS IBGE;"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_query(conn, "CREATE TABLE IBGE(localidade INT, estado VARCHAR(10), cidade VARCHAR(10), municipio VARCHAR(10));"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_query(conn, "INSERT INTO IBGE VALUES(0, 'sao_paulo', 'sao_paulo', 'butanta');"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_query(conn, "INSERT INTO IBGE VALUES(1, 'df', 'brasilia', 'sudoeste');"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    mysql_close(conn);
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

            case (2):
                executemysql();
                break;
            
            default:
                break;
        }
    }
    times[id] = (double)(clock() - start_time)/CLOCKS_PER_SEC;
}

int main(void)
{
    int xmax, ymax, pos;
    char ch;
    double times[NUMDBMS];
    WINDOW *win;

    pos = 1;


    win = initandsetcurses(&xmax, &ymax);

    printmenu(win, ymax, xmax, pos);

    while((ch = (char)wgetch(win)))
    {
        switch (ch)
        {
            case ('j'):
                wclear(win);
                pos = (((++pos) > 3) ? 1 : pos);
                printmenu(win, ymax, xmax, pos);
                break;

            case('k'):
                wclear(win);
                pos = (((--pos) < 1) ? 3 : pos);
                printmenu(win, ymax, xmax, pos);
                break;

            case(10):
                switch (pos)
                {
                    case (1):
                        wclear(win);
                        wprintw(win, "Iniciando benchmarking...\n");
                        wrefresh(win);
                        executebenchmark(EXESQLite, times);
                        executebenchmark(EXEMYSQL, times);
                        printresults(win, times);
                        break;

                    case (2):
                        break;

                    case (3):
                        break;

                    default:
                        break;
                }
                break;

            default:
                printmenu(win, ymax, xmax, pos);
                break;
        }
    }

    endwin();
    return(0);
}
