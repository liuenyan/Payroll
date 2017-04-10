#ifndef _PAYCHECK_H_
#define _PAYCHECK_H_

#include <map>
#include <string>
#include "Date.h"

class Paycheck 
{
    public:
        Paycheck(const Date &payDate)
            : itsGrossPay(0), itsDeductions(0), itsNetPay(0)
            , itsPayDate(payDate) {};
            
        double getGrossPay() const { return itsGrossPay; };
        double getDeductions() const { return itsDeductions; };
        double getNetPay() const { return itsNetPay; };
        const Date &getPayDate() const { return itsPayDate; };
        const std::string &getField(const std::string &key) const;

        void setGrossPay(double grossPay) { itsGrossPay = grossPay; };
        void setDeductions(double deductions) { itsDeductions = deductions; };
        void setNetPay(double netPay) { itsNetPay = netPay; };
        void setPayDate(const Date &payDate) { itsPayDate = payDate; };
        void setField(const std::string &key, const std::string &value);
    private: 
        double itsGrossPay;
        double itsDeductions;
        double itsNetPay;
        Date itsPayDate;
        std::map<std::string, std::string> itsFields;
};

#endif
