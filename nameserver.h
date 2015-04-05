#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__

//#include "printer.h"
#include <vector>

_Task VendingMachine;
_Monitor Printer;

_Task NameServer {
    void main();
    //pass in
    Printer& prt;
    unsigned int numVendingMachines;
    unsigned int numStudents;

    unsigned int matchNext;//store the next number of Vending machine that should get match
    std::vector<VendingMachine*>machines;
    void advance();//advance one position for matchNext
    
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};

#endif
