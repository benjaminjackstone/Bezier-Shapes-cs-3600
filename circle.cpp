#include "circle.h"
#include <iostream>
Circle::Circle()
{

}
Circle::Circle(double x1, double y1, double radius, const Color &color_in)
	:Shape(color_in), mx1(x1), my1(y1), mradius(radius)
{
	mPrevX = 0;
	mPrevY = 0;
}
int Circle::Clicked(double x, double y) const {
	if (x > mx1 - mradius     &&
		x < mx1 + mradius &&
		y > my1 - mradius     &&
		y < my1 + mradius) {
		return 1;
	}
	return -1;
}
void Circle::Paint()
{
	glColor3d(color.r, color.g, color.b);
	glBegin(GL_POLYGON);
	for (int i = 0; i<32; i++)
	{
		double theta = (double)i / 32.0 * 2.0 * 3.1415926;
		double x = mx1 + mradius * cos(theta);
		double y = my1 + mradius * sin(theta);
		glVertex2d(x, y);
	}
	glEnd();
}
void Circle::Save(std::ostream &os) const
{
	os << "circle " << mx1 << " " << my1 << " " << mradius << " " << color.r << " " << color.g << " " << color.b << std::endl;
}
void Circle::Load(std::istream &is)
{
	is >> mx1 >> my1 >> mradius >> color.r >> color.g >> color.b;
}