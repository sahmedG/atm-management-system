#include "login.h"

int deleteAccount(PGconn *conn, int user_id) {
  int accountNumber;
  printw("Enter account number to delete: ");
  scanw("%d", &accountNumber);

  char query[MAX_LENGTH];
  sprintf(
      query,
      "SELECT balance FROM accounts WHERE user_id = %d AND account_number = %d",
      user_id, accountNumber);

  PGresult *res;
  res = PQexec(conn, query);
  if (PQresultStatus(res) != PGRES_TUPLES_OK) {
    PQclear(res);
    return 3;
  }
  int num_rows = PQntuples(res);
  if (num_rows == 0) {
    PQclear(res);
    return 3; // Account not found
  }

  double balance = atof(PQgetvalue(res, 0, 0));
  PQclear(res);

  if (balance > 0) {
    return 2;
  } else {
    char delete_transactions_query[MAX_LENGTH];
    sprintf(delete_transactions_query,
            "DELETE FROM transactions WHERE to_account_number = %d",
            accountNumber);
    res = PQexec(conn, delete_transactions_query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
      PQclear(res);
      return 3;
    }
    PQclear(res);

    char delete_account_query[MAX_LENGTH];
    sprintf(delete_account_query,
            "DELETE FROM accounts WHERE user_id = %d AND account_number = %d",
            user_id, accountNumber);
    res = PQexec(conn, delete_account_query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
      PQclear(res);
      return 3;
    }
    PQclear(res);
    return 0;
  }
}
