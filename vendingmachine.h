#include "nameserver.h"
#include "printer.h"
#include "watcard.h"
#include "config.h"

_Task Printer;
_Task BottlingPlant;

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
