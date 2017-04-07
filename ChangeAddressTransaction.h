#ifndef _CHANGEADDRESSTRANSACTION_H_
#define _CHANGEADDRESSTRANSACTION_H_

#include <string>
#include "ChangeEmployeeTransaction.h"

class ChangeAddressTransaction : public ChangeEmployeeTransaction
{
    public:
        ChangeAddressTransaction(int empId, const std::string &address);
        virtual ~ChangeAddressTransaction();
        void change(Employee &e) override;
    private:
        std::string itsAddress;
};

#endif
