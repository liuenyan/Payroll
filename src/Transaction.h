#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_

class Transaction
{
    public:
        virtual void execute() = 0;
        virtual ~Transaction() = 0;
};

inline Transaction::~Transaction() {};

#endif
