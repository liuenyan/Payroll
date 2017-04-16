#ifndef _WEEKLYSCHEDULE_H_
#define _WEEKLYSCHEDULE_H_

#include "PaymentSchedule.h"

class WeeklySchedule : public PaymentSchedule
{
    public:
        virtual ~WeeklySchedule() {};
        bool isPayDate(const Date &date) const override;
        Date getPayPeriodStartDate(const Date &payPeriodEndDate) const override;
};

#endif
