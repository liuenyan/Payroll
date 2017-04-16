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
    for(auto salesReceipt : itsSalesReceipts) {
        delete salesReceipt;
    }
}


void CommissionedClassification::addSalesReceipt(SalesReceipt *sc)
{
    itsSalesReceipts.push_back(sc);
}

SalesReceipt *CommissionedClassification::getSalesReceipt(Date &date)
{
    vector<SalesReceipt *>::iterator it = 
        find_if(itsSalesReceipts.begin(), itsSalesReceipts.end(),
                [&date] (SalesReceipt *sc) { return sc->getDate() == date; });

    if(it != itsSalesReceipts.end())
        return *it;
    return nullptr;
}

double CommissionedClassification::calculatePay(Paycheck &pc) const
{
    double pay = itsSalary;
    for (auto it = itsSalesReceipts.begin(); it != itsSalesReceipts.end(); ++it)
    {
        if(isInPayPeriod((*it)->getDate(), pc.getPayPeriodStartDate(), pc.getPayPeriodEndDate())) {
            pay += itsCommissionRate * (*it)->getAmount();
        }
    }
    return pay;
}
