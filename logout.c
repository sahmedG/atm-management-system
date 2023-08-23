#include "login.h"

void logoutUser(int user_id, PGconn *conn) {
  char query[100];
  sprintf(query, "UPDATE users SET logged_in = 0 WHERE user_id = %d", user_id);
  PGresult *res;
  res = PQexec(conn, query);
  if (PQresultStatus(res) != PGRES_COMMAND_OK) {
    printw("Error updating login status in the database.\n");
  }
  PQclear(res);
}
