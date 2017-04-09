#include <algorithm>
#include "UnionAffiliation.h"
#include "ServiceCharge.h"

using namespace std;

UnionAffiliation::UnionAffiliation(int memberId, double dues) 
    : itsMemberId(memberId), itsDues(dues) 
{

}

UnionAffiliation::~UnionAffiliation() 
{
    for(auto serviceCharge : itsServiceCharges) {
        delete serviceCharge; 
    }
}

void UnionAffiliation::addServiceCharge(Date date, double charge)
{
    ServiceCharge *sc = new ServiceCharge(date, charge);
    itsServiceCharges.push_back(sc);
}

ServiceCharge *UnionAffiliation::getServiceCharge(Date date)
{ 
    vector<ServiceCharge *>::iterator it = 
        find_if(itsServiceCharges.begin(),
                itsServiceCharges.end(), 
                [&date] (ServiceCharge *sc) ->bool { return sc->getDate() == date; }
                );
    if (it != itsServiceCharges.end())
        return *it;
    return nullptr;
}
