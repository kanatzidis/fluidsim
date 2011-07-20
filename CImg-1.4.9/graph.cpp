#include "CImg.h"
#include <iostream>
#include <fstream>

using namespace cimg_library;

class Point {
	public:
		int X;
		int Y;
		Point() {X=0; Y=0;}
		~Point() {}
};

bool split(std::string input, std::string first, std::string second, Point *p);
bool getnewp(Point *p);

std::ifstream data("icecube.prt");
char buffer[20];
int i;
bool timeslice;

int main() {
	i=0;
	timeslice=false;
	Point p,oldp;
	CImg<unsigned char> blank(100, 100, 1, 3, 0), visu(500, 500, 1, 3, 0);
	const unsigned char red[] = {255,0,0}, green[] = {0,255,0}, blue[] = {0,0,255};
	CImgDisplay main_disp(blank, "click to stop"), draw_disp(visu, "Fluid Vis");
	visu.fill(0);
	while(!draw_disp.is_closed()) {
		if(!timeslice){
		if(!main_disp.button()) {
		oldp.X = p.X; oldp.Y = p.Y;
		bool test=getnewp(&p);
		if(test) {
			if(0<=p.X<=500 && 0<=p.Y<=500) {
			visu(p.X, 500-p.Y, 0, 0)=255;
			visu(p.X, 500-p.Y, 0, 1)=0;
			visu(p.X, 500-p.Y, 0, 2)=0;
		}}
		if(data.eof()) {
			std::cout<<"End of File"<<std::endl;
			std::string s;
			std::cin>>s;
		}}
		else {
			std::cout<<i<<std::endl;
			return 0;
		}
	}else{
		visu.display(draw_disp);
		std::cout<<"advance to next timestep? [y/n] ";
		std::string y;
		std::cin>>y;
		if(!strcmp(y.c_str(),"y")){
			visu.fill(0);
			timeslice=false;
		}else{
			return 0;
		}
	}
	}
	return 0;
}

bool getnewp(Point *p) {
	char* x = "";
	char* y = "";
	if(!data.is_open()) {
		std::cout<<"Error opening file";
		exit(1);
	}
	if(!data.eof()) {
		data.getline(buffer, 19);
		if(split(buffer, x, y, p)) {
				return true;
			
		}else {
			p->X=0; p->Y=0;
			i++;
		}

		return false;
	}
		if(data.eof()) {
			std::cout<<"End of File"<<std::endl;
			return false;
		}
}

bool split(std::string input, std::string first, std::string second, Point *p) {
	std::string::size_type pos;
	pos=input.find(' ',0);
	if(pos==-1){
		timeslice=true;
		return false;
	}
	second=input.substr(pos+1);
	first=input.substr(0,pos);
	p->X=(int)(50*(atof(first.c_str()))+.5); p->Y=(int)(50*(atof(second.c_str()))+.5);	
	return true;
}
