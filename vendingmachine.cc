#include "vendingmachine.h"

#include "nameserver.h"
#include "printer.h"
#include "watcard.h"
//#include "config.h"
#include <iostream>
using namespace std;

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                                unsigned int maxStockPerFlavour ){
    this->print = &prt;
    this->nameServer = &nameServer;
    this->id = id;
    this->sodaCost = sodaCost;
    this->maxStockPerFlavour = maxStockPerFlavour;
    noBuy = false;
    for( int i = 0; i < 2; i++ ) {
        stocks[i] = 0;
    }
    //Register with nameServer
}

void VendingMachine::main(){
    print->print(Printer::Vending, id, 'S', sodaCost);
    nameServer->VMregister( this );    
    for(;;){
      _Accept( VendingMachine::~VendingMachine ){
            print->print(Printer::Vending, id, 'F');
            return;
        } or _When(noBuy) _Accept( VendingMachine::restocked ){

        } or _When(!noBuy) _Accept( VendingMachine::inventory, VendingMachine::buy ){
        
        }
    }
}

void VendingMachine::buy( Flavours flavour, WATCard &card ){
    unsigned int balance = card.getBalance();
    unsigned int stock = stocks[flavour];
    //Need Flag variable according to assingment??
    //Check to make sure stock and balance is okay
    uRendezvousAcceptor();
    if( balance < sodaCost ) {
      throw VendingMachine::Funds();
    } else if( stock == 0 ) {
      throw VendingMachine::Stock();
    } else {
      print->print(Printer::Vending, id, 'B', (int)flavour, stocks[flavour] - (unsigned int)1);
      stocks[flavour]--;
      card.withdraw( sodaCost );
    } 
}

unsigned int* VendingMachine::inventory(){
    noBuy = true;
    print->print(Printer::Vending, id, 'r');
    return stocks; 
}

void VendingMachine::restocked(){
    noBuy = false;
    print->print(Printer::Vending, id, 'R');
}

unsigned int VendingMachine::cost() {
    return sodaCost;
}

unsigned int VendingMachine::getId(){
    return id;
}
