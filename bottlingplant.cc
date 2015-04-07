#include "bottlingplant.h"
#include "printer.h"
#include <iostream>
using namespace std;

extern MPRNG rand_gen;

BottlingPlant::BottlingPlant(Printer &prt,NameServer &nameServer,unsigned int numVendingMachines,
			     unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
			     unsigned int timeBetweenShipments )
  :prt(prt),nameServer(nameServer),numVendingMachines(numVendingMachines),
   maxShippedPerFlavour(maxShippedPerFlavour),maxStockPerFlavour(maxStockPerFlavour),
   timeBetweenShipments(timeBetweenShipments),totalcount(0),shutdown(false)
{
  //init stock space
  for(int i=0;i<4;i++){
    stock.push_back(0);
  }
  cout<<"begin:"<<shutdown<<endl;
}

void BottlingPlant::getShipment(unsigned int cargo[]){
  //the truck calls getShipment to obtain a shipment from the plant
  //and the shipment is copied into the cargo array passed by the truck
  cout<<"getship:"<<shutdown<<endl;
  if(shutdown){
    throw Shutdown();
  }
  
  prt.print(Printer::BottlingPlant,'P');
  
  //production run
  //??? consequence to move it here
  for(unsigned int i=0;i<maxShippedPerFlavour;i++){
    unsigned int mynumber=(rand_gen(maxShippedPerFlavour));
    stock[i]=mynumber;
    totalcount+=mynumber;
  }
  
  prt.print(Printer::BottlingPlant,'G',totalcount);
  
  //ready to ship
  for(unsigned int i=0;i<4;i++){
    cargo[i]=stock[i];
    cargo[i]=0;
  }
}

void BottlingPlant::main(){
  //it begines by creating a truck, performing a production run
  //MaxShippedPerFlavour is the maximum number of bottles of each flavour generated during production
  prt.print(Printer::BottlingPlant,'S');
  mytruck=new Truck(prt,nameServer,*this,numVendingMachines,maxStockPerFlavour);
  
  /*
  for(unsigned int i=0;i<maxShippedPerFlavour;i++){
    unsigned int mynumber=(rand_gen(maxShippedPerFlavour));
    stock[i]=mynumber;
    totalcount+=mynumber;
  }
  */
  
  while(true){
    //and waiting for the truck to pickup the production run
    _Accept(~BottlingPlant){
      shutdown=true;
      //uRendezvousAcceptor();
      _Accept(getShipment);
      break;
    }
    or _Accept(getShipment){
      yield(timeBetweenShipments);
      /*
      for(unsigned int i=0;i<maxShippedPerFlavour;i++){
	unsigned int mynumber=(rand_gen(maxShippedPerFlavour));
	stock[i]=mynumber;
	totalcount+=mynumber;
      }
      */
    }
  }
  prt.print(Printer::BottlingPlant,'F');
}
