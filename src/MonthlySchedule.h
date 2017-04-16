#ifndef _MONTHLYSCHEDULE_H_
#define _MONTHLYSCHEDULE_H_

#include "PaymentSchedule.h"

class MonthlySchedule : public PaymentSchedule
{
    public:
        virtual ~MonthlySchedule() {};
        bool isPayDate(const Date &date) const override;
        Date getPayPeriodStartDate(const Date &payPeriodEndDate) const override;
};

#endif
