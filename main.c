#include "login.h"

bool terminateThread = false;

int main() {

  initscr();
  cbreak();
  keypad(stdscr, TRUE);

  PGconn *conn = PQconnectdb("host=localhost port=5432 dbname=atm_system "
                             "user=postgres password=password");

  if (PQstatus(conn) == CONNECTION_BAD) {

    fprintf(stderr, "Connection to database failed: %s\n",
            PQerrorMessage(conn));
    PQfinish(conn);
  }
  initMenu(conn);
  endwin(); 
  PQfinish(conn);

  return 0;
}
