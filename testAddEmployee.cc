#include <iostream>
#include <string>
#include <cassert>
#include "PayrollDatabase.h"
#include "Transaction.h"
#include "AddSalariedEmployee.h"
#include "PaymentClassification.h"
#include "SalariedClassification.h"
#include "PaymentSchedule.h"
#include "MonthlySchedule.h"
#include "HoldMethod.h"
#include "AddHourlyEmployee.h"
#include "HourlyClassification.h"
#include "WeeklySchedule.h"
#include "AddCommissionedEmployee.h"
#include "CommissionedClassification.h"
#include "BiweeklySchedule.h"

using namespace std;

PayrollDatabase gPayrollDatabase;

void testAddSalariedEmployee()
{
    int empId = 1;
    Transaction *addSalariedEmployee = new AddSalariedEmployee(
            empId, string("Alice"), string("Home"), 1000.32); 
    addSalariedEmployee->execute();

    Employee *e = gPayrollDatabase.getEmployee(empId);
    assert(e->getName() == string("Alice"));
    assert(e->getAddress() == string("Home"));

    PaymentClassification *pc = e->getClassification();
    SalariedClassification *sc = dynamic_cast<SalariedClassification *>(pc);
    assert(sc);
    
    assert(1000.32 == sc->getSalary());

    PaymentSchedule *ps = e->getSchedule();
    MonthlySchedule *ms = dynamic_cast<MonthlySchedule *>(ps);
    assert(ms);

    PaymentMethod *pm = e->getMethod();
    HoldMethod *hm = dynamic_cast<HoldMethod *>(pm);
    assert(hm);
}

void testAddHourlyEmployee()
{
    int empId = 2;
    Transaction *addHourlyEmployee = new AddHourlyEmployee(
            empId, string("Bob"), string("Home"), 80.0); 
    addHourlyEmployee->execute();

    Employee *e = gPayrollDatabase.getEmployee(empId);
    assert(e->getName() == string("Bob"));
    assert(e->getAddress() == string("Home"));

    PaymentClassification *pc = e->getClassification();
    HourlyClassification *hc = dynamic_cast<HourlyClassification *>(pc);
    assert(hc);
    
    assert(80.0 == hc->getHourlyRate());

    PaymentSchedule *ps = e->getSchedule();
    WeeklySchedule *ws = dynamic_cast<WeeklySchedule *>(ps);
    assert(ws);

    PaymentMethod *pm = e->getMethod();
    HoldMethod *hm = dynamic_cast<HoldMethod *>(pm);
    assert(hm);
}

void testAddCommissionedEmployee()
{
    int empId = 3;
    Transaction *addCommissionedEmployee = new AddCommissionedEmployee(
            empId, string("Carl"), string("Home"), 800.0, 40.0); 
    addCommissionedEmployee->execute();

    Employee *e = gPayrollDatabase.getEmployee(empId);
    assert(e->getName() == string("Carl"));
    assert(e->getAddress() == string("Home"));

    PaymentClassification *pc = e->getClassification();
    CommissionedClassification *cc = dynamic_cast<CommissionedClassification *>(pc);
    assert(cc);
    
    assert(800.0 == cc->getSalary());
    assert(40.0 == cc->getCommissionRate());

    PaymentSchedule *ps = e->getSchedule();
    BiweeklySchedule *ws = dynamic_cast<BiweeklySchedule *>(ps);
    assert(ws);

    PaymentMethod *pm = e->getMethod();
    HoldMethod *hm = dynamic_cast<HoldMethod *>(pm);
    assert(hm);
}

int main()
{
    testAddSalariedEmployee();
    testAddHourlyEmployee();
    testAddCommissionedEmployee();
    return 0;
}
