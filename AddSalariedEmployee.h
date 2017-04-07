#ifndef _ADDSALARIEDEMPLOYEE_H_
#define _ADDSALARIEDEMPLOYEE_H_

#include "AddEmployeeTransaction.h"

class AddSalariedEmployee : public AddEmployeeTransaction
{
    public:
        AddSalariedEmployee(
                int empId, 
                const std::string &name, 
                const std::string &address, 
                double salary);
        virtual ~AddSalariedEmployee();
        PaymentClassification *getPaymentClassification() override;
        PaymentSchedule *getPaymentSchedule() override;
        PaymentMethod *getPaymentMethod() override;
    private:
        double itsSalary;
};

#endif
