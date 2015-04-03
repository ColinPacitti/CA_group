#include "student.h"
#include "vendingmachine.h"
#include <assert.h>

extern MPRNG rand_gen;//!!! TODO: declare on driver

Student::Student(Printer &prt,NameServer &NameServer,WATCardOffice &cardOffice,unsigned int id,unsigned int maxPurchases):
  NameServer(NameServer), cardOffice(cardOffice),id(id),maxPurchases(maxPurchases){}

void Student::main(){
  //random choose a number of bottle to purchase [1,MaxPurchases]
  unsigned int myBottlesCount=rand_gen(1,maxPurchases);
  
  //a random favourite flavour [0,3]
  unsigned int myFlavour=rand_gen(3);
  
  //create a WatCard via the WATCardOffice with $5 balance
  Future_WATCard mycard=cardOffice.create(id,5);
  
  //obtains the location of a vending machine from the nameserver
  VendingMachine& mymachine=NameServer.getMachine(id);
  
  //a student terminates after purchasing all the soda initally selected
  for (unsigned int i=0;i<myBottlesCount;i++){
    //before each attempt to buy a soda, a student yield a random number of times [1,10]
    yield(rand_gen(1,10));
    
    //the student may have to block until the amount transferr appears on their WATCard
    //!!! TODO: make exception on vending machine
    bool repeat=true;
    while(repeat){//for some reason i did not get my drink
      try{
	_Enable{//cross stack
	  response=machine.buy(myFalvour,*(mycard()));
	  //if no exception
	  repeat=false;//i just bought it
	}
      }
      //if a courier has lost student's watcard, lost is raised
      //student must crate a new WATCard via WATCardOffice with $5, reattempt without yield
      catch(WATCardOffice::Lost e){
	mycard=office.create(id,5);
      }
      //if vending machine indicates insufficient fund, student transfercurrent soda cost plus $5
      catch(VendingMachine::Fund e){
	unsigned int amount=5+mymachine.cost();
	mycard=office.transfer(id,amount,mycard());
      }
      //if the vending machine is out of flavour, the student obtain a new vending machine
      catch(VendingMachine::Stock e){
	mymachine=NameServer.getMachine(id);
      }
    }
    
    //update all variable for next purchase
    mymachine=NameServer.getMachine(id);
  }
}
