#include "PayrollDatabase.h"

PayrollDatabase gPayrollDatabase;

PayrollDatabase::~PayrollDatabase() 
{

}

Employee *PayrollDatabase::getEmployee(int empId)
{
    return itsEmployees[empId];
}

void PayrollDatabase::addEmployee(int empId, Employee *e)
{
    itsEmployees[empId] = e;
}

void PayrollDatabase::deleteEmployee(int empId)
{
    itsEmployees.erase(empId);
}
