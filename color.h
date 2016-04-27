#ifndef _COLOR_H_
#define _COLOR_H_

class Color
{
public:
	Color();
	Color(double ri, double gi, double bi)
		: r(ri), g(gi), b(bi) { }
	double r, g, b;
protected:
private:
};

#endif 