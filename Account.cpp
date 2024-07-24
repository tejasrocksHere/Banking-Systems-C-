#include "Account.h"
#include <iostream>

int Account::account_counter = 0;

// Default constructor
Account::Account() : fname(""), lname(""), balance(0.0), acc_num(0) {}

// Parameterized constructor
Account::Account(const std::string& f_name, const std::string& l_name, float b)
    : fname(f_name), lname(l_name), balance(b), acc_num(++account_counter) {}

std::string Account::get_fname() const {
    return fname;
}

std::string Account::get_lname() const {
    return lname;
}

float Account::get_balance() const {
    return balance;
}

int Account::get_account_number() const {
    return acc_num;
}

void Account::set_new_balance(float val) {
    balance = val;
}

void Account::display() const {
    std::cout << "First Name: " << fname << std::endl;
    std::cout << "Last Name: " << lname << std::endl;
    std::cout << "Balance: " << balance << std::endl;
    std::cout << "Account Number: " << acc_num << std::endl;
}
