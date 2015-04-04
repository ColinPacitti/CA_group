#include "bank.h"
using namespace std;

Bank::Bank( unsigned int numStudents ) {
    waitCond = new uCondition[numStudents];
    for( unsigned int i = 0; i < numStudents; i++ ) {
        balances.push_back(0);
    }
}

Bank::~Bank(){
    delete [] waitCond;
}

void Bank::deposit( unsigned int id, unsigned int amount ) {
    balances.at(id)+= amount;
    waitCond[id].signal();
}

void Bank::withdraw( unsigned int id, unsigned int amount ) {
    while( amount > balances.at(id) ) {
       waitCond[id].wait();
    }
    balances.at(id)-=amount;
}
