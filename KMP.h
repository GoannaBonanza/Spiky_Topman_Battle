#ifndef KMP_H_INCLUDED
#define KMP_H_INCLUDED
#include <fstream>
#include <iostream>
#include "Begoman.h"

class KMPObject{
private:
//for storing object info
unsigned char data[0x3c];
//little to big conversion
union{
	struct{unsigned char b, a;} s;
	unsigned short ab;
} mutable bigEnd;
//for writing a little short into 2 big bytes
void writeShort(unsigned short ab, unsigned char *pos);
void clear();
public:
//default, unknown object
KMPObject()=default;
KMPObject(unsigned char *);
//for constructing from begoman and manager objects
KMPObject(const Manager &);
KMPObject(const Begoman &);
KMPObject(const KMPObject &);
KMPObject& operator=(const KMPObject &);
KMPObject& operator=(const Manager &);
KMPObject& operator=(const Begoman &);
~KMPObject()=default;
//for position
void setPosition(float x, float y, float z);
void setRotation(float x, float y, float z);
//for placing kmp object into kmp file with proper shenanigans
friend std::ofstream& operator<<(std::ofstream &file, const KMPObject &obj){
	file.write((char *)obj.data, 0x3c);
	return file;
}
};

/*class KMPFile{
private:
//raw object section and easily editable object section
unsigned char *objectData=nullptr;
char *rawObjectData=nullptr;
//file offsets that need to be updated after objects added
char *offsets=nullptr;
//all remaining data after object section
char *postBuffer=nullptr;
public:
//no default KMP file
KMPFile()=delete;
//reads file data into rawdata and data, same pointer
KMPFile(const char*);
};*/


#endif //KMP_H_INCLUDED
