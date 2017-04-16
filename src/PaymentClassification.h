#ifndef _PAYMENTCLASSIFICATION_H_
#define _PAYMENTCLASSIFICATION_H_

#include "Paycheck.h"

class PaymentClassification
{
    public:
        virtual ~PaymentClassification() = 0;
        virtual double calculatePay(Paycheck &pc) const = 0;
    protected:
        bool isInPayPeriod(const Date &theDate, const Date &startDate, 
                const Date &endDate) const {
            return isBetween(theDate, startDate, endDate);
        }
};

inline PaymentClassification::~PaymentClassification() {};

#endif
