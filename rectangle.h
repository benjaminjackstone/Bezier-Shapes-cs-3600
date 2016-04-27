#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_
#include "shape.h"

class Rectangle : public Shape
{

public:
	Rectangle();
	Rectangle(double x1, double y1, double x2, double y2, const Color &color_in);
	virtual void Paint();
	virtual int Clicked(double x, double y) const;
	virtual void SetY(double y, int p) { int tempy = my2 - my1; my1 = y; my2 = my1 + abs(tempy); }
	virtual void SetX(double x, int p) { int tempx = mx2 - mx1; mx1 = x; mx2 = mx1 + abs(tempx); }
	void SetPrevX(double x) { mPrevX = x; }
	void SetPrevY(double y) { mPrevY = y; }
	double GetPrevX() { return mPrevX; }
	double GetPrevY() { return mPrevY; }
	virtual void Save(std::ostream &os) const;
	virtual void Load(std::istream &is);
protected:
	double mx1, my1, mx2, my2, mPrevX, mPrevY;
private:
};

#endif