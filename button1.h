#ifndef _BUTTON_H_
#define _BUTTON_H_
#include "rectangle.h"

class Button : public Rectangle
{
public:
	Button(double x, double y, double h, double w, char* label, bool state, const Color &color_in);
	bool SetState(bool state);
	bool Clicked(Button *b, double x, double y);
	void ButtonPress(Button *b, double x, double y);
	virtual void Paint(Button *b);
	void Font(void *font, char* text, double x, double y);
	void SetColor(Button *b, double red, double green, double blue);
	bool SetX(double x1);
	bool SetY(double y1);
	bool SetH(double h1);
	bool SetW(double w1);
	bool SetLabel(char* label);
	bool GetState();


protected:
	int highlighted;
	double mx, my, mw, mh;
	double r, g, b;
	char * mlabel;
	bool mstate;

};


#endif