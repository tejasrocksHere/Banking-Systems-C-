#include "Transaction.h"
#include <iostream>

void Transaction::deposit(Bank& b, int acc_num, float amount) {
    if (b.is_account_present(acc_num)) {
        std::cout << "Depositing amount: " << amount << std::endl;
        Account& acc = b.get_account(acc_num);
        float new_balance = acc.get_balance() + amount;
        acc.set_new_balance(new_balance);
    } else {
        std::cout << "Account not found!" << std::endl;
    }
}
