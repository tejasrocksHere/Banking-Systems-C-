#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

class Account {
private:
    string fname;
    string lname;
    float balance;
    int acc_num;

public:
    static int account_counter;

    // Default constructor
    Account() {
        fname="";
        lname="";
        balance=0;
        acc_num=0;
    }

    // Parameterized constructor
    Account(string f_name, string l_name, float b) {
        fname = f_name;
        lname = l_name;
        balance = b;
        acc_num = ++account_counter;
    }

    // Getters
    string get_fname() const { return fname; }
    string get_lname() const { return lname; }
    float get_balance() const { return balance; }
    int get_account_number() const { return acc_num; }

    // Setters
    void set_new_balance(float val) { balance = val; }

    // Display method
    virtual void display() const {
        cout << "First Name: " << fname << endl;
        cout << "Last Name: " << lname << endl;
        cout << "Balance: " << balance << endl;
        cout << "Account Number: " << acc_num << endl;
    }

    // Save account details to a file
    virtual void save_to_file(ofstream& file) const {
        file << fname << " " << lname << " " << balance << " " << acc_num << endl;
    }

    // Load account details from a file
    virtual void load_from_file(ifstream& file) {
        file >> fname >> lname >> balance >> acc_num;
    }
};

int Account::account_counter = 0;

class SavingsAccount : public Account {
public:
    SavingsAccount(string f_name, string l_name, float b) : Account(f_name, l_name, b) {}

    void display() const override {
        cout << "Savings Account:" << endl;
        Account::display();
    }
};

class CheckingAccount : public Account {
public:
    CheckingAccount(string f_name, string l_name, float b) : Account(f_name, l_name, b) {}

    void display() const override {
        cout << "Checking Account:" << endl;
        Account::display();
    }
};

class Bank {
private:
    map<int, Account*> bank_account;

public:
    // Constructor
    Bank() {
        load_from_file("accounts.txt");
    }

    ~Bank() {
        // Clean up dynamically allocated accounts
        for (auto& pair : bank_account) {
            delete pair.second;
        }
    }

    // Display all accounts
    void display_all_accounts() const {
        for (const auto& pair : bank_account) {
            cout << "Account Number: " << pair.first << endl;
            pair.second->display();
        }
    }

    // Check if account exists
    bool is_account_present(int val) const {
        return bank_account.find(val) != bank_account.end();
    }

    // Get account by number
    Account* get_account(int val) const {
        auto it = bank_account.find(val);
        return it != bank_account.end() ? it->second : nullptr;
    }

    // Set account details
    void set_account(int val, Account* account) {
        if (bank_account.find(val) != bank_account.end())
            cout << "Account already exists" << endl;
        else {
            bank_account[val] = account;
        }
    }

    // Save all accounts to file
    void save_to_file(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            file << Account::account_counter << endl;  // Save the account counter
            for (const auto& pair : bank_account) {
                pair.second->save_to_file(file);
            }
            file.close();
        } else {
            cout << "Unable to open file for writing!" << endl;
        }
    }

    // Load all accounts from file
    void load_from_file(const string& filename) {
        ifstream file(filename); // Open the file for reading
        if (file.is_open()) {    // Check if the file was successfully opened
            int counter;
            file >> counter;  // Load the account counter
            Account::account_counter = counter;

            // Read accounts from the file
            while (file) {
                string fname, lname;
                float balance;
                int acc_num;
                file >> fname >> lname >> balance >> acc_num;
                if (file && acc_num != 0) { // Check if loading was successful
                    // Create a new account object based on some condition (for simplicity, using SavingsAccount here)
                    Account* acc = new SavingsAccount(fname, lname, balance); // Or use CheckingAccount as needed
                    bank_account[acc_num] = acc; // Insert account into the map
                }
            }

            file.close(); // Close the file
        } else {
            cout << "Unable to open file for reading!" << endl; // Error message if file opening fails
        }
    }

    // Delete account by number
    void delete_account(int account_num) {
        if (is_account_present(account_num)) {
            cout << "Deleting account number: " << account_num << endl;
            delete bank_account[account_num]; // Delete the Account object
            bank_account.erase(account_num); // Remove the pointer from the map
        } else {
            cout << "Account not found!" << endl;
        }
    }
};

class Transaction {
public:
    virtual void execute(Bank& b, int acc_num, float amount) = 0; //abstract class
   friend void transfer_money(Bank& b, int acc_num, float amount, int acc_num1, float amount1);
};

