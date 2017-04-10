#ifndef _CHANGECLASSIFICATION_H_
#define _CHANGECLASSIFICATION_H_

#include "ChangeEmployeeTransaction.h"

class ChangeClassificationTransaction : public ChangeEmployeeTransaction
{
    public:
        ChangeClassificationTransaction(int empId);
        virtual ~ChangeClassificationTransaction();
        void change(Employee &e) override;
        virtual PaymentClassification *getClassification() const = 0;
        virtual PaymentSchedule *getSchedule() const = 0; 
};

#endif