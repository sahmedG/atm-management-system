#include "login.h"
void makeTransactionsMenu(PGconn *conn, int user_id, char *username)
{

    int choice;
    int highlight = 0;
    int numOptions = 4;

    while (1)
    {
        clear();
        printw("Make Transactions\n");

        for (int i = 0; i < numOptions; i++)
        {
            if (i == highlight)
                attron(A_REVERSE);
            printw("%d. ", i + 1);
            switch (i)
            {
            case 0:
                printw("Deposit Money\n");
                break;
            case 1:
                printw("Withdraw Money\n");
                break;
            case 2:
                printw("Transfer Money\n");
                break;
            case 3:
                printw("Back to Main Menu\n");
                break;
            }
            attroff(A_REVERSE);
        }

        choice = getch();

        switch (choice)
        {
        case KEY_UP:
            if (highlight > 0)
                highlight--;
            break;

        case KEY_DOWN:
            if (highlight < numOptions - 1)
                highlight++;
            break;

        case '\n':
            clear();
            switch (highlight)
            {
            case 0:
                depositMoney(conn, user_id);
                break;
            case 1:
                withdrawMoney(conn, user_id);
                break;
            case 2:
                transferMoney(conn, user_id);
                break;
            case 3:
                mainMenu(conn,user_id,username);
                break;
            }
            refresh();
            getch();
            break;

        default:
            break;
        }
    }

    endwin();
    exit(1);
}
