#include "watcardoffice.h"

WATCardOffice::WATCardOffice(Printer &prt,Bank &bank,unsigned int numCouriers)
  :prt(prt),bank(bank),numCouriers(numCouriers),requests(NULL),deleteflag(false)
{
  //Initally, the WATCard office creates a fixed sized courier pool to communicate with bank
  //additional couriers may not be created after the WATCardOffice begines
  courierPool=new Couriers(numCouriers);
  for(unsigned int i=0;i<numCouriers;i++){
    courierPool[i]=new Courier(i,this,prt);
  }
}

WATCard::FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount){
  //a student performs an asychronous call to create to create real WATCard with balance
  //COURIER: a future WATCard is returned and sufficient funds are subsequently obtained from bank
  //via a courier to satisfy the request
  myjob=new Job(Args(sid,amount,NULL,bank));
  requests.push_back(myjob);
  return myjob->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ){
  //a student proform an asynchronous call to transfer when its WATCard indicates 
  //there is insufficient fund to buy soda
  //COURIER: A future WATCard is returned and suffieient funds are obtain from bank via courier
  myjob=new Job(Args(sid,amount,card,bank));
  requests.push_back(myjob);
  return myjob->result;
}

Job* WATCardOffice::requestWork(){
  //Each courier task calls request Work, blocks until a job request is ready
  //and then receives the next Job request as the result of the call
  if(deleteflag){
    return NULL;//end the task now
  }
  //return the head job and remove it from vector
  Job* thejob=requests.front();//??? block at this position?
  requests.pop_front();
  return thejob;
}

void WATCardOffice::Courier::main(){
  while(true){
    Job* thejob=requestWork();
    if(thejob==NULL) break;//break condition
    
    
  }
}

WATCardOffice::~WATCardOffice(){
  //dynamic fill in
  for(unsigned int i=0;i<numCouriers;i++){
    delete courierPool[i];
  }
  delete courierPool;
}
