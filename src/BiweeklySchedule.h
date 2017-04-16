#ifndef _BIWEEKLYSCHEDULE_H_
#define _BIWEEKLYSCHEDULE_H_

#include "PaymentSchedule.h"

class BiweeklySchedule : public PaymentSchedule
{
    public:
        virtual ~BiweeklySchedule() {};
        bool isPayDate(const Date &date) const override;
        Date getPayPeriodStartDate(const Date &payPeriodEndDate) const override;
};

#endif
