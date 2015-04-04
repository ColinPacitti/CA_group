CXX = u++
CXXFLAGS = -g -Wall -Wno-unused-label -MD
OBJECTS = bank.o config.o nameserver.o parent.o soda.o truck.o vendingmachine.o watcar.o watcardoffice.o bottlingplant.o truck.o printer.o # object files forming first executable with prefix ``q2''
DEPENDS = ${OBJECTS:.o=.d}
EXECS = sleepingbarber
MAKEFLAGS = --no-print-directory

${EXECS} : ${OBJECTS}
	${CXX} $^ -o $@

clean :
	rm -f ${DEPENDS} ${OBJECTS} ${EXECS}

-include ${DEPENDS}
