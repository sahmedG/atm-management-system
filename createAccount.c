#include "login.h"

void createAccount(PGconn *conn, int user_id)
{
    float initialBalance = 0.0;
    float interestRate = 0.0;
    char query[MAX_LENGTH + 200];
    char country[50];
    char phoneNumber[50];
    char accountType[50];

    printw("Enter country: ");
    getstr(country);
    printw("Enter phone number: ");
    getstr(phoneNumber);

    printw("Enter account type (savings/fixed01/fixed02/fixed03/current): ");
    getstr(accountType);
    if (strcmp(accountType, "savings") == 0)
    {
        interestRate = 0.07;
    }
    else if (strcmp(accountType, "fixed01") == 0)
    {
        interestRate = 0.04;
    }
    else if (strcmp(accountType, "fixed02") == 0)
    {
        interestRate = 0.05;
    }
    else if (strcmp(accountType, "fixed03") == 0)
    {
        interestRate = 0.08;
    }
    else if (strcmp(accountType, "current") == 0)
    {
        interestRate = 0.0;
        printw("You will not get interests because the account is of type current.\n");
    }
    else
    {
        printw("Invalid account type.\n");
        return;
    }

    sprintf(query, "INSERT INTO accounts (user_id, country, phone_number, balance, interest_rate, account_type) "
                   "VALUES ( %d, '%s', '%s', %.2f, %.4f, '%s')",
            user_id, country, phoneNumber, initialBalance, interestRate, accountType);

    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        printw("Error creating account: %s\n", PQerrorMessage(conn));
    }
    else
    {
        printw("Account created successfully!\n");
    }
    printw("Press enter to go back\n");
    PQclear(res);
    getch();
}
