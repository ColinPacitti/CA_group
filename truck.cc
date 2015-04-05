#include "truck.h"
#include "printer.h"
#include "nameserver.h"
#include "bottlingplant.h"
#include "printer.h"

using namespace std;
extern MPRNG rand_gen;

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
              unsigned int numVendingMachines, unsigned int maxStockPerFlavour ){
    print = prt;
    nameServer = nameServer;
    plant = plant;
    numVendingMachines = numVendingMachines;
    maxStockPerFlavour = maxStockPerFlavour;
    for( int i = 0; i < 4; i++ ) {
        stock[i] = 0;
    }
}

void Truck::main(){
    for(;;) {
        VendingMachine **list = nameServer->getMachineList();
        int rand = rand_gen(1, 10);
        yield(rand);

        try {
            bool status = plant->getShipment( stock );
        } catch ( BottlingPlant::Shutdown e ) {
            returnl
        }

        if ( status == 1 ) {
            return;
        }       
        for( unsigned int i = 0; i < numVendingMachines; i++ ) {
            int id = list[i]->getId();
            unsigned int *inventory = list[i]->inventory();
           for( int j = 0; j < 4; j++ ) {
                //Might need to add unstocked_sum or num_bottles
                unsigned int fill = maxStockPerFlavour - inventory[i]; 
                inventory[i]+= fill;
                stock-=fill;
           }
           list[i]->restocked();
        }
    }
}
