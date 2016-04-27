#ifndef _BEZIER_H_
#define _BEZIER_H_

class Bezier : public Shape
{
public:
	Bezier();
	Bezier(double x1, double y1, double x2, double y2, double x3, double y3,/* double x4, double y4,*/ const Color &color_in);
	virtual void Paint();
	virtual int Clicked(double x, double y) const;
	Point Evaluate(double t) const;
	void SetY(double y, int p);
	void SetX(double x, int p);
	void SetPrevX(double x) { mPrevX = x;}
	void SetPrevY(double y) { mPrevY = y; }
	double GetPrevX() { return mPrevX; }
	double GetPrevY() { return mPrevY; }
	virtual void Save(std::ostream &os) const;
	virtual void Load(std::istream &is);
protected:
	double mx1, my1, mx2, my2, mx3, my3;// , mx4, my4;
	double mPrevX;
	double mPrevY;
private:
	std::vector<std::vector<double>> gLines;
	std::vector<Point> mPoints;
};

#endif