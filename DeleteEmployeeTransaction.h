#ifndef _DELETEEMPLOYEETRANSACTION_H_
#define _DELETEEMPLOYEETRANSACTION_H_

#include "Transaction.h"

class DeleteEmployeeTransaction : public Transaction
{
    public:
        DeleteEmployeeTransaction(int empId);
        virtual ~DeleteEmployeeTransaction();
        void execute() override;
    private:
        int itsEmpId;
};

#endif
