#ifndef _SERVICECHARGETRANSACTION_H_
#define _SERVICECHARGETRANSACTION_H_

#include "Transaction.h"
#include "Date.h"

class ServiceChargeTransaction : public Transaction
{
    public:
        ServiceChargeTransaction(int memberId, Date &date, double amount);
        ~ServiceChargeTransaction();
        void execute() override;
    private:
        int itsMemberId;
        Date itsDate;
        double itsAmount;
};

#endif

