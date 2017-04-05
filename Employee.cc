#include "Employee.h"

using namespace std;

Employee::Employee(int empId, string name, string address)
    : itsEmpId(empId), itsName(name), itsAddress(address)
{

}

Employee::~Employee()
{

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

