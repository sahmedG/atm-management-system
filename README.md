ATM-MANAGEMENT-SYSTEM

This project was developed using C language.

The aim of this project is to build a program running on C and postgresql to mimic some functionalities of atm-management-system.

Features available in the program:
1.Register new user.
2.Login with existing user.
   2.a. Create new account under the logged in user.
   2.b. Update information of a specific account.
   2.c. Check the details of a specific account.
   2.d. Make a transaction:
      2.d.a. Deposit to a specific account.
      2.d.b. Withdraw from a specific account.
      2.d.c. Transfer money from one account to another.
   2.e. Check all acounts owned by the user.
   2.f. Transfer an owned account to another user  > second user will recieve a notification is they were logged in at same time of the transaction.
   2.g. Delete a specific account.
   2.h. Exit the program.

The program is connected to rational database of type postgresql to hanlde all users and accounts details.
The program allows the following account types:
    savings: interest rate 7%
    fixed01(1 year account): interest rate 4%
    fixed02(2 year account): interest rate 5%
    fixed03(3 year account): interest rate 8%
    If the account is current you must display You will not get interests because the account is of type current

Withdrawing money is allowed only to account types of: Savings and Current.

Terminal was modified using ncurses library to enhance the user experience.

Thank you.
