#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// ===== Transaction Class =====
class Transaction {
public:
    string type;
    double amount;
    string date;

    Transaction(string t, double a) {
        type = t;
        amount = a;

        // Get current time
        time_t now = time(0);
        char* dt = ctime(&now);

        // Remove newline from ctime()
        string temp(dt);
        if (!temp.empty() && temp[temp.size() - 1] == '\n')
            temp[temp.size() - 1] = '\0';

        date = temp;
    }

    void showTransaction() const {
        cout << type << " of Rs." << amount << " on " << date << endl;
    }
};

// ===== Account Class =====
class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int accNo, double initialBalance = 0.0) {
        accountNumber = accNo;
        balance = initialBalance;
    }

    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount));
        cout << "\n? Deposit successful! New Balance: Rs." << balance << endl;
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            transactions.push_back(Transaction("Withdrawal", amount));
            cout << "\n? Withdrawal successful! New Balance: Rs." << balance << endl;
        } else {
            cout << "\n? Insufficient balance!" << endl;
        }
    }

    void transfer(Account &receiver, double amount) {
        if (amount <= balance) {
            balance -= amount;
            receiver.balance += amount;
            transactions.push_back(Transaction("Transfer Sent", amount));
            receiver.transactions.push_back(Transaction("Transfer Received", amount));
            cout << "\n? Transfer successful! Sent Rs." << amount
                 << " to Account " << receiver.getAccountNumber() << endl;
        } else {
            cout << "\n? Insufficient balance for transfer!" << endl;
        }
    }

    void showTransactions() const {
        cout << "\n--- Transaction History for Account " << accountNumber << " ---\n";
        if (transactions.empty()) {
            cout << "No transactions found.\n";
        } else {
            for (size_t i = 0; i < transactions.size(); i++) {
                transactions[i].showTransaction();
            }
        }
    }
};

// ===== Customer Class =====
class Customer {
private:
    string name;
    int id;
    vector<Account> accounts;

public:
    Customer(string n, int i) {
        name = n;
        id = i;
    }

    void addAccount(Account acc) {
        accounts.push_back(acc);
    }

    void showAccounts() {
        cout << "\nCustomer: " << name << " (ID: " << id << ")\n";
        for (size_t i = 0; i < accounts.size(); i++) {
            cout << "Account No: " << accounts[i].getAccountNumber()
                 << " | Balance: Rs." << accounts[i].getBalance() << endl;
        }
    }

    Account* getAccount(int accNo) {
        for (size_t i = 0; i < accounts.size(); i++) {
            if (accounts[i].getAccountNumber() == accNo)
                return &accounts[i];
        }
        return NULL;
    }
};

// =====
int main() {
    Customer c1("Eman", 1);
    Account a1(1001, 5000);
    Account a2(1002, 3000);

    c1.addAccount(a1);
    c1.addAccount(a2);

    Account* acc1 = c1.getAccount(1001);
    Account* acc2 = c1.getAccount(1002);
if (acc1 && acc2) {
        acc1->deposit(2000);
        acc1->withdraw(1500);
        acc1->transfer(*acc2, 1000);
        acc1->showTransactions();
        acc2->showTransactions();
    }

    c1.showAccounts();

    return 0;
}
