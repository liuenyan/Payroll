#include <gtest/gtest.h>

#include "PayrollDatabase.h"
#include "AddSalariedEmployee.h"
#include "AddHourlyEmployee.h"
#include "AddCommissionedEmployee.h"
#include "DeleteEmployeeTransaction.h"
#include "TimeCardTransaction.h"
#include "SalesReceiptTransaction.h"
#include "ServiceChargeTransaction.h"

#include "ChangeNameTransaction.h"
#include "ChangeAddressTransaction.h"
#include "ChangeHourlyTransaction.h"
#include "ChangeSalariedTransaction.h"
#include "ChangeCommissionedTransaction.h"
#include "ChangeHoldMethodTransaction.h"
#include "ChangeDirectMethodTransaction.h"
#include "ChangeMailMethodTransaction.h"
#include "ChangeAffiliationTransaction.h"
#include "ChangeMemberTransaction.h"
#include "ChangeUnaffiliatedTransaction.h"

#include "PaydayTransaction.h"

#include "SalariedClassification.h"
#include "HourlyClassification.h"
#include "CommissionedClassification.h"

#include "MonthlySchedule.h"
#include "WeeklySchedule.h"
#include "BiweeklySchedule.h"

#include "HoldMethod.h"
#include "DirectMethod.h"
#include "MailMethod.h"

#include "UnionAffiliation.h"
#include "NoAffiliation.h"

namespace 
{
    using namespace std;
    class PayrollTest : public ::testing::Test 
    {
        protected:
            PayrollTest(){};
            virtual ~PayrollTest() {};
            void SetUp(){};
            void TearDown() { gPayrollDatabase.clear(); };
        public:
            void validatePaycheck(PaydayTransaction &pt, int empId, double pay, const Date &date);
    };
    
    void PayrollTest::validatePaycheck(PaydayTransaction &pt, int empId, double pay, const Date &date)
    {
        Paycheck *pc = pt.getPaycheck(empId);
        assert(pc);
        assert(pc->getPayPeriodEndDate() == date);
        assert(pc->getField("Disposition") == string("Hold"));
        assert(pc->getGrossPay() == pay);
        assert(pc->getDeductions() == 0);
        assert(pc->getNetPay() == pay);
    }

