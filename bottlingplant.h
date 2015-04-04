#ifndef __BOTTLINGPLANT_H__
#define __BOTTLINGPLANT_H__

#include "MPRNG.h"
#include "nameserver.h"
#include "truck.h"
#include <vector>

_Task BottlingPlant {
  void main();
  //pass in
  Printer& prt;
  NameServer& nameServer;
  unsigned int numVendingMachines;
  unsigned int maxShippedPerFlavour;
  unsigned int maxStockPerFlavour;
  unsigned int timeBetweenShipments;

  std::vector<unsigned int>stock;
  Truck* mytruck;
  unsigned int totalcount;
  bool shutdown;//bool to indicate shut down
 public:
  _Event Shutdown {};                    // shutdown plant
  BottlingPlant(Printer &prt,NameServer &nameServer,unsigned int numVendingMachines,
                unsigned int maxShippedPerFlavour,unsigned int maxStockPerFlavour,
                unsigned int timeBetweenShipments);
  void getShipment(unsigned int cargo[]);
  };
  
#endif
