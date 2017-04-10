#ifndef _CHANGENAMETRANSACTION_H_
#define _CHANGENAMETRANSACTION_H_

#include <string>
#include "ChangeEmployeeTransaction.h"

class ChangeNameTransaction : public ChangeEmployeeTransaction
{
    public:
        ChangeNameTransaction(int empId, const std::string &name);
        virtual ~ChangeNameTransaction();
        void change(Employee &e) override;
    private:
        std::string itsName;
};

#endif
