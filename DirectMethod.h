#ifndef _DIRECTMETHOD_H_
#define _DIRECTMETHOD_H_

#include <string>
#include "PaymentMethod.h"

class DirectMethod : public PaymentMethod
{
    public:
        DirectMethod(const std::string &bank, const std::string &account)
            : itsBank(bank), itsAccount(account) {};
        virtual ~DirectMethod(){};
        const std::string &getBank() const { return itsBank; };
        const std::string &getAccount() const { return itsAccount; };
        void pay(Paycheck &pc) const override;
    private:
        std::string itsBank;
        std::string itsAccount;
};

#endif
