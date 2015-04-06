#include "config.h"
#include "MPRNG.h"
#include <iostream>
#include <time.h>

#include "printer.h"
#include "bank.h"
#include "parent.h"
#include "watcardoffice.h"
#include "nameserver.h"
#include "vendingmachine.h"
#include "bottlingplant.h"
#include "student.h"

using namespace std;

MPRNG rand_gen;

void uMain::main(){
  
  //prepare target
  string passin="test.config";
  //char* target=new char[passin.size()+1];
  //target[passin.size()]=NULL;//null terminate
  //copy(passin.begin(),passin.end(),target);
  
  const char* target=passin.c_str();
  ConfigParms myparms;
  
  //prepare 
  processConfigFile(target,myparms);
  //cout<<myparms.maxStockPerFlavour<<endl;
  
  int seed=time(NULL);
  rand_gen.seed(seed);
  
  Printer myprinter(myparms.numStudents,myparms.numVendingMachines,myparms.numCouriers);
  Bank mybank(myparms.numStudents);
  Parent* myparent=new Parent(myprinter,mybank,myparms.numStudents,myparms.parentalDelay);
  WATCardOffice* myoffice=new WATCardOffice(myprinter,mybank,myparms.numCouriers);
  NameServer* mynameserver=new NameServer(myprinter,myparms.numVendingMachines,myparms.numStudents);
  
  BottlingPlant* mybottlingplant=new BottlingPlant(myprinter,*mynameserver,myparms.numVendingMachines,myparms.maxShippedPerFlavour,myparms.maxStockPerFlavour,myparms.timeBetweenShipments);
  
  VendingMachine* mymachines[myparms.numVendingMachines];
  for(unsigned int i=0;i<myparms.numVendingMachines;i++){
    mymachines[i]=new VendingMachine(myprinter,*mynameserver,i,myparms.sodaCost,myparms.maxStockPerFlavour);
  }
  
  //clean up
  delete mybottlingplant;
  for (unsigned int i=0;i<myparms.numVendingMachines;i++){
    delete mymachines[i];
  }
  delete mynameserver;
  delete myoffice;
  delete myparent;
}
