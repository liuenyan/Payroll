#include "ChangeNameTransaction.h"

using namespace std;

ChangeNameTransaction::ChangeNameTransaction(int empId, const string &name)
    : ChangeEmployeeTransaction(empId), itsName(name)
{

}

ChangeNameTransaction::~ChangeNameTransaction()
{

}

void ChangeNameTransaction::change(Employee &e)
{
    e.setName(itsName); 
}

