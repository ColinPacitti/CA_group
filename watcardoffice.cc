#include "watcardoffice.h"

//#include "watcard.h"
#include "bank.h"
#include "printer.h"

using namespace std;

extern MPRNG rand_gen;//!!! TODO: declare on driver

WATCardOffice::WATCardOffice(Printer &prt,Bank &bank,unsigned int numCouriers)
  :prt(prt),bank(bank),numCouriers(numCouriers),deleteflag(false)
{
  //Initally, the WATCard office creates a fixed sized courier pool to communicate with bank
  //additional couriers may not be created after the WATCardOffice begines
  courierPool=new Courier*[numCouriers];
  for(unsigned int i=0;i<numCouriers;i++){
    courierPool[i]=new Courier(i,this,prt);
  }
}

WATCard::FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount){
  //a student performs an asychronous call to create to create real WATCard with balance
  //COURIER: a future WATCard is returned and sufficient funds are subsequently obtained from bank
  //via a courier to satisfy the request
  Job* myjob=new Job(Args(sid,amount,NULL,bank));
  requests.push_back(myjob);
  //waitChan.signalBlock();//??? question, is this right, down there is same one
  return myjob->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ){
  //a student proform an asynchronous call to transfer when its WATCard indicates 
  //there is insufficient fund to buy soda
  //COURIER: A future WATCard is returned and suffieient funds are obtain from bank via courier
  Job* myjob=new Job(Args(sid,amount,card,bank));
  requests.push_back(myjob);
  //waitChan.signalBlock();
  return myjob->result;
}

WATCardOffice::Job* WATCardOffice::requestWork(){
  //Each courier task calls request Work, blocks until a job request is ready
  //and then receives the next Job request as the result of the call
  if(deleteflag){
    return NULL;//end the task now
  }
  
  //waitChan.wait();
  
  //return the head job and remove it from vector
  Job* thejob=requests[0];//get the job
  requests.erase(requests.begin());
  return thejob;
}

void WATCardOffice::main(){
  while(true){
    _Accept(~WATCardOffice){
      deleteflag=true;
      
      for(unsigned int i=0;i<numCouriers;i++){
	_Accept(requestWork);
      }
      
    }
    or _When(requests.size()==0) _Accept(create,transfer);
    or _Accept(requestWork);
  }
}

void WATCardOffice::Courier::main(){
  while(true){
    //each courier task calls requestWork, blocks until a job request is ready
    //and then receives the next job request as the result of the call
    WATCardOffice::Job* thejob=myoffice->requestWork();
    if(thejob==NULL) break;//break condition
    
    //as soon as the request is satisfied, the courier updates the student's WATCard
    //there is a 1 in 6 chance a courier loses a student's WatCard
    unsigned int lostChance=rand_gen(5);
    if(lostChance==0){
      WATCard* thecard=thejob->args.mycard;
      if(thecard!=NULL) delete thecard;//drop it
      thejob->result.exception(new Lost);
    }
    
    //or i do not drop it
    else{
      //obtain parameters
      Bank& thebank=thejob->args.mybank;
      unsigned int theid=thejob->args.sid;
      unsigned int theamount=thejob->args.myamount;
      WATCard* thecard=thejob->args.mycard;
      
      //withdraw from bank
      thebank.withdraw(theid,theamount);
      
      //add to watcard
      thecard->deposit(theamount);
      
      //tell future i done it
      thejob->result.delivery(thecard);
    }
    
    //clean up
    delete thejob;
  }
}

WATCardOffice::~WATCardOffice(){
  for(unsigned int i=0;i<numCouriers;i++){
    delete courierPool[i];
  }
  delete[] courierPool;
}

