CREATE TABLE users (
    user_id SERIAL PRIMARY KEY,
    username TEXT NOT NULL UNIQUE,
    password VARCHAR NOT NULL,
    logged_in INT NOT NULL,
    creation_date TIMESTAMP default current_timestamp
);

CREATE TABLE accounts (
    account_number SERIAL PRIMARY KEY,
    user_id INTEGER NOT NULL REFERENCES users(user_id),
    country VARCHAR,
    phone_number VARCHAR,
    balance REAL,
    interest_rate REAL,
    account_type TEXT NOT NULL,
    creation_date TIMESTAMP
);

CREATE TABLE transactions (
    transaction_id SERIAL PRIMARY KEY,
    user_id INTEGER NOT NULL REFERENCES users(user_id),
    from_account_number INTEGER NOT NULL REFERENCES accounts(account_number),
    to_account_number INTEGER NOT NULL REFERENCES accounts(account_number),
    transaction_type TEXT NOT NULL,
    amount REAL NOT NULL,
    transaction_date TIMESTAMP
);
