#include "login.h"
void depositMoney(PGconn *conn, int user_id) {
  char query[MAX_LENGTH];
  int accountNumber;
  float amount;
  PGresult *res;

  printw("Enter account number: ");
  scanw("%d", &accountNumber);
  printw("Enter amount to deposit: $");
  scanw("%f", &amount);

  sprintf(query,
          "SELECT count(*) FROM accounts WHERE account_number = %d AND user_id = %d",
          accountNumber, user_id);

  res = PQexec(conn, query);
  if (PQresultStatus(res) != PGRES_TUPLES_OK) {
    printw("Error checking account: %s\n", PQerrorMessage(conn));
    PQclear(res);
    return;
  }

  int count = atoi(PQgetvalue(res, 0, 0));
  PQclear(res);

  if (count == 0) {
    printw("\nAccount does not exist!\n");
    return;
  }

  sprintf(query,
          "UPDATE accounts SET balance = balance + %0.2f WHERE account_number = %d",
          amount, accountNumber);

  res = PQexec(conn, query);
  if (PQresultStatus(res) != PGRES_COMMAND_OK) {
    printw("Error depositing money: %s\n", PQerrorMessage(conn));
    PQclear(res);
    return;
  }
  PQclear(res);

  sprintf(query,
          "INSERT INTO transactions (user_id, from_account_number, to_account_number, transaction_type, amount) VALUES (%d, %d, %d, 'DEPOSIT', %lf)",
          user_id, accountNumber, accountNumber, amount);

  res = PQexec(conn, query);
  if (PQresultStatus(res) != PGRES_COMMAND_OK) {
    printw("Error inserting transaction: %s\n", PQerrorMessage(conn));
    PQclear(res);
    return;
  }
  PQclear(res);

  printw("Deposit successful.\n");
}
