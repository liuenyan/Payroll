#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_

#include <string>
#include "PaymentClassification.h"
#include "PaymentSchedule.h"
#include "PaymentMethod.h"
#include "Affiliation.h"

class Employee 
{
    public:
        Employee(int empId, const std::string &name, const std::string &address);
        ~Employee();
        void setName(std::string &name);
        void setAddress(std::string &address);
        void setClassification(PaymentClassification *pc);
        void setSchedule(PaymentSchedule *ps);
        void setMethod(PaymentMethod *pm);
        void setAffiliation(Affiliation *af);
        const std::string &getName() const { return itsName; };
        const std::string &getAddress() const { return itsAddress; };
        PaymentClassification *getClassification() const { return itsClassification; };
        PaymentSchedule *getSchedule() const { return itsSchedule; };
        PaymentMethod *getMethod() const { return itsMethod; };
        Affiliation *getAffiliation() const { return itsAffiliation; };
    private:
        int itsEmpId;
        std::string itsName;
        std::string itsAddress;
        PaymentClassification *itsClassification;
        PaymentSchedule *itsSchedule;
        PaymentMethod *itsMethod;
        Affiliation *itsAffiliation;
};

#endif
