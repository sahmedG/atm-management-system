#include "login.h"

bool updateAccountInfo(PGconn *conn, int user_id)
{
    char query[MAX_LENGTH + 200];
    int accountNumber;
    char newCountry[50];
    char newPhoneNumber[50];

    printw("Enter account number: ");
    scanw("%d", &accountNumber);

    printw("Enter new country: ");
    getstr(newCountry);

    printw("Enter new phone number: ");
    getstr(newPhoneNumber);

    sprintf(query, "UPDATE accounts SET country = '%s', phone_number = '%s' WHERE account_number = %d AND user_id = %d",
            newCountry, newPhoneNumber, accountNumber, user_id);

    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK || atoi(PQcmdTuples(res)) == 0)
    {
        PQclear(res);
        return false;
    }
    else
    {
        PQclear(res);
        return true;
    }
}
