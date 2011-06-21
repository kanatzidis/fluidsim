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

bool getnewp(Point *p);

std::ifstream data("circle.dat");
char buffer[20];

int main() {
	Point p,oldp;
	CImg<unsigned char> visu(1100, 205, 1, 3, 0);
	const unsigned char red[] = {255,0,0}, green[] = {0,255,0}, blue[] = {0,0,255};
	CImgDisplay draw_disp(visu, "Fluid Vis");
	visu.fill(0);
	while(!draw_disp.is_closed()) {
		oldp = p;
		if(getnewp(&p)&&!data.eof()) {
			visu.draw_line(oldp.X, oldp.Y, p.X, p.Y, green).display(draw_disp);
		}
	}
}

bool getnewp(Point *p) {
	char* x;
	char* y;
	if(!data.is_open()) {
		std::cout<<"Error opening file";
		exit(1);
	}
	if(!data.eof()) {
		data.getline(buffer, 19);
		for(int i=0; i<20; i++) {
			char* c = &buffer[i];
			if(strcmp(c," ")==0) {
				for(int j=0; j<i; j++) {
					x+= buffer[j];
				}
				for(int j=i+1; j<20; j++) {
					y+= buffer[j];
				}

				p->X=(1100*atoi(x)/22); p->Y=(205*atoi(y)/4.1);
				return true;
			}
		}
		return false;
	}
}

