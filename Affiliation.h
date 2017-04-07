#ifndef _AFFILIATION_H_
#define _AFFILIATION_H_

#include <vector>
#include "ServiceCharge.h"

class Affiliation 
{
    public:
        Affiliation(int memberId) : itsMemberId(memberId) {};
        virtual ~Affiliation() = 0;
        int getMemberId() const { return itsMemberId; };
    private:
        int itsMemberId;
};

inline Affiliation::~Affiliation() {};

#endif
