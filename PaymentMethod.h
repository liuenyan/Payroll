#ifndef _PAYMENTMETHOD_H_
#define _PAYMENTMETHOD_H_

class PaymentMethod
{
    public:
        virtual ~PaymentMethod() = 0;
};

inline PaymentMethod::~PaymentMethod() {};

#endif
