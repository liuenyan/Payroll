#include "AddSalariedEmployee.h"
#include "SalariedClassification.h"
#include "MonthlySchedule.h"
#include "HoldMethod.h"

AddSalariedEmployee::AddSalariedEmployee(
        int empId, std::string name, std::string address, double salary)
    : AddEmployeeTransaction(empId, name, address), itsSalary(salary)
{

}

AddSalariedEmployee::~AddSalariedEmployee()
{

}

PaymentClassification *AddSalariedEmployee::getPaymentClassification()
{
    return new SalariedClassification(itsSalary);
}

PaymentSchedule *AddSalariedEmployee::getPaymentSchedule()
{
    return new MonthlySchedule();
}

PaymentMethod *AddSalariedEmployee::getPaymentMethod()
{
    return new HoldMethod();
}

