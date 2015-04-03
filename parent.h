#include "bank.h"
#include "printer.h"

_Task Parent {
    unsigned int numStudents;
    unsigned int parentalDelay;
    Bank *bank;
    Printer *print;
    void main();
    public:
        Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};
