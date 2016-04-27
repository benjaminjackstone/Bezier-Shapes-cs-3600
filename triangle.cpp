#include "shape.h"
#include "triangle.h"
#include <iostream>
Triangle::Triangle(){

}
Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3, const Color &color_in)
	:Shape(color_in), mx1(x1), mx2(x2), mx3(x3), my1(y1), my2(y2), my3(y3)
{
	mPrevX = 0;
	mPrevY = 0;
}
void Triangle::SetY(double y, int p) { 
	int tempy = my2 - my1;
	int tempy3 = my3 - my1;
	my1 = y; 
	my2 = my1 + abs(tempy); 
	my3 = my1 + abs(tempy3);
}

void Triangle::SetX(double x, int p) { 
	int tempx = mx2 - mx1;
	int tempx3 = mx3 - mx1;
	mx1 = x; mx2 = mx1 + abs(tempx);
	mx3 = mx1 + abs(tempx3);
}

int Triangle::Clicked(double x, double y) const {
	if (mx1 >= mx2 >= mx3) {
		if (x > mx3      &&
			x < mx1 &&
			y > my3      &&
			y < my2) {
			return 1;
		}
	}
	if (mx1 >= mx3 >= mx2) {
		if (x > mx2      &&
			x < mx1 &&
			y > my2      &&
			y < my3) {
			return 1;
		}
	}
	if (mx2 >= mx1 >= mx3) {
		if (x > mx3      &&
			x < mx2 &&
			y > my3      &&
			y < my1) {
			return 1;
		}
	}
	if (mx2 >= mx3 >= mx1) {
		if (x > mx1      &&
			x < mx2 &&
			y > my1      &&
			y < my3) {
			return 1;
		}
	}
	if (mx3 >= mx1 >= mx2) {
		if (x > mx2      &&
			x < mx3 &&
			y > my2      &&
			y < my1) {
			return 1;
		}
	}
	if (mx3 >= mx2 >= mx1) {
		if (x > mx1      &&
			x < mx3 &&
			y > my1      &&
			y < my3) {
			return 1;
		}
	}
	return -1;
}
void Triangle::Paint()
{
	glColor3d(color.r, color.g, color.b);
	glBegin(GL_TRIANGLES);
	glVertex2d(mx1, my1);
	glVertex2d(mx2, my2);
	glVertex2d(mx3, my3);
	glEnd();
}
void Triangle::Save(std::ostream &os) const
{
	os << "triangle " << mx1 << " " << my1 << " " << mx2 << " " << my2 << " " << mx3 << " " << my3 << " " << color.r << " " << color.g << " " << color.b << std::endl;
}
void Triangle::Load(std::istream &is)
{
	is >> mx1 >> my1 >> mx2 >> my2 >> mx3 >> my3 >> color.r >> color.g >> color.b;
}