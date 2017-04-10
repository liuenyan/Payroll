#include "ChangeHoldMethodTransaction.h"
#include "HoldMethod.h"

ChangeHoldMethodTransaction::ChangeHoldMethodTransaction(int empId)
    : ChangeMethodTransaction(empId)
{
    
}

ChangeHoldMethodTransaction::~ChangeHoldMethodTransaction()
{

}

PaymentMethod *ChangeHoldMethodTransaction::getPaymentMethod() const
{
    return new HoldMethod();
}
