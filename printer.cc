#include "printer.h"
#include <iostream>
#include <vector>
using namespace std;

Printer::Printer(unsigned int numStudents, unsigned int numVendingMachines,unsigned int numCouriers)
  :numStudents(numStudents),numVendingMachines(numVendingMachines),numCouriers(numCouriers)
{
  cout<<"Parent";
  cout<<"\t";
  cout<<"WATOff";
  cout<<"\t";
  cout<<"Names";
  cout<<"\t";
  cout<<"Truck";
  cout<<"\t";
  cout<<"Plant";
  cout<<"\t";
  
  for(int i=0;i<5;i++){
    storages.push_back(storage('0',(unsigned int)0,(unsigned int)0,false));
  }
  
  for(unsigned int i=0;i<numStudents;i++){
    cout<<"Stud"<<i<<"\t";
    storages.push_back(storage('0',(unsigned int)0,(unsigned int)0,false));
  }
  
  for (unsigned int i=0;i<numVendingMachines;i++){
    cout<<"Mach"<<i<<"\t";
    storages.push_back(storage('0',(unsigned int)0,(unsigned int)0,false));
  }
  
  for (unsigned int i=0;i<numCouriers;i++){
    cout<<"Cour"<<i<<"\t";
    storages.push_back(storage('0',(unsigned int)0,(unsigned int)0,false));
  }
  cout<<endl;
  
  totalCount=5+numStudents+numVendingMachines+numCouriers;
  for (unsigned int i=0;i<totalCount;i++){
    cout<<"*******"<<"\t";
  }
  
  cout<<endl;
}


//print all blocks, and reset values
void Printer::flush(){
  bool haveData=false;
  //check if any data there
  for (unsigned int i=0;i<totalCount;i++){
    if(storages[i].flag) haveData=true;
  }
  if(!haveData) return;
  
  for(unsigned int i=0;i<totalCount;i++){
    if(storages[i].flag){//only print if there is data
      storages[i].flag=false;
      cout<<storages[i].state;
      if(storages[i].value1==NULL){
	cout<<"\t";
	continue;
      }
      cout<<storages[i].value1;
      if(storages[i].value2==NULL){
	cout<<"\t";
	continue;
      }
      cout<<','<<storages[i].value2;
      //cout<<"\t";
    }
    cout<<"\t";
  }
  cout<<endl;
}

//just reset all blocks, so clear a line
void Printer::reset(){
  for(int i=0;i<totalCount;i++){
    storages[i].flag=false;
  }
}

_Mutex void Printer::helper( unsigned int index, char state, unsigned int value1, unsigned int value2) {
  //check if state is F first
  //if it is, just print it.
  if(state=='F'){
    flush();
    for(unsigned int i=0;i<totalCount;i++){
      if(index==i){
	cout<<"F"<<"\t";
      }
      else{
	cout<<"..."<<"\t";
      }
    }
    cout<<endl;
    return;
  }
  
  if(storages[index].flag){//flush and store information
    flush();
  }

  storages[index]=(storage(state,value1,value2,true));
}

void Printer::debug(){
  cout<<"ddddebug"<<endl;
  for (int i=0;i<storages.size();i++){
    cout<<storages[i].state<<" "<<storages[i].value1<<" "<<storages[i].value2<<storages[i].flag<<endl;
  }
}

void Printer::print(Kind kind,char state){
  unsigned int myindex=getindex(kind,0);
  //debug();
  helper(myindex,state,NULL,NULL);
}

void Printer::print( Kind kind, char state, int value1 ){
  helper(getindex(kind,0),state,value1,NULL);
}

void Printer::print( Kind kind, char state, int value1, int value2 ){
  helper(getindex(kind,0),state,value1,value2);
}

void Printer::print( Kind kind, unsigned int lid, char state ){
  helper(getindex(kind,lid),state,NULL,NULL);
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ){
  helper(getindex(kind,lid),state,value1,NULL);
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ){
  //cout<<"vvv::"<<value1<<" "<<value2<<endl;
  helper(getindex(kind,lid),state,value1,value2);
}

Printer::~Printer(){
  cout<<"***********************"<<endl;
}

unsigned int Printer::getindex(Kind kind,unsigned int index){
  //unsigned int value;
  // WATCardOffice, NameServer, Truck, BottlingPlant,
  //Student, Vending, Courier
  switch(kind){
  case Parent:
    return 0;
    break;
  case WATCardOffice:
    return 1;
    break;
  case NameServer:
    return 2;
    break;
  case Truck:
    return 3;
    break;
  case BottlingPlant:
    return 4;
    break;
  case Student:
    return 5+index;
    break;
  case Vending:
    return 5+numStudents+index;
    break;
  case Courier:
    //default:
    return 5+numStudents+numVendingMachines+index;
    break;
  }
  return 0;
}

/*

void uMain::main(){
  Printer p (3,3,3);
  p.print(Printer::Parent,'F');
  //p.print(Printer::Truck,'d',14,15);
  //p.print(Printer::Courier,2,'c');
  //p.print(Printer::Courier,2,'c',12,23);
  //p.print(Printer::Courier,'c',2);
  //p.print(Printer::Courier,'c',2);

  p.print(Printer::WATCardOffice,'S');
  p.print(Printer::NameServer,'S');
  p.print(Printer::Truck,'S');
  p.print(Printer::BottlingPlant,'S');
  p.print(Printer::BottlingPlant,'S');
  
  p.print(Printer::Parent,'F');
}
*/
