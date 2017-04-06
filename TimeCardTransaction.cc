#include "TimeCardTransaction.h"
#include "PayrollDatabase.h"
#include "TimeCard.h"
#include "HourlyClassification.h"

TimeCardTransaction::TimeCardTransaction(Date date, double hours, int empId)
    : itsDate(date), itsHours(hours), itsEmpId(empId)
{

}


TimeCardTransaction::~TimeCardTransaction()
{

}

void TimeCardTransaction::execute()
{
    TimeCard *tc = new TimeCard(itsDate, itsHours);
    Employee *e = gPayrollDatabase.getEmployee(itsEmpId);
    if(!e) {
        throw("No such employee.");
    }

    PaymentClassification *c = e->getClassification();
    HourlyClassification *hc = dynamic_cast<HourlyClassification *>(c);
    if(!hc) {
        throw("Tried to add timecard to non-hourly employee");
    }
    hc->addTimeCard(tc);
}

