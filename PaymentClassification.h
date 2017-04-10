#ifndef _PAYMENTCLASSIFICATION_H_
#define _PAYMENTCLASSIFICATION_H_

#include "Paycheck.h"

class PaymentClassification
{
    public:
        virtual ~PaymentClassification() = 0;
        virtual double calculatePay(Paycheck &pc) const = 0;
};

inline PaymentClassification::~PaymentClassification() {};

#endif
