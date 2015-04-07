#include "student.h"

#include <assert.h>

#include "nameserver.h"
#include "printer.h"
#include "watcardoffice.h"
#include <iostream>

extern MPRNG rand_gen;//!!! TODO: declare on driver

Student::Student(Printer &prt,NameServer &nameServer,WATCardOffice &cardOffice,unsigned int id,unsigned int maxPurchases):
  prt(prt),nameServer(nameServer), cardOffice(cardOffice),id(id),maxPurchases(maxPurchases){}

void Student::main(){
  //random choose a number of bottle to purchase [1,MaxPurchases]
  unsigned int myBottlesCount=rand_gen(1,maxPurchases);
  
  //a random favourite flavour [0,3]
  VendingMachine::Flavours myFlavour=VendingMachine::Flavours(rand_gen(3));
  
  prt.print(Printer::Student,id,'S',myFlavour,myBottlesCount);
  
  //create a WatCard via the WATCardOffice with $5 balance
  WATCard::FWATCard mycard=cardOffice.create(id,5);
  
  //obtains the location of a vending machine from the nameserver
  VendingMachine* mymachine=nameServer.getMachine(id);
  WATCard* fcard = NULL;
  //a student terminates after purchasing all the soda initally selected
  for (unsigned int i=0;i<myBottlesCount;i++){
    std::cout<<"sit:"<<i<<std::endl;
    //before each attempt to buy a soda, a student yield a random number of times [1,10]
    yield(rand_gen(1,10));
    
    prt.print(Printer::Student,id,'V',mymachine->getId());
    
    //the student may have to block until the amount transferr appears on their WATCard
    //!!! TODO: make exception on vending machine
    bool repeat=true;
    while(repeat){//for some reason i did not get my drink
      try{
	fcard=mycard();
	std::cout<<fcard->getBalance()<<std::endl;
	mymachine->buy(myFlavour,*fcard);
	//if no exception
	prt.print(Printer::Student,id,'B',mymachine->getId());
	repeat=false;//i just bought it
      }
      //if a courier has lost student's watcard, lost is raised
      //student must crate a new WATCard via WATCardOffice with $5, reattempt without yield
      catch(WATCardOffice::Lost e){
	mycard=cardOffice.create(id,5);
	prt.print(Printer::Student,id,'L');
      }
      //if vending machine indicates insufficient fund, student transfercurrent soda cost plus $5
      catch(VendingMachine::Funds e){
	std::cout << "funds" << std::endl;
	unsigned int amount=5+(mymachine->cost());
	std::cout << "before: " << fcard->getBalance() << std::endl;
	mycard=cardOffice.transfer(id,amount,fcard);
	//mycard();
	std::cout << "after: " << fcard->getBalance() << std::endl;
      }
      //if the vending machine is out of flavour, the student obtain a new vending machine
      catch(VendingMachine::Stock e){
	std::cout << "stocks" << std::endl;
	mymachine=nameServer.getMachine(id);
	prt.print(Printer::Student,id,'V',mymachine->getId());
      }
    }
    
    //update all variable for next purchase
    mymachine=nameServer.getMachine(id);
  }
  prt.print(Printer::Student,id,'F');
  delete fcard;
}
