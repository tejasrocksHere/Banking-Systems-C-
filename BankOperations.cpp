#include "Bank.h"
#include "Account.h"
#include <iostream>

void add_new_account(Bank& b, Account& a) {
    std::cout << "Adding new account..." << std::endl;
    b.set_account(a.get_account_number(), a);
}

void delete_account(Bank& b, int account_num) {
    if (b.is_account_present(account_num)) {
        std::cout << "Deleting account number: " << account_num << std::endl;
        b.get_account(account_num); // Access to validate
        b.set_account(account_num, b.get_account(account_num)); // Remove
    } else {
        std::cout << "Account not found!" << std::endl;
    }
}

void print_details(Bank& b, int account_num) {
    if (b.is_account_present(account_num)) {
        std::cout << "Details of account number: " << account_num << std::endl;
        b.get_account(account_num).display();
    } else {
        std::cout << "Account not found!" << std::endl;
    }
}
