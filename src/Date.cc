#include "Date.h"


bool isBetween(const Date &theDate, const Date &startDate, const Date &endDate)
{
    return startDate <= theDate && theDate <= endDate; 
}
