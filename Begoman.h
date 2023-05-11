#ifndef BEGOMAN_H_INCLUDED
#define BEGOMAN_H_INCLUDED
#include <fstream>
#include <iostream>
//#include "KMP.h"
class Begoman{
private:
unsigned short id, r1, t12, r2, t13, r3, t14, r4;
public:
//for ease of making default begomans
static constexpr unsigned short NORING=0x1068;
static constexpr unsigned short RING1=0x1518;
static constexpr unsigned short RING2=0x1af4;
static constexpr unsigned short RING3=0x20d0;
static constexpr unsigned short BEGOMAN_ID=0x1a3;
//empty begoman cannot exist
Begoman()=delete;
//begoman ID known
Begoman(unsigned short i, unsigned short ring_bound);
//default stuff
~Begoman()=default;
Begoman(const Begoman &)=default;
Begoman& operator=(const Begoman &)=default;
//setters
void range1(unsigned short s);
void range2(unsigned short s);
void range3(unsigned short s);
void range4(unsigned short s);
void time12(unsigned short s);
void time13(unsigned short s);
void time14(unsigned short s);
void ID(unsigned short s);
//ring_bound contains constexpr depending on number of rings
void allRange(unsigned short ring_bound);
//getters
unsigned short range1() const;
unsigned short range2() const;
unsigned short range3() const;
unsigned short range4() const;
unsigned short time12() const;
unsigned short time13() const;
unsigned short time14() const;
unsigned short ID() const;
friend class KMPObject;
};

class Manager{
private:
//settings
unsigned short id, numControl, firstBegoId, behavior, totalBegoman, s6=0, s7=0, s8=0;
//static variables
static constexpr unsigned short MANAGER_ID=0x16;
public:
//default manager not possible
Manager()=delete;
//manager id known
Manager(unsigned char);
//standard stuff
~Manager()=default;
Manager(const Manager &)=default;
Manager& operator=(const Manager &)=default;
//setters
void ID(unsigned short);
void behave(unsigned short);
void total_through(unsigned short);
//for making proper settings to control begoman, ie: control 5 begoman from id 3
void manage(unsigned short num);
//getters
unsigned short ID() const;
unsigned short amount() const;
unsigned short first_id() const;
unsigned short behave() const;
unsigned short total_through() const;
friend class KMPObject;
};


#endif //BEGOMAN_H_INCLUDED
