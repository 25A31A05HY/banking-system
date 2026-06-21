#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Transaction structure to store transaction details
struct Transaction {
    string type;        // "Deposit", "Withdraw", "Transfer"
    double amount;
    double balanceAfter;
    string date;
    string description;
};

// Account class to manage account operations
class Account {
private:
    string accountId;
    string accountType;  // "Savings" or "Checking"
    double balance;
    vector<Transaction> history;

public:
    // Constructor
    Account(string id, string type, double initialBalance) {
        accountId = id;
        accountType = type;
        balance = initialBalance;
    }

    // Get account ID
    string getAccountId() {
        return accountId;
    }

    // Get account type
    string getAccountType() {
        return accountType;
    }

    // Get balance
    double getBalance() {
        return balance;
    }

    // Deposit money
    bool deposit(double amount, string desc) {
        if (amount <= 0) {
            cout << "ERROR: Amount must be positive!\n";
            return false;
        }
        balance += amount;
        Transaction t;
        t.type = "Deposit";
        t.amount = amount;
        t.balanceAfter = balance;
        t.date = "2024-01-15";
        t.description = desc;
        history.push_back(t);
        cout << "✓ Deposit successful! Balance: " << balance << endl;
        return true;
    }

    // Withdraw money
    bool withdraw(double amount, string desc) {
        if (amount <= 0) {
            cout << "ERROR: Amount must be positive!\n";
            return false;
        }
        if (amount > balance) {
            cout << "ERROR: Insufficient funds! Balance: " << balance << endl;
            return false;
        }
        balance -= amount;
        Transaction t;
        t.type = "Withdraw";
        t.amount = amount;
        t.balanceAfter = balance;
        t.date = "2024-01-15";
        t.description = desc;
        history.push_back(t);
        cout << "✓ Withdrawal successful! Balance: " << balance << endl;
        return true;
    }

    // Transfer out
    bool transferOut(double amount, string receiverName) {
        if (amount <= 0) {
            cout << "ERROR: Amount must be positive!\n";
            return false;
        }
        if (amount > balance) {
            cout << "ERROR: Insufficient funds!\n";
            return false;
        }
        balance -= amount;
        Transaction t;
        t.type = "Transfer Out";
        t.amount = amount;
        t.balanceAfter = balance;
        t.date = "2024-01-15";
        t.description = "Sent to " + receiverName;
        history.push_back(t);
        cout << "✓ Transfer successful! New Balance: " << balance << endl;
        return true;
    }

    // Transfer in
    void transferIn(double amount, string senderName) {
        balance += amount;
        Transaction t;
        t.type = "Transfer In";
        t.amount = amount;
        t.balanceAfter = balance;
        t.date = "2024-01-15";
        t.description = "Received from " + senderName;
        history.push_back(t);
        cout << "✓ Transfer received! New Balance: " << balance << endl;
    }

    // Display account info
    void displayInfo() {
        cout << "\n========== ACCOUNT INFO =========\n";
        cout << "Account ID: " << accountId << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Current Balance: $" << balance << endl;
        cout << "Total Transactions: " << history.size() << endl;
        cout << "================================\n";
    }

    // Display recent transactions
    void displayTransactions() {
        if (history.empty()) {
            cout << "No transactions yet.\n";
            return;
        }
        cout << "\n===== TRANSACTION HISTORY =====\n";
        for (int i = 0; i < history.size(); i++) {
            cout << (i + 1) << ". " << history[i].type 
                 << " | Amount: $" << history[i].amount 
                 << " | Balance: $" << history[i].balanceAfter 
                 << " | " << history[i].description << endl;
        }
        cout << "================================\n";
    }
};

// Customer class to manage customer information
class Customer {
private:
    string customerId;
    string name;
    string email;
    vector<Account> accounts;

public:
    // Constructor
    Customer(string id, string n, string e) {
        customerId = id;
        name = n;
        email = e;
    }

    // Get customer ID
    string getCustomerId() {
        return customerId;
    }

    // Get customer name
    string getName() {
        return name;
    }

    // Create new account
    void createAccount(string accId, string accType, double initialBalance) {
        Account newAcc(accId, accType, initialBalance);
        accounts.push_back(newAcc);
        cout << "✓ " << accType << " Account created! Account ID: " << accId << endl;
    }

    // Get account by ID
    Account* getAccount(string accId) {
        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i].getAccountId() == accId) {
                return &accounts[i];
            }
        }
        return NULL;
    }

    // Get total balance of all accounts
    double getTotalBalance() {
        double total = 0;
        for (int i = 0; i < accounts.size(); i++) {
            total += accounts[i].getBalance();
        }
        return total;
    }

    // Display customer info
    void displayInfo() {
        cout << "\n====== CUSTOMER INFO ======\n";
        cout << "Customer ID: " << customerId << endl;
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Total Accounts: " << accounts.size() << endl;
        cout << "Total Balance: $" << getTotalBalance() << endl;
        cout << "===========================\n";
    }

    // Display all accounts
    void displayAccounts() {
        if (accounts.empty()) {
            cout << "No accounts found.\n";
            return;
        }
        cout << "\n====== YOUR ACCOUNTS ======\n";
        for (int i = 0; i < accounts.size(); i++) {
            cout << (i + 1) << ". ID: " << accounts[i].getAccountId() 
                 << " | Type: " << accounts[i].getAccountType() 
                 << " | Balance: $" << accounts[i].getBalance() << endl;
        }
        cout << "===========================\n";
    }
};

