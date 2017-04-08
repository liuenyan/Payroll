#ifndef _ADDCOMMISSIONEDEMPLOYEE_H_
#define _ADDCOMMISSIONEDEMPLOYEE_H_

#include "AddEmployeeTransaction.h"

class AddCommissionedEmployee : public AddEmployeeTransaction
{
    public:
        AddCommissionedEmployee(
                int empId,
                const std::string &name, 
                const std::string &address, 
                double salary, 
                double commissionRate);

        virtual ~AddCommissionedEmployee();
        PaymentClassification *getPaymentClassification() override;
        PaymentSchedule *getPaymentSchedule() override;
    private:
        double itsSalary;
        double itsCommissionRate;
};

#endif
