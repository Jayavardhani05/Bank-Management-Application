#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <limits>

using namespace std;


class BankAccount {
private:
    int accountNumber;
    string accountHolderName;
    string accountType; 
    double balance;

public:
   
    BankAccount(int accNum = 0, string name = "", string type = "Savings", double bal = 0.0) {
        accountNumber = accNum;
        accountHolderName = name;
        accountType = type;
        balance = bal;
    }

   
    int getAccountNumber() const { return accountNumber; }
    string getHolderName() const { return accountHolderName; }
    string getAccountType() const { return accountType; }
    double getBalance() const { return balance; }

    bool deposit(double amount) {
        if (amount <= 0) return false;
        balance += amount;
        return true;
    }

    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance) return false;
        balance -= amount;
        return true;
    }

   
    void displayAccountSummary() const {
        cout << "\n====================================" << endl;
        cout << "         ACCOUNT STATEMENT          " << endl;
        cout << "====================================" << endl;
        cout << " Account Number : " << accountNumber << endl;
        cout << " Holder Name    : " << accountHolderName << endl;
        cout << " Account Type   : " << accountType << endl;
        cout << " Current Balance: $" << fixed << setprecision(2) << balance << endl;
        cout << "====================================" << endl;
    }
};


class BankEngine {
private:
    const string dbFilename = "bank_database.dat";
    vector<BankAccount> accountsCache;
    unordered_map<int, size_t> accountIndexMap; 

    void flushInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }


    void rebuildIndex() {
        accountIndexMap.clear();
        for (size_t i = 0; i < accountsCache.size(); ++i) {
            accountIndexMap[accountsCache[i].getAccountNumber()] = i;
        }
    }

public:
    
    BankEngine() {
        loadDataFromDisk();
    }

 
    ~BankEngine() {
        saveDataToDisk();
    }

    void createAccount() {
        int accNum;
        string name, type;
        double initialDeposit;

        cout << "\n--- Open New Bank Account ---\n";
        cout << "Enter Desired Account Number (Integer): ";
        while (!(cin >> accNum)) {
            cout << "Invalid input. Enter a valid account number: ";
            flushInputBuffer();
        }
        flushInputBuffer();

     
        if (accountIndexMap.find(accNum) != accountIndexMap.end()) {
            cout << "❌ Error: Account number " << accNum << " already exists!\n";
            return;
        }

        cout << "Enter Account Holder's Full Name: ";
        getline(cin, name);

        int typeChoice;
        cout << "Select Account Type (1. Savings | 2. Current): ";
        while (!(cin >> typeChoice) || (typeChoice != 1 && typeChoice != 2)) {
            cout << "Invalid choice. Select 1 or 2: ";
            flushInputBuffer();
        }
        type = (typeChoice == 1) ? "Savings" : "Current";

        cout << "Enter Initial Opening Deposit: $";
        while (!(cin >> initialDeposit) || initialDeposit < 0) {
            cout << "Opening deposit cannot be negative. Enter amount: $";
            flushInputBuffer();
        }

        
        BankAccount newAccount(accNum, name, type, initialDeposit);
        accountsCache.push_back(newAccount);
        

        accountIndexMap[accNum] = accountsCache.size() - 1;

        cout << "🎉 Account successfully created for " << name << "!\n";
    }

    void processDeposit() {
        int accNum;
        double amount;

        cout << "\n--- Deposit Money ---\n";
        cout << "Enter Account Number: ";
        cin >> accNum;

        auto it = accountIndexMap.find(accNum);
        if (it == accountIndexMap.end()) {
            cout << "❌ Error: Account record not found.\n";
            return;
        }

        size_t index = it->second;
        cout << "Enter Deposit Amount: $";
        while (!(cin >> amount) || amount <= 0) {
            cout << "Invalid amount. Enter a positive number: $";
            flushInputBuffer();
        }

        if (accountsCache[index].deposit(amount)) {
            cout << "✅ Successfully deposited $" << fixed << setprecision(2) << amount << endl;
            cout << "New Balance: $" << accountsCache[index].getBalance() << endl;
        }
    }


    void processWithdrawal() {
        int accNum;
        double amount;

        cout << "\n--- Withdraw Money ---\n";
        cout << "Enter Account Number: ";
        cin >> accNum;

        auto it = accountIndexMap.find(accNum);
        if (it == accountIndexMap.end()) {
            cout << "❌ Error: Account record not found.\n";
            return;
        }

        size_t index = it->second;
        cout << "Available Balance: $" << fixed << setprecision(2) << accountsCache[index].getBalance() << endl;
        cout << "Enter Withdrawal Amount: $";
        while (!(cin >> amount) || amount <= 0) {
            cout << "Invalid amount. Enter a positive number: $";
            flushInputBuffer();
        }

 
        if (accountsCache[index].withdraw(amount)) {
            cout << "✅ Successfully withdrew $" << fixed << setprecision(2) << amount << endl;
            cout << "Remaining Balance: $" << accountsCache[index].getBalance() << endl;
        } else {
            cout << "❌ Transaction Aborted: Insufficient funds or invalid amount request.\n";
        }
    }

 
    void checkBalance() const {
        int accNum;
        cout << "\n--- Balance Inquiry ---\n";
        cout << "Enter Account Number: ";
        cin >> accNum;

        auto it = accountIndexMap.find(accNum);
        if (it == accountIndexMap.end()) {
            cout << "❌ Error: Account record not found.\n";
            return;
        }

        accountsCache[it->second].displayAccountSummary();
    }

   
    void closeAccount() {
        int accNum;
        cout << "\n--- Close Bank Account ---\n";
        cout << "Enter Account Number to terminate: ";
        cin >> accNum;

        auto it = accountIndexMap.find(accNum);
        if (it == accountIndexMap.end()) {
            cout << "❌ Error: Account record not found.\n";
            return;
        }

        size_t index = it->second;
        cout << "Warning: Terminating account belonging to '" << accountsCache[index].getHolderName() << "'\n";
        cout << "Are you sure? (y/n): ";
        char confirm;
        cin >> confirm;

        if (confirm == 'y' || confirm == 'Y') {
       
            accountsCache.erase(accountsCache.begin() + index);
            
            
            rebuildIndex();
            cout << "🗑️ Account successfully permanently deleted from active systems.\n";
        } else {
            cout << "Account closure canceled.\n";
        }
    }

   
    void displayAllAccounts() const {
        if (accountsCache.empty()) {
            cout << "\nThe bank database contains zero active profiles.\n";
            return;
        }

        cout << "\n-----------------------------------------------------------------------\n";
        cout << left << setw(15) << "Account No" << setw(30) << "Holder Name" << setw(12) << "Type" << setw(15) << "Balance" << endl;
        cout << "-----------------------------------------------------------------------\n";
        for (const auto& acc : accountsCache) {
            cout << left << setw(15) << acc.getAccountNumber()
                 << setw(30) << acc.getHolderName()
                 << setw(12) << acc.getAccountType()
                 << "$" << fixed << setprecision(2) << setw(14) << acc.getBalance() << endl;
        }
        cout << "-----------------------------------------------------------------------\n";
    }

