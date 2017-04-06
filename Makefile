all: testEmployee

CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -Wextra
RM = rm -r

testEmployee: testEmployee.o Employee.o PayrollDatabase.o \
	AddEmployeeTransaction.o AddSalariedEmployee.o AddHourlyEmployee.o \
	AddCommissionedEmployee.o DeleteEmployeeTransaction.o \
	TimeCardTransaction.o TimeCard.o Date.o HourlyClassification.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o:%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-$(RM) *.o testEmployee 
