#include "bottlingplant"
using namespace std;

extern MPRNG rand_gen;

BottlingPlant::BottlingPlant(Printer &prt,NameServer &nameServer,unsigned int numVendingMachines,
			     unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
			     unsigned int timeBetweenShipments )
  :prt(prt),nameServer(nameServer),numVendingMachines(numVendingMachines),
   maxShippedPerFlavour(maxShippedPerFlavour),maxStockPerFlavour(maxStockPerFlavour),
   timeBetweenShipments(timeBetweenShipments)
{
  //init stock space
  for(int i=0;i<4;i++){
    stock.push_back(0);
  }
}

void BottlingPlant::getShipment(unsigned int cargo[]){
  //the truck calls getShipment to obtain a shipment from the plant
  //and the shipment is copied into the cargo array passed by the truck
  if(shutdown){
    throw Shutdown;
  }
  
  for(unsigned int i=0;i<4;i++){
    cargo[i]=stock[i];
    cargo[i]=0;
  }
}

void BottlingPlant::main(){
  //it begines by creating a truck, performing a production run
  //MaxShippedPerFlavour is the maximum number of bottles of each flavour generated during production
  mytruck=new Truck(prt,nameServer,*this,numVendingMachines,maxStockPerFlavour);
  
  for(unsigned int i=0;i<maxShippedFlavour;i++){
    mynumber=(rand_gen(maxShippedFlavour))
      stock[i]=mynumber;
    totalcount+=mynumber;
  }
  
  while(true){
    //and waiting for the truck to pickup the production run
    _Accept(~BottlingPlant){
      shutdown=true;
      _Accept(getShipment);
    }
    or _Accept(getShipment){
      yield(timeBetweenShipments);
      for(unsigned int i=0;i<maxShippedFlavour;i++){
	mynumber=(rand_gen(maxShippedFlavour))
	stock[i]=mynumber;
	totalcount+=mynumber;
      }
    }
  }
}
