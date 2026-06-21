# Simple Banking System in C++

A console-based Banking Management System implemented in modern C++ showcasing core Object-Oriented Programming (OOP) concepts, secure data handling, and transactional tracking.

## 🚀 Features
- *Customer Management*: Register unique customers and manage profiles.
- *Multi-Account Support*: Create both Savings and Checking accounts under a single customer.
- *Core Banking Operations*: Support for deposits, withdrawals, and error-checked balance tracking.
- *Inter-Account Transfers*: Safe transfer of funds between a customer's own accounts or between different customers.
- *Transaction History*: Comprehensive ledger tracking for every activity (Deposits, Withdrawals, Transfers In/Out).

## 🛠️ Architecture & OOP Concepts Demonstrated
The system is built using a clean, layered architecture consisting of four core components:
1. *Transaction (Struct)*: Captures immutable metadata about a financial event.
2. *Account (Class)*: Encapsulates individual financial state and modifies ledger history.
3. *Customer (Class)*: Aggregates multiple accounts owned by an individual.
4. *Bank (Class)*: Acts as the root database coordinator facilitating transfers between customers.

### Key Technical Highlight: Pointer Safety
To prevent C++ vector reallocation issues and memory copying bugs, the database methods utilize explicit memory address retrieval (&) to guarantee that state alterations persist globally across the system.

## 💻 Getting Started

### Prerequisites
- A C++ compiler supporting *C++11* or higher (e.g., g++, clang, or MSVC).

### Installation & Execution
1. Clone this repository to your local machine:
   ```bash
   git clone 
