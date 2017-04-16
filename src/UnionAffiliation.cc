#include <algorithm>
#include "UnionAffiliation.h"
#include "ServiceCharge.h"

using namespace std;

namespace {
    int getPayPeriodFridays(const Date &beginDate, const Date &endDate)
    {

        int fridays = 0;

        for(DayIterator it(beginDate); (*it) <= endDate; ++it) {
            if(it->day_of_week() == WeekdayEnum::Friday) {
                fridays++;
            }
        }
        return fridays;
    }
}

UnionAffiliation::UnionAffiliation(int memberId, double dues) 
    : itsMemberId(memberId), itsDues(dues) 
{

}

UnionAffiliation::~UnionAffiliation() 
{
    for(auto serviceCharge : itsServiceCharges) {
        delete serviceCharge; 
    }
}

void UnionAffiliation::addServiceCharge(Date date, double charge)
{
    ServiceCharge *sc = new ServiceCharge(date, charge);
    itsServiceCharges.push_back(sc);
}

ServiceCharge *UnionAffiliation::getServiceCharge(Date date)
{ 
    vector<ServiceCharge *>::iterator it = 
        find_if(itsServiceCharges.begin(),
                itsServiceCharges.end(), 
                [&date] (ServiceCharge *sc) ->bool { return sc->getDate() == date; }
                );
    if (it != itsServiceCharges.end())
        return *it;
    return nullptr;
}

double UnionAffiliation::calculateDeductions(Paycheck &pc) const 
{
    double deductions =  getPayPeriodFridays(pc.getPayPeriodStartDate(), pc.getPayPeriodEndDate()) * itsDues;

    for(auto it = itsServiceCharges.begin(); it!=itsServiceCharges.end(); ++it) {
        if(isBetween((*it)->getDate(), pc.getPayPeriodStartDate(), pc.getPayPeriodEndDate())) {
            deductions += (*it)->getAmount(); 
        }
    }

    return deductions;
}
