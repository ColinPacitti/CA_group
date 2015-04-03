#ifndef __WATCARD_H__
#define __WATCARD_H__

class WATCard {
  unsigned int balance;
  WATCard( const WATCard & );            // prevent copying
  WATCard &operator=( const WATCard & );
 public:
  WATCard();
  typedef Future_ISM<WATCard *> FWATCard; // future watcard pointer
  void deposit( unsigned int amount );//by courier
  void withdraw( unsigned int amount );//by vending machine
  unsigned int getBalance();
};

#endif
