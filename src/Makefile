all: testEmployee

#CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -Wextra
RM = rm -r
#LIBS = -lboost_date_time

ADD_EMPLOYEE_SRCS = AddEmployeeTransaction.cc AddSalariedEmployee.cc \
    AddHourlyEmployee.cc AddCommissionedEmployee.cc

DELETE_EMPLOYEE_SRCS = DeleteEmployeeTransaction.cc

CHANGE_EMPLOYEE_SRCS = ChangeEmployeeTransaction.cc ChangeNameTransaction.cc \
    ChangeAddressTransaction.cc ChangeClassificationTransaction.cc \
    ChangeHourlyTransaction.cc ChangeSalariedTransaction.cc \
    ChangeCommissionedTransaction.cc ChangeMethodTransaction.cc \
    ChangeHoldMethodTransaction.cc ChangeDirectMethodTransaction.cc \
    ChangeMailMethodTransaction.cc ChangeAffiliationTransaction.cc \
    ChangeMemberTransaction.cc ChangeUnaffiliatedTransaction.cc

PAYDAY_SRCS = PaydayTransaction.cc Paycheck.cc

TIMECARD_SRCS = TimeCardTransaction.cc TimeCard.cc
SALESRECEIPT_SRCS = SalesReceiptTransaction.cc SalesReceipt.cc
SERVICECHARGE_SRCS = ServiceChargeTransaction.cc

CLASSIFICATION_SRCS = SalariedClassification.cc CommissionedClassification.cc \
    HourlyClassification.cc
SCHEDULE_SRCS = WeeklySchedule.cc BiweeklySchedule.cc MonthlySchedule.cc
AFFILIATION_SRCS = UnionAffiliation.cc
METHOD_SRCS = HoldMethod.cc DirectMethod.cc MailMethod.cc

sources = testEmployee.cc Employee.cc PayrollDatabase.cc \
 $(ADD_EMPLOYEE_SRCS) \
 $(DELETE_EMPLOYEE_SRCS) \
 $(CHANGE_EMPLOYEE_SRCS) \
 $(PAYDAY_SRCS) \
 $(TIMECARD_SRCS) \
 $(SALESRECEIPT_SRCS) \
 $(SERVICECHARGE_SRCS) \
 $(CLASSIFICATION_SRCS) \
 $(SCHEDULE_SRCS) \
 $(AFFILIATION_SRCS) \
 $(METHOD_SRCS)
	
testEmployee:$(sources:.cc=.o)
	$(CXX) $(CXXFLAGS) -o $@ $^

include $(sources:.cc=.d)

%.d:%.cc
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed -e 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

%.o:%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-$(RM) *.o *.d *.stackdump testEmployee 

test:
	./testEmployee
