#include "ChangeMethodTransaction.h"

ChangeMethodTransaction::ChangeMethodTransaction(int empId)
    : ChangeEmployeeTransaction(empId)
{
    
}

ChangeMethodTransaction::~ChangeMethodTransaction()
{

}
void ChangeMethodTransaction::change(Employee &e)
{
    e.setMethod(getPaymentMethod());
}
