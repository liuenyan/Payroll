#ifndef _CHANGECOMMISSIONEDTRANSACTION_H_
#define _CHANGECOMMISSIONEDTRANSACTION_H_

#include "ChangeClassificationTransaction.h"

class ChangeCommissionedTransaction : public ChangeClassificationTransaction
{
    public:
        ChangeCommissionedTransaction(int empId, double salary, double commissionRate);
        virtual ~ChangeCommissionedTransaction();
        PaymentClassification *getClassification() const override;
        PaymentSchedule *getSchedule() const override;
    private:
        double itsSalary;
        double itsCommissionRate;
};

#endif