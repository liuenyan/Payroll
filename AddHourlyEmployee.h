#ifndef _ADDHOURLYEMPLOYEE_H_
#define _ADDhOURLYeMPLOYEE_H_

#include "AddEmployeeTransaction.h"

class AddHourlyEmployee : public AddEmployeeTransaction
{
    public:
        AddHourlyEmployee(
                int empId, 
                std::string name, 
                std::string address, 
                double hourlyRate);

        virtual ~AddHourlyEmployee();
        PaymentClassification *getPaymentClassification() override;
        PaymentSchedule *getPaymentSchedule() override;
        PaymentMethod *getPaymentMethod() override;
    private:
        double itsHourlyRate;
};

#endif
