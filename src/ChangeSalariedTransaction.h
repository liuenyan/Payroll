#ifndef _CHANGESALARIEDTRANSACTION_H_
#define _CHANGESALARIEDTRANSACTION_H_

#include "ChangeClassificationTransaction.h"

class ChangeSalariedTransaction : public ChangeClassificationTransaction
{
    public:
        ChangeSalariedTransaction(int empId, double salary);
        virtual ~ChangeSalariedTransaction();
        PaymentClassification *getClassification() const override;
        PaymentSchedule *getSchedule() const override;
    private:
        double itsSalary;
};

#endif