# Bank Management System 

---

# 1. Introduction

The **Bank Management System** is a console-based application developed using **C++** programming language.
The project is designed to simulate basic banking operations such as:

* Creating bank accounts
* Depositing money
* Withdrawing money
* Checking account balance
* Closing bank accounts
* Viewing all account details

The system uses **Object-Oriented Programming (OOP)** concepts and **file handling** to store customer account information permanently.

The project demonstrates how real-world banking operations can be implemented using C++ classes, vectors, file management, and data validation.

---

# 2. Objectives of the Project

The main objectives of this project are:

* To understand Object-Oriented Programming concepts
* To implement real-world banking operations
* To learn file handling in C++
* To perform CRUD-like operations on bank records
* To build a secure and user-friendly console application

---

# 3. Technologies Used

| Technology    | Purpose                      |
| ------------- | ---------------------------- |
| C++           | Main programming language    |
| File Handling | Permanent data storage       |
| STL Vector    | Dynamic account storage      |
| Unordered Map | Fast account searching       |
| OOP Concepts  | Encapsulation and modularity |

---

# 4. Features of the System

## 4.1 Create New Bank Account

The system allows users to:

* Create Savings or Current account
* Provide initial deposit
* Generate unique account records

### Validations

* Duplicate account numbers are prevented
* Negative deposit amounts are rejected

---

## 4.2 Deposit Funds

Users can:

* Deposit money into existing accounts
* Automatically update balance

### Validation

* Deposit amount must be positive

---

## 4.3 Withdraw Funds

Users can:

* Withdraw money from their account

### Validation

* Withdrawal amount cannot exceed balance
* Negative withdrawals are rejected

---

## 4.4 Balance Inquiry

Displays:

* Account Number
* Holder Name
* Account Type
* Current Balance

---

## 4.5 Close Bank Account

Allows:

* Permanent deletion of accounts
* Confirmation before deletion

---

## 4.6 Display All Accounts

Shows all active bank accounts in tabular format.

---

# 5. System Architecture

```text
+---------------------------+
|       User Interface      |
+---------------------------+
              |
              v
+---------------------------+
|        BankEngine         |
+---------------------------+
 |      |       |        |
 v      v       v        v
Create Deposit Withdraw Balance
              |
              v
+---------------------------+
|     bank_database.dat     |
+---------------------------+
```

---

# 6. Classes Used in the Project

---

# 6.1 BankAccount Class

The `BankAccount` class represents an individual customer account.

## Data Members

```cpp
int accountNumber;
string accountHolderName;
string accountType;
double balance;
```

---

## Member Functions

| Function                | Purpose                  |
| ----------------------- | ------------------------ |
| getAccountNumber()      | Returns account number   |
| getHolderName()         | Returns holder name      |
| getAccountType()        | Returns account type     |
| getBalance()            | Returns current balance  |
| deposit()               | Adds money               |
| withdraw()              | Withdraws money          |
| displayAccountSummary() | Displays account details |

---

# 6.2 BankEngine Class

Handles all banking operations and manages data storage.

---

## Important Data Structures

### Vector

```cpp
vector<BankAccount> accountsCache;
```

Stores all account objects dynamically.

---

### Unordered Map

```cpp
unordered_map<int, size_t> accountIndexMap;
```

Provides fast account searching using account number.

---

# 7. File Handling

The system stores data inside:

```text
bank_database.dat
```

---

## Example Stored Data

```text
1001|Rahul Sharma|Savings|5000
1002|Priya K|Current|12000
```

---

## File Operations Used

### Reading Data

```cpp
ifstream dbFile(dbFilename);
```

### Writing Data

```cpp
ofstream dbFile(dbFilename, ios::trunc);
```

---

# 8. Input Validation Techniques

The system prevents invalid operations such as:

| Validation               | Description                   |
| ------------------------ | ----------------------------- |
| Duplicate Account Number | Prevents repeated account IDs |
| Negative Deposits        | Not allowed                   |
| Invalid Withdrawals      | Cannot exceed balance         |
| Wrong Menu Inputs        | Handled safely                |
| Invalid Numeric Inputs   | Buffer cleared properly       |

---

# 9. Program Workflow

## Step 1

Program starts and loads saved account data.

---

## Step 2

Main menu is displayed.

---

## Step 3

User selects banking operation.

---

## Step 4

Operation is performed.

---

## Step 5

Data is updated in memory.

---

## Step 6

On exit, all data is saved into disk file.

---

# 10. Complete Detailed Input and Output

---

# 10.1 Main Menu

## Output

```text
====================================
      APEX BANK MANAGEMENT CORE
====================================
 1. Create New Bank Account
 2. Deposit Funds
 3. Withdraw Funds
 4. Balance Inquiry Statement
 5. Close/Terminate Account
 6. Master Accounts Ledger View
 7. Exit Financial Core Application
------------------------------------
Select Operation Option (1-7):
```

---

# 10.2 Create New Account

## Input

```text
1
1001
Rahul Sharma
1
5000
```

## Output

