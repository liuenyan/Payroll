#ifndef _PAYCHECK_H_
#define _PAYCHECK_H_

#include <map>
#include <string>
#include "Date.h"

class Paycheck 
{
    public:
        Paycheck(const Date &payStartDate, const Date &payEndDate)
            : itsGrossPay(0)
            , itsDeductions(0) 
            , itsNetPay(0)
            , itsPayPeriodStartDate(payStartDate)
            , itsPayPeriodEndDate(payEndDate) {};
            
        double getGrossPay() const { return itsGrossPay; };
        double getDeductions() const { return itsDeductions; };
        double getNetPay() const { return itsNetPay; };
        const Date &getPayPeriodStartDate() const { return itsPayPeriodStartDate; };
        const Date &getPayPeriodEndDate() const { return itsPayPeriodEndDate; };
        const std::string &getField(const std::string &key) const;
        void setGrossPay(double grossPay) { itsGrossPay = grossPay; };
        void setDeductions(double deductions) { itsDeductions = deductions; };
        void setNetPay(double netPay) { itsNetPay = netPay; };
        void setPayPeriodStartDate(const Date &date) { itsPayPeriodStartDate = date; };
        void setPayPeriodEndDate(const Date &date) { itsPayPeriodEndDate = date; };
        void setField(const std::string &key, const std::string &value);
    private:
        double itsGrossPay;
        double itsDeductions;
        double itsNetPay;
        Date itsPayPeriodStartDate;
        Date itsPayPeriodEndDate;
        std::map<std::string, std::string> itsFields;
};

#endif
