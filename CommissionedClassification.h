#ifndef _COMMISSIONEDCLASSFICATION_H_
#define _COMMISSIONEDCLASSFICATION_H_

#include <vector>
#include "PaymentClassification.h"
#include "SalesReceipt.h"

class CommissionedClassification : public PaymentClassification
{
    public:
        CommissionedClassification(double salary, double commissionRate);
        virtual ~CommissionedClassification();
        double calculatePay(Paycheck &pc) const override;
        double getSalary() const { return itsSalary; };
        double getCommissionRate() const { return itsCommissionRate; };
        void addSalesReceipt(SalesReceipt *sc);
        SalesReceipt *getSalesReceipt(Date &date);
    private:
        double itsSalary;
        double itsCommissionRate;
        std::vector<SalesReceipt *> itsSalesReceipts;
};

#endif
