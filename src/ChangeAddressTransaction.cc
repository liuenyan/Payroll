#include "ChangeAddressTransaction.h"

ChangeAddressTransaction::ChangeAddressTransaction(
        int empId, const std::string &address)
    : ChangeEmployeeTransaction(empId)
    , itsAddress(address)
{

}

ChangeAddressTransaction::~ChangeAddressTransaction()
{

}

void ChangeAddressTransaction::change(Employee &e)
{
    e.setAddress(itsAddress);
}
