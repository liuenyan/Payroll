#ifndef _PAYROLLDATABASE_H_
#define _PAYROLLDATABASE_H_

#include <map>
#include "Employee.h"

class PayrollDatabase 
{
    public:
        virtual ~PayrollDatabase();
        Employee *getEmployee(int empId);
        void addEmployee(int empId, Employee *e);
        void deleteEmployee(int empId);
        Employee *getUnionMember(int memberId);
        void addUnionMember(int memberId, Employee *e);
        void clear(){ itsEmployees.clear(); };
    private:
        std::map<int, Employee *> itsEmployees;
        std::map<int, Employee *> itsUnionMembers; 
};

extern PayrollDatabase gPayrollDatabase;

#endif
