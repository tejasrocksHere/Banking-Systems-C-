#ifndef BANK_H
#define BANK_H

#include "Account.h"
#include <map>

class Bank {
private:
    std::map<int, Account> bank_account;

    friend void add_new_account(Bank& b, Account& a);
    friend void delete_account(Bank& b, int account_num);
    friend void print_details(Bank& b, int account_num);
    friend class Transaction;

public:
    void display_all_accounts() const;
    bool is_account_present(int val) const;
    Account& get_account(int val);
    void set_account(int val, Account& account);
};

#endif // BANK_H
