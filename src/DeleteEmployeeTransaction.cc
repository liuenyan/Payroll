#include "DeleteEmployeeTransaction.h"
#include "PayrollDatabase.h"

DeleteEmployeeTransaction::DeleteEmployeeTransaction(int empId)
    : itsEmpId(empId)
{
}

DeleteEmployeeTransaction::~DeleteEmployeeTransaction()
{
}


void DeleteEmployeeTransaction::execute()
{
    gPayrollDatabase.deleteEmployee(itsEmpId);
}

