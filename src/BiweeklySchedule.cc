#include "BiweeklySchedule.h"

bool BiweeklySchedule::isPayDate(const Date &date) const
{
    Date first_pay_date(2017, 3, 31);
    DateDuration duration = date - first_pay_date;

    if ( duration.days() % 14 == 0)
        return true;
    else
        return false;
}


Date BiweeklySchedule::getPayPeriodStartDate(const Date &payPeriodEndDate) const
{
    return Date(payPeriodEndDate - DateDuration(13));
}
