#ifndef _DATE_H_
#define _DATE_H_

#include <boost/date_time/gregorian/gregorian.hpp>

typedef boost::gregorian::date Date;
typedef boost::gregorian::date_duration DateDuration;
typedef boost::date_time::weekdays WeekdayEnum;
typedef boost::gregorian::day_iterator DayIterator;

bool isBetween(const Date &theDate, const Date &startDate, const Date &endDate);

#endif
