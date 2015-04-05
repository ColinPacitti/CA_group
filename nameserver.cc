#include "nameserver.h"

#include <assert.h>
#include "vendingmachine.h"
#include "printer.h"
using namespace std;

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents )
  :prt(prt),numVendingMachines(numVendingMachines),numStudents(numStudents),matchNext(numVendingMachines-1),fillposition(0)
{
  machines=new VendingMachine*[numVendingMachines];
}

NameServer::~NameServer(){
  delete []machines;
}

void NameServer::VMregister(VendingMachine* vendingmachine){
  //machines.push_back(vendingmachine);
  machines[fillposition]=vendingmachine;
  fillposition++;
  assert(fillposition<=numVendingMachines+1);//exceed max amount
}

void NameServer::advance(){
  assert(numVendingMachines!=0);
  if(matchNext==(numVendingMachines-1)){
    matchNext=0;
  }
  else{
    matchNext++;
  }
}

VendingMachine* NameServer::getMachine( unsigned int id ){
  advance();
  assert(matchNext<fillposition);//within position i filled
  return machines[matchNext];
}

VendingMachine** NameServer::getMachineList(){
  return machines;
}

void NameServer::main(){
  while(true){
    //mysize=machines.size();
    
    _Accept(~NameServer) break;
    //or _When(==numVendingMachine) _Accept(getMachine,getMachineList);
    //or _When(true) _Accept(VMregister);//??? right way?
    or _When(matchNext<=fillposition) _Accept(getMachine);
    or _When(fillposition==(numVendingMachines)) _Accept(getMachineList);
    or _Accept(VMregister);
  }
}
