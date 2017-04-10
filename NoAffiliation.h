#ifndef _NOAFFILIATION_H_
#define _NOAFFILIATION_H_

#include "Affiliation.h"

class NoAffiliation : public Affiliation
{
    public:
        NoAffiliation() {};
        virtual ~NoAffiliation() {};
        double calculateDeductions(Paycheck &pc) const override { return 0.0; };
};

#endif
