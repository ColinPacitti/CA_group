#include "bank.h"
#include "printer.h"
#include "parent.h"
#include <iostream>
using namespace std;

extern MPRNG rand_gen;

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) {
    
    this->print = &prt;
    this->bank = &bank;
    this->numStudents = numStudents;
    this->parentalDelay = parentalDelay;
    this->print->print(Printer::Parent,'S');
}

Parent::~Parent(){

}

void Parent::main() {
    for (;;) {
      _Accept(Parent::~Parent){
	print->print(Printer::Parent,'F');
	return;
      } _Else {
	yield(parentalDelay);
	unsigned int amount = rand_gen(1,3);
	unsigned int id = rand_gen(numStudents - 1);
	print->print(Printer::Parent,'D',id,amount);
	bank->deposit( id, amount);
      }
    }
}
