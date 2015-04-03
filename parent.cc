#include "parent.h"
using namepspace std;

extern MPRNG rand_gen;

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) {
    print = prt;
    bank = bank;
    numStudents = numStudents;
    parentalDelay = parentalDelay;
}

void main() {
    for (;;) {
       _Accept(~Parent){
            return;
        } _Else {
            yield(parentalDelay);
            int amount = rand_gen(1);
            int id = rand_gen(numStudents);
            if ( amount == 0 ) {
                bank.deposit( id, 1);
            } else {
                bank.deposit( id, 3);
            }
        }
    }
}
