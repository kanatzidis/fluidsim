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

void split(std::string input, std::string first, std::string second, Point *p);
bool getnewp(Point *p);

std::ifstream data("circle.dat");
char buffer[20];
int i;

int main() {
	i=0;
	Point p,oldp;
	CImg<unsigned char> blank(100, 100, 1, 3, 0), visu(1100, 205, 1, 3, 0);
	const unsigned char red[] = {255,0,0}, green[] = {0,255,0}, blue[] = {0,0,255};
	CImgDisplay main_disp(blank, "click to stop"), draw_disp(visu, "Fluid Vis");
	visu.fill(0);
	while(!draw_disp.is_closed()) {
		if(!main_disp.button()) {
		oldp.X = p.X; oldp.Y = p.Y;
		bool test=getnewp(&p);
		if(test) {
			visu.draw_line(oldp.X, oldp.Y, p.X, p.Y, green).display(draw_disp);
		}
		if(data.eof()) {
			std::cout<<"End of File"<<std::endl;
			std::string s;
			std::cin>>s;
		}}
		else {
			std::cout<<i<<std::endl;
			return 0;
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
		if(!(strcmp(buffer, "338")==0)) {
			split(buffer, x ,y, p);
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

void split(std::string input, std::string first, std::string second, Point *p) {
	std::string::size_type pos;
	pos=input.find(' ',0);
	second=input.substr(pos+1);
	first=input.substr(0,pos);
	p->X=(int)(50*(atof(first.c_str()))+.5); p->Y=(int)(50*(atof(second.c_str()))+.5);	
}
