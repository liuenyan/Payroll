#include "ChangeUnaffiliatedTransaction.h"
#include "PayrollDatabase.h"
#include "UnionAffiliation.h"
#include "NoAffiliation.h"

ChangeUnaffiliatedTransaction::ChangeUnaffiliatedTransaction(int empId)
    : ChangeAffiliationTransaction(empId)
{

}

ChangeUnaffiliatedTransaction::~ChangeUnaffiliatedTransaction()
{
    
}

void ChangeUnaffiliatedTransaction::recordMembership(Employee *e) const
{
    Affiliation *af = e->getAffiliation();
    UnionAffiliation *uaf = dynamic_cast<UnionAffiliation *>(af);
    if(uaf) {
        gPayrollDatabase.removeUnionMember(uaf->getMemberId());
    }
}

Affiliation *ChangeUnaffiliatedTransaction::getAffiliation() const
{
    return new NoAffiliation();
}
