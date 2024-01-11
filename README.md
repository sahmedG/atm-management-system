# ATM MANAGEMENT SYSTEM

Welcome to the ATM Management System repository! This C++ program provides a simulation of an ATM system, allowing users to perform various banking operations. Whether you are interested in learning C++ programming or exploring how an ATM system works at a code level, this project is a great resource.

## Features

- User authentication with PIN
- Balance inquiry
- Cash withdrawal
- Deposit funds
- Transfer funds between accounts
- View transaction history
  
Features

    The Registration feature, you must be able to register new users, users with the same name can not exist (names must be unique). They must be saved in the right file.

    The Update information of existing account feature, users must be able to update their country or phone number.

    2.1. You must ask users to input the account id they want to change, followed by a prompt asking which field they want to also change (the only fields that are permitted to update is the phone number and the country).

    2.2. Whenever users update an account, it must be saved into the corresponding file.

    The Checking the details of existing accounts feature, users must be able to check just one account at a time.

    3.1. For this they must be asked to input the account id they want to see

    3.2. If the account is either savings, fixed01, fixed02 and fixed03 the system will display the information of that account and the interest you will acquire depending on the account:
        savings: interest rate 7%
        fixed01(1 year account): interest rate 4%
        fixed02(2 year account): interest rate 5%
        fixed03(3 year account): interest rate 8%
        If the account is current you must display You will not get interests because the account is of type current

    For example: for an account of type savings with a deposit date of 10/10/2002 and an amount of $1023.20 the system will show "You will get $5.97 as interest on day 10 of every month".

    The Make transaction feature, users must be able to create transactions, withdrawing or depositing money to a certain account. All transactions must be updated and saved into the corresponding file. Accounts of type fixed01, fixed02 and fixed03 are not allowed to make transactions and an error message should be displayed if transactions are attempted with these accounts.

    The Remove existing account feature, users must be able to delete their own account, the same must happen here, updates must be saved into the corresponding file.

    The Transfer owner feature, users can transfer their account to another user, by:

    6.1. Identifying the account and the user they want to transfer the ownership to

    6.2. Saving the information in the corresponding file

    Encryption of passwords
    Adding your own Makefile
