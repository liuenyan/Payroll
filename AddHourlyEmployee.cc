#include "AddHourlyEmployee.h"
#include "HourlyClassification.h"
#include "WeeklySchedule.h"
#include "HoldMethod.h"

using namespace std;

AddHourlyEmployee::AddHourlyEmployee(
        int empId, string name, string address, double hourlyRate)
    : AddEmployeeTransaction(empId, name, address), itsHourlyRate(hourlyRate)
{

}

AddHourlyEmployee::~AddHourlyEmployee()
{

}

PaymentClassification *AddHourlyEmployee::getPaymentClassification()
{
    return new HourlyClassification(itsHourlyRate);
} 
 
PaymentSchedule *AddHourlyEmployee::getPaymentSchedule() 
{
    return new WeeklySchedule();
}

PaymentMethod *AddHourlyEmployee::getPaymentMethod()
{
    return new HoldMethod();
}

