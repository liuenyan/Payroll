#ifndef _CHANGEMEMBERTRANSACTION_H_
#define _CHANGEMEMBERTRANSACTION_H_

#include "ChangeAffiliationTransaction.h"

class ChangeMemberTransaction : public ChangeAffiliationTransaction
{
    public:
        ChangeMemberTransaction(int empId, int memberId, double dues);
        ~ChangeMemberTransaction();
        void recordMembership(Employee *e) const override;
        Affiliation *getAffiliation() const override;
    private:
        int itsMemberId;
        double itsDues;
};

#endif
