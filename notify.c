#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include "libpq-fe.h"

int main(int argc, char **argv) {
        const char *conninfo;
        PGconn     *conn;
        PGresult   *res;
        PGnotify   *notify;
        char db_name[] = "shkekina_yuliya";

        conn = PQsetdbLogin(NULL,NULL,NULL,NULL,db_name,NULL,NULL);
        if (PQstatus(conn) != CONNECTION_OK) {
                fprintf(stderr, "Ahtung! Connection failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
        }

        res = PQexec(conn, "NOTIFY Shkekina");
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
                fprintf(stderr, "Oh no! NOTIFY failed: %s", PQerrorMessage(conn));
                PQclear(res);
                PQfinish(conn);
                exit(1);
        }
        PQclear(res);
        PQfinish(conn);
        return 0;
}
