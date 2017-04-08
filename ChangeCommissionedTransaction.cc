#include "ChangeCommissionedTransaction.h"
#include "CommissionedClassification.h"
#include "BiweeklySchedule.h"

ChangeCommissionedTransaction::ChangeCommissionedTransaction(
        int empId, double salary, double commissionRate)
    : ChangeClassificationTransaction(empId)
    , itsSalary(salary)
    , itsCommissionRate(commissionRate)
{

}

ChangeCommissionedTransaction::~ChangeCommissionedTransaction()
{

}

PaymentClassification *ChangeCommissionedTransaction::getClassification() const
{
    return new CommissionedClassification(itsSalary, itsCommissionRate);
}

PaymentSchedule *ChangeCommissionedTransaction::getSchedule() const
{
    return new BiweeklySchedule();
}