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
#include "DeleteEmployeeTransaction.h"
#include "TimeCardTransaction.h"
#include "Date.h"

using namespace std;

void testAddSalariedEmployee()
{
    cerr << "test add salaried employee" << endl;
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
    cerr << "test add hourly employee" << endl;
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
    cerr << "test add commissioned employee" << endl;
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

void testDeleteEmployee()
{
    cerr << "Test delete employee" << endl;
    int empId = 4;
    AddEmployeeTransaction *add = new AddCommissionedEmployee(
            empId, string("Dell"), string("CA"), 800, 0.2);     
    add->execute();
    
    Employee *e = gPayrollDatabase.getEmployee(empId);
    assert(e);

    DeleteEmployeeTransaction *del = new DeleteEmployeeTransaction(empId);
    del->execute();

    Employee *e1 = gPayrollDatabase.getEmployee(empId);
    assert(!e1);
}

void testAddTimeCard()
{
    cerr << "Test AddTimeCard" << endl;
    int empId = 5;
    AddEmployeeTransaction *add = new AddHourlyEmployee(
            empId, string("John"), string("CA"), 10.0);
    add->execute();
    delete add;
    
    Date date(2017, 4, 6);
    TimeCardTransaction *tct = new TimeCardTransaction(date, 4, empId);
    tct->execute();
    delete tct;

    Employee *e = gPayrollDatabase.getEmployee(empId); 
    assert(e);

    PaymentClassification *pc = e->getClassification();
    assert(pc);
    HourlyClassification *hc = dynamic_cast<HourlyClassification *>(pc);
    assert(hc);

    TimeCard *tc = hc->getTimeCard(date);
    assert(tc);
    assert(tc->getHours() == 4);
}

int main()
{
    testAddSalariedEmployee();
    testAddHourlyEmployee();
    testAddCommissionedEmployee();
    testDeleteEmployee();
    testAddTimeCard();
    return 0;
}
