#ifndef _HOURLYCLASSIFICATION_H_
#define _HOURLYCLASSIFICATION_H_

#include "PaymentClassification.h"

class HourlyClassification : public PaymentClassification 
{
    public:
        HourlyClassification(double hourlyRate) : itsHourlyRate(hourlyRate) {};
        virtual ~HourlyClassification() {};
        double getHourlyRate() const { return itsHourlyRate; };
    private:
        double itsHourlyRate;
};

#endif
