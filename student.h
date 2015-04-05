#ifndef __STUDENTS_H__
#define __STUDENTS_H__

#include "MPRNG.h"
#include "watcard.h"
#include "vendingmachine.h"
//#include "nameserver.h"
//#include "printer.h"
//#include "watcardoffice.h"

_Task NameServer;
_Monitor Printer;
_Task WATCardOffice;

_Task Student{
 private:
  //pass in
  Printer& prt;
  NameServer& nameServer;
  WATCardOffice& cardOffice;
  unsigned int id;
  unsigned int maxPurchases;

  void main();
 public:
  Student(Printer &prt,NameServer &nameServer,WATCardOffice &cardOffice, unsigned int id,unsigned int maxPurchases);
};

#endif
