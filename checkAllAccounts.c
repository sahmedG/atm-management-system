#include "login.h"


bool checkAllAccounts(PGconn *conn, int user_id) {
    char query_account[MAX_LENGTH];
    char query_user[MAX_LENGTH];
    PGresult *res_user, *res_account;
    sprintf(query_user, "SELECT username FROM users WHERE user_id = %d", user_id);
    sprintf(query_account, "SELECT * FROM accounts WHERE user_id = %d", user_id);

    res_user = PQexec(conn, query_user);
    if (PQresultStatus(res_user) != PGRES_TUPLES_OK) {
        PQclear(res_user);
        return false;
    }

    const char *username = PQgetvalue(res_user, 0, 0);
    PQclear(res_user);

    res_account = PQexec(conn, query_account);
    if (PQresultStatus(res_account) != PGRES_TUPLES_OK) {
        PQclear(res_account);
        return false;
    } else {
        printw("====== All accounts from user, %s =====\n\n", username);
        int rows = PQntuples(res_account);
        for (int i = 0; i < rows; i++) {
            printw("_____________________\n");
            int accountNumber = atoi(PQgetvalue(res_account, i, 0));
            const char *accountType = PQgetvalue(res_account, i, 6);
            float balance = atof(PQgetvalue(res_account, i, 4));
            const char *country = PQgetvalue(res_account, i, 2);
            const char *phone_no = PQgetvalue(res_account, i, 3);
            const char *created_on = PQgetvalue(res_account, i, 7);
            printw("Account Number: %d\n", accountNumber);
            printw("Account Type: %s\n", accountType);
            printw("Balance: %.2f\n", balance);
            printw("Country: %s\n", country);
            printw("Phone Number: %s\n", phone_no);
            printw("Created On: %s\n", created_on);
        }
        PQclear(res_account); // Don't forget to clear the result
        return true;
    }
}
