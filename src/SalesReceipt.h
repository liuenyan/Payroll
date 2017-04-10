#ifndef _SALESRECEIPT_H_
#define _SALESRECEIPT_H_

#include "Date.h"

class SalesReceipt
{
    public:
        SalesReceipt(Date date, int amount);
        const Date &getDate() const { return itsDate; };
        int getAmount() const { return itsAmount; };
    private:
        Date itsDate;
        int itsAmount;
};

#endif
