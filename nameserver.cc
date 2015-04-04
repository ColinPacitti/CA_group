#include "nameserver.h"
#include <assert.h>
#include "vendingmachine.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents )
  :prt(prt),numVendingMachine(numVendingMachine),numStudents(numStudents),matchNext(numVendingMachines-1)
{}

void NameServer::VMregister(VendingMachine* vendingmachine){
  machines.push_back(vendingmachine);
}

void NameServer::advance(){
  assert(numVendingMachine!=0);
  if(matchNext==(numVendingMachine-1)){
    matchNext=0;
  }
  else{
    matchNext++;
  }
}

VendingMachine* NameServer::getMachine( unsigned int id ){
  advance();
  return machines[matchNext];
}

VendingMachine** NameServer::getMachineList(){
  return machines;
}

void NameServer::main(){
  while(true){
    mysize=machines.size();
    
    _Accept(~NameServer) break;
    or _When(mysize==numVendingMachine) _Accept(getMachine,getMachineList);
    or _When(true) _Accept(VMregister);//??? right way?
  }
}
