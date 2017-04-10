#ifndef _PAYDAYTRANSACTION_H_
#define _PAYDAYTRANSACTION_H_

#include <map>
#include "Transaction.h"
#include "Date.h"
#include "Paycheck.h"

class PaydayTransaction : public Transaction
{
    public:
        PaydayTransaction(const Date &date);
        virtual ~PaydayTransaction();
        void execute() override;
        Paycheck *getPaycheck(int empId) const;
    private:
        Date itsPayDate;
        std::map<int, Paycheck *> itsPaychecks;
};

#endif
