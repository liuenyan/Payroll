#include "ChangeAffiliationTransaction.h"


ChangeAffiliationTransaction::ChangeAffiliationTransaction(int empId)
    : ChangeEmployeeTransaction(empId)
{
    
}

ChangeAffiliationTransaction::~ChangeAffiliationTransaction()
{

}

void ChangeAffiliationTransaction::change(Employee &e)
{
    recordMembership(&e);
    e.setAffiliation(getAffiliation());
}
