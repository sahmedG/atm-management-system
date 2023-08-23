#include "login.h"

void mainMenu(PGconn *conn, int user_id, char *username) {

  pthread_t thread;
  if (pthread_create(&thread, NULL, notificationThread, (void *)username) !=
      0) {
    perror("Thread creation error");
    exit(1);
  }

  int choice;
  while (1) {
    clear();
    printw("======= ATM Management System =======\n");
    printw("\n\tWelcome to the Main Menu %s!\n", username);
    printw("1. Create a new account\n");
    printw("2. Update account information\n");
    printw("3. Check account details\n");
    printw("4. Make Transaction\n");
    printw("5. Check list of owned account\n");
    printw("6. Transfer Ownership\n");
    printw("7. Delete account\n");
    printw("8. Exit\n");
    refresh();

    choice = getch();

    switch (choice) {
    case '1':
      clear();
      createAccount(conn, user_id);
      refresh();
      getch();
      break;

    case '2':
      clear();
      if (updateAccountInfo(conn, user_id)) {
        printw("Account info updated successfully!\n");
      } else {
        printw("No records were updated. Please check the account number and "
               "ownership.\n");
      };
      refresh();
      printw("Press enter to go back\n");
      getch();
      break;

    case '3':
      clear();
      checkOneAccount(conn, user_id);
      refresh();
      getch();
      break;

    case '4':
      clear();
      makeTransactionsMenu(conn, user_id, username);
      refresh();
      getch();
      break;

    case '5':
      clear();
      if (checkAllAccounts(conn, user_id)) {
        printw("Press enter to go back\n");
      } else {
        printw("Authentication query error: %s\n", PQerrorMessage(conn));
      };
      refresh();
      getch();
      break;

    case '6':
      clear();
      transferOwnership(conn, user_id);
      refresh();
      getch();
      break;

    case '7':
      clear();
      int err_code;
      err_code = deleteAccount(conn, user_id);
      switch (err_code) {
      case 0:
        printw("Account was deleted!\n");
        break;
      case 3:
        printw("Account not found!\n");
        break;
      case 2:
        printw("Account balance is greater than zero. Please transfer the "
               "amount to another account before deleting.\n");
        break;
      default:
        printw("Error excuting the sql!\n");
        break;
      };
      refresh();
      printw("Press enter to go back\n");
      getch();
      break;

    case '8':
      logoutUser(user_id, conn);
      PQfinish(conn);
      endwin();
      exit(0);
    default:
      printw("Invalid choice. Choose between '1' and '8'.\n");
      refresh();
      getch();
      break;
    }
    refresh();
  }
  terminateThread = true;
  pthread_join(thread, NULL);
  endwin();
  PQfinish(conn);
  exit(0);
}
