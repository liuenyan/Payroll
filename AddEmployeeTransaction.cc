#include "AddEmployeeTransaction.h"
#include "Employee.h"
#include "PayrollDatabase.h"

using namespace std;

extern PayrollDatabase gPayrollDatabase;

AddEmployeeTransaction::AddEmployeeTransaction(
        int empId, string name, string address)
    : itsEmpId(empId), itsName(name), itsAddress(address)
{

}

AddEmployeeTransaction::~AddEmployeeTransaction() 
{

}

void AddEmployeeTransaction::execute()
{
    PaymentClassification *pc = getPaymentClassification();
    PaymentSchedule *ps = getPaymentSchedule();
    PaymentMethod *pm = getPaymentMethod();

    Employee *e = new Employee(itsEmpId, itsName, itsAddress);
    e->setClassification(pc);
    e->setSchedule(ps);
    e->setMethod(pm);
    gPayrollDatabase.addEmployee(itsEmpId, e);
}

