#include <fstream>
#include "Begoman.h"

//Begoman class
//begoman ID known
Begoman::Begoman(unsigned short i, unsigned short ring_bound) : id(i) {
	allRange(ring_bound);
}
//setters
void Begoman::range1(unsigned short s){r1=s;}
void Begoman::range2(unsigned short s){r2=s;}
void Begoman::range3(unsigned short s){r2=s;}
void Begoman::range4(unsigned short s){r2=s;}
void Begoman::time12(unsigned short s){t12=s;}
void Begoman::time13(unsigned short s){t13=s;}
void Begoman::time14(unsigned short s){t14=s;}
void Begoman::ID(unsigned short s){id=s;}
//ring_bound contains constexpr depending on number of rings
void Begoman::allRange(unsigned short ring_bound){
	r1=ring_bound;
	r2=ring_bound;
	r3=ring_bound;
	r4=ring_bound;
	t12=0xffff;
	t13=0xffff;
	t14=0xffff;
}
//getters
unsigned short Begoman::range1() const {return r1;}
unsigned short Begoman::range2() const {return r2;}
unsigned short Begoman::range3() const {return r3;}
unsigned short Begoman::range4() const {return r4;}
unsigned short Begoman::time12() const {return t12;}
unsigned short Begoman::time13() const {return t13;}
unsigned short Begoman::time14() const {return t14;}
unsigned short Begoman::ID() const {return id;}


//Manager class
//manager id known
Manager::Manager(unsigned char i) : id(i) {}
//setters
void Manager::ID(unsigned short s) {id=s;}
void Manager::behave(unsigned short s) {behavior=s;}
void Manager::total_through(unsigned short s){totalBegoman=s;}
//for making proper settings to control begoman, ie: control 5 begoman from id 3
void Manager::manage(unsigned short num){
	firstBegoId=id;
	numControl=num;
}
//getters
unsigned short Manager::ID() const{return id;}
unsigned short Manager::amount() const{return numControl;}
unsigned short Manager::first_id() const{return firstBegoId;}
unsigned short Manager::behave() const{return behavior;}
unsigned short Manager::total_through() const{return totalBegoman;}
