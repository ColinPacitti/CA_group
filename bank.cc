#include "bank.h"
using namepspace std;

Bank::Bank( unsigned int numStudents ) {
    waitCond = new uCondition[numStudents];
    for( int i = 0; i < numStudents; i++ ) {
        balances.push_back(0);
    }
}

void Bank::main() {

}

void Bank::deposit( unsigned int id, unsigned int amount ) {
    balances.at(id)+= amount;
}

void Bank::withdraw( unsigned int id, unsigned int amount ) {
    while( amount > balances.at(id) ) {
       waitCond[id].wait();
    }
    balances.at(id)-=amount;
}
