#include "printer.h"
#include "nameserver.h"
#include "bottlingplant.h"

_Task Truck {
void main();
Printer *print;
NameServer *nameServer;
BottlingPlant *plant;
unsigned int numVendingMachines;
unsigned int maxStockPerFlavour;
unsigned int stock [4];
public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
    unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};
