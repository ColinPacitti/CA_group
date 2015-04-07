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
  cout << "whats your issure man" << endl;
}

void Truck::main(){
    for(;;) {
        VendingMachine **list = nameServer->getMachineList();
        int rand = rand_gen(1, 10);
        yield(rand);

	unsigned int shipcount = 0;
	unsigned int notFilled = 0;
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
	  print->print(Printer::Truck,'F');
	  cout << "get here" << endl;
	  _Accept(Truck::~Truck);
	  return;
        } catch ( ... ) {
	  print->print(Printer::Truck,'F');
	  cout << "get here2" << endl;
	  _Accept(Truck::~Truck);
	  return;
	}

        for( unsigned int i = 0; i < numVendingMachines; i++ ) {
	  if( shipcount == 0 ) {
	    break;
	  }
	  unsigned int id = list[i]->getId();
	  cout << "before inventory" << endl; 
	  unsigned int *inventory = list[i]->inventory();
	  cout << "after inventory" << endl;
	  print->print(Printer::Truck, 'd', id, shipcount); 
	  for( int j = 0; j < 4; j++ ) {
	    unsigned int fill = maxStockPerFlavour - inventory[j]; 
	    if ( stock[j] < fill ) {
	      fill = stock[j];
	    }
	    inventory[j]+= fill;
	    stock[j]-=fill;
	    shipcount-=fill;
	    notFilled = notFilled + (maxStockPerFlavour - inventory[j]);
	  }
	  if ( notFilled > 0 ) {
	    print->print(Printer::Truck, 'U', id, notFilled);
	  } else {
	    print->print(Printer::Truck,'D', id, shipcount);
	  }
	  list[i]->restocked();
        }
    }
    
}
