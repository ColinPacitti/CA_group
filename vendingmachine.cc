#include "vendingmachine.h"

#include "nameserver.h"
#include "printer.h"
#include "watcard.h"
//#include "config.h"

using namespace std;

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                                unsigned int maxStockPerFlavour ){
    print = &prt;
    this->nameServer = &nameServer;
    id = id;
    sodaCost = sodaCost;
    maxStockPerFlavour = maxStockPerFlavour;
    noBuy = false;
    for( int i = 0; i < 2; i++ ) {
        stocks[i] = 0;
    }
    //Register with nameServer
}

void VendingMachine::main(){
    print->print(Printer::Vending, 'S', sodaCost);
    nameServer->VMregister( this );    
    for(;;){
        _Accept( ~VendingMachine ){i
            print->print(Printer::Vending, 'F');
            break;
        } or _When(noBuy) _Accept( restocked ){

        } or _When(!noBuy) _Accept(buy, inventory ){
        
        }
    }
}

void VendingMachine::buy( Flavours flavour, WATCard &card ){
    unsigned int balance = card.getBalance();
    unsigned int *allStock = inventory();
    unsigned int stock = allStock[flavour];    
    print->print(Printer::Vending, 'B', (int)flavour, stock[flavour] - 1);
    //Need Flag variable according to assingment??
    //Check to make sure stock and balance is okay
    if( balance < sodaCost ) {
        throw Funds();
    } else if( stock == 0 ) {
        throw Stock();
    } else {
        card.withdraw( sodaCost );
    } 
}

unsigned int* VendingMachine::inventory(){
    noBuy = true;
    print->print(Printer::Vending, 'r');
    return stocks; 
}

void VendingMachine::restocked(){
    noBuy = false;
    print->print(Printer::Vending, 'R');
}

unsigned int VendingMachine::cost() {
    return sodaCost;
}

unsigned int VendingMachine::getId(){
    return id;
}
