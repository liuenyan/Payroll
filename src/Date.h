#ifndef _DATE_H_
#define _DATE_H_

#include <boost/date_time/gregorian/gregorian.hpp>

typedef boost::gregorian::date Date;
typedef boost::gregorian::date_duration DateDuration;

/*
class Date 
{
    public:
        Date(int year, int month, int day);
        int getYear() const { return itsYear; };
        int getMonth() const { return itsMonth; };
        int getDay() const { return itsDay; };
        bool operator==(const Date &other) const;
    private:
        int itsYear;
        int itsMonth;
        int itsDay;
};*/



#endif
