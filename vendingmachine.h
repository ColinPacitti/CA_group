#ifndef __VENDINGMACHINE_H__
#define __VENDINGMACHINE_H__

//#include "nameserver.h"
//#include "printer.h"
//#include "watcard.h"
#include "config.h"

_Monitor Printer;
_Task BottlingPlant;
_Task NameServer;
class WATCard;

_Task VendingMachine {
    unsigned int stocks [5];
    bool noBuy;
    Printer *print;
    NameServer *nameServer;
    unsigned int id;
    unsigned int sodaCost;
    unsigned int maxStockPerFlavour;
    void main();
    public:
        enum Flavours { BLUES, CREAM, ROOT, LIME }; // flavours of soda (YOU DEFINE)
        _Event Funds {}; // insufficient funds
        _Event Stock {}; // out of stock for particular flavour
        VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                        unsigned int maxStockPerFlavour );
        void buy( Flavours flavour, WATCard &card );
        unsigned int *inventory();
        void restocked();
        _Nomutex unsigned int cost();
        _Nomutex unsigned int getId();
};
#endif
