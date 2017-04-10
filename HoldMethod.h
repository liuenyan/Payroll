#ifndef _HOLDMETHOD_H_
#define _HOLDMETHOD_H_

#include "PaymentMethod.h"

class HoldMethod : public PaymentMethod
{
    public:
        virtual ~HoldMethod() {};
        void pay(Paycheck &pc) const override;
};

#endif