class Transfer : public Transaction {
public:
    void transfer_money(Bank& b, int acc_num, float amount, int acc_num1, float to_be_transferred) {
        if (b.is_account_present(acc_num) && b.is_account_present(acc_num1)) {
            float cur_amount1 = b.get_account(acc_num)->get_balance();
            if (cur_amount1 > to_be_transferred) {
                b.get_account(acc_num)->set_new_balance(cur_amount1 - to_be_transferred);
                float temp = b.get_account(acc_num1)->get_balance() + to_be_transferred;
                b.get_account(acc_num1)->set_new_balance(temp);
                cout << "Transferred " << to_be_transferred << " from account " << acc_num << " to account " << acc_num1 << endl;
            } else {
                cout << "Low balance" << endl;
            }
        } else {
            cout << "One or both accounts do not exist" << endl;
        }
    }

    void execute(Bank& b, int acc_num, float amount) override {
        // This method is not used for the Transfer class
    }
};

class DepositTransaction : public Transaction {
public:
    void execute(Bank& b, int acc_num, float amount) override {
        if (b.is_account_present(acc_num)) {
            cout << "Depositing amount: " << amount << endl;
            float current_balance = b.get_account(acc_num)->get_balance();
            float new_balance = current_balance + amount;
            b.get_account(acc_num)->set_new_balance(new_balance);
        } else {
            cout << "Account not found!" << endl;
        }
    }
};

class WithdrawTransaction : public Transaction {
public:
    void execute(Bank& b, int acc_num, float amount) override {
        if (b.is_account_present(acc_num)) {
            float current_balance = b.get_account(acc_num)->get_balance();
            if (current_balance >= amount) {
                cout << "Withdrawing amount: " << amount << endl;
                float new_balance = current_balance - amount;
                b.get_account(acc_num)->set_new_balance(new_balance);
            } else {
                cout << "Insufficient balance!" << endl;
            }
        } else {
            cout << "Account not found!" << endl;
        }
    }
};

void add_new_account(Bank& b, Account* a) {
    cout << "Adding new account..." << endl;
    b.set_account(a->get_account_number(), a);
}

void delete_account(Bank& b, int account_num) {
    b.delete_account(account_num);
}

void print_details(Bank& b, int account_num) {
    if (b.is_account_present(account_num)) {
        cout << "Details of account number: " << account_num << endl;
        b.get_account(account_num)->display();
    } else {
        cout << "Account not found!" << endl;
    }
}

int main() {
    Bank b;
    // Load accounts from file

    while (true) {
        cout << "\nSelect your choice (1-6):\n";
        cout << "1. Create account\n";
        cout << "2. Delete account\n";
        cout << "3. Account inquiry\n";
        cout << "4. Deposit\n";
        cout << "5. Display all accounts\n";
        cout << "6. Transfer money\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 9) {
            // Save accounts to file
            b.save_to_file("accounts.txt");
            break;
        }

        switch (choice) {
            case 1: {
                cout << "Create account\n";
                cout << "Enter your first name: ";
                string fname;
                cin >> fname;
                cout << "Enter your last name: ";
                string lname;
                cin >> lname;
                cout << "Enter initial balance: ";
                float balance;
                cin >> balance;

                cout << "Select account type:\n";
                cout << "1. Savings\n";
                cout << "2. Checking\n";
                int acc_type;
                cin >> acc_type;

                Account* new_acc = nullptr;
                if (acc_type == 1) {
                    new_acc = new SavingsAccount(fname, lname, balance);
                } else if (acc_type == 2) {
                    new_acc = new CheckingAccount(fname, lname, balance);
                }

                if (new_acc) {
                    add_new_account(b, new_acc);
                } else {
                    cout << "Invalid account type selected!" << endl;
                }

                b.save_to_file("accounts.txt");
                break;
            }

            case 2: {
                cout << "Delete account\n";
                cout << "Enter account number: ";
                int acc_num;
                cin >> acc_num;

                delete_account(b, acc_num);
                b.save_to_file("accounts.txt");
                break;
            }

            case 3: {
                cout << "Account inquiry\n";
                cout << "Enter account number: ";
                int acc_num;
                cin >> acc_num;

                print_details(b, acc_num);
                break;
            }

            case 4: {
                cout << "Deposit\n";
                cout << "Enter account number: ";
                int acc_num;
                cin >> acc_num;
                cout << "Enter amount to deposit: ";
                float amount;
                cin >> amount;

                DepositTransaction deposit;
                deposit.execute(b, acc_num, amount);

                b.save_to_file("accounts.txt");
                break;
            }

            case 5: {
                cout << "Display all accounts\n";
                b.display_all_accounts();
                break;
            }

            case 6: {
                cout << "Enter account number of yours: ";
                int acc;
                cin >> acc;
                cout << "Enter amount to be transferred: ";
                float amt;
                cin >> amt;
                cout << "Enter account of another person: ";
                int acc1;
                cin >> acc1;

                Transfer transfer;
                transfer.transfer_money(b, acc, amt, acc1, amt);

                b.save_to_file("accounts.txt");
                break;
            }

            default: {
                cout << "Invalid choice. Please select a valid option." << endl;
                break;
            }
        }
    }

    return 0;
}
