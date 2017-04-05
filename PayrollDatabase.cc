#include "PayrollDatabase.h"

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

