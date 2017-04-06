#ifndef _TIMECARD_H_
#define _TIMECARD_H_

#include "Date.h"

class TimeCard 
{
    public:
        TimeCard(Date date, double hours);
        const Date &getDate() const { return itsDate; };
        double getHours() const {return itsHours; };
    private:
        Date itsDate;
        double itsHours;
};

#endif
