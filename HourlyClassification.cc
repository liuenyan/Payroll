#include "HourlyClassification.h"
#include <algorithm>

using namespace std;


HourlyClassification::HourlyClassification(double hourlyRate)
    : itsHourlyRate(hourlyRate)
{

}

HourlyClassification::~HourlyClassification()
{
    for(auto tc : itsTimeCards) {
        delete tc;
    }
}

void HourlyClassification::addTimeCard(TimeCard *tc)
{
    itsTimeCards.push_back(tc);
}

TimeCard *HourlyClassification::getTimeCard(Date date)
{
    vector<TimeCard *>::iterator it = 
        find_if(itsTimeCards.begin(),
                itsTimeCards.end(), 
                [&date] (TimeCard *tc) ->bool { return tc->getDate() == date; }
                );
    if (it != itsTimeCards.end())
        return *it;
    return nullptr;
}
