#ifndef _ADDEMPLOYEETRANSACTION_H_
#define _ADDEMPLOYEETRANSACTION_H_

#include <string>
#include "Transaction.h"
#include "PaymentClassification.h"
#include "PaymentSchedule.h"
#include "PaymentMethod.h"

class AddEmployeeTransaction : public Transaction 
{
    public:
        AddEmployeeTransaction(int empId, std::string name, std::string address);
        virtual ~AddEmployeeTransaction();
        virtual PaymentClassification *getPaymentClassification() = 0;
        virtual PaymentSchedule *getPaymentSchedule() = 0;
        virtual PaymentMethod *getPaymentMethod() = 0;
        void execute() override;
    private:
        int itsEmpId;
        std::string itsName;
        std::string itsAddress;
};

#endif
