#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// ANSI Colors
#define RESET "\033[0m"
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define CYAN "\033[1;36m"
#define YELLOW "\033[1;33m"

class Account {
public:
    string username;
    string password;
    double balance;
    vector<string> history;

    Account(string u, string p) {
        username = u;
        password = p;
        balance = 0;
    }
};

vector<Account> accounts;

// Utility: Find account
int findAccount(string username) {
    for (int i = 0; i < accounts.size(); i++) {
        if (accounts[i].username == username)
            return i;
    }
    return -1;
}

// Dashboard UI
void showDashboard(Account &acc) {
    cout << CYAN;
    cout << "\n=========================================\n";
    cout << "        🏦 BANKING DASHBOARD\n";
    cout << "=========================================\n";
    cout << RESET;

    cout << GREEN << "User: " << acc.username << RESET << endl;
    cout << GREEN << "Balance: ₹" << fixed << setprecision(2) << acc.balance << RESET << endl;

    cout << YELLOW;
    cout << "\n-----------------------------------------\n";
    cout << "1. Deposit\n";
    cout << "2. Withdraw\n";
    cout << "3. Transfer\n";
    cout << "4. Transaction History\n";
    cout << "5. Logout\n";
    cout << "-----------------------------------------\n";
    cout << RESET;
}

// Features
void deposit(Account &acc) {
    double amt;
    cout << "Enter amount: ";
    cin >> amt;

    if (amt > 0) {
        acc.balance += amt;
        acc.history.push_back("Deposited ₹" + to_string(amt));
        cout << GREEN << "✔ Deposit Successful\n" << RESET;
    } else {
        cout << RED << "✘ Invalid Amount\n" << RESET;
    }
}

void withdraw(Account &acc) {
    double amt;
    cout << "Enter amount: ";
    cin >> amt;

    if (amt > acc.balance) {
        cout << RED << "⚠ Insufficient Balance\n" << RESET;
        acc.history.push_back("Failed Withdrawal ₹" + to_string(amt));
    } else if (amt > 0) {
        acc.balance -= amt;
        acc.history.push_back("Withdrawn ₹" + to_string(amt));
        cout << GREEN << "✔ Withdrawal Successful\n" << RESET;
    } else {
        cout << RED << "✘ Invalid Amount\n" << RESET;
    }
}

void transfer(Account &acc) {
    string toUser;
    double amt;

    cout << "Enter receiver username: ";
    cin >> toUser;

    int idx = findAccount(toUser);

    if (idx == -1) {
        cout << RED << "User not found!\n" << RESET;
        return;
    }

    cout << "Enter amount: ";
    cin >> amt;

    if (amt > acc.balance) {
        cout << RED << "Insufficient Balance!\n" << RESET;
    } else if (amt > 0) {
        acc.balance -= amt;
        accounts[idx].balance += amt;

        acc.history.push_back("Transferred ₹" + to_string(amt) + " to " + toUser);
        accounts[idx].history.push_back("Received ₹" + to_string(amt) + " from " + acc.username);

        cout << GREEN << "✔ Transfer Successful\n" << RESET;
    } else {
        cout << RED << "Invalid Amount\n" << RESET;
    }
}

void showHistory(Account &acc) {
    cout << YELLOW << "\n--- Transaction History ---\n" << RESET;

    if (acc.history.empty()) {
        cout << "No transactions yet.\n";
    } else {
        for (int i = 0; i < acc.history.size(); i++) {
            cout << i + 1 << ". " << acc.history[i] << endl;
        }
    }
}

// Main
int main() {
    int choice;

    while (true) {
        cout << CYAN;
        cout << "\n========== BANK SYSTEM ==========\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "================================\n";
        cout << RESET;

        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string user, pass;
            cout << "Enter username: ";
            cin >> user;

            if (findAccount(user) != -1) {
                cout << RED << "User already exists!\n" << RESET;
                continue;
            }

            cout << "Enter password: ";
            cin >> pass;

            accounts.push_back(Account(user, pass));
            cout << GREEN << "✔ Registration Successful\n" << RESET;
        }

        else if (choice == 2) {
            string user, pass;
            cout << "Enter username: ";
            cin >> user;
            cout << "Enter password: ";
            cin >> pass;

            int idx = findAccount(user);

            if (idx != -1 && accounts[idx].password == pass) {
                cout << GREEN << "✔ Login Successful\n" << RESET;

                while (true) {
                    showDashboard(accounts[idx]);

                    int ch;
                    cout << "Enter choice: ";
                    cin >> ch;

                    if (ch == 1) deposit(accounts[idx]);
                    else if (ch == 2) withdraw(accounts[idx]);
                    else if (ch == 3) transfer(accounts[idx]);
                    else if (ch == 4) showHistory(accounts[idx]);
                    else if (ch == 5) break;
                    else cout << "Invalid choice\n";
                }
            } else {
                cout << RED << "Invalid login!\n" << RESET;
            }
        }

        else if (choice == 3) {
            cout << "Exiting...\n";
            break;
        }

        else {
            cout << "Invalid choice!\n";
        }
    }
}