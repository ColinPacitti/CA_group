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
    numVendingMachines = numVendingMachines;
    maxStockPerFlavour = maxStockPerFlavour;
    for( int i = 0; i < 4; i++ ) {
        stock[i] = 0;
    }
    prt.print(Printer::Truck,'S');
}

void Truck::main(){
    for(;;) {
        VendingMachine **list = nameServer->getMachineList();
        int rand = rand_gen(1, 10);
        yield(rand);

	    unsigned int shipcount;
        unsigned int notFilled;
        try {
            plant->getShipment( stock );
	        //if do not throw, i get the shipment
	        for (unsigned int i=0;i<4;i++){
	            shipcount+=stock[i];
	        }
	        print->print(Printer::Truck,'P',shipcount);
        } catch ( BottlingPlant::Shutdown e ) {
	  print->print(Printer::Truck,'F');
	  return;
        }

        for( unsigned int i = 0; i < numVendingMachines; i++ ) {
            unsigned int id = list[i]->getId();
            unsigned int *inventory = list[i]->inventory();
            print->print(Printer::Vending, 'd', id, shipcount); 
           for( int j = 0; j < 4; j++ ) {
                //Might need to add unstocked_sum or num_bottles
                unsigned int fill = maxStockPerFlavour - inventory[j]; 
                inventory[j]+= fill;
                stock[j]-=fill;
                shipcount-=fill;
                notFilled = stock[j] - fill;
           }
	       print->print(Printer::Vending, 'U', id, notFilled);
           list[i]->restocked();
	       print->print(Printer::Truck,'D', id, shipcount);
        }
    }
    
}
