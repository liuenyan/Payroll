#ifndef _ADDCOMMISSIONEDEMPLOYEE_H_
#define _ADDCOMMISSIONEDEMPLOYEE_H_

#include "AddEmployeeTransaction.h"

class AddCommissionedEmployee : public AddEmployeeTransaction
{
    public:
        AddCommissionedEmployee(
                int empId, 
                std::string name, 
                std::string address, 
                double salary, 
                double commissionRate);

        virtual ~AddCommissionedEmployee();
        PaymentClassification *getPaymentClassification() override;
        PaymentSchedule *getPaymentSchedule() override;
        PaymentMethod *getPaymentMethod() override;
    private:
        double itsSalary;
        double itsCommissionRate;
};

#endif
