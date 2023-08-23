#include "login.h"

void registerUser(PGconn *conn) {
  char query[MAX_LENGTH + 200];
  char username[50];
  char password[MAX_LENGTH];

  clear();
  printw("New user register\n");
  printw("Enter new username: ");
  getstr(username);
  printw("Password: ");
  refresh();

  noecho();
  getstr(password);
  echo();

  // Generate the hashed password using crypt() function
  char *crypt_hash = crypt(password, crypt_gensalt("$2a$", 12, NULL, 0));
  if (crypt_hash == NULL) {
    printw("Error generating crypt hash.\n");
    exit(1);
  }

  sprintf(query, "INSERT INTO users (username, password, logged_in) VALUES ('%s', $1, 0)",
          username);

  // Prepare the statement and bind parameters
  PGresult *res;
  const char *paramValues[1] = { crypt_hash };
  res = PQexecParams(conn, query, 1, NULL, paramValues, NULL, NULL, 0);

  if (PQresultStatus(res) == PGRES_COMMAND_OK) {
    printw("\nUser registered successfully!\n");
    printw("Press Enter to go back to the main menu...");
    getch();
    endwin();
    initMenu(conn);
  } else {
    printw("Error registering user. A similar username may already exist.\n");
    exit(0);
  }

  PQclear(res);
}
