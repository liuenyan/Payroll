#ifndef _CHANGEMAILMETHODTRANSACTION_H_
#define _CHANGEMAILMETHODTRANSACTION_H_

#include <string>
#include "ChangeMethodTransaction.h"

class ChangeMailMethodTransaction : public ChangeMethodTransaction
{
    public:
        ChangeMailMethodTransaction(int empId, const std::string &address);
        virtual ~ChangeMailMethodTransaction();
        PaymentMethod *getPaymentMethod() const override;
    private:
        std::string itsAddress;
};

#endif
