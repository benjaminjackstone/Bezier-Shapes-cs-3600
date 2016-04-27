#include "rectangle.h"

Rectangle::Rectangle(){

}
Rectangle::Rectangle(double x1, double y1, double x2, double y2, const Color &color_in)
	:Shape(color_in), mx1(x1), my1(y1), mx2(x2), my2(y2)
{
	mPrevY = 0;
	mPrevX = 0;
}
int Rectangle::Clicked(double x, double y) const {
	if (my1 < my2) {
		if (x > mx1      &&
			x < mx2 &&
			y > my1      &&
			y < my2) {
			return 1;
		}
	}
	if (my1 > my2) {
		if (x > mx1      &&
			x < mx2 &&
			y > my2      &&
			y < my1) {
			return 1;
		}
	}
	return -1;
}
void Rectangle::Paint()
{
	glColor3d(color.r, color.g, color.b);
	glBegin(GL_QUADS);
	glVertex2d(mx1, my1);
	glVertex2d(mx2, my1);
	glVertex2d(mx2, my2);
	glVertex2d(mx1, my2);
	glEnd();
}
void Rectangle::Save(std::ostream &os) const
{
	os << "rectangle " << mx1 << " " << my1 << " " << mx2 << " " << my2 << " "<< color.r << " " << color.g << " " << color.b << std::endl;
}
void Rectangle::Load(std::istream &is)
{
	is >>  mx1 >> my1 >> mx2 >> my2 >> color.r >> color.g >> color.b;
}