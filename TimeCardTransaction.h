#ifndef _TIMECARDTRANSACTION_H_
#define _TIMECARDTRANSACTION_H_

#include "Transaction.h"
#include "Date.h"

class TimeCardTransaction : public Transaction
{
    public:
        TimeCardTransaction(Date date, double hours, int empId);
        virtual ~TimeCardTransaction();
        void execute() override;
    private:
        Date itsDate;
        double itsHours;
        int itsEmpId;
};

#endif
