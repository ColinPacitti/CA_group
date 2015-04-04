#ifndef _BANK_
#define _BANK_
#include <vector>
using namespace std;
_Monitor Bank {
    vector<unsigned int> balances;
    uCondition *waitCond;
    public:
        Bank( unsigned int  numStudents);
        ~Bank();
        void deposit( unsigned int id, unsigned int amount );
        void withdraw( unsigned int id, unsigned int amount );
};
#endif
