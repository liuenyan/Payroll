#include <algorithm>
#include "CommissionedClassification.h"

using namespace std;

CommissionedClassification::CommissionedClassification(
        double salary, double commissionRate)
        : itsSalary(salary), itsCommissionRate(commissionRate)
{

}

CommissionedClassification::~CommissionedClassification() 
{
    for(auto &pair : itsSalesReceipts) {
        delete pair.second;
    }
}


void CommissionedClassification::addSalesReceipt(SalesReceipt *sc)
{
    itsSalesReceipts[sc->getDate()] = sc;
}

SalesReceipt *CommissionedClassification::getSalesReceipt(Date &date)
{
    return itsSalesReceipts[date];
}

double CommissionedClassification::calculatePay(Paycheck &pc) const
{
    double pay = itsSalary;
    for (auto it = itsSalesReceipts.begin(); it != itsSalesReceipts.end(); ++it)
    {
        if(isInPayPeriod(it->first, pc.getPayPeriodStartDate(), pc.getPayPeriodEndDate())) {
            pay += itsCommissionRate * it->second->getAmount();
        }
    }
    return pay;
}
