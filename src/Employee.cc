#include "Employee.h"

using namespace std;

Employee::Employee(int empId, const string &name, const string &address)
    : itsEmpId(empId)
    , itsName(name)
    , itsAddress(address)
    , itsClassification(nullptr)
    , itsSchedule(nullptr)
    , itsMethod(nullptr)
    , itsAffiliation(nullptr)
{

}

Employee::~Employee()
{
    delete itsClassification;
    delete itsSchedule;
    delete itsMethod;
    delete itsAffiliation;
}

void Employee::setName(std::string &name)
{
    itsName = name;
}

void Employee::setAddress(string &address)
{
    itsAddress = address;
}

void Employee::setClassification(PaymentClassification *pc)
{
    delete itsClassification;
    itsClassification = pc;
}

void Employee::setSchedule(PaymentSchedule *ps)
{
    delete itsSchedule;
    itsSchedule = ps;
}

void Employee::setMethod(PaymentMethod *pm)
{
    delete itsMethod;
    itsMethod = pm;
}

void Employee::setAffiliation(Affiliation *af)
{
    delete itsAffiliation;
    itsAffiliation = af;
}

bool Employee::isPayDate(const Date &date) const
{
    return  itsSchedule->isPayDate(date);
}

Date Employee::getPayPeriodStartDate(const Date &payPeriodEndDate) const
{
    return itsSchedule->getPayPeriodStartDate(payPeriodEndDate);
}

void Employee::payDay(Paycheck &pc)
{
    double grossPay = itsClassification->calculatePay(pc);
    double deductions = itsAffiliation->calculateDeductions(pc);
    double netPay = grossPay - deductions;

    pc.setGrossPay(grossPay);
    pc.setDeductions(deductions);
    pc.setNetPay(netPay);

    itsMethod->pay(pc);
}
