#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Bank.h"

class Transaction {
public:
    static void deposit(Bank& b, int acc_num, float amount);
};

#endif // TRANSACTION_H
