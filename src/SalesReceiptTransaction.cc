#include "SalesReceiptTransaction.h"
#include "PayrollDatabase.h"
#include "CommissionedClassification.h"
#include "SalesReceipt.h"

SalesReceiptTransaction::SalesReceiptTransaction(
        Date date, double amount, int empId)
    : itsDate(date), itsAmount(amount), itsEmpId(empId)
{

}


SalesReceiptTransaction::~SalesReceiptTransaction()
{

}

void SalesReceiptTransaction::execute()
{
    Employee *e = gPayrollDatabase.getEmployee(itsEmpId);
    if(!e) {
        throw("No such employee");
    }
    PaymentClassification *pc = e->getClassification();
    CommissionedClassification *cc = 
        dynamic_cast<CommissionedClassification *>(pc);

    if(!cc) {
        throw("Tried to add sales receipt to non-commissioned employee");
    }

    SalesReceipt *sr = new SalesReceipt(itsDate, itsAmount);
    cc->addSalesReceipt(sr);
}

