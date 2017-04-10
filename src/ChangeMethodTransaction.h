#ifndef _CHANGEMETHODTRANSACTION_H_
#define _CHANGEMETHODTRANSACTION_H_

#include "ChangeEmployeeTransaction.h"

class ChangeMethodTransaction : public ChangeEmployeeTransaction
{
    public:
        ChangeMethodTransaction(int empId);
        virtual ~ChangeMethodTransaction();
        void change(Employee &e) override;
        virtual PaymentMethod *getPaymentMethod() const = 0;
};

#endif
