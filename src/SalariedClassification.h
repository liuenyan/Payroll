#ifndef _SALARIEDCLASSIFICATION_H_
#define _SALARIEDCLASSIFICATION_H_

#include "PaymentClassification.h"

class SalariedClassification : public PaymentClassification 
{
    public:
        SalariedClassification(double salary) : itsSalary(salary){};
        virtual ~SalariedClassification() {};
        double calculatePay(Paycheck &pc) const override;
        double getSalary() const { return itsSalary; };
    private:
        double itsSalary;
};

#endif
