#ifndef _UNIONAFFILIATION_H_
#define _UNIONAFFILIATION_H_ 

#include <map>
#include "Affiliation.h"
#include "Date.h"
#include "ServiceCharge.h"

class UnionAffiliation : public Affiliation
{
    public:
        UnionAffiliation(int memberId, double dues);
        virtual ~UnionAffiliation();
        double calculateDeductions(Paycheck &pc) const override;
        int getMemberId() const { return itsMemberId; };
        double getDues() const { return itsDues; };
        void addServiceCharge(Date date, double charge);
        ServiceCharge *getServiceCharge(Date date);
    private:
        int itsMemberId;
        double itsDues;
        std::map<Date, ServiceCharge *> itsServiceCharges;
};

#endif
