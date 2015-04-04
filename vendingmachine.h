#ifndef __VENDINGMACHINE_H__
#define __VENDINGMACHINE_H__

#include "nameserver.h"
#include "printer.h"
#include "watcard.h"
#include "config.h"

_Task VendingMachine {
    int stocks [4];
    bool noBuy;
    Printer *print;
    NameServer *nameServer;
    unsigned int id;
    unsigned int sodaCost;
    unsigned int maxStockPerFlavour;
    void main();
    public:
        enum Flavours { CHERRY, LIME }; // flavours of soda (YOU DEFINE)
        Event Funds {}; // insufficient funds
        Event Stock {}; // out of stock for particular flavour
        VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                        unsigned int maxStockPerFlavour );
        void buy( Flavours flavour, WATCard &card );
        unsigned int *inventory();
        void restocked();
        Nomutex unsigned int cost();
        Nomutex unsigned int getId();
};
#endif
