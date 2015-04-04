CXX = u++
CXXFLAGS = -g -Wall -Wno-unused-label -MD
OBJECTS = printer.o bank.o config.o watcard.o nameserver.o parent.o soda.o truck.o vendingmachine.o watcardoffice.o bottlingplant.o truck.o # object files forming first executable with prefix ``q2''
DEPENDS = ${OBJECTS:.o=.d}
EXECS = bottlingplant
MAKEFLAGS = --no-print-directory

${EXECS} : ${OBJECTS}
	${CXX} $^ -o $@

clean :
	rm -f ${DEPENDS} ${OBJECTS} ${EXECS}

-include ${DEPENDS}