private:

    void loadDataFromDisk() {
        ifstream dbFile(dbFilename);
        if (!dbFile) return; 

        accountsCache.clear();
        string line;

        while (getline(dbFile, line)) {
            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);
            size_t pos3 = line.find('|', pos2 + 1);

            if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
                int accNum = stoi(line.substr(0, pos1));
                string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
                string type = line.substr(pos2 + 1, pos3 - pos2 - 1);
                double balance = stod(line.substr(pos3 + 1));

                accountsCache.push_back(BankAccount(accNum, name, type, balance));
            }
        }
        dbFile.close();
        rebuildIndex();
    }

    void saveDataToDisk() const {
        ofstream dbFile(dbFilename, ios::trunc);
        if (!dbFile) {
            cout << "Fatal System Error: Disk serialization permissions restricted.\n";
            return;
        }

        for (const auto& acc : accountsCache) {
            dbFile << acc.getAccountNumber() << "|"
                   << acc.getHolderName() << "|"
                   << acc.getAccountType() << "|"
                   << acc.getBalance() << "\n";
        }
        dbFile.close();
    }
};


int main() {
    BankEngine bank;
    int inputCommand;

    do {
        cout << "\n====================================" << endl;
        cout << "      APEX BANK MANAGEMENT CORE     " << endl;
        cout << "====================================" << endl;
        cout << " 1. Create New Bank Account" << endl;
        cout << " 2. Deposit Funds" << endl;
        cout << " 3. Withdraw Funds" << endl;
        cout << " 4. Balance Inquiry Statement" << endl;
        cout << " 5. Close/Terminate Account" << endl;
        cout << " 6. Master Accounts Ledger View" << endl;
        cout << " 7. Exit Financial Core Application" << endl;
        cout << "------------------------------------" << endl;
        cout << "Select Operation Option (1-7): ";

        if (!(cin >> inputCommand)) {
            cout << "Invalid system instruction code. Select numbers 1-7.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (inputCommand) {
            case 1: bank.createAccount(); break;
            case 2: bank.processDeposit(); break;
            case 3: bank.processWithdrawal(); break;
            case 4: bank.checkBalance(); break;
            case 5: bank.closeAccount(); break;
            case 6: bank.displayAllAccounts(); break;
            case 7: cout << "\nShutting down financial core securely. Active data caches flushed down to disk.\n"; break;
            default: cout << "Option outside range boundary limitations.\n";
        }
    } while (inputCommand != 7);

    return 0;
}