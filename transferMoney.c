#include "login.h"
#include <curses.h>
#include <postgresql/libpq-fe.h>

void transferMoney(PGconn *conn, int user_id) {
  clear();
  int fromAccountNumber, toAccountNumber;
  float amount;

  printw("Transfer Money\n");
  printw("Enter source account number: ");
  scanw("%d", &fromAccountNumber);

  printw("Enter destination account number: ");
  scanw("%d", &toAccountNumber);

  printw("Enter the amount you wish to transfer: $");
  scanw("%f", &amount);

  char query[MAX_LENGTH];
  PGresult *res;

  sprintf(query,
          "SELECT balance, account_type FROM accounts WHERE account_number = "
          "%d AND user_id = %d",
          fromAccountNumber, user_id);

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
    printw("Source account not found or doesn't belong to you!\n");
    printw("Press enter to return");
  } else {
    float balance = atof(PQgetvalue(res, 0, 0));
    const char *accountType = PQgetvalue(res, 0, 1);
    PQclear(res);

    if (strcmp(accountType, "savings") == 0 ||
        strcmp(accountType, "current") == 0) {
      if (amount <= balance) {
        // Check if destination account exists
        sprintf(query,
                "SELECT COUNT(*) FROM accounts WHERE account_number = %d",
                toAccountNumber);

        res = PQexec(conn, query);
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
          printw("Query error: %s\n", PQerrorMessage(conn));
          PQclear(res);
          refresh();
          getch();
          return;
        }

        if (atoi(PQgetvalue(res, 0, 0)) > 0) {
          PQclear(res);

          // Update 'from' account balance
          sprintf(query,
                  "UPDATE accounts SET balance = balance - %.2f WHERE "
                  "account_number = %d AND user_id = %d",
                  amount, fromAccountNumber, user_id);
          res = PQexec(conn, query);
          if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            printw("Error updating balance: %s\n", PQerrorMessage(conn));
            PQclear(res);
            refresh();
            getch();
            return;
          }
          PQclear(res);

          // Update 'to' account balance
          sprintf(query,
                  "UPDATE accounts SET balance = balance + %.2f WHERE "
                  "account_number = %d AND user_id = %d",
                  amount, toAccountNumber, user_id);
          res = PQexec(conn, query);
          if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            printw("Error updating balance: %s\n", PQerrorMessage(conn));
            PQclear(res);
            refresh();
            getch();
            return;
          }
          PQclear(res);

          sprintf(query,
                  "INSERT INTO transactions (user_id, from_account_number, "
                  "to_account_number, transaction_type, amount) VALUES (%d, "
                  "%d, %d, 'Transfer', %lf)",
                  user_id, fromAccountNumber, toAccountNumber, amount);
          res = PQexec(conn, query);
          if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            printw("Error inserting transaction: %s\n", PQerrorMessage(conn));
            PQclear(res);
            refresh();
            getch();
            return;
          }
          PQclear(res);

          printw("Money transferred successfully!\n");
        } else {
          printw("Destination account does not exist.\n");
        }
      } else {
        printw("Insufficient balance in the source account.\n");
      }
    } else {
      printw("Cannot transfer from this type of account.\n");
    }
  }
  refresh();
}
