#include "ChangeMemberTransaction.h"
#include "PayrollDatabase.h"
#include "UnionAffiliation.h"

ChangeMemberTransaction::ChangeMemberTransaction(int empId, int memberId, double dues)
    : ChangeAffiliationTransaction(empId), itsMemberId(memberId), itsDues(dues)
{
    
}

ChangeMemberTransaction::~ChangeMemberTransaction()
{
    
}

void ChangeMemberTransaction::recordMembership(Employee *e) const
{
    gPayrollDatabase.addUnionMember(itsMemberId, e);
}

Affiliation *ChangeMemberTransaction::getAffiliation() const
{
    return new UnionAffiliation(itsMemberId, itsDues);
}
