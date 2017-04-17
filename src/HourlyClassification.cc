#include "HourlyClassification.h"
#include <algorithm>

using namespace std;


HourlyClassification::HourlyClassification(double hourlyRate)
    : itsHourlyRate(hourlyRate)
{

}

HourlyClassification::~HourlyClassification()
{
    for(auto &pair : itsTimeCards) {
        delete pair.second;
    }
}

void HourlyClassification::addTimeCard(TimeCard *tc)
{
    itsTimeCards[tc->getDate()] = tc;
}

TimeCard *HourlyClassification::getTimeCard(Date date)
{
    return itsTimeCards[date];
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
    for(auto pair : itsTimeCards) {
        if(isInPayPeriod(pair.first, pc.getPayPeriodStartDate(), pc.getPayPeriodEndDate())) {
            grossPay += calculatePayForTimeCard(pair.second);
        }
    }
    return grossPay;
}
