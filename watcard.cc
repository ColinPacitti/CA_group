#include "watcard.h"

WATCard::WATCard():
  balance(0)
{}

WATCard::WATCard(const WATCard&){
  //prevent copying
}

WATCard::WATCard &operator=(const WATCard&){
  //prevent copying
}


void deposit(unsigned int amount){
  balance+=amount;
}

void withdraw(unsigned int amount){
  balance-=amount;
}

unsigned int getBalance(){
  return balance;
}
