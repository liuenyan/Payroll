#include "HourlyClassification.h"
#include <algorithm>

using namespace std;


HourlyClassification::HourlyClassification(double hourlyRate)
    : itsHourlyRate(hourlyRate)
{

}

HourlyClassification::~HourlyClassification()
{
    for(auto tc : itsTimeCards) {
        delete tc;
    }
}

void HourlyClassification::addTimeCard(TimeCard *tc)
{
    itsTimeCards.push_back(tc);
}

TimeCard *HourlyClassification::getTimeCard(Date date)
{
    vector<TimeCard *>::iterator it = 
        find_if(itsTimeCards.begin(),
                itsTimeCards.end(), 
                [&date] (TimeCard *tc) ->bool { return tc->getDate() == date; }
                );
    if (it != itsTimeCards.end())
        return *it;
    return nullptr;
}

bool HourlyClassification::isInPayPeriod(TimeCard *tc, const Date &period) const
{
    Date payPeriodStartDate = period - DateDuration(5);
    Date payPeriodEndDate = period;
    return payPeriodStartDate <= tc->getDate() && tc->getDate() <= payPeriodEndDate;
}

double HourlyClassification::calculatePayForTimeCard(TimeCard *tc) const
{
    double hours = tc->getHours();
    double overtime = max(0.0, hours - 8.0);
    double straighttime = hours -overtime;
    return straighttime * itsHourlyRate + overtime * itsHourlyRate * 1.5;
}

double HourlyClassification::calculatePay(Paycheck &pc) const
{
    double grossPay = 0.0;
    for(auto tc : itsTimeCards) {
        if(isInPayPeriod(tc, pc.getPayDate())) {
            grossPay += calculatePayForTimeCard(tc);
        }
    }
    return grossPay;
}
