#include "PayrollDatabase.h"

using namespace std;

PayrollDatabase gPayrollDatabase;

PayrollDatabase::~PayrollDatabase() 
{

}

void PayrollDatabase::getAllEmployeeIds(list<int> &empIds) const
{
    for(auto it = itsEmployees.begin(); it!=itsEmployees.end(); ++it) {
        empIds.push_back(it->first);
    }
}

Employee *PayrollDatabase::getEmployee(int empId)
{
    return itsEmployees[empId];
}

void PayrollDatabase::addEmployee(int empId, Employee *e)
{
    itsEmployees[empId] = e;
}

void PayrollDatabase::deleteEmployee(int empId)
{
    map<int, Employee *>::iterator it = itsEmployees.find(empId);
    
    if(it != itsEmployees.end()) {
        delete it->second;
        itsEmployees.erase(it);
    }
}


Employee *PayrollDatabase::getUnionMember(int memberId)
{
    return itsUnionMembers[memberId];
}


void PayrollDatabase::addUnionMember(int memberId, Employee *e)
{
    itsUnionMembers[memberId] = e;
}

void PayrollDatabase::removeUnionMember(int memberId) 
{
    map<int, Employee *>::iterator it = itsUnionMembers.find(memberId);
    if(it != itsUnionMembers.end()) {
        itsUnionMembers.erase(it);
    }
}

