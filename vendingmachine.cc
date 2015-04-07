#include "vendingmachine.h"

#include "nameserver.h"
#include "printer.h"
#include "watcard.h"
//#include "config.h"
#include <iostream>
using namespace std;
//Set all values to default
VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                                unsigned int maxStockPerFlavour ){
    this->print = &prt;
    this->nameServer = &nameServer;
    this->id = id;
    this->sodaCost = sodaCost;
    this->maxStockPerFlavour = maxStockPerFlavour;
    exe = -1;
    noBuy = false;
    //Set stock to 0
    for( int i = 0; i < 2; i++ ) {
        stocks[i] = 0;
    }
}

VendingMachine::~VendingMachine(){
}

void VendingMachine::main(){
    print->print(Printer::Vending, id, 'S', sodaCost);
    //Register with nameserver
    nameServer->VMregister( this );    
    for(;;){
      _Accept( VendingMachine::~VendingMachine ){
            //if shutting down allow an inventory to finish
            print->print(Printer::Vending, id, 'F');
            if(noBuy) {
                _Accept(VendingMachine::restocked);
            }
            return;
        //if someone is refilling stock wait for finish
        } or _When(noBuy) _Accept( VendingMachine::restocked ){
            noBuy = false;
            print->print(Printer::Vending, id, 'R');
        //Otherwise allow both buy and inventory
        } or _When(!noBuy) _Accept( VendingMachine::inventory){
            noBuy = true;
            print->print(Printer::Vending, id, 'r');
        } or _When(!noBuy) _Accept( VendingMachine::buy ){
            exe = -1;
            unsigned int balance = card->getBalance();
            unsigned int stock = stocks[flav];
            //uRendezvousAcceptor();
            //Check for funds and stock erros
            if( balance < sodaCost ) {
                exe = 1;
            } else if( stock == 0 ) {
                exe = 0;
            } else {
            //seccuessful buy
                print->print(Printer::Vending, id, 'B', (int)flav, stocks[flav] - (unsigned int)1);
                stocks[flav]-=1;
                card->withdraw( sodaCost );
            }
            buyWait.signalBlock();    
        }
    }
}

void VendingMachine::buy( Flavours flavour, WATCard &card ){
    flav = flavour;
    this->card = &card;
    //Wait for buy to be accepted
    buyWait.wait();
    if( exe == 1 ) {
        throw VendingMachine::Funds();
    } else if( exe == 0) {
        throw VendingMachine::Stock();
    }
}

unsigned int* VendingMachine::inventory(){
    return stocks; 
}

void VendingMachine::restocked(){
}

//get cost or ID
unsigned int VendingMachine::cost() {
    return sodaCost;
}

unsigned int VendingMachine::getId(){
    return id;
}
