#include "button1.h"
#include <cstdlib>
#include <iostream>

Button::Button(double x, double y, double h, double w, char *label, bool state, const Color &color_in)
	:Rectangle(x, y, w, h, color_in), mx(x), my(y), mh(h), mw(w), mlabel(label), mstate(state)
{
	SetX(x);
	SetY(y);
	SetH(h);
	SetW(w);
	SetLabel(label);
	SetState(state);
}

bool Button::SetX(double x1){
	this->mx = x1;
	return true;
}
bool Button::SetY(double y1){
	this->my = y1;
	return true;
}
bool Button::SetH(double h1){
	this->mh = h1;
	return true;
}
bool Button::SetW(double w1){
	this->mw = w1;
	return true;
}
bool Button::SetLabel(char* label){
	this->mlabel = label;
	return true;
}

bool Button::GetState(){
	return this->mstate;
}
bool Button::SetState(bool state){
	this->mstate = state;
	return true;
}
void Button::ButtonPress(Button *b, double x, double y)
{
	if (b)
	{
		/*
			if the mouse moved over the control
		*/
		if (Clicked(b, x, y))
		{
			
			if (b->highlighted == 0) {
				b->highlighted = 1;
			}
		}
		else

			/*
			
			*/
			if (b->highlighted == 1)
			{
				b->highlighted = 0;
			}
	}
}
bool Button::Clicked(Button *b, double x, double y){
	if (b){
		if (x > b->mx      &&
			x < b->mx + b->mw &&
			y > b->my      &&
			y < b->my + b->mh){
			return true;
		}
	}
	return false;
}


void Button::Font(void *font, char *text, double x, double y){
	glRasterPos2i(x, y);

	while (*text != '\0')
	{
		glutBitmapCharacter(font, *text);
		++text;
	}
}


void Button::SetColor(Button *b, double red, double green, double blue){
	this->r = red;
	this->g = green;
	this->b = blue;
}
void Button::Paint(Button *b){
	int fontx;
	int fonty;

	if (b)
	{
		glColor3f(0.6f, 0.6f, 0.6f);

		if (b->mlabel == "REDS" || b->mlabel == "GREENS" || b->mlabel == "BLUES"){
			glColor3f(this->r, this->g, this->b);
		}
		//if button is clicked, change color

		else if (b->GetState()){
			glColor3f(0.7f, 0.7f, 0.8f);
		}


		//draw background for the button.
		glBegin(GL_QUADS);
		glVertex2i(b->mx, b->my);
		glVertex2i(b->mx, b->my + b->mh);
		glVertex2i(b->mx + b->mw, b->my + b->mh);
		glVertex2i(b->mx + b->mw, b->my);
		glEnd();

		/*
		*	Draw an outline around the button
		*/
		glLineWidth(4);

		/*
		*	The colors for the outline are reversed when the button.
		*/
		if (b->mstate){
			glColor3f(0.4f, 0.4f, 0.4f);
		}
		else{
			glColor3f(0.8f, 0.8f, 0.8f);

			glBegin(GL_LINE_STRIP);
			glVertex2i(b->mx + b->mw, b->my);
			glVertex2i(b->mx, b->my);
			glVertex2i(b->mx, b->my + b->mh);
			glEnd();
		}
		if (b->mstate){
			glColor3f(0.8f, 0.8f, 0.8f);
		}
		else{
			glColor3f(0.4f, 0.4f, 0.4f);

			glBegin(GL_LINE_STRIP);
			glVertex2i(b->mx, b->my + b->mh);
			glVertex2i(b->mx + b->mw, b->my + b->mh);
			glVertex2i(b->mx + b->mw, b->my);
			glEnd();
			glLineWidth(2);
		}




		//	Calculate the x and y coords for the text string in order to center it.

		fontx = b->mx + 5;
		fonty = b->my + 5;


		/*	if the button is pressed, make it look as though the string has been pushed
		*	down.
		*/
		if (b->mstate) {
			fontx += 2;
			fonty += 2;
		}


		if (b->mlabel == "REDS"){
			glColor3f(.5, 0, 0);

			Font(GLUT_BITMAP_HELVETICA_18, b->mlabel, fontx, fonty);
		}
		else if (b->mlabel == "GREENS"){
			glColor3f(0, .5, 0);

			Font(GLUT_BITMAP_HELVETICA_18, b->mlabel, fontx, fonty);
		}
		else if (b->mlabel == "BLUES"){
			glColor3f(0, 0, .5);

			Font(GLUT_BITMAP_HELVETICA_18, b->mlabel, fontx, fonty);
		}
		else{
			glColor3f(1, 1, 1);

			Font(GLUT_BITMAP_HELVETICA_18, b->mlabel, fontx, fonty);
		}
	}

}