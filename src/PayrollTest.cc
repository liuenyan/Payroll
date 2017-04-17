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
        ASSERT_NE(nullptr, pc);
        ASSERT_EQ(date, pc->getPayPeriodEndDate());
        ASSERT_EQ(string("Hold"), pc->getField("Disposition"));
        ASSERT_DOUBLE_EQ(pay, pc->getGrossPay());
        ASSERT_DOUBLE_EQ(0, pc->getDeductions());
        ASSERT_DOUBLE_EQ(pay, pc->getNetPay());
    }

    TEST_F(PayrollTest, testAddSalariedEmployee) {
        //cerr << "Test add salaried employee" << endl;
        int empId = 1;
        AddSalariedEmployee addSalariedEmployee(
                empId, string("Alice"), string("Home"), 1000.0); 
        addSalariedEmployee.execute();

        Employee *e = gPayrollDatabase.getEmployee(empId);
        ASSERT_EQ(string("Alice"), e->getName());
        ASSERT_EQ(string("Home"), e->getAddress());

        PaymentClassification *pc = e->getClassification();
        SalariedClassification *sc = dynamic_cast<SalariedClassification *>(pc);
        ASSERT_NE(nullptr, sc);

        ASSERT_DOUBLE_EQ(1000.0, sc->getSalary());

        PaymentSchedule *ps = e->getSchedule();
        MonthlySchedule *ms = dynamic_cast<MonthlySchedule *>(ps);
        ASSERT_NE(nullptr, ms);

        PaymentMethod *pm = e->getMethod();
        HoldMethod *hm = dynamic_cast<HoldMethod *>(pm);
        ASSERT_NE(nullptr, hm);
    }
    TEST_F(PayrollTest, testAddHourlyEmployee) {

        //cerr << "Test add hourly employee" << endl;
        int empId = 2;
        AddHourlyEmployee addHourlyEmployee(
                empId, string("Bob"), string("Home"), 80.0); 
        addHourlyEmployee.execute();

        Employee *e = gPayrollDatabase.getEmployee(empId);
        ASSERT_EQ(string("Bob"), e->getName());
        ASSERT_EQ(string("Home"), e->getAddress());

        PaymentClassification *pc = e->getClassification();
        HourlyClassification *hc = dynamic_cast<HourlyClassification *>(pc);
        ASSERT_NE(nullptr, hc);

        ASSERT_DOUBLE_EQ(80.0, hc->getHourlyRate());

        PaymentSchedule *ps = e->getSchedule();
        WeeklySchedule *ws = dynamic_cast<WeeklySchedule *>(ps);
        ASSERT_NE(nullptr, ws);

        PaymentMethod *pm = e->getMethod();
        HoldMethod *hm = dynamic_cast<HoldMethod *>(pm);
        ASSERT_NE(nullptr, hm);
    }

    TEST_F(PayrollTest, testAddCommissionedEmployee) {

        //cerr << "Test add commissioned employee" << endl;
        int empId = 3;
        AddCommissionedEmployee addCommissionedEmployee(
                empId, string("Carl"), string("Home"), 1000.0, 0.2); 
        addCommissionedEmployee.execute();

        Employee *e = gPayrollDatabase.getEmployee(empId);
        ASSERT_EQ(string("Carl"), e->getName());
        ASSERT_EQ(string("Home"), e->getAddress());

        PaymentClassification *pc = e->getClassification();
        CommissionedClassification *cc = dynamic_cast<CommissionedClassification *>(pc);
        ASSERT_NE(nullptr, cc);

        ASSERT_DOUBLE_EQ(1000.0, cc->getSalary());
        ASSERT_DOUBLE_EQ(0.2, cc->getCommissionRate());

        PaymentSchedule *ps = e->getSchedule();
        BiweeklySchedule *ws = dynamic_cast<BiweeklySchedule *>(ps);
        ASSERT_NE(nullptr, ws);

        PaymentMethod *pm = e->getMethod();
        HoldMethod *hm = dynamic_cast<HoldMethod *>(pm);
        ASSERT_NE(nullptr, hm);
    }
    TEST_F(PayrollTest, testDeleteEmployee) {

        //cerr << "Test delete employee" << endl;
        int empId = 3;
        AddCommissionedEmployee add(
                empId, string("Bob"), string("Home"), 800, 0.2);     
        add.execute();

        Employee *e = gPayrollDatabase.getEmployee(empId);
        ASSERT_NE(nullptr, e);

        DeleteEmployeeTransaction *del = new DeleteEmployeeTransaction(empId);
        del->execute();

        Employee *e1 = gPayrollDatabase.getEmployee(empId);
        ASSERT_EQ(nullptr, e1);
    }
    TEST_F(PayrollTest, testAddTimeCard) {

        //cerr << "Test AddTimeCard" << endl;
        int empId = 5;
        AddHourlyEmployee add(empId, string("John"), string("Home"), 10.0);
        add.execute();

        Date date(2017, 4, 6);
        TimeCardTransaction tct(date, 4, empId);
        tct.execute();

        Employee *e = gPayrollDatabase.getEmployee(empId); 
        ASSERT_NE(nullptr, e);

        PaymentClassification *pc = e->getClassification();
        ASSERT_NE(nullptr, pc);
        HourlyClassification *hc = dynamic_cast<HourlyClassification *>(pc);
        ASSERT_NE(nullptr, hc);

        TimeCard *tc = hc->getTimeCard(date);
        ASSERT_NE(nullptr, tc);
        ASSERT_DOUBLE_EQ(4, tc->getHours());
    }
    TEST_F(PayrollTest, testAddSalesReceipt) {
        //cerr << "Test AddSalesReceipt" << endl;
        int empId = 6;
        AddCommissionedEmployee add(empId, string("Jack"), string("CA"), 800.0, 0.2);
        add.execute();

        Date date(2017, 4, 6);
        SalesReceiptTransaction srt(date, 15, empId);
        srt.execute();

        Employee *e = gPayrollDatabase.getEmployee(empId); 
        ASSERT_NE(nullptr, e);

        PaymentClassification *pc = e->getClassification();
        ASSERT_NE(nullptr, pc);
        CommissionedClassification *cc = dynamic_cast<CommissionedClassification *>(pc);
        ASSERT_NE(nullptr, cc);

        SalesReceipt *sr = cc->getSalesReceipt(date);
        ASSERT_NE(nullptr, sr);
        ASSERT_DOUBLE_EQ(15, sr->getAmount());
    }

    TEST_F(PayrollTest, testAddServiceCharge)
    {
        //cerr << "Test AddServiceCharge" << endl;
        int empId = 7;

        AddHourlyEmployee add(empId, string("James"), string("CA"), 10.0);
        add.execute();

        Employee *e = gPayrollDatabase.getEmployee(empId);
        ASSERT_NE(nullptr, e);

        int memberId = 87;
        UnionAffiliation *af = new UnionAffiliation(memberId, 12.5);
        e->setAffiliation(af);

        gPayrollDatabase.addUnionMember(memberId, e);

        Date date(2017, 4, 7);
        ServiceChargeTransaction sct(memberId, date, 12.95);
        sct.execute();

        Employee *e1 = gPayrollDatabase.getUnionMember(memberId);
        ASSERT_EQ(e1, e);
        ServiceCharge *sc = af->getServiceCharge(date);    
        ASSERT_NE(nullptr, sc);

        ASSERT_DOUBLE_EQ(12.95, sc->getAmount());
    }

    TEST_F(PayrollTest, testChangeEmployeeName)
    {

        //cerr << "Test change employee name" << endl;
        int empId = 8;

        AddSalariedEmployee a(empId, string("Mark"), string("Home"), 1000.32); 
        a.execute();

        string name = string("Joe");
        ChangeNameTransaction cnt = ChangeNameTransaction(empId, name);
        cnt.execute();

        Employee *e = gPayrollDatabase.getEmployee(empId);
        ASSERT_EQ(name, e->getName()); 
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
        ASSERT_EQ(address, e->getAddress());
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
        ASSERT_NE(nullptr, pc);
        HourlyClassification *hc = dynamic_cast<HourlyClassification *>(pc);
        ASSERT_NE(nullptr, hc);
        ASSERT_DOUBLE_EQ(20.0, hc->getHourlyRate());
        PaymentSchedule *ps = e->getSchedule();
        ASSERT_NE(nullptr, ps);
        WeeklySchedule *ws = dynamic_cast<WeeklySchedule *>(ps);
        ASSERT_NE(nullptr, ws);
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
        ASSERT_NE(nullptr, pc);
        SalariedClassification *sc = dynamic_cast<SalariedClassification *>(pc);
        ASSERT_NE(nullptr, sc);
        ASSERT_DOUBLE_EQ(1000, sc->getSalary());
        PaymentSchedule *ps = e->getSchedule();
        ASSERT_NE(nullptr, ps);
        MonthlySchedule *ms = dynamic_cast<MonthlySchedule *>(ps);
        ASSERT_NE(nullptr, ms);
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
        ASSERT_NE(nullptr, pc);
        CommissionedClassification *cc = dynamic_cast<CommissionedClassification *>(pc);
        ASSERT_NE(nullptr, cc);
        ASSERT_DOUBLE_EQ(1000, cc->getSalary());
        ASSERT_DOUBLE_EQ(0.2, cc->getCommissionRate());
        PaymentSchedule *ps = e->getSchedule();
        ASSERT_NE(nullptr, ps);
        BiweeklySchedule *ms = dynamic_cast<BiweeklySchedule *>(ps);
        ASSERT_NE(nullptr, ms);
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
        ASSERT_NE(nullptr, pm);
        DirectMethod *dm = dynamic_cast<DirectMethod *>(pm);
        ASSERT_NE(nullptr, dm);
        ASSERT_EQ(string("Bank1"), dm->getBank());
        ASSERT_EQ(string("b112233"), dm->getAccount()) ;

        ChangeMailMethodTransaction cmmt(empId, string("Home1"));
        cmmt.execute();
        e = gPayrollDatabase.getEmployee(empId);
        pm = e->getMethod();
        ASSERT_NE(nullptr, pm);
        MailMethod *mm = dynamic_cast<MailMethod *>(pm);
        ASSERT_NE(nullptr, mm);
        ASSERT_EQ(string("Home1"), mm->getAddress());

        ChangeHoldMethodTransaction chmt(empId);
        chmt.execute();
        e = gPayrollDatabase.getEmployee(empId);
        pm = e->getMethod();
        ASSERT_NE(nullptr, pm);
        HoldMethod *hm = dynamic_cast<HoldMethod *>(pm);
        ASSERT_NE(nullptr, hm);
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
        ASSERT_NE(nullptr, e);
        Affiliation *af = e->getAffiliation();
        ASSERT_NE(nullptr, af);
        UnionAffiliation *uaf = dynamic_cast<UnionAffiliation *>(af);
        ASSERT_NE(nullptr, uaf);
        ASSERT_DOUBLE_EQ(99.42, uaf->getDues());

        Employee *member = gPayrollDatabase.getUnionMember(memberId);
        ASSERT_EQ(member, e);

        ChangeUnaffiliatedTransaction cut(empId);
        cut.execute();

        e = gPayrollDatabase.getEmployee(empId);
        ASSERT_NE(nullptr, e);
        af = e->getAffiliation();
        ASSERT_NE(nullptr, af);
        NoAffiliation *naf = dynamic_cast<NoAffiliation *>(af);
        ASSERT_NE(nullptr, naf);

        member = gPayrollDatabase.getUnionMember(memberId);
        ASSERT_EQ(nullptr, member);
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
        ASSERT_EQ(nullptr, pc);
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
        ASSERT_EQ(nullptr, pc);
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

    TEST_F(PayrollTest, testPaySingleCommissionedEmployeeNoSaleReceipt) 
    {
        int empId = 3;
        Date payday(2017, 4, 14);
        
        AddCommissionedEmployee a(empId, string("Carl"), string("Home"), 800, 40);
        a.execute();

        PaydayTransaction pt(payday);
        pt.execute();

        validatePaycheck(pt, empId, 800, payday);
    }

    TEST_F(PayrollTest, testPaySingleCommissionedEmployeeOneSaleReceipt)
    {
        int empId = 3;
        Date payday(2017, 4, 14);
        
        AddCommissionedEmployee a(empId, string("Carl"), string("Home"), 800, 0.2);
        a.execute();

        SalesReceiptTransaction srt(Date(2017, 4, 13), 100, empId);
        srt.execute();

        PaydayTransaction pt(payday);
        pt.execute();

        validatePaycheck(pt, empId, 800+100*0.2, payday);
    }

    TEST_F(PayrollTest, testPaySingleCommissionedEmployeeOnWrongDate)
    {
        int empId = 3;
        Date payday(2017, 4, 13);
        
        AddCommissionedEmployee a(empId, string("Carl"), string("Home"), 800, 0.2);
        a.execute();

        PaydayTransaction pt(payday);
        pt.execute();

        Paycheck *pc = pt.getPaycheck(empId);
        ASSERT_EQ(nullptr, pc);
    }

    TEST_F(PayrollTest, testPaySingleCommissionedEmployeeTwoSaleReceipt)
    {

        int empId = 3;
        Date payday(2017, 4, 14);
        
        AddCommissionedEmployee a(empId, string("Carl"), string("Home"), 800, 0.2);
        a.execute();

        SalesReceiptTransaction srt1(Date(2017, 4, 7), 100, empId);
        srt1.execute();
        
        SalesReceiptTransaction srt2(payday, 150, empId);
        srt2.execute();

        PaydayTransaction pt(payday);
        pt.execute();

        validatePaycheck(pt, empId, 800+(100+150)*0.2, payday);
    }

    TEST_F(PayrollTest, testPaySingleCommissionedEmployeeTwoSaleReceiptSpanningTwoPayPeriod)
    {
        int empId = 3;
        Date payday(2017, 4, 14);
        
        AddCommissionedEmployee a(empId, string("Carl"), string("Home"), 800, 0.2);
        a.execute();

        SalesReceiptTransaction srt1(Date(2017, 3, 31), 100, empId);
        srt1.execute();
        
        SalesReceiptTransaction srt2(payday, 150, empId);
        srt2.execute();

        PaydayTransaction pt(payday);
        pt.execute();

        validatePaycheck(pt, empId, 800+150*0.2, payday);
    }
    TEST_F(PayrollTest, testSalariedUnionMemberDues)
    {
        int empId = 1;
        int membetId = 7789;
        int fridays = 4;
        AddSalariedEmployee a(empId, string("Bob"), string("Home"), 1000.0);
        a.execute();

        ChangeMemberTransaction cmt(empId, membetId, 9.42);
        cmt.execute();

        Date payday(2017, 4, 30);
        PaydayTransaction pt(payday);
        pt.execute();
        
        Paycheck *pc = pt.getPaycheck(empId);
        ASSERT_NE(nullptr, pc);
        ASSERT_EQ(payday, pc->getPayPeriodEndDate());
        ASSERT_EQ(string("Hold"), pc->getField("Disposition"));
        ASSERT_DOUBLE_EQ(1000.0, pc->getGrossPay());
        ASSERT_DOUBLE_EQ(9.42*fridays, pc->getDeductions());
        ASSERT_DOUBLE_EQ(1000.0-9.42*fridays, pc->getNetPay());
    }
    
    TEST_F(PayrollTest, testHourlyUnionMemberDues)
    {
        int empId = 1;
        int memberId = 7789;
        int fridays = 1;
        Date payday(2017, 4, 14);

        AddHourlyEmployee a(empId, string("Bill"), string("Home"), 15.5);
        a.execute();

        TimeCardTransaction tct(payday, 8, empId);
        tct.execute();

        ChangeMemberTransaction cmt(empId, memberId, 9.42);
        cmt.execute();
        
        PaydayTransaction pt(payday);
        pt.execute();

        Paycheck *pc = pt.getPaycheck(empId);
        ASSERT_NE(nullptr, pc);
        ASSERT_EQ(payday, pc->getPayPeriodEndDate());
        ASSERT_EQ(string("Hold"), pc->getField("Disposition"));
        ASSERT_DOUBLE_EQ(15.5*8, pc->getGrossPay());
        ASSERT_DOUBLE_EQ(9.42*fridays, pc->getDeductions());
        ASSERT_DOUBLE_EQ(15.5*8-9.42*fridays, pc->getNetPay());
    }

    TEST_F(PayrollTest, testCommissionedUnionMemberDues)
    {
        int empId = 3;
        int memberId = 7789;
        int fridays = 2;
        Date payday(2017, 4, 14);

        AddCommissionedEmployee a(empId, string("Carl"), string("Home"), 1000, 0.2);
        a.execute();

        SalesReceiptTransaction srt(payday, 300, empId);
        srt.execute();

        ChangeMemberTransaction cmt(empId, memberId, 9.42);
        cmt.execute();
        
        PaydayTransaction pt(payday);
        pt.execute();

        Paycheck *pc = pt.getPaycheck(empId);
        ASSERT_NE(nullptr, pc);
        ASSERT_EQ(payday, pc->getPayPeriodEndDate());
        ASSERT_EQ(string("Hold"), pc->getField("Disposition"));
        ASSERT_DOUBLE_EQ(1000+300*0.2, pc->getGrossPay()) ;
        ASSERT_DOUBLE_EQ(9.42*fridays, pc->getDeductions());
        ASSERT_DOUBLE_EQ(1000+300*0.2-9.42*fridays, pc->getNetPay());
    }

    TEST_F(PayrollTest, testHourlyUnionMemberServiceCharge)
    {
        int empId = 1;
        int memberId = 7789;
        int fridays = 1;
        Date payday(2017, 4, 14);

        AddHourlyEmployee a(empId, string("Bill"), string("Home"), 15.5);
        a.execute();

        TimeCardTransaction tct(payday, 8, empId);
        tct.execute();

        ChangeMemberTransaction cmt(empId, memberId, 9.42);
        cmt.execute();

        ServiceChargeTransaction sct(memberId, payday, 13.5);
        sct.execute();
        
        PaydayTransaction pt(payday);
        pt.execute();

        Paycheck *pc = pt.getPaycheck(empId);
        ASSERT_NE(nullptr, pc);
        ASSERT_EQ(payday, pc->getPayPeriodEndDate());
        ASSERT_EQ(string("Hold"), pc->getField("Disposition"));
        ASSERT_DOUBLE_EQ(15.5*8, pc->getGrossPay());
        ASSERT_DOUBLE_EQ(9.42*fridays + 13.5, pc->getDeductions());
        ASSERT_DOUBLE_EQ(15.5*8-(9.42*fridays + 13.5), pc->getNetPay());
    }
    
    TEST_F(PayrollTest, testServiceChargesSpanningMultiplePayperiod)
    {
        int empId = 1;
        int memberId = 7789;
        int fridays = 1;
        Date payday(2017, 4, 14);
        Date earlyDay(2017, 4, 7);
        Date lateDay(2017, 4, 21);

        AddHourlyEmployee a(empId, string("Bill"), string("Home"), 15.5);
        a.execute();

        TimeCardTransaction tct(payday, 8, empId);
        tct.execute();

        ChangeMemberTransaction cmt(empId, memberId, 9.42);
        cmt.execute();

        ServiceChargeTransaction sct(memberId, payday, 13.5);
        sct.execute();
        ServiceChargeTransaction sctEarly(memberId,earlyDay, 6.5);
        sctEarly.execute();
        ServiceChargeTransaction sctLate(memberId, lateDay, 7.5);
        sctLate.execute();
        
        PaydayTransaction pt(payday);
        pt.execute();

        Paycheck *pc = pt.getPaycheck(empId);
        ASSERT_NE(nullptr, pc);
        ASSERT_EQ(payday, pc->getPayPeriodEndDate());
        ASSERT_EQ(string("Hold"), pc->getField("Disposition"));
        ASSERT_DOUBLE_EQ(15.5*8, pc->getGrossPay());
        ASSERT_DOUBLE_EQ(9.42*fridays + 13.5, pc->getDeductions());
        ASSERT_DOUBLE_EQ(15.5*8-(9.42*fridays + 13.5), pc->getNetPay());
    }
};

int main(int argc, char **argv)
{

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
