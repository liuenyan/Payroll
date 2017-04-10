#ifndef _AFFILIATION_H_
#define _AFFILIATION_H_

#include "Paycheck.h"

class Affiliation 
{
    public:
        virtual ~Affiliation() = 0;
        virtual double calculateDeductions(Paycheck &pc) const = 0;
};

inline Affiliation::~Affiliation() {};

#endif
