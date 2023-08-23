CFLAGS = -Wall -Wextra -pedantic -std=c99 -D_WIN32_WINNT=0x0601
LDFLAGS = -lsqlite3 -lcrypto -lncurses -lcrypt -I/usr/include/postgresql/libpq-fe.h -lpq
SRC = main.c initial_menu.c program_menu.c register.c login.c createAccount.c updateAccount.c checkAllAccounts.c depositMoney.c withdrawMoney.c transferMoney.c transferOwnership.c checkOneaccount.c transactoins.c deletAccount.c ReceiveNotification.c sendNotification.c threadHandle.c logout.c
OBJ = $(SRC:.c=.o)

atm: $(OBJ)#include <stdbool.h>
	cc -o atm.exe $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) atm.exe