// Bank class to manage all customers
class Bank {
private:
    string bankName;
    vector<Customer> customers;

public:
    // Constructor
    Bank(string name) {
        bankName = name;
    }

    // Register new customer
    void registerCustomer(string custId, string name, string email) {
        Customer newCust(custId, name, email);
        customers.push_back(newCust);
        cout << "✓ Customer registered! Customer ID: " << custId << endl;
    }

    // Get customer by ID
    Customer* getCustomer(string custId) {
        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].getCustomerId() == custId) {
                return &customers[i];
            }
        }
        return NULL;
    }

    // Transfer between two accounts
    bool transfer(string fromAccId, string toAccId, double amount, 
                  string fromCustId, string toCustId) {
        Customer* fromCust = getCustomer(fromCustId);
        Customer* toCust = getCustomer(toCustId);

        if (fromCust == NULL || toCust == NULL) {
            cout << "ERROR: Customer not found!\n";
            return false;
        }

        Account* fromAcc = fromCust->getAccount(fromAccId);
        Account* toAcc = toCust->getAccount(toAccId);

        if (fromAcc == NULL || toAcc == NULL) {
            cout << "ERROR: Account not found!\n";
            return false;
        }

        if (fromAcc->getBalance() < amount) {
            cout << "ERROR: Insufficient funds!\n";
            return false;
        }

        cout << "\n--- TRANSFER IN PROGRESS ---\n";
        fromAcc->transferOut(amount, toCust->getName());
        toAcc->transferIn(amount, fromCust->getName());
        cout << "----------------------------\n";
        return true;
    }

    // Display all customers
    void displayAllCustomers() {
        if (customers.empty()) {
            cout << "No customers registered.\n";
            return;
        }
        cout << "\n====== ALL CUSTOMERS ======\n";
        for (int i = 0; i < customers.size(); i++) {
            cout << (i + 1) << ". Name: " << customers[i].getName() 
                 << " | ID: " << customers[i].getCustomerId() 
                 << " | Total Balance: $" << customers[i].getTotalBalance() << endl;
        }
        cout << "===========================\n";
    }

    // Display bank info
    void displayInfo() {
        cout << "\n====== BANK INFO ======\n";
        cout << "Bank Name: " << bankName << endl;
        cout << "Total Customers: " << customers.size() << endl;
        cout << "=======================\n";
    }
};

// Main demonstration
int main() {
    cout << "\n==================================\n";
    cout << "   SIMPLE BANKING SYSTEM\n";
    cout << "==================================\n";

    // Create bank
    Bank bank("National Bank");

    // Register customers
    cout << "\n[1] REGISTERING CUSTOMERS...\n";
    bank.registerCustomer("C001", "John Doe", "john@email.com");
    bank.registerCustomer("C002", "Jane Smith", "jane@email.com");

    // Get customers
    Customer* cust1 = bank.getCustomer("C001");
    Customer* cust2 = bank.getCustomer("C002");

    // Create accounts
    cout << "\n[2] CREATING ACCOUNTS...\n";
    cust1->createAccount("A001", "Savings", 5000);
    cust1->createAccount("A002", "Checking", 2000);
    cust2->createAccount("A003", "Savings", 3000);

    // Get accounts
    Account* acc1 = cust1->getAccount("A001");
    Account* acc2 = cust1->getAccount("A002");
    Account* acc3 = cust2->getAccount("A003");

    // Display customer info
    cout << "\n[3] CUSTOMER INFORMATION...\n";
    cust1->displayInfo();
    cust1->displayAccounts();

    // Deposit money
    cout << "\n[4] DEPOSITING MONEY...\n";
    acc1->deposit(1500, "Salary");
    acc2->deposit(500, "Bonus");

    // Withdraw money
    cout << "\n[5] WITHDRAWING MONEY...\n";
    acc1->withdraw(1000, "ATM");
    acc2->withdraw(200, "Shopping");

    // Transfer between own accounts
    cout << "\n[6] TRANSFER BETWEEN OWN ACCOUNTS...\n";
    acc1->transferOut(500, "John Doe");
    acc2->transferIn(500, "John Doe");

    // Display transactions
    cout << "\n[7] TRANSACTION HISTORY...\n";
    acc1->displayTransactions();

    // Transfer between different customers
    cout << "\n[8] INTER-CUSTOMER TRANSFER...\n";
    bank.transfer("A001", "A003", 750, "C001", "C002");

    // Display all customers
    cout << "\n[9] ALL CUSTOMERS...\n";
    bank.displayAllCustomers();

    // Display account info
    cout << "\n[10] ACCOUNT DETAILS...\n";
    acc1->displayInfo();
    acc3->displayInfo();

    // Display bank info
    cout << "\n[11] BANK SUMMARY...\n";
    bank.displayInfo();

    // Error handling
    cout << "\n[12] ERROR HANDLING...\n";
    cout << "\nTrying to withdraw more than balance:\n";
    acc2->withdraw(5000, "Test");

    cout << "\nTrying to deposit negative amount:\n";
    acc1->deposit(-100, "Test");

    return 0;
}
