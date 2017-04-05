#include "AddCommissionedEmployee.h"
#include "CommissionedClassification.h"
#include "BiweeklySchedule.h"
#include "HoldMethod.h"

using namespace std;

AddCommissionedEmployee::AddCommissionedEmployee(
        int empId, 
        string name, 
        string address, 
        double salary, 
        double commissionRate)
    : AddEmployeeTransaction(empId, name, address)
    , itsSalary(salary)
    , itsCommissionRate(commissionRate)
{

}

AddCommissionedEmployee::~AddCommissionedEmployee()
{

}

PaymentClassification *AddCommissionedEmployee::getPaymentClassification()
{
    return new CommissionedClassification(itsSalary, itsCommissionRate);
}

PaymentSchedule *AddCommissionedEmployee::getPaymentSchedule()
{
    return new BiweeklySchedule();
}

PaymentMethod *AddCommissionedEmployee::getPaymentMethod()
{
    return new HoldMethod();
}

