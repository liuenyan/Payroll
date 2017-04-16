#include "MonthlySchedule.h"

namespace {
    bool isLastDayOfMonth(const Date &date) 
    {
        int m1 = date.month();
        int m2 = (date+DateDuration(1)).month();
        return m1 != m2;
    }
};

bool MonthlySchedule::isPayDate(const Date &date) const
{
    return isLastDayOfMonth(date);
}

Date MonthlySchedule::getPayPeriodStartDate(const Date &payPeriodEndDate) const
{
    return Date(payPeriodEndDate.year(), payPeriodEndDate.month(), 1);
}
