#ifndef _BANK_
#define _BANK_

_Monitor Bank {
    vector<int> balances;
    uCondition *waitCond;
    void main();
    public:
        Bank( unsigned int  numStudents);
        void deposit( unsigned int id, unsigned int amount );
        void withdraw( unsigned int id, unsigned int amount );
}
#endif
