#include "vendingmachine.h"
using namespace std;

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                                unsigned int maxStockPerFlavour ){
    print = prt;
    nameServer = nameServer;
    id = id;
    sodaCost = sodaCost;
    maxStockPerFlavour = maxStockPerFlavour;
    for( int i = 0; i < 2; i++ ) {
        stocks[i] = 0;
    }
    //Register with nameServer
    nameServer->VMregister( this );    
}

void VendingMachine::buy( Flavours flavour, WATCard &card ){
    for(;;){
        if( noBuy ) {
            _Accept( restocked ){
                noBuy = false;
                break;
            } or _Accept( cost, getId, inventory, ~VendingMachine ){};
        }
    }

    int balance = card.getBalance();
    int *allStock = inventory();
    int stock - allStock[flavour];    
    //Need Flag variable according to assingment??
    //Check to make sure stock and balance is okay
    if( balance < sodaCost ) {
        throw Funds;
    } else if( stock == 0 ) {
        throw Stock
    } else {
        card.withdraw( sodaCost );
    } 
}

unsigned int* VendingMachine::inventory(){
    noBuy = true;
    return &stocks; 
}

void VendingMachine::restocked(){
    //Used to indicate stocking is finished
}

unsigned int VendingMachine::cost() {
    return sodaCost;
}

unsigned int VendingMachine::getId(){
    return id;
}
