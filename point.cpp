#include "Point.h"

Point::Point()
{

}
Point::Point(double x_in, double y_in, const Color &color_in)
	: Shape(color_in), x(x_in), y(y_in)
{
	mPrevX = 0;
	mPrevY = 0;
}
int Point::Clicked(double xx, double yy)  const {

	if (x > xx      &&
		x < xx + 10 &&
		y > yy      &&
		y < yy + 10) {
		return 1;
	}
	return 0;
}
void Point::Paint()
{
	
	glColor3d(color.r, color.g, color.b);
	glPointSize(3.0);
	glBegin(GL_POINTS);
	glVertex2i(this->x, this->y);
	glEnd();
}
void Point::Save(std::ostream &os) const{
	os << "point " << x << " " << y << " " << color.r << " " << color.g << " " << color.b << std::endl;
}
void Point::Load(std::istream &is)
{
	is >> x >> y >> color.r >> color.g >> color.b;
}