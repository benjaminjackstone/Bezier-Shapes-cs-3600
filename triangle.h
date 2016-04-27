#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

class Triangle: public Shape
{
public:
	Triangle();
	Triangle(double x1, double y1, double x2, double y2, double x3, double y3, const Color &color_in);
	virtual void Paint();
	virtual int Clicked(double x, double y) const;
	virtual void SetY(double y, int p);
	virtual void SetX(double x, int p);
	void SetPrevX(double x) { mPrevX = x; }
	void SetPrevY(double y) { mPrevY = y; }
	double GetPrevX() { return mPrevX; }
	double GetPrevY() { return mPrevY; }
	virtual void Save(std::ostream &os) const;
	virtual void Load(std::istream &is);
protected:
	double mx1, my1, mx2, my2, mx3, my3, mPrevX, mPrevY;
private:
};

#endif