#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_

#include <string>
#include "PaymentClassification.h"
#include "PaymentSchedule.h"
#include "PaymentMethod.h"

class Employee 
{
    public:
        Employee(int empId, std::string name, std::string address);
        ~Employee();
        void setClassification(PaymentClassification *pc);
        void setSchedule(PaymentSchedule *ps);
        void setMethod(PaymentMethod *pm);
        const std::string &getName() const { return itsName; };
        const std::string &getAddress() const { return itsAddress; };
        PaymentClassification *getClassification() const { return itsClassification; };
        PaymentSchedule *getSchedule() const { return itsSchedule; };
        PaymentMethod *getMethod() const { return itsMethod; };
    private:
        int itsEmpId;
        std::string itsName;
        std::string itsAddress;
        PaymentClassification *itsClassification;
        PaymentSchedule *itsSchedule;
        PaymentMethod *itsMethod;
};

#endif
