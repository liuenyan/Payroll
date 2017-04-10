#ifndef _SERVICECHARGE_H_
#define _SERVICECHARGE_H_

#include "Date.h"

class ServiceCharge
{
    public:
        ServiceCharge(Date &date, double amount)
            : itsDate(date), itsAmount(amount) {};
        ~ServiceCharge() {};
        const Date &getDate() const { return itsDate; };
        double getAmount() const { return itsAmount; };
    private:
        Date itsDate;
        double itsAmount;
};

#endif
