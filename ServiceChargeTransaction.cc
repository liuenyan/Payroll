#include "ServiceChargeTransaction.h"
#include "PayrollDatabase.h"
#include "UnionAffiliation.h"

ServiceChargeTransaction::ServiceChargeTransaction(
        int memberId, Date &date, double amount) 
    : itsMemberId(memberId), itsDate(date), itsAmount(amount)
{

}

ServiceChargeTransaction::~ServiceChargeTransaction()
{

}

void ServiceChargeTransaction::execute()
{
    Employee *e = gPayrollDatabase.getUnionMember(itsMemberId);
    
    Affiliation *af = e->getAffiliation();
    UnionAffiliation *uaf = dynamic_cast<UnionAffiliation *>(af);
    if(uaf) {
        uaf->addServiceCharge(itsDate, itsAmount);
    }
}
