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
  string passin;
   try {
    passin = argv[1];  
  } catch ( ... ) {
    cout << "./soda [config filename]" << endl;
  }
    //prepare target
  //string passin="test.config";
  //char* target=new char[passin.size()+1];
  //target[passin.size()]=NULL;//null terminate
  //copy(passin.begin(),passin.end(),target);
  
  const char* target=passin.c_str();
  ConfigParms myparms;
  
  //prepare 
  processConfigFile(target, myparms);
  int seed=time(NULL);
  rand_gen.seed(seed);
  
  Printer myprinter(myparms.numStudents,myparms.numVendingMachines,myparms.numCouriers);
  Bank mybank(myparms.numStudents);
  Parent myparent(myprinter,mybank,myparms.numStudents,myparms.parentalDelay);
  WATCardOffice myoffice(myprinter,mybank,myparms.numCouriers);
  NameServer mynameserver(myprinter,myparms.numVendingMachines,myparms.numStudents);
  BottlingPlant mybottlingplant(myprinter,mynameserver,myparms.numVendingMachines,myparms.maxShippedPerFlavour,myparms.maxStockPerFlavour,myparms.timeBetweenShipments);
  
  VendingMachine* mymachines[myparms.numVendingMachines];
  
  Student* mystudents[myparms.numStudents];
  
  for(unsigned int i=0;i<myparms.numVendingMachines;i++){
    mymachines[i]=new VendingMachine(myprinter,mynameserver,i,myparms.sodaCost,myparms.maxStockPerFlavour);
  }
  
  for(unsigned int i=0;i<myparms.numStudents;i++){
    mystudents[i]=new Student(myprinter,mynameserver,myoffice,i,myparms.maxPurchases);
  }
  
  for(unsigned int i=0;i<myparms.numStudents;i++){
    delete mystudents[i];
  }
  
  for(unsigned int i=0;i<myparms.numVendingMachines;i++){
    delete mymachines[i];
  }
}