    TEST_F(PayrollTest, testAddSalariedEmployee) {
        //cerr << "Test add salaried employee" << endl;
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
    TEST_F(PayrollTest, testAddHourlyEmployee) {

        //cerr << "Test add hourly employee" << endl;
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
    TEST_F(PayrollTest, testAddCommissionedEmployee) {

        //cerr << "Test add commissioned employee" << endl;
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
    TEST_F(PayrollTest, testDeleteEmployee) {

        //cerr << "Test delete employee" << endl;
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
    TEST_F(PayrollTest, testAddTimeCard) {

        //cerr << "Test AddTimeCard" << endl;
        int empId = 5;
        AddEmployeeTransaction *add = new AddHourlyEmployee(
                empId, string("John"), string("CA"), 10.0);
        add->execute();
        delete add;

        Date date(2017, 4, 6);
        //cout << date << endl;
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
    TEST_F(PayrollTest, testAddSalesReceipt) {
        //cerr << "Test AddSalesReceipt" << endl;
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

    TEST_F(PayrollTest, testAddServiceCharge)
    {
        //cerr << "Test AddServiceCharge" << endl;
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

    TEST_F(PayrollTest, testChangeEmployeeName)
    {

        //cerr << "Test change employee name" << endl;
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

    TEST_F(PayrollTest, testChangeEmployeeAddress)
    {

        //cerr << "Test change employee address" << endl;
        int empId = 9;

        AddSalariedEmployee a = AddSalariedEmployee(empId, string("Marc"), string("Home"), 1000); 
        a.execute();

        string address = string("Joel");
        ChangeAddressTransaction cat = ChangeAddressTransaction(empId, address);
        cat.execute();

        Employee *e = gPayrollDatabase.getEmployee(empId);
        assert(e->getAddress() == address);
    }

    TEST_F(PayrollTest, testChangeHourlyTransaction)
    {
        //cerr << "Test change hourly transaction" << endl;
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

    TEST_F(PayrollTest, testChangeSalariedTransaction)
    {
        //cerr << "Test change salaried transaction" << endl;
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


    TEST_F(PayrollTest, testChangeCommissionedTransaction)
    {
        //cerr << "Test change commissioned transaction" << endl;
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

    TEST_F(PayrollTest, testChangeMethodTransaction)
    {
        //cerr << "Test change method transaction" << endl;
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

    TEST_F(PayrollTest, testChangeAffiliation)
    {
        //cerr << "Test change affiliation transaction" << endl;
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


    TEST_F(PayrollTest, testPaySingleSarlariedEmployee)
    {
        //cerr <<  "Test pay single salaried employee" << endl;
        int empId = 15;

        AddSalariedEmployee a(empId, string("Bob"), string("Home"), 1000.0); 
        a.execute();

        Date d(2017, 4, 30);
        PaydayTransaction pt(d);
        pt.execute();
        validatePaycheck(pt, empId, 1000.0, d);
    }

    TEST_F(PayrollTest, testPaySingleSalariedEmployeeOnWrongDate)
    {
        //cerr <<  "Test pay single salaried employee on wrong date" << endl;
        int empId = 16;

        AddSalariedEmployee a(empId, string("Bob"), string("Home"), 1000.0); 
        a.execute();
        Date d(2017, 4, 29);
        PaydayTransaction pt(d);
        pt.execute();
        Paycheck *pc = pt.getPaycheck(empId);
        assert(!pc);
    }

    TEST_F(PayrollTest, testPaySingleHourlyEmployeeNoTimeCards)
    {
        //cerr << "Test pay single hourly employee no timecards" << endl;
        int empId = 17;
        AddHourlyEmployee a(empId, string("Bill"), string("Home"), 15.25);
        a.execute();
        Date d(2017, 4, 14);
        PaydayTransaction pt(d);
        pt.execute();
        validatePaycheck(pt, empId, 0, d);
    }

    TEST_F(PayrollTest, testPaySingleHourlyEmployeeOneTimeCard)
    {
        //cerr << "Test pay single hourly employee one timecard" << endl;
        int empId = 18;
        AddHourlyEmployee a(empId, string("Bill"), string("Home"), 15.25);
        a.execute();

        Date d1(2017, 4, 11);
        TimeCardTransaction tct(d1, 2, empId);
        tct.execute();

        Date d(2017, 4, 14);
        PaydayTransaction pt(d);
        pt.execute();
        validatePaycheck(pt, empId, 30.5, d);
    }

    TEST_F(PayrollTest, testPaySingleHourlyEmployeeOvertimeOneTimeCard)
    {
        //cerr << "Test pay single hourly employee overtime one timecard" << endl;
        int empId = 19;
        AddHourlyEmployee a(empId, string("Bill"), string("Home"), 15.25);
        a.execute();

        Date d1(2017, 4, 11);
        TimeCardTransaction tct(d1, 9, empId);
        tct.execute();

        Date d(2017, 4, 14);
        PaydayTransaction pt(d);
        pt.execute();
        validatePaycheck(pt, empId, 15.25*(8+1.5), d);
    }

    TEST_F(PayrollTest, testPaySingleHourlyEmployeeOnWrongDate)
    {
        //cerr <<  "Test pay single hourly employee on wrong date" << endl;
        int empId = 20;

        AddHourlyEmployee a(empId, string("Bill"), string("Home"), 15.25); 
        a.execute();

        Date d1(2017, 4, 11);
        TimeCardTransaction tct(d1, 9, empId);
        tct.execute();

        Date d(2017, 4, 12);
        PaydayTransaction pt(d);
        pt.execute();
        Paycheck *pc = pt.getPaycheck(empId);
        assert(!pc);
    }

    TEST_F(PayrollTest, testPaySingleHourlyEmployeeTwoTimeCards)
    {
        //cerr << "Test pay single hourly employee two timecard" << endl;
        int empId = 21;
        Date payday(2017, 4, 14);
        AddHourlyEmployee a(empId, string("Bill"), string("Home"), 15.25);
        a.execute();

        Date d1(2017, 4, 11);
        TimeCardTransaction tct(d1, 2, empId);
        tct.execute();

        TimeCardTransaction tct2(payday, 5, empId);
        tct2.execute();

        PaydayTransaction pt(payday);
        pt.execute();
        validatePaycheck(pt, empId, 15.25*7, payday);
    }

    TEST_F(PayrollTest, testPaySingleHourlyEmployeeTwoTimeCardsSpanningTwoPayPeriod)
    {
        //cerr << "Test pay single hourly employee two timecard spanning two pay period" << endl;
        int empId = 22;
        Date payday(2017, 4, 14);
        AddHourlyEmployee a(empId, string("Bill"), string("Home"), 15.25);
        a.execute();

        Date d1(2017, 4, 7);
        TimeCardTransaction tct(d1, 2, empId);
        tct.execute();

        TimeCardTransaction tct2(payday, 5, empId);
        tct2.execute();

        PaydayTransaction pt(payday);
        pt.execute();
        validatePaycheck(pt, empId, 15.25*5, payday);
    }
};

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
