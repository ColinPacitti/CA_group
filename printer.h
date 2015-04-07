#ifndef __PRINTER_H__
#define __PRINTER_H__
#include <vector>
using namespace std;

_Monitor Printer{ 
 
public:
  enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
  Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
  ~Printer();
  void print( Kind kind, char state );
  void print( Kind kind, char state, int value1 );
  void print( Kind kind, char state, int value1, int value2 );
  void print( Kind kind, unsigned int lid, char state );
  void print( Kind kind, unsigned int lid, char state, int value1 );
  void print( Kind kind, unsigned int lid, char state, int value1, int value2 );

 private:
 struct storage{
    char state;
    unsigned int value1;
    unsigned int value2;
    bool flag;
  storage(char state,unsigned int value1,unsigned int value2,bool flag)
  :state(state),value1(value1),value2(value2),flag(flag)
    {}
  };
  vector<storage>storages;
  void helper(unsigned int index, char state, unsigned int value1, unsigned int value2);
  unsigned int getindex(Kind kind,unsigned int index);
  void reset();
  void debug();
  
  //pass in
  unsigned int numStudents;
  unsigned int numVendingMachines;
  unsigned int numCouriers;
  
  unsigned int totalCount;
  void flush();  
};

#endif
