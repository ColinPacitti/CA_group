#ifndef __STUDENTS_H__
#define __STUDENTS_H__

#include "MPRNG.h"
#include "nameserver.h"
#include "printer.h"
#include "watcardoffice.h"

_Task Student{
 private:
  //pass in
  Printer& prt;
  NameServer& NameServer;
  WATCardOffice& cardOffice;
  unsigned int id;
  unsigned int maxPurchases;

  void main();
 public:
  Student(Printer &prt,NameServer &nameServer,WATCardOffice &cardOffice, unsigned int id,unsigned int maxPurchases);
}

#endif
