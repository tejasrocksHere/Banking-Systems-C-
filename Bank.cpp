#include "Bank.h"
#include <iostream>

void Bank::display_all_accounts() const {
    for (const auto& pair : bank_account) {
        std::cout << "Account Number: " << pair.first << std::endl;
        pair.second.display();
    }
}

bool Bank::is_account_present(int val) const {
    return bank_account.find(val) != bank_account.end();
}

Account& Bank::get_account(int val) {
    return bank_account[val];
}

void Bank::set_account(int val, Account& account) {
    if (bank_account.find(val) != bank_account.end()) {
        std::cout << "Account already exists" << std::endl;
    } else {
        bank_account[val] = account;
    }
}
