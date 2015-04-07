#ifndef __PARENT_H__
#define __PARENT_H__
//#include "bank.h"
//#include "printer.h"
#include "MPRNG.h"

_Monitor Bank;
_Monitor Printer;

_Task Parent {
    unsigned int numStudents;
    unsigned int parentalDelay;
    Bank *bank;
    Printer *print;
    void main();
    public:
        Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
        ~Parent();
};
#endif
