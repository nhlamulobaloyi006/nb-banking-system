# NB Smart Banking System (C++)

A command line banking system written in C++ for the Gauteng City College
Introduction to Programming (NQF 4) assignment.

## Features
- Login with username and 4 digit PIN
- Check balance and account details
- Deposit cash (amount must be more than 0)
- Withdraw cash (cannot withdraw more than the balance)
- Send cash to another account (checks the account exists and the balance is enough)
- Sign out and Exit
- Receipts with date and time
- Input validation with clear error messages

## Test users
| Username | PIN  | Account number |
|----------|------|----------------|
| Nhlamulo | 0625 | 20154545       |
| Ocean    | 0514 | 20456942       |
| Liyema   | 0524 | 20649863       |
| Martin   | 0824 | 20348548       |

## How to run
```
g++ main.cpp -o bank
./bank
```
(On Windows with Code::Blocks, just build and run main.cpp.)

## Concepts used
Functions, if/else and switch, loops (while, do-while, for) and arrays.

