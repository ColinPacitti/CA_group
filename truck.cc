#include "truck.h"
#include "printer.h"
#include "nameserver.h"
#include "bottlingplant.h"
#include "printer.h"
#include "vendingmachine.h"

#include <iostream>

using namespace std;
extern MPRNG rand_gen;

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
              unsigned int numVendingMachines, unsigned int maxStockPerFlavour ){
    print = &prt;
    this->nameServer = &nameServer;
    this->plant = &plant;
    this->numVendingMachines = numVendingMachines;
    this->maxStockPerFlavour = maxStockPerFlavour;
    for( int i = 0; i < 4; i++ ) {
        stock[i] = 0;
    }
    prt.print(Printer::Truck,'S');
}

Truck::~Truck(){
  cout<<"truck des"<<endl;
}

void Truck::main(){
    for(;;) {
      cout << "aaron dont leave me" << endl;
        VendingMachine **list = nameServer->getMachineList();
        int rand = rand_gen(1, 10);
        yield(rand);

	unsigned int shipcount;
	unsigned int notFilled;
        try {
	  cout << "before aaron" << endl;
	  plant->getShipment( stock );
	  cout << "after aaron" << endl;
	  //if do not throw, i get the shipment
	  for (unsigned int i=0;i<4;i++){
	    shipcount+=stock[i];
	  }
	  print->print(Printer::Truck,'P',shipcount);
        } catch ( BottlingPlant::Shutdown e ) {
	  cout<<"bott catchhhhhhhhh"<<endl;
	  print->print(Printer::Truck,'F');
	  return;
        }
	cout << "numVending " << numVendingMachines << endl;
        for( unsigned int i = 0; i < numVendingMachines; i++ ) {
	  cout << "aaron you are my girl" << endl;
	  unsigned int id = list[i]->getId();
	  unsigned int *inventory = list[i]->inventory();
	  cout << "is it here aaron" << endl;
	  print->print(Printer::Vending, 'd', id, shipcount); 
	  for( int j = 0; j < 4; j++ ) {
	    unsigned int fill = maxStockPerFlavour - inventory[j]; 
	    inventory[j]+= fill;
	    stock[j]-=fill;
	    shipcount-=fill;
	    notFilled = notFilled + (stock[j] - fill);
	  }
	  print->print(Printer::Vending, 'U', id, notFilled);
	  list[i]->restocked();
	  cout << "or here aaron??" << endl;
	  print->print(Printer::Truck,'D', id, shipcount);
	  cout << "where the fuck is aaron" << endl;
        }
	cout<< "is aaron here" << endl;
    }
    
}
