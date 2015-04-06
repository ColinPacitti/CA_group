#include "truck.h"
#include "printer.h"
#include "nameserver.h"
#include "bottlingplant.h"
#include "printer.h"
#include "vendingmachine.h"

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

        try {
            plant->getShipment( stock );
	    //if do not throw, i get the shipment
	    unsigned int shipcount;
	    for (unsigned int i=0;i<4;i++){
	      shipcount+=stock[i];
	    }
	    prt.print(Printer::Truck,'P',shipcount);
        } catch ( BottlingPlant::Shutdown e ) {
            return;
        }

        //if ( status == 1 ) {
        //    return;
        //}       
        for( unsigned int i = 0; i < numVendingMachines; i++ ) {
            unsigned int id = list[i]->getId();
            unsigned int *inventory = list[i]->inventory();
           for( int j = 0; j < 4; j++ ) {
                //Might need to add unstocked_sum or num_bottles
                unsigned int fill = maxStockPerFlavour - inventory[i]; 
                inventory[i]+= fill;
                stock[i]-=fill;
           }
	   
           list[i]->restocked();
	   //prt.print(Printer::Truck,'D',);
        }
    }
    prt.print(Printer::Truck,'F');
}
