#ifndef _SLIDER_H_
#define _SLIDER_H_

#include "button1.h"
class Slider : public Button
{
public:
	Slider(double x, double y, double h, double w, char *label, bool state, const Color &color_in);
protected:

private:

};
#endif