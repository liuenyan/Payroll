#ifndef _CHANGEEMPLOYEETRANSACTION_H_
#define _CHANGEEMPLOYEETRANSACTION_H_

#include "Transaction.h"
#include "Employee.h"

class ChangeEmployeeTransaction : public Transaction
{
    public:
        ChangeEmployeeTransaction(int empId);
        virtual ~ChangeEmployeeTransaction();
        void execute() override;
        virtual void change(Employee &e) = 0;
    private:
        int itsEmpId;
};

#endif
