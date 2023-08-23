#include "login.h"
#include <postgresql/libpq-fe.h>

void withdrawMoney(PGconn *conn, int user_id) {
  char query[MAX_LENGTH];
  int accountNumber;
  float amount;
  PGresult *res;

  clear();
  printw("Withdraw Money\n");
  printw("Enter account number: ");
  scanw("%d", &accountNumber);

  printw("Enter amount to withdraw: $");
  scanw("%f", &amount);

  sprintf(query,
          "SELECT balance, account_type FROM accounts WHERE account_number = "
          "%d AND user_id = %d",
          accountNumber, user_id);

  res = PQexec(conn, query);
  if (PQresultStatus(res) != PGRES_TUPLES_OK) {
    printw("Query error: %s\n", PQerrorMessage(conn));
    PQclear(res);
    refresh();
    getch();
    return;
  }

  int row_count = PQntuples(res);
  if (row_count == 0) {
    printw("Account not found or doesn't belong to you!\n");
    printw("Press enter to return.");
  } else {

    float balance = atof(PQgetvalue(res, 0, 0));
    const char *accountType = PQgetvalue(res, 0, 1);
    PQclear(res);

    if (strcmp(accountType, "savings") == 0 ||
        strcmp(accountType, "current") == 0) {
      if (amount <= balance) {
        sprintf(query,
                "UPDATE accounts SET balance = balance - %.2f WHERE "
                "account_number = %d AND user_id = %d",
                amount, accountNumber, user_id);

        res = PQexec(conn, query);
        if (PQresultStatus(res) == PGRES_COMMAND_OK) {
          PQclear(res);

          sprintf(query,
                  "INSERT INTO transactions (user_id, from_account_number, "
                  "to_account_number, transaction_type, amount) VALUES (%d, "
                  "%d, %d, 'WITHDRAW', %lf)",
                  user_id, accountNumber, accountNumber, amount);

          res = PQexec(conn, query);
          if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            printw("Error inserting transaction: %s\n", PQerrorMessage(conn));
            PQclear(res);
            refresh();
            getch();
            return;
          }
          PQclear(res);

          printw("Money withdrawn successfully!\n");
        } else {
          printw("Error withdrawing money: %s\n", PQerrorMessage(conn));
        }
      } else {
        printw("Insufficient balance.\n");
      }
    } else {
      printw("Cannot withdraw from this type of account.\n");
    }
  }
  refresh();
}
