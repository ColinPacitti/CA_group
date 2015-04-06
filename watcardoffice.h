#ifndef __WATCARDOFFICE_H__
#define __WATCARDOFFICE_H__

#include "watcard.h"
#include "MPRNG.h"
//#include "bank.h"
//#include "printer.h"
#include <vector>

//class WATCard;
_Monitor Bank;
_Monitor Printer;

_Task WATCardOffice {
  _Task Courier;   
 
  //store info in Job
  struct Args{
    unsigned int sid;
    unsigned int myamount;
    WATCard* mycard;
    Bank& mybank;
    //constructor
  Args(unsigned int sid,unsigned int myamount, WATCard* mycard,Bank& mybank)
  :sid(sid),myamount(myamount),mycard(mycard),mybank(mybank)
    {}
  };
  

  struct Job {                         // marshalled arguments and return future
    Args args;                         // call arguments (YOU DEFINE "Args")
    WATCard::FWATCard result;          // return future
    //consturctor
  Job( Args args )
  :args( args ) 
    {}
  };

  
  _Task Courier {
    unsigned int id;
    WATCardOffice *myoffice;
    Printer& prt;
    void main();
  public:
    Courier(unsigned int id,WATCardOffice* myoffice,Printer& prt)
      :id(id),myoffice(myoffice),prt(prt)
      {}
  };                 // communicates with bank
  

  //pass in
  Printer& prt;
  Bank& bank;
  unsigned int numCouriers;

  std::vector<Job*>requests;//server request vector
  bool deleteflag;//use to sync when destruct
  Courier** courierPool;
  
  void main();

 public:
    _Event Lost {};                        // lost WATCard
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    ~WATCardOffice();
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job* requestWork();
};

#endif
