// #include <openssl/evp.h>
// #include <openssl/sha.h>
#include <pthread.h>
#include <sqlite3.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include </usr/include/postgresql/libpq-fe.h>

#include <crypt.h>
#include <fcntl.h>
#include <ncurses.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_LENGTH 200
#define PIPE_NAME_TEMPLATE "/tmp/ATMNotification_%s"
#define MAX_MESSAGES 10
#define MAX_MESSAGE_LENGTH 256
#define MAX_LOGGED_IN_USERS

extern bool terminateThread;

extern int loggedInUserCount;
void authenticateUser(PGconn *conn);
void depositMoney(PGconn *conn, int user_id);
bool checkAllAccounts(PGconn *conn, int user_id);
bool updateAccountInfo(PGconn *conn, int accountId);
void withdrawMoney(PGconn *conn, int user_id);
void createAccount(PGconn *conn, int user_id);
void transferMoney(PGconn *conn, int user_id);
void registerUser(PGconn *conn);
void transferOwnership(PGconn *conn, int user_id);
void success(PGconn *conn, int user_id);
void initMenu(PGconn *conn);
void mainMenu(PGconn *conn,int user_id, char *username);
void checkOneAccount(PGconn *conn, int user_id);
void Success(PGconn *conn, int user_id);
void makeTransactionsMenu(PGconn *conn, int user_id, char *username);
void Gotoxy(int x, int y);
int deleteAccount(PGconn *conn, int user_id);
void SendNotification(const char *targetUsername, const char *message);
void ReceiveNotifications(const char *username);
void *notificationThread(void *args);
void logoutUser(int user_id, PGconn *conn);
int main();
