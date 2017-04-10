#ifndef _PAYMENTMETHOD_H_
#define _PAYMENTMETHOD_H_

#include "Paycheck.h"

class PaymentMethod
{
    public:
        virtual ~PaymentMethod() = 0;
        virtual void pay(Paycheck &pc) const = 0;
};

inline PaymentMethod::~PaymentMethod() {};

#endif
