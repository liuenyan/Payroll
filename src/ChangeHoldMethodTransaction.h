#ifndef _CHANGEHOLDMETHODTRANSACTION_H_
#define _CHANGEHOLDMETHODTRANSACTION_H_

#include "ChangeMethodTransaction.h"

class ChangeHoldMethodTransaction : public ChangeMethodTransaction
{
    public:
        ChangeHoldMethodTransaction(int empId);
        virtual ~ChangeHoldMethodTransaction();
        PaymentMethod *getPaymentMethod() const override;
};

#endif
