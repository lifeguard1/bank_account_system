# Bank Account Management System

## Overview
This C program is a simple console-based bank account management system. It allows users to create a bank account, login, check balance, deposit funds, and transfer money to another account. 

## Features
- **Create Account**: Register a new bank account with personal and login details.
- **Login**: Access an existing account using a username and password.
- **Check Balance**: View the current balance in the account.
- **Deposit**: Add funds to the account.
- **Transfer**: Send funds to another user's account.

## Prerequisites
- GCC Compiler (or any C compiler like Clang, MSVC)
- Windows Operating System (due to specific system calls like `system("cls")` and Windows API usage)

## Compilation
Compile the program using the following GCC command:
gcc -o BankSystem bank_acc_sys.c

After compilation, you can run the program using
./BankSystem
