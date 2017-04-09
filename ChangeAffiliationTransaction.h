#ifndef _CHANGEAFFICATIONTRANSACTION_H_
#define _CHANGEAFFICATIONTRANSACTION_H_

#include "ChangeEmployeeTransaction.h"
#include "Affiliation.h"

class ChangeAffiliationTransaction : public ChangeEmployeeTransaction
{
    public:
        ChangeAffiliationTransaction(int empId);
        virtual ~ChangeAffiliationTransaction();
        void change(Employee &e) override;
        virtual void recordMembership(Employee *e) const = 0;
        virtual Affiliation *getAffiliation() const = 0;
};

#endif
