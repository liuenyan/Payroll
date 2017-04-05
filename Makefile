all: testAddEmployee

CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -Wextra
RM = rm -r

testAddEmployee: testAddEmployee.o Employee.o PayrollDatabase.o \
	AddEmployeeTransaction.o AddSalariedEmployee.o AddHourlyEmployee.o \
	AddCommissionedEmployee.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o:%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-$(RM) *.o testAddEmployee
