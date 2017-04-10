#include "ChangeDirectMethodTransaction.h"
#include "DirectMethod.h"

using namespace std;

ChangeDirectMethodTransaction::ChangeDirectMethodTransaction(
    int empId, const string &bank, const string &account)
    : ChangeMethodTransaction(empId), itsBank(bank), itsAccount(account)
{
    
}

ChangeDirectMethodTransaction::~ChangeDirectMethodTransaction()
{

}

PaymentMethod *ChangeDirectMethodTransaction::getPaymentMethod() const
{
    return new DirectMethod(itsBank, itsAccount);
}