```text
--- Open New Bank Account ---
Enter Desired Account Number (Integer): 1001
Enter Account Holder's Full Name: Rahul Sharma
Select Account Type (1. Savings | 2. Current): 1
Enter Initial Opening Deposit: $5000

🎉 Account successfully created for Rahul Sharma!
```

---

# 10.3 Deposit Funds

## Input

```text
2
1001
2000
```

## Output

```text
--- Deposit Money ---
Enter Account Number: 1001
Enter Deposit Amount: $2000

✅ Successfully deposited $2000.00
New Balance: $7000.00
```

---

# 10.4 Withdraw Funds

## Input

```text
3
1001
1500
```

## Output

```text
--- Withdraw Money ---
Enter Account Number: 1001
Available Balance: $7000.00
Enter Withdrawal Amount: $1500

✅ Successfully withdrew $1500.00
Remaining Balance: $5500.00
```

---

# 10.5 Insufficient Balance Withdrawal

## Input

```text
3
1001
10000
```

## Output

```text
--- Withdraw Money ---
Enter Account Number: 1001
Available Balance: $5500.00
Enter Withdrawal Amount: $10000

❌ Transaction Aborted: Insufficient funds or invalid amount request.
```

---

# 10.6 Balance Inquiry

## Input

```text
4
1001
```

## Output

```text
====================================
         ACCOUNT STATEMENT
====================================
 Account Number : 1001
 Holder Name    : Rahul Sharma
 Account Type   : Savings
 Current Balance: $5500.00
====================================
```

---

# 10.7 Display All Accounts

## Input

```text
6
```

## Output

```text
-----------------------------------------------------------------------
Account No    Holder Name                  Type        Balance
-----------------------------------------------------------------------
1001          Rahul Sharma                 Savings     $5500.00
1002          Priya K                      Current     $12000.00
-----------------------------------------------------------------------
```

---

# 10.8 Close Account

## Input

```text
5
1001
y
```

## Output

```text
--- Close Bank Account ---
Enter Account Number to terminate: 1001

Warning: Terminating account belonging to 'Rahul Sharma'
Are you sure? (y/n): y

🗑️ Account successfully permanently deleted from active systems.
```

---

# 10.9 Exit Application

## Input

```text
7
```

## Output

```text
Shutting down financial core securely. Active data caches flushed down to disk.
```

---

# 11. Advantages of the Project

* Fast account searching using unordered_map
* Permanent storage using files
* User-friendly menu interface
* Secure validation mechanisms
* Efficient memory handling using vectors
* Beginner-friendly implementation

---

# 12. Limitations of the System

* No graphical user interface
* No password protection
* Single-user environment
* Uses text-based storage instead of database
* No online banking support

---

# 13. Future Enhancements

## 13.1 Database Integration

Replace file handling with:

* MySQL
* MongoDB
* PostgreSQL

---

## 13.2 User Authentication

Add:

* Login system
* Password protection
* PIN verification

---

## 13.3 Online Banking Features

Implement:

* Fund transfer
* UPI payments
* Mobile banking

---

## 13.4 Transaction History

Store:

* Deposit logs
* Withdrawal history
* Date and time tracking

---

## 13.5 GUI Interface

Develop graphical banking software using:

* Qt Framework
* C++ GUI libraries

---

## 13.6 Interest Calculation

Automatically calculate:

* Savings interest
* Fixed deposit maturity

---

## 13.7 ATM Simulation

Add:

* PIN authentication
* Cash withdrawal interface
* Mini statement

---

# 14. GitHub Commands

---

## Clone Repository

```bash
git clone <repository-url>
```

### Example

```bash
git clone https://github.com/username/bank-management-system.git
```

---

## Navigate into Project Folder

```bash
cd Bank-Management-Application

```

---

## Compile Program

### Using g++

```bash
g++ main.cpp -o bank
```

---

## Run Program

### Windows

```bash
bank.exe
```

### Linux / Mac

```bash
./bank
```

---

# 15. Git Commands for Uploading Project

---

## Initialize Git

```bash
git init
```

---

## Add Files

```bash
git add .
```

---

## Commit Changes

```bash
git commit -m "Initial commit"
```

---

## Connect GitHub Repository

```bash
git remote add origin https://github.com/username/bank-management-system.git
```

---

## Push Project

```bash
git branch -M main
git push -u origin main
```

---

# 16. Folder Structure

```text
Bank-Management-System/
│
├── main.cpp
├── bank_database.dat
├── README.md
└── .gitignore
```

---

# 17. README.md Short Description

```md
A console-based Bank Management System built using C++ and File Handling.
The project supports account creation, deposits, withdrawals, balance inquiry, and account management using Object-Oriented Programming concepts.
```

---

# 18. Conclusion

The **Bank Management System** project successfully demonstrates the implementation of banking operations using C++ and file handling techniques.

The project combines:

* Object-Oriented Programming
* Data validation
* File persistence
* Efficient searching algorithms

This system provides a strong foundation for developing advanced banking software and helps beginners understand how real-world financial systems can be simulated using C++.
