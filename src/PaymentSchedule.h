#ifndef _PAYMENTSCHEDULE_H_
#define _PAYMENTSCHEDULE_H_

#include "Date.h"

class PaymentSchedule
{
    public:
        virtual ~PaymentSchedule() = 0;
        virtual bool isPayDate(const Date &date) const = 0;
        virtual Date getPayPeriodStartDate(const Date &payPeriodEndDate) const = 0;
};

inline PaymentSchedule::~PaymentSchedule() {};

#endif
