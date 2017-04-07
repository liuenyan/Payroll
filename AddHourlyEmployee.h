#ifndef _ADDHOURLYEMPLOYEE_H_
#define _ADDHOURLYEMPLOYEE_H_

#include "AddEmployeeTransaction.h"

class AddHourlyEmployee : public AddEmployeeTransaction
{
    public:
        AddHourlyEmployee(
                int empId, 
                const std::string &name, 
                const std::string &address, 
                double hourlyRate);

        virtual ~AddHourlyEmployee();
        PaymentClassification *getPaymentClassification() override;
        PaymentSchedule *getPaymentSchedule() override;
        PaymentMethod *getPaymentMethod() override;
    private:
        double itsHourlyRate;
};

#endif
