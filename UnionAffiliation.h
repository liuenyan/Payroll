#ifndef _UNIONAFFILIATION_H_
#define _UNIONAFFILIATION_H_ 

#include "Affiliation.h"
#include "Date.h"

class UnionAffiliation : public Affiliation
{
    public:
        UnionAffiliation(int memberId, double dues);
        virtual ~UnionAffiliation();
        double getDues() const { return itsDues; };
        void addServiceCharge(Date date, double charge);
        ServiceCharge *getServiceCharge(Date date);
    private:
        double itsDues;
        std::vector<ServiceCharge *> itsServiceCharges;
};

#endif
