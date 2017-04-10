#ifndef _MAILMETHOD_H_
#define _MAILMETHOD_H_

#include <string>
#include "PaymentMethod.h"

class MailMethod : public PaymentMethod
{
    public:
        MailMethod(const std::string &address) : itsAddress(address) {};
        virtual ~MailMethod() {};
        const std::string &getAddress() const { return itsAddress; };
        void pay(Paycheck &pc) const override;
    private:
        std::string itsAddress;
};

#endif
