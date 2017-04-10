#include "ChangeMailMethodTransaction.h"
#include "MailMethod.h"

using namespace std;

ChangeMailMethodTransaction::ChangeMailMethodTransaction(
    int empId, const string &address)
    : ChangeMethodTransaction(empId), itsAddress(address)
{
    
}

ChangeMailMethodTransaction::~ChangeMailMethodTransaction()
{

}

PaymentMethod *ChangeMailMethodTransaction::getPaymentMethod() const
{
    return new MailMethod(itsAddress);
}
