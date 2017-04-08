#include "ChangeSalariedTransaction.h"
#include "SalariedClassification.h"
#include "MonthlySchedule.h"

ChangeSalariedTransaction::ChangeSalariedTransaction(int empId, double salary)
    : ChangeClassificationTransaction(empId), itsSalary(salary)
{

}

ChangeSalariedTransaction::~ChangeSalariedTransaction()
{

}

PaymentClassification *ChangeSalariedTransaction::getClassification() const
{
    return new SalariedClassification(itsSalary);
}

PaymentSchedule *ChangeSalariedTransaction::getSchedule() const
{
    return new MonthlySchedule();
}
