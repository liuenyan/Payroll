#include "ChangeEmployeeTransaction.h"
#include "PayrollDatabase.h"

ChangeEmployeeTransaction::ChangeEmployeeTransaction(int empId)
    : itsEmpId(empId)
{

}

ChangeEmployeeTransaction::~ChangeEmployeeTransaction()
{

}

void ChangeEmployeeTransaction::execute()
{
    Employee *e = gPayrollDatabase.getEmployee(itsEmpId); 
    if(e) {
        change(*e);
    }
}
