#include "Employee.h"

using namespace std;

Employee::Employee(int empId, const string &name, const string &address)
    : itsEmpId(empId), itsName(name), itsAddress(address)
    , itsAffiliation(nullptr)
{

}

Employee::~Employee()
{

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
    itsClassification = pc;
}

void Employee::setSchedule(PaymentSchedule *ps)
{
    itsSchedule = ps;
}

void Employee::setMethod(PaymentMethod *pm)
{
    itsMethod = pm;
}

void Employee::setAffiliation(Affiliation *af)
{
    itsAffiliation = af;
}

