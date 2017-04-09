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
#include "SalesReceiptTransaction.h"
#include "UnionAffiliation.h"
#include "ServiceChargeTransaction.h"
#include "ChangeNameTransaction.h"
#include "ChangeAddressTransaction.h"
#include "ChangeHourlyTransaction.h"
#include "ChangeSalariedTransaction.h"
#include "ChangeCommissionedTransaction.h"
#include "ChangeDirectMethodTransaction.h"
#include "ChangeMailMethodTransaction.h"
#include "ChangeHoldMethodTransaction.h"
#include "MailMethod.h"
#include "DirectMethod.h"
#include "ChangeMemberTransaction.h"
#include "ChangeUnaffiliatedTransaction.h"
#include "NoAffiliation.h"

using namespace std;

void testAddSalariedEmployee()
{
    cerr << "Test add salaried employee" << endl;
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
    cerr << "Test add hourly employee" << endl;
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
    cerr << "Test add commissioned employee" << endl;
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

void testAddSalesReceipt()
{
    cerr << "Test AddSalesReceipt" << endl;
    int empId = 6;
    AddEmployeeTransaction *add = new AddCommissionedEmployee(
            empId, string("Jack"), string("CA"), 800.0, 0.2);
    add->execute();
    delete add;
    
    Date date(2017, 4, 6);
    SalesReceiptTransaction *srt = new SalesReceiptTransaction(date, 15, empId);
    srt->execute();
    delete srt;
    
    Employee *e = gPayrollDatabase.getEmployee(empId); 
    assert(e);

    PaymentClassification *pc = e->getClassification();
    assert(pc);
    CommissionedClassification *cc = dynamic_cast<CommissionedClassification *>(pc);
    assert(cc);

    SalesReceipt *sr = cc->getSalesReceipt(date);
    assert(sr);
    assert(sr->getAmount() == 15);
}

void testAddServiceCharge()
{
    cerr << "Test AddServiceCharge" << endl;
    int empId = 7;

    AddEmployeeTransaction *add = new AddHourlyEmployee(
            empId, string("James"), string("CA"), 10.0);
    add->execute();
    delete add;
    
    Employee *e = gPayrollDatabase.getEmployee(empId);
    assert(e);

    int memberId = 87;
    UnionAffiliation *af = new UnionAffiliation(memberId, 12.5);
    e->setAffiliation(af);

    gPayrollDatabase.addUnionMember(memberId, e);

    Date date(2017, 4, 7);
    ServiceChargeTransaction *sct = 
        new ServiceChargeTransaction(memberId, date, 12.95);
    sct->execute();
    delete sct;
    
    Employee *e1 = gPayrollDatabase.getUnionMember(memberId);
    assert(e1 == e);
    ServiceCharge *sc = af->getServiceCharge(date);    
    assert(sc);

    assert(sc->getAmount() == 12.95);
}

void testChangeEmployeeName()
{

    cerr << "Test change employee name" << endl;
    int empId = 8;
    
    AddSalariedEmployee a = 
        AddSalariedEmployee(empId, string("Mark"), string("Home"), 1000.32); 
    a.execute();
    
    string name = string("Joe");
    ChangeNameTransaction cnt = ChangeNameTransaction(empId, name);
    cnt.execute();
    
    Employee *e = gPayrollDatabase.getEmployee(empId);
    assert(e->getName() == name); 
}

void testChangeEmployeeAddress()
{

    cerr << "Test change employee address" << endl;
    int empId = 9;
    
    AddSalariedEmployee a = 
        AddSalariedEmployee(empId, string("Marc"), string("Home"), 1000); 
    a.execute();
    
    string address = string("Joel");
    ChangeAddressTransaction cat = ChangeAddressTransaction(empId, address);
    cat.execute();
    
    Employee *e = gPayrollDatabase.getEmployee(empId);
    assert(e->getAddress() == address);
}

void testChangeHourlyTransaction()
{
    cerr << "Test change hourly transaction" << endl;
    int empId = 10;
     
    AddSalariedEmployee a(empId, string("Bob"), string("Home"), 1000); 
    a.execute();

    ChangeHourlyTransaction cht(empId, 20.0);
    cht.execute();

    Employee *e = gPayrollDatabase.getEmployee(empId);
    PaymentClassification *pc = e->getClassification();
    assert(pc);
    HourlyClassification *hc = dynamic_cast<HourlyClassification *>(pc);
    assert(hc);
    assert(hc->getHourlyRate() == 20.0);
    PaymentSchedule *ps = e->getSchedule();
    assert(ps);
    WeeklySchedule *ws = dynamic_cast<WeeklySchedule *>(ps);
    assert(ws);
}

void testChangeSalariedTransaction()
{
    cerr << "Test change salaried transaction" << endl;
    int empId = 11;
     
    AddHourlyEmployee a(empId, string("Bob"), string("Home"), 20); 
    a.execute();

    ChangeSalariedTransaction cst(empId, 1000);
    cst.execute();

    Employee *e = gPayrollDatabase.getEmployee(empId);
    PaymentClassification *pc = e->getClassification();
    assert(pc);
    SalariedClassification *sc = dynamic_cast<SalariedClassification *>(pc);
    assert(sc);
    assert(sc->getSalary() == 1000);
    PaymentSchedule *ps = e->getSchedule();
    assert(ps);
    MonthlySchedule *ms = dynamic_cast<MonthlySchedule *>(ps);
    assert(ms);
}


void testChangeCommissionedTransaction()
{
    cerr << "Test change commissioned transaction" << endl;
    int empId = 12;
     
    AddHourlyEmployee a(empId, string("Bob"), string("Home"), 20); 
    a.execute();

    ChangeCommissionedTransaction cct(empId, 1000, 0.2);
    cct.execute();

    Employee *e = gPayrollDatabase.getEmployee(empId);
    PaymentClassification *pc = e->getClassification();
    assert(pc);
    CommissionedClassification *cc = dynamic_cast<CommissionedClassification *>(pc);
    assert(cc);
    assert(cc->getSalary() == 1000);
    assert(cc->getCommissionRate() == 0.2);
    PaymentSchedule *ps = e->getSchedule();
    assert(ps);
    BiweeklySchedule *ms = dynamic_cast<BiweeklySchedule *>(ps);
    assert(ms);
}

void testChangeMethodTransaction()
{
    cerr << "Test change method transaction" << endl;
    int empId = 13;
     
    AddHourlyEmployee a(empId, string("Bob"), string("Home"), 20); 
    a.execute();

    ChangeDirectMethodTransaction cdmt(empId, string("Bank1"), string("b112233"));
    cdmt.execute();
    Employee *e = gPayrollDatabase.getEmployee(empId);
    PaymentMethod *pm = e->getMethod();
    assert(pm);
    DirectMethod *dm = dynamic_cast<DirectMethod *>(pm);
    assert(dm);
    assert(dm->getBank() == string("Bank1"));
    assert(dm->getAccount() == string("b112233"));

    ChangeMailMethodTransaction cmmt(empId, string("Home1"));
    cmmt.execute();
    e = gPayrollDatabase.getEmployee(empId);
    pm = e->getMethod();
    assert(pm);
    MailMethod *mm = dynamic_cast<MailMethod *>(pm);
    assert(mm);
    assert(mm->getAddress() == string("Home1"));

    ChangeHoldMethodTransaction chmt(empId);
    chmt.execute();
    e = gPayrollDatabase.getEmployee(empId);
    pm = e->getMethod();
    assert(pm);
    HoldMethod *hm = dynamic_cast<HoldMethod *>(pm);
    assert(hm);
}

void testChangeAffiliation()
{
    cerr << "Test change affiliation transaction" << endl;
    int empId = 14;
    int memberId = 7752;
     
    AddHourlyEmployee a(empId, string("Bill"), string("Home"), 15.25); 
    a.execute();
    ChangeMemberTransaction cmt(empId, memberId, 99.42);
    cmt.execute();

    Employee *e = gPayrollDatabase.getEmployee(empId);
    assert(e);
    Affiliation *af = e->getAffiliation();
    assert(af);
    UnionAffiliation *uaf = dynamic_cast<UnionAffiliation *>(af);
    assert(uaf);
    assert(uaf->getDues() == 99.42);

    Employee *member = gPayrollDatabase.getUnionMember(memberId);
    assert(member == e);

    ChangeUnaffiliatedTransaction cut(empId);
    cut.execute();

    e = gPayrollDatabase.getEmployee(empId);
    assert(e);
    af = e->getAffiliation();
    assert(af);
    NoAffiliation *naf = dynamic_cast<NoAffiliation *>(af);
    assert(naf);
    
    member = gPayrollDatabase.getUnionMember(memberId);
    assert(member == nullptr);
}

int main()
{
    testAddSalariedEmployee();
    testAddHourlyEmployee();
    testAddCommissionedEmployee();
    testDeleteEmployee();
    testAddTimeCard();
    testAddSalesReceipt();
    testAddServiceCharge();
    testChangeEmployeeName();
    testChangeEmployeeAddress();
    testChangeHourlyTransaction();
    testChangeSalariedTransaction();
    testChangeCommissionedTransaction();
    testChangeMethodTransaction();
    testChangeAffiliation();
    return 0;
}
