#ifndef _CHANGEHOURLYTRANSACTION_H_
#define _CHANGEHOURLYTRANSACTION_H_

#include "ChangeClassificationTransaction.h"

class ChangeHourlyTransaction : public ChangeClassificationTransaction
{
    public:
        ChangeHourlyTransaction(int empId, double hourlyRate);
        virtual ~ChangeHourlyTransaction();
        PaymentClassification *getClassification() const override;
        PaymentSchedule *getSchedule() const override;
    private:
        double itsHourlyRate;
};


#endif