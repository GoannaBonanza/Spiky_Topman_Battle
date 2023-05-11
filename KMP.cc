#include "KMP.h"
#include "Begoman.h"
#include <fstream>
//for writing a little short into 2 big bytes
void KMPObject::writeShort(unsigned short ab, unsigned char *pos){
	union{
		struct{unsigned char b, a;} s;
		unsigned short ab;
	} bigEnd;
	bigEnd.ab=ab;
	pos[0]=bigEnd.s.a;
	pos[1]=bigEnd.s.b;
}
void KMPObject::clear(){
	for(unsigned short i=0; i<0x3c; ++i){
		data[i]=0;
	}
}
//for constructing from begoman and manager objects
KMPObject::KMPObject(const Manager &ma){
	clear();
	//object id
	writeShort(ma.MANAGER_ID, &data[0x0]);
	//scale 1 on all axis
	data[0x1c]=0x3f;
	data[0x1d]=0x80;
	data[0x20]=0x3f;
	data[0x21]=0x80;
	data[0x24]=0x3f;
	data[0x25]=0x80;
	//route used, no route
	data[0x28]=0xff;
	data[0x29]=0xff;
	//object settings
	writeShort(ma.id, &data[0x2a]);
	writeShort(ma.numControl, &data[0x2c]);
	writeShort(ma.firstBegoId, &data[0x2e]);
	writeShort(ma.behavior, &data[0x30]);
	writeShort(ma.totalBegoman, &data[0x32]);
	//presence flag
	data[0x3b]=0x3f;
}
KMPObject::KMPObject(const Begoman &be){
	clear();
	//object id
	writeShort(be.BEGOMAN_ID, &data[0x0]);
	//scale 1 on all axis
	data[0x1c]=0x3f;
	data[0x1d]=0x80;
	data[0x20]=0x3f;
	data[0x21]=0x80;
	data[0x24]=0x3f;
	data[0x25]=0x80;
	//route used, no route
	data[0x28]=0xff;
	data[0x29]=0xff;
	//object settings
	writeShort(be.id, &data[0x2a]);
	writeShort(be.r1, &data[0x2c]);
	writeShort(be.t12, &data[0x2e]);
	writeShort(be.r2, &data[0x30]);
	writeShort(be.t13, &data[0x32]);
	writeShort(be.r3, &data[0x34]);
	writeShort(be.t14, &data[0x36]);
	writeShort(be.r4, &data[0x38]);
	//presence flag
	data[0x3b]=0x3f;
}
//DEBUGGING
KMPObject::KMPObject(unsigned char *pos){
	for(unsigned short i=0; i<0x3c; ++i) data[i]=pos[i];
}
KMPObject::KMPObject(const KMPObject &o){
	for(unsigned short i=0; i<0x3c; ++i) data[i]=o.data[i];
	bigEnd.ab=0;
}
KMPObject& KMPObject::operator=(const KMPObject &o){
	for(unsigned short i=0; i<0x3c; ++i) data[i]=o.data[i];
	bigEnd.ab=0;
	return *this;
}
KMPObject& KMPObject::operator=(const Manager &m){
	*this=KMPObject(m);
	return *this;
}
KMPObject& KMPObject::operator=(const Begoman &b){
	*this=KMPObject(b);
	return *this;
}
void KMPObject::setPosition(float x, float y, float z){
	auto writeFloat=[](float f, unsigned char *pos) -> void {
		union{
			struct{unsigned char d, c, b, a;} s;
			float abcd;
		} float_convert;
		float_convert.abcd=f;
		pos[0]=float_convert.s.a;
		pos[1]=float_convert.s.b;
		pos[2]=float_convert.s.c;
		pos[3]=float_convert.s.d;
	};
	writeFloat(x, &data[0x4]);
	writeFloat(y, &data[0x8]);
	writeFloat(z, &data[0xc]);
}
void KMPObject::setRotation(float x, float y, float z){
	auto writeFloat=[](float f, unsigned char *pos) -> void {
		union{
			struct{unsigned char d, c, b, a;} s;
			float abcd;
		} float_convert;
		float_convert.abcd=f;
		pos[0]=float_convert.s.a;
		pos[1]=float_convert.s.b;
		pos[2]=float_convert.s.c;
		pos[3]=float_convert.s.d;
	};
	writeFloat(x, &data[0x10]);
	writeFloat(y, &data[0x14]);
	writeFloat(z, &data[0x18]);
}
