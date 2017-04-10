#include "ChangeClassificationTransaction.h"

ChangeClassificationTransaction::ChangeClassificationTransaction(int empId)
    : ChangeEmployeeTransaction(empId)
{

}

ChangeClassificationTransaction::~ChangeClassificationTransaction()
{

}

void ChangeClassificationTransaction::change(Employee &e)
{
    e.setClassification(getClassification());
    e.setSchedule(getSchedule());
}
