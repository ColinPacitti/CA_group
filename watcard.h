#ifndef __WATCARD_H__
#define __WATCARD_H__

#include <uFuture.h>

/*
class WATCard {
  unsigned int balance;
  WATCard( const WATCard & );            // prevent copying
  WATCard &operator=( const WATCard & );
 public:
  WATCard();
  void deposit( unsigned int amount );//by courier
  void withdraw( unsigned int amount );//by vending machine
  unsigned int getBalance();
};

typedef Future_ISM<WATCard*> FWATCard; // future watcard pointer
*/

class WATCard {
  private:
    unsigned int balance;
    WATCard( const WATCard & ) {}			// prevent copying
    WATCard &operator=( const WATCard & card);
  public:
    WATCard();
    void deposit( unsigned int amount );
    void withdraw( unsigned int amount );
    unsigned int getBalance();
};

typedef Future_ISM<WATCard *> FWATCard;	
#endif
