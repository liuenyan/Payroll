#include "AddEmployeeTransaction.h"
#include "Employee.h"
#include "PayrollDatabase.h"
#include "HoldMethod.h"

using namespace std;

extern PayrollDatabase gPayrollDatabase;

AddEmployeeTransaction::AddEmployeeTransaction(
        int empId, const string &name, const string &address)
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
    PaymentMethod *pm = new HoldMethod();

    Employee *e = new Employee(itsEmpId, itsName, itsAddress);
    e->setClassification(pc);
    e->setSchedule(ps);
    e->setMethod(pm);
    gPayrollDatabase.addEmployee(itsEmpId, e);
}

