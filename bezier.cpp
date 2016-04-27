#include "shape.h"
#include "point.h"
#include "bezier.h"
#include <iostream>
#include <vector>
//std::vector<std::vector<double>> gLines;
Bezier::Bezier() {
}
Bezier::Bezier(double x1, double y1, double x2, double y2, double x3, double y3/*, double x4, double y4*/,const Color &color_in)
	:Shape(color_in), mx1(x1), my1(y1), mx2(x2), my2(y2), mx3(x3), my3(y3)//, mx4(x4), my4(y4)
{
	mPoints.push_back(Point(mx1, my1, color));
	mPoints.push_back(Point(mx2, my2, color));
	mPoints.push_back(Point(mx3, my3, color));
	//mPoints.push_back(Point(mx4, my4, color));
	mPrevX = 0;
	mPrevY = 0;
}
int Bezier::Clicked(const double x, const double y) const {
	for (int i = 0; i < mPoints.size(); i++) {
		if (x > mPoints[i].x - 20      &&
			x < mPoints[i].x + 20 &&
			y > mPoints[i].y - 20 &&
			y < mPoints[i].y + 20) {
			return i+1;
		}
	}
	for (int i = 0; i < gLines.size(); i++) {
		if (x > gLines[i][0] - 20 &&
			x < gLines[i][0] + 20 &&
			y > gLines[i][1] - 20 &&
			y < gLines[i][1] + 20) {
			return 10;
		}
	}
	return -1;
}

Point Bezier::Evaluate(double t) const {
	//double pX = mPoints[0].x*(1 - t)*(1 - t)*(1 - t) + 3 * mPoints[1].x*(1 - t)*(1 - t)*t + 3 * mPoints[2].x*(1 - t)*t*t + mPoints[3].x*t*t*t;
	//double pY = mPoints[0].y*(1 - t)*(1 - t)*(1 - t) + 3 * mPoints[1].y*(1 - t)*(1 - t)*t + 3 * mPoints[2].y*(1 - t)*t*t + mPoints[3].y*t*t*t;
	double pX = mPoints[0].x*(1 - t)*(1 - t) + 2 * mPoints[1].x*(1 - t)*t + mPoints[2].x*t*t;
	double pY = mPoints[0].y*(1 - t)*(1 - t) + 2 * mPoints[1].y*(1 - t)*t + mPoints[2].y*t*t;
	Point point = Point(pX, pY, color);
	return point;
}

void Bezier::Paint()
{
	gLines = {};
	double tInc = 1.0 / 20.0;
	glColor3d(color.r, color.g, color.b);
	glLineWidth(2.5);
	glBegin(GL_LINES);
	double currT = 0;
	Point pre = Point(mPoints[0].x, mPoints[0].y,color);
	Point currP;
	for (int i = 0; i <= 20; i++){
		std::vector<double> points;
		currP = Evaluate(currT);
		glVertex2f(pre.x, pre.y);
		points.push_back(pre.x);
		points.push_back(pre.y);
		glVertex2f(currP.x, currP.y);
		gLines.push_back(points);
		pre = currP;
		currT += tInc;
	}
	glEnd();
	glPointSize(7.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < mPoints.size(); i++) {
		glVertex2i(mPoints[i].x, mPoints[i].y);
	}
	glEnd();
}
void Bezier::SetY(double y, int p) {
	if (p == 9 && mPrevY > 0) {
		for (int i = 0; i < mPoints.size(); i++) {
			mPoints[i].y += (y - GetPrevY());
		}
	}
	if(p < 4 && p >= 0) {
		mPoints[p].y = y;
	}
}
void Bezier::SetX(double x, int p) {
	if (p > 4 && mPrevX > 0) {
			for (int i = 0; i < mPoints.size(); i++) {
				mPoints[i].x += (x - GetPrevX());
			}
	}
	if (p < 4 && p >= 0) {
		mPoints[p].x = x;
	}
}
void Bezier::Save(std::ostream &os) const
{
	os << "bezier " << mPoints[0].x << " " << mPoints[0].y << " " << mPoints[1].x << " " << mPoints[1].y << " " << mPoints[2].x << " " << mPoints[2].y << " " /*<< mPoints[3].x << " " << mPoints[3].y << " " << color.r << " "*/ << color.g << " " << color.b << std::endl;
}
void Bezier::Load(std::istream &is)
{
	is >> mx1 >> my1 >> mx2 >> my2 >> mx3 >> my3/* >> mx4 >> my4*/ >> color.r >> color.g >> color.b;
	mPoints.push_back(Point(mx1, my1, color));
	mPoints.push_back(Point(mx2, my2, color));
	mPoints.push_back(Point(mx3, my3, color));
	//mPoints.push_back(Point(mx4, my4, color));
	mPrevX = 0;
	mPrevY = 0;
}