#ifndef _SALESRECEIPTTRANSACTION_H_
#define _SALESRECEIPTTRANSACTION_H_

#include "Transaction.h"
#include "Date.h"

class SalesReceiptTransaction : public Transaction
{
    public:
        SalesReceiptTransaction(Date date, double amount, int empId);
        virtual ~SalesReceiptTransaction();
        void execute() override;
    private:
        Date itsDate;
        double itsAmount;
        int itsEmpId;
};

#endif
