#include "login.h"

void transferOwnership(PGconn *conn, int user_id) {
  char query[MAX_LENGTH + 200];
  char update_owner[MAX_LENGTH + 200];
  int accountNumber;
  char newOwner[50];
  PGresult *res;

  printw("Enter account number: ");
  scanw("%d", &accountNumber);

  printw("Enter new owner username: ");
  getstr(newOwner);

  sprintf(query, "SELECT user_id FROM accounts WHERE account_number = %d",
          accountNumber);

  res = PQexec(conn, query);
  if (PQresultStatus(res) != PGRES_TUPLES_OK) {
    printw("Query error: %s\n", PQerrorMessage(conn));
    PQclear(res);
    refresh();
    printw("Press enter to go back.");
    return;
  }
  int num_rows = PQntuples(res);
  if (num_rows != 0) {
    int owner_id = atoi(PQgetvalue(res, 0, 0));
    PQclear(res);

    if (owner_id != user_id) {
      printw("Error: This account does not belong to you.\n");
      printw("Press enter to go back.");
      refresh();
      return;
    } else {
      sprintf(query, "SELECT user_id FROM users WHERE username = '%s'",
              newOwner);
      res = PQexec(conn, query);
      if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        printw("Authentication query error: %s\n", PQerrorMessage(conn));
        PQclear(res);
        printw("Press enter to go back.");
        return;
      }
      num_rows = PQntuples(res);
      if (num_rows != 0) {
        int new_user_id = atoi(PQgetvalue(res, 0, 0));
        PQclear(res);
          sprintf(update_owner,
                  "UPDATE accounts SET user_id = %d WHERE account_number = %d",
                  new_user_id, accountNumber);
          res = PQexec(conn, update_owner);
          if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            printw("Error transferring ownership: %s\n", PQerrorMessage(conn));
            PQclear(res);
            return;
          } else {
            printw("Ownership transferred successfully!\n");
            sprintf(query, "SELECT logged_in FROM users WHERE username = '%s'",
                    newOwner);

            res = PQexec(conn, query);
            if (PQresultStatus(res) != PGRES_TUPLES_OK) {
              printw("Error querying user info: %s\n", PQerrorMessage(conn));
              PQclear(res);
              return;
            }

            int user_logged_in = atoi(PQgetvalue(res, 0, 0));
            PQclear(res);

            if (user_logged_in == 1) {
              SendNotification(newOwner, "Account transferred to you!");
            }
            printw("Press enter to go back.");
          }

      } else {
        printw("This user doesn't exist.\n");
        printw("Press enter to go back.");
        return;
      }
    }
  } else {
    printw("Account not found.\n");
    printw("Press enter to go back.");
  }
}
