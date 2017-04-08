#ifndef _CHANGEDIRECTMETHODTRANSACTION_H_
#define _CHANGEDIRECTMETHODTRANSACTION_H_

#include <string>
#include "ChangeMethodTransaction.h"

class ChangeDirectMethodTransaction : public ChangeMethodTransaction
{
    public:
        ChangeDirectMethodTransaction(
            int empId, const std::string &bank, const std::string &account);
        virtual ~ChangeDirectMethodTransaction();
        PaymentMethod *getPaymentMethod() const override;
    private:
        std::string itsBank;
        std::string itsAccount;
};

#endif
