#ifndef _POINT_H_
#define _POINT_H_
#include "shape.h"

class Point: public Shape
{
public:
	Point();
	Point(double x_in, double y_in, const Color &color_in);
	virtual void Paint();
	virtual int Clicked(double x, double y) const;
	virtual void SetY(double y, int p) {}
	virtual void SetX(double x, int p) { }
	void SetPrevX(double x) { mPrevX = x; }
	void SetPrevY(double y) { mPrevY = y; }
	double GetPrevX() { return mPrevX; }
	double GetPrevY() { return mPrevY; }
	virtual void Save(std::ostream &os) const;
	virtual void Load(std::istream &is);
	double x, y;
protected:
	double mPrevX, mPrevY;
private:
};
#endif