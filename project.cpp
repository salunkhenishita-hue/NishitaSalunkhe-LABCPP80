#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <limits>
using namespace std;

// Abstract base class
class BankAccount {
private:
    double balance;
    int pin;

public:
    BankAccount(int p, double b) {
        pin = p;
        balance = b;
    }

    virtual ~BankAccount() {}

    bool verifyPIN(int enteredPIN) const {
        return pin == enteredPIN;
    }

    double getBalance() const {
        return balance;
    }

    virtual string accountType() const = 0;

    void deposit(double amount) {
        if (amount <= 0)
            throw invalid_argument("Amount must be positive.");

        balance += amount;
        cout << "Deposit successful!\n";
    }

    void withdraw(double amount) {
        if (amount <= 0)
            throw invalid_argument("Amount must be positive.");

        if (amount > balance)
            throw runtime_error("Insufficient balance.");

        balance -= amount;
        cout << "Withdrawal successful!\n";
    }

    // Save balance in a file
    void saveBalance() const {
        ofstream file("account.txt");
        if (!file)
            throw runtime_error("Unable to save account data.");

        file << balance;
        file.close();
    }

    // Record transactions
    void recordTransaction(const string& message) {
        ofstream file("transactions.txt", ios::app);
        if (!file)
            throw runtime_error("Unable to save transaction.");

        file << message << '\n';
        file.close();
    }

    void showBalance() const {
        cout << "Available Balance: Rs. "
             << balance << '\n';
    }
};

// Inheritance
class SavingsAccount : public BankAccount {
public:
    SavingsAccount(int p, double b)
        : BankAccount(p, b) {}

    // Polymorphism
    string accountType() const override {
        return "Savings Account";
    }
};
double loadBalance() {
    ifstream file("account.txt");
    double amount;

    if (file >> amount && amount >= 0)
        return amount;

    return 5000.0; // Initial balance
}

int main() {
    try {
        SavingsAccount account(1234, loadBalance());

        // Base-class pointer demonstrates abstraction
        BankAccount* atm = &account;

        int enteredPIN;
        int attempts = 0;
        bool loggedIn = false;

        cout << "===== ATM BANKING SYSTEM =====\n";

        while (attempts < 3) {
            cout << "Enter your 4-digit PIN: ";

            if (!(cin >> enteredPIN)) {
                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(), '\n');
                cout << "Enter numbers only.\n";
                continue;
            }

            if (atm->verifyPIN(enteredPIN)) {
                loggedIn = true;
                break;
            }

            attempts++;
            cout << "Incorrect PIN. Attempts left: "
                 << 3 - attempts << '\n';
        }

        if (!loggedIn) {
            cout << "Access denied.\n";
            return 0;
        }

        cout << "\nWelcome to your "
             << atm->accountType() << "!\n";

        int choice;

        do {
            cout << "\n===== ATM MENU =====\n";
            cout << "1. Check Balance\n";
            cout << "2. Deposit Money\n";
            cout << "3. Withdraw Money\n";
            cout << "4. View Transactions\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";

            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Enter a number.\n";
                continue;
            }

            try {
                double amount;

                switch (choice) {
                case 1:
                    atm->showBalance();
                    break;

                case 2:
                    cout << "Enter deposit amount: Rs. ";
                    if (!(cin >> amount) ||
                        !cin.good()) {
                        cin.clear();
                        cin.ignore(
                            numeric_limits<streamsize>::max(),
                            '\n');
                        cout << "Invalid amount.\n";
                        break;
                    }

                    atm->deposit(amount);
                    atm->saveBalance();
                    atm->recordTransaction(
                        "Money deposited: Rs. " +
                        to_string(amount));
                    break;

                case 3:
                    cout << "Enter withdrawal amount: Rs. ";
                    if (!(cin >> amount) ||
                        !cin.good()) {
                        cin.clear();
                        cin.ignore(
                            numeric_limits<streamsize>::max(),
                            '\n');
                        cout << "Invalid amount.\n";
                        break;
                    }

                    atm->withdraw(amount);
                    atm->saveBalance();
                    atm->recordTransaction(
                        "Money withdrawn: Rs. " +
                        to_string(amount));
                    break;

                case 4: {
                    ifstream file("transactions.txt");
                    string line;

                    cout << "\nTransaction History:\n";

                    if (!file || file.peek() ==
                        ifstream::traits_type::eof()) {
                        cout << "No transactions found.\n";
                    } else {
                        while (getline(file, line))
                            cout << line << '\n';
                    }
                    break;
                }

                case 5:
                    cout << "Thank you for using our ATM!\n";
                    break;

                default:
                    cout << "Invalid choice. Try again.\n";
                }
            }
            catch (const exception& e) {
                cout << "Error: " << e.what() << '\n';
            }

        } while (choice != 5);

    }
    catch (const exception& e) {
        cout << "System error: " << e.what() << '\n';
    }

    return 0;
}

