#ifndef _CHANGEUNAFFILIATEDTRANSACTION_H_
#define _CHANGEUNAFFILIATEDTRANSACTION_H_

#include "ChangeAffiliationTransaction.h"

class ChangeUnaffiliatedTransaction : public ChangeAffiliationTransaction
{
    public:
        ChangeUnaffiliatedTransaction(int empId);
        ~ChangeUnaffiliatedTransaction();
        void recordMembership(Employee *e) const override;
        Affiliation *getAffiliation() const override;
};

#endif
