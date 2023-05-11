#include "Begoman.h"
#include "KMP.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
void writeInt(unsigned int abcd, char *pos){
	union{
		struct{unsigned char d, c, b, a;} s;
		unsigned int abcd;
	} bigEnd;
	bigEnd.abcd=abcd;
	pos[0]=bigEnd.s.a;
	pos[1]=bigEnd.s.b;
	pos[2]=bigEnd.s.c;
	pos[3]=bigEnd.s.d;
}
void perfect_polygon(unsigned short count, const Begoman &begoman, ofstream &file, const float FALL_HEIGHT=15000, const float distance_from_center=1000){
	//make object out of topman
	KMPObject obj(begoman);
	if(count==1){
		obj.setPosition(0, FALL_HEIGHT, 0);
		file << obj;
		return;
	}
	if(count==2){
		obj.setPosition(distance_from_center, FALL_HEIGHT, 0);
		file << obj;
		obj.setPosition(-distance_from_center, FALL_HEIGHT, 0);
		file << obj;
		return;
	}
	//get angle jump
	const float angle=360/count;
	float total_angle=0;
	float xpos, zpos;
	for(unsigned short i=0; i<count; ++i){
		//make point with sine and cosine
		xpos=cos(total_angle*0.0175)*distance_from_center;
		zpos=sin(total_angle*0.0175)*distance_from_center;
		//set object position and write it to file
		obj.setPosition(xpos, FALL_HEIGHT, zpos);
		file << obj;
		total_angle+=angle;
	}
}
void start_begoman(unsigned short count, const Begoman &begoman, ofstream &file){
	//starting positions
	static constexpr float X1START=-478;
	static constexpr float X2START=1482;
	static constexpr float X3START=-2172;
	static constexpr float YSTART=9940;
	static constexpr float Z1START=-2421;
	static constexpr float Z2START=-2226;
	static constexpr float Z3START=-1455;
	static constexpr float R1=9;
	static constexpr float R2=-34;
	static constexpr float R3=58;
	KMPObject topman(begoman);
	if(count>3){
		//not feasable starting positions known, make polygon
		perfect_polygon(count, begoman, file, YSTART);
		return;
	}
	else if(count==1 || count==3){
		topman.setPosition(X1START, YSTART, Z1START);
		topman.setRotation(0, R1, 0);
		file << topman;
		if(count==3){
			topman.setPosition(X2START, YSTART, Z2START);
			topman.setRotation(0, R2, 0);
			file << topman;
			topman.setPosition(X3START, YSTART, Z3START);
			topman.setRotation(0, R3, 0);
			file << topman;
		}
		return;
	}
	else if(count==2){
		topman.setPosition(X2START, YSTART, Z2START);
		topman.setRotation(0, R2, 0);
		file << topman;
		topman.setPosition(X3START, YSTART, Z3START);
		topman.setRotation(0, R3, 0);
		file << topman;
	}
}
void make_begoman(Begoman &begoman, unsigned short ring_count){
	switch (ring_count){
	case 1:
		begoman.allRange(begoman.RING1);
		break;
	case 2:
		begoman.allRange(begoman.RING2);
		break;
	case 3:
		begoman.allRange(begoman.RING3);
		break;
	default:
		//already at NORING
		break;
	}
}
void set_topman_settings(unsigned short *topman_control, unsigned short manager_count, char *prog){
	for(unsigned short i=0; i<manager_count; ++i){
		//get number of topmen to control for each
		unsigned short count=0;
		unsigned short behavior=0;
		cout << "How many topman are controlled by manager " << i << " >>> ";
		cin >> count;
		if(!cin){
			cerr << prog << "Bad input given\n";
			delete[] topman_control;
			exit(1);
		}
		cout << "What is the topman behavior (0 for default) for manager " << i << " >>> ";
		cin >> behavior;
		if(!cin){
			cerr << prog << "Bad input given\n";
			delete[] topman_control;
			exit(1);
		}
		if(count>255 || count==0){
			cerr << prog << ": Too many or too few topmen, must be (1-255)\n";
			delete[] topman_control;
			exit(1);
		}
		topman_control[i]=count;
		topman_control[i+manager_count]=behavior;
	}
}
unsigned int make_big(char *pos){
	//takes 4 chars and interprets them as a big endian int
	union{
		struct{unsigned char d, c, b, a;} s;
		unsigned int abcd;
	} bigEnd;
	bigEnd.s.a=pos[0];
	bigEnd.s.b=pos[1];
	bigEnd.s.c=pos[2];
	bigEnd.s.d=pos[3];
	return bigEnd.abcd;
}
void writeNewObjects(unsigned short *topman_control, Begoman &begoman, unsigned short manager_count, ofstream &file){
	for(unsigned short i=0; i<manager_count; ++i){
		//make topman for each manager, uses fact that all topman with ID will be treated correctly by manager
		begoman.ID(i+1);
		//now write all topmen to file
		if(i==0) start_begoman(topman_control[i], begoman, file);
		else perfect_polygon(topman_control[i], begoman, file);
	}
	//loop through all managers
	for(unsigned short i=0; i<manager_count; ++i){
		Manager manager(0);
		unsigned short count;
		manager.ID(i+1);
		i!=(manager_count-1)?manager.manage(topman_control[i]):manager.manage(0);
		manager.behave(topman_control[i+manager_count]);
		count=0;
		for(unsigned short j=0; j<i+1; ++j){
			count+=topman_control[j];
		}
		//setting 5, unknown, assumed to be total number of topmen controlled through this point?
		i!=0?manager.total_through(count):manager.total_through(0);
		//manager created, now place object into file
		file << KMPObject(manager);
	}
} 
void writeToFile(unsigned short *topman_control, Begoman &begoman, unsigned short manager_count, const char *filename="new_topman.kmp"){
	//slightly modified topman 222 tournament kmp for building off
	ifstream reference("course.kmp");
	//get header into file
	char file_header[0x4c];
	reference.seekg(0);
	reference.read(file_header, 0x4c);
	//offset values
	unsigned int gobj=make_big(&file_header[0x2c]), poti=make_big(&file_header[0x30]), area=make_big(&file_header[0x34]),
	came=make_big(&file_header[0x38]), jgpt=make_big(&file_header[0x3c]), cnpt=make_big(&file_header[0x40]),
	mspt=make_big(&file_header[0x44]), stgi=make_big(&file_header[0x48]);
	//make array for all data up until gobj
	char *pre_GOBJ=new char[gobj];
	reference.read(pre_GOBJ, gobj);
	//for object count updating
	char gobj_header[0x8];
	reference.read(gobj_header, 0x8);
	//for existing objects and rest of file
	reference.seekg(0, reference.end);
	//get end of file minus header, section header, and gobj length array
	unsigned int remlen=reference.tellg();
	reference.seekg(gobj+0x8+0x4c);
	//remaining data after gobj header until end of file
	char *remainder=new char[remlen-0x4c-gobj-0x8];
	reference.read(remainder, remlen-0x4c-gobj-0x8);
	//all data now stored in arrays
	unsigned short total_new_objects=0;
	//add all topmen
	for(unsigned short i=0; i<manager_count; ++i) total_new_objects+=topman_control[i];
	total_new_objects+=manager_count;
	//update all offsets;
	poti+=0x3c*total_new_objects;
	area+=0x3c*total_new_objects;
	came+=0x3c*total_new_objects;
	jgpt+=0x3c*total_new_objects;
	cnpt+=0x3c*total_new_objects;
	mspt+=0x3c*total_new_objects;
	stgi+=0x3c*total_new_objects;
	//cout << poti << ' ' << area << ' ' << came << ' ' << jgpt << ' ' << cnpt << ' ' << mspt << ' ' << stgi << '\n';
	//uptade header
	writeInt(poti, &file_header[0x30]);
	writeInt(area, &file_header[0x34]);
	writeInt(came, &file_header[0x38]);
	writeInt(jgpt, &file_header[0x3c]);
	writeInt(cnpt, &file_header[0x40]);
	writeInt(mspt, &file_header[0x44]);
	writeInt(stgi, &file_header[0x48]);
	gobj_header[0x5]+=total_new_objects;
	//now start writing to file
	ofstream file(filename);
	file.write(file_header, 0x4c);
	file.write(pre_GOBJ, gobj);
	file.write(gobj_header, 0x8);
	//insert the new objects
	writeNewObjects(topman_control, begoman, manager_count, file);
	//finally, write the rest of the file
	file.write(remainder, remlen-0x4c-gobj-0x8);
	delete[] remainder;
	delete[] pre_GOBJ;
}
int main(int argc, char **argv){
	if(!ifstream("course.kmp")){
		cerr << argv[0] << ": No default KMP present, should be regular galaxy arena with no begoman or managers\n";
		return 1;
	}
	unsigned short manager_count, ring_count;
	Begoman begoman(0, begoman.NORING);
	cout << "How many topman managers are there >>> ";
	cin >> manager_count;
	if(manager_count>256 || manager_count==0){
		//technically could be more than 256 managers but come on
		cerr << argv[0] << ": Invalid amount of managers, must be (1-256)\n";
		return 1;
	}
	cout << "How many rings are present >>> ";
	cin >> ring_count;
	if(ring_count>3){
		cerr << argv[0] << ": Too many rings present, must be (0-3)\n";
		return 1;
	}
	make_begoman(begoman, ring_count);
	//how many topmen controlled by each manager
	unsigned short *topman_control=new unsigned short[manager_count*2];
	set_topman_settings(topman_control, manager_count, argv[0]);
	//topman_control should contain manager_count counts followed by manager_count behaviors
	argc==1?writeToFile(topman_control, begoman, manager_count):writeToFile(topman_control, begoman, manager_count, argv[1]);
	//writeToFile should never fail, excluding extreme cases
	delete[] topman_control;
	return 0;
}
