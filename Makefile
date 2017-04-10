all: testEmployee

#CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -Wextra
RM = rm -r
#LIBS = -lboost_date_time

ADD_EMPLOYEE_OBJECTS = AddEmployeeTransaction.o AddSalariedEmployee.o \
    AddHourlyEmployee.o AddCommissionedEmployee.o

DELETE_EMPLOYEE_OBJECTS = DeleteEmployeeTransaction.o

CHANGE_EMPLOYEE_OBJECTS = ChangeEmployeeTransaction.o ChangeNameTransaction.o \
    ChangeAddressTransaction.o ChangeClassificationTransaction.o \
    ChangeHourlyTransaction.o ChangeSalariedTransaction.o \
    ChangeCommissionedTransaction.o ChangeMethodTransaction.o \
    ChangeHoldMethodTransaction.o ChangeDirectMethodTransaction.o \
    ChangeMailMethodTransaction.o ChangeAffiliationTransaction.o \
    ChangeMemberTransaction.o ChangeUnaffiliatedTransaction.o

PAYDAY_OBJECTS = PaydayTransaction.o Paycheck.o

TIMECARD_OBJECTS = TimeCardTransaction.o TimeCard.o
SALESRECEIPT_OBJECTS = SalesReceiptTransaction.o SalesReceipt.o
SERVICECHARGE_OBJECTS = ServiceChargeTransaction.o

CLASSIFICATION_OBJECTS = SalariedClassification.o CommissionedClassification.o \
    HourlyClassification.o
SCHEDULE_OBJECTS = WeeklySchedule.o BiweeklySchedule.o MonthlySchedule.o
AFFILIATION_OBJECTS = UnionAffiliation.o
METHOD_OBJECTS = HoldMethod.o DirectMethod.o MailMethod.o


# testEmployee: testEmployee.o Employee.o PayrollDatabase.o \
# 	AddEmployeeTransaction.o AddSalariedEmployee.o AddHourlyEmployee.o \
# 	AddCommissionedEmployee.o DeleteEmployeeTransaction.o \
# 	TimeCardTransaction.o TimeCard.o Date.o HourlyClassification.o \
# 	SalesReceiptTransaction.o SalesReceipt.o CommissionedClassification.o \
# 	UnionAffiliation.o ServiceChargeTransaction.o \
# 	ChangeEmployeeTransaction.o ChangeNameTransaction.o ChangeAddressTransaction.o \
# 	ChangeClassificationTransaction.o ChangeHourlyTransaction.o \
# 	ChangeSalariedTransaction.o ChangeCommissionedTransaction.o \
# 	ChangeMethodTransaction.o ChangeHoldMethodTransaction.o \
# 	ChangeDirectMethodTransaction.o ChangeMailMethodTransaction.o \
# 	ChangeAffiliationTransaction.o ChangeMemberTransaction.o \
# 	ChangeUnaffiliatedTransaction.o \
# 	MonthlySchedule.o BiweeklySchedule.o WeeklySchedule.o \
# 	SalariedClassification.o  \
# 	PaydayTransaction.o Paycheck.o \
# 	HoldMethod.o DirectMethod.o MailMethod.o 
# 	$(CXX) $(CXXFLAGS) -o $@ $^

testEmployee: testEmployee.o Employee.o PayrollDatabase.o \
	$(ADD_EMPLOYEE_OBJECTS) \
	$(DELETE_EMPLOYEE_OBJECTS) \
	$(CHANGE_EMPLOYEE_OBJECTS) \
	$(PAYDAY_OBJECTS) \
	$(TIMECARD_OBJECTS) \
	$(SALESRECEIPT_OBJECTS) \
	$(SERVICECHARGE_OBJECTS) \
	$(CLASSIFICATION_OBJECTS) \
	$(SCHEDULE_OBJECTS) \
	$(AFFILIATION_OBJECTS) \
	$(METHOD_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o:%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-$(RM) *.o testEmployee 

test:
	./testEmployee
