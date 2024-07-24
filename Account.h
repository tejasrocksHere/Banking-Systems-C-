#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
private:
    std::string fname;
    std::string lname;
    float balance;
    int acc_num;

public:
    static int account_counter;

    // Default constructor
    Account();
    Account(const std::string& f_name, const std::string& l_name, float b);

    std::string get_fname() const;
    std::string get_lname() const;
    float get_balance() const;
    int get_account_number() const;

    void set_new_balance(float val);
    void display() const;
};

#endif // ACCOUNT_H
