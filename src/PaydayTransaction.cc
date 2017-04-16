#include <list>
#include "PaydayTransaction.h"
#include "PayrollDatabase.h"

using namespace std;

PaydayTransaction::PaydayTransaction(const Date &payDate)
    : itsPayDate(payDate)
{

}

PaydayTransaction::~PaydayTransaction()
{
    for(auto it=itsPaychecks.begin(); it != itsPaychecks.end(); ++it) {
        delete it->second;
    }
}

void PaydayTransaction::execute()
{
    list<int> empIds;
    gPayrollDatabase.getAllEmployeeIds(empIds);
    
    for(int empId : empIds) {
        Employee *e = gPayrollDatabase.getEmployee(empId);
        if(e && e->isPayDate(itsPayDate)) {
            Paycheck *pc = new Paycheck(e->getPayPeriodStartDate(itsPayDate), itsPayDate);
            itsPaychecks[empId] = pc;
            e->payDay(*pc);
        }
    }
}

Paycheck *PaydayTransaction::getPaycheck(int empId) const
{
    auto it = itsPaychecks.find(empId);
    if (it != itsPaychecks.end()) 
        return it->second;
    return nullptr;
}
