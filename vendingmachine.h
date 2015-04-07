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
    public:
        enum Flavours { BLUES = 0, CREAM = 1, ROOT = 2, LIME = 3 }; // flavours of soda (YOU DEFINE)
        _Event Funds {}; // insufficient funds
        _Event Stock {}; // out of stock for particular flavour
        VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                        unsigned int maxStockPerFlavour );
        void buy( Flavours flavour, WATCard &card );
        ~VendingMachine();
        unsigned int *inventory();
        void restocked();
        _Nomutex unsigned int cost();
        _Nomutex unsigned int getId();
    private:
        int exe;
        Flavours flav;
        WATCard *card;
        unsigned int stocks [5];
        bool noBuy;
        Printer *print;
        NameServer *nameServer;
        unsigned int id;
        unsigned int sodaCost;
        unsigned int maxStockPerFlavour;
        uCondition buyWait;
        void main();
};
#endif
