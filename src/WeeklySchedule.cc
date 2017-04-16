#include "WeeklySchedule.h"

bool WeeklySchedule::isPayDate(const Date &date) const
{
    return date.day_of_week() == WeekdayEnum::Friday;
}


Date WeeklySchedule::getPayPeriodStartDate(const Date &payPeriodEndDate) const
{
    return Date(payPeriodEndDate - DateDuration(5));
}
