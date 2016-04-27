#ifndef _CIRCLE_H_
#define _CIRCLE_H_
#include "shape.h"

class Circle: public Shape
{
public:
	Circle();
	Circle(double x1, double y1, double radius, const Color &color_in);
	virtual void Paint();
	virtual int Clicked(double x, double y) const;
	virtual void SetY(double y, int p) { my1 = y; }
	virtual void SetX(double x, int p) { mx1 = x; }
	void SetPrevX(double x) { mPrevX = x; }
	void SetPrevY(double y) { mPrevY = y; }
	double GetPrevX() { return mPrevX; }
	double GetPrevY() { return mPrevY; }
	virtual void Save(std::ostream &os) const;
	virtual void Load(std::istream &is);
protected:
	double mPrevX, mPrevY;
	double mx1, my1;
	double mradius;
private:
};

#endif