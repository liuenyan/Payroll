#ifndef _COMMISSIONEDCLASSFICATION_H_
#define _COMMISSIONEDCLASSFICATION_H_

#include "PaymentClassification.h"

class CommissionedClassification : public PaymentClassification
{
    public:
        CommissionedClassification(double salary, double commissionRate)
            : itsSalary(salary), itsCommissionRate(commissionRate)
        {};

        virtual ~CommissionedClassification() {};
        double getSalary() const { return itsSalary; };
        double getCommissionRate() const { return itsCommissionRate; };
    private:
        double itsSalary;
        double itsCommissionRate;
};

#endif
