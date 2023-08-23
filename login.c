#include "login.h"

void authenticateUser(PGconn *conn) {
  char username[50];
  char password[50];
  char query[MAX_LENGTH + 200];

  clear();
  printw("Login\n");
  printw("Username: ");
  getstr(username);
  printw("Password: ");
  refresh();

  // Hide the password input
  noecho();
  getstr(password);
  echo();

  int user_id;
  sprintf(query,
          "SELECT user_id, password, logged_in FROM users WHERE username = '%s'",
          username);

  PGresult *res = PQexec(conn, query);
  if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res) > 0) {
    user_id = atoi(PQgetvalue(res, 0, 0));
    const char *storedHashedPassword = PQgetvalue(res, 0, 1);
    int logged_in = atoi(PQgetvalue(res, 0, 2));
    char *hashedInputPassword = crypt(password, storedHashedPassword);
    if (strcmp(hashedInputPassword, storedHashedPassword) == 0) {
      if (logged_in == 0) {
        sprintf(query, "UPDATE users SET logged_in = 1 WHERE user_id = %d", user_id);
        PGresult *updateRes = PQexec(conn, query);
        if (PQresultStatus(updateRes) != PGRES_COMMAND_OK) {
          printw("Error updating login status in the database.\n");
        }
        PQclear(updateRes);
        printw("\nLogin Successful.\n");
        getch();
        mainMenu(conn,user_id, username);
      } else {
        printw("User is already logged in.\n");
      }
    } else {
      printw("\nWrong username or password.\n");
      printw("Press enter to try again\n");
      getch();
      initMenu(conn);
    }
  } else {
    printw("\nWrong username or password.\n");
    printw("Press enter to try again\n");
    getch();
    initMenu(conn);
  }

  PQclear(res);
}
