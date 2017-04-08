#include "ChangeHourlyTransaction.h"
#include "HourlyClassification.h"
#include "WeeklySchedule.h"

ChangeHourlyTransaction::ChangeHourlyTransaction(int empId, double hourlyRate)
    : ChangeClassificationTransaction(empId), itsHourlyRate(hourlyRate)
{

}

ChangeHourlyTransaction::~ChangeHourlyTransaction()
{

}

PaymentClassification *ChangeHourlyTransaction::getClassification() const
{
    return new HourlyClassification(itsHourlyRate);
}

PaymentSchedule *ChangeHourlyTransaction::getSchedule() const
{
    return new WeeklySchedule();
}