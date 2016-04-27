#ifndef _SHAPE_H_
#define _SHAPE_H_
#include <string>
#include <vector>
#include <fstream>
#include <istream>
#include <set>
#include <cmath>
#include "color.h"
#include "glut.h"
class Shape
{
public:
	Shape();
	Shape(const Color &color_in);
	virtual void Paint() = 0;
	virtual int Clicked(double x, double y) const = 0;
	virtual void SetX(double x, int p) = 0;
	virtual void SetY(double y, int p) = 0;
	virtual void SetPrevX(double x) = 0;
	virtual void SetPrevY(double y) = 0;
	virtual double GetPrevX() = 0;
	virtual double GetPrevY() = 0;
	void SetColor(double r, double g, double b);
	virtual void Save(std::ostream &os) const = 0;
	virtual void Load(std::istream &is) = 0;
	//virtual void std::vector<Point> getPoints() const = 0
protected:
	Color color;

private:
};

#endif