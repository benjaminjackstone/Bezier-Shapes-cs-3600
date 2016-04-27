
#include <cstdlib>
#include "glut.h"
#include "point.h"
#include "circle.h"
#include "triangle.h"
#include "slider.h"
#include "bezier.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <crtdbg.h>
#ifdef _WIN32
#else
#ifdef __APPLE__
#include <GLUT/glut.h>

#else
#include <GL/glut.h>
#endif
#endif

double screen_x = 700;
double screen_y = 500;
//button is a shape but still wanted its own vector
std::vector<Button *> g_buttons;
std::vector<Shape *> g_shapes;
std::vector<Point *> g_points;
//vector for redo button
std::vector<Shape *> g_old_shapes;
//track button position
const int BEZIER_MODE = 3;
const int CIRCLE_MODE = 0;
const int RECTANGLE_MODE = 1;
const int TRIANGLE_MODE = 2;
const int RED = 4;
const int GREEN = 5;
const int BLUE = 6;
const int UNDO = 7;
const int CLEAR = 8;
const int REDO = 9;
const int SAVE = 10;
const int LOAD = 11;
const int QUIT = 12;
const int SELECT_MODE = 13;
int mode = 0;
//initialize colors
double g_red = .55;
double g_green = .35;
double g_blue = .75;
bool select_mode = false;
double gPrevX = -1;
double gPrevY = -1;
int gselect = -1;
int gpoint = -1;
void DrawText(double x, double y, const char *string)
{
	void *font = GLUT_BITMAP_9_BY_15;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	int len, i;
	glRasterPos2d(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}

	glDisable(GL_BLEND);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(0, 0, 1);
	//kept points and buttons in separate vectors so they could be drawn and erased and saved differently
	std::vector<Shape *>::const_iterator sit;
	for (sit = g_shapes.begin(); sit != g_shapes.end(); sit++)
	{
		(*sit)->Paint();
	}
	std::vector<Button *>::const_iterator vit;
	for (vit = g_buttons.begin(); vit != g_buttons.end(); vit++)
	{
		(*vit)->Paint(*vit);
	}
	std::vector<Point *>::const_iterator pit;
	for (pit = g_points.begin(); pit != g_points.end(); pit++)
	{
		(*pit)->Paint();
	}

	glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 'q':
	case 27: // escape character means to quit the program

		exit(0);
		break;
	case 'b':
		// do something when 'b' character is hit.
		break;
	default:
		return; // if we don't care, return without glutPostRedisplay()
	}
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	screen_x = w;
	screen_y = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);

}

void mouse(int mouse_button, int state, int x, int y)
{
	// translate pixel coordinates to display coordinates
	double xdisplay = x;
	double ydisplay = screen_y - y;
	Circle *cir;
	Triangle *tri;
	Bezier *bez;
	Rectangle *rect;
	Color *color;
	Point *p;
	bool used = false;
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(mode != SELECT_MODE) gselect = -1;
		for (int i = 0; i <= BEZIER_MODE; i++){
			if (g_buttons[i]->Clicked(g_buttons[i], xdisplay, ydisplay)){
				for (int k = 0; k < g_buttons.size(); k++){
					g_buttons[k]->SetState(false);
				}
				g_buttons[i]->SetState(true);
				g_buttons[i]->ButtonPress(g_buttons[i], xdisplay, ydisplay);
				used = true;
				mode = i;
				select_mode = false;
			}
		}
		for (int j = RED; j < UNDO; j++){
			if (g_buttons[j]->Clicked(g_buttons[j], xdisplay, ydisplay)){
				if (j == RED){
					g_red = xdisplay / 100;
				}
				if (j == GREEN){
					g_green = xdisplay / 100;
				}
				if (j == BLUE){
					g_blue = xdisplay / 100;
				}
				for (int i = 0; i < g_buttons.size(); i++){
					g_buttons[i]->SetColor(g_buttons[i], g_red, g_green, g_blue);
				}
				used = true;
			}
		}

			for (int i = UNDO; i <= SELECT_MODE; i++){
				if (g_buttons[i]->Clicked(g_buttons[i], xdisplay, ydisplay)){
					g_buttons[i]->SetState(true);
					select_mode = false;
					if (i == SELECT_MODE) {
						for (int k = 0; k < g_buttons.size(); k++) {
							g_buttons[k]->SetState(false);
						}
						g_buttons[i]->SetState(true);
						g_buttons[i]->ButtonPress(g_buttons[i], xdisplay, ydisplay);
						used = true;
						mode = i;
						select_mode = true;
					}
					if (i == UNDO){
						gpoint = -1;
						gPrevX = 0;
						gPrevY = 0;
						//store erased shape element in restoring vector
						if (g_shapes.size() > 0){
							g_old_shapes.push_back(g_shapes.back());
							g_shapes.erase(g_shapes.begin() + g_shapes.size() - 1);
						}
						gselect = g_shapes.size() -1;
					}
					//clear shapes but first store them in vector for restoration
					if (i == CLEAR){
						for (int i = 0; i < g_shapes.size(); i++){
							g_old_shapes.push_back(g_shapes[i]);
						}
						gselect = -1;
						gpoint = -1;
						gPrevX = 0;
						gPrevY = 0;
						g_shapes.clear();
						g_points.clear();
					}
					if (i == REDO){
						//restore last delete shape
						if (g_old_shapes.size() > 0){
							g_shapes.push_back(g_old_shapes.back());
							g_old_shapes.erase(g_old_shapes.begin() + g_old_shapes.size() - 1);
						}
					}
					if (i == SAVE){
						std::ofstream fout("shapes1.txt");
						for (int i = 0; i < g_shapes.size(); i++){
							g_shapes[i]->Save(fout);
						}
						for (int i = 0; i < g_points.size(); i++){
							g_points[i]->Save(fout);
						}
						fout.close();
					}
					if (i == LOAD){
						
						g_shapes.clear();
						g_points.clear();
						std::ifstream fin("shapes1.txt");
						std::string key;
						while (fin >> key)
						{
						Shape *s = 0;
							if (key == "circle")
							{ 
								s = new Circle();//make a default constructor in classes
								s->Load(fin);
								g_shapes.push_back(s);
							}
							else if (key == "rectangle")
							{
								s = new Rectangle();//make a default constructor in classes
								s->Load(fin);
								g_shapes.push_back(s);
							}
							else if (key == "triangle")
							{
								s = new Triangle();//make a default constructor in classes
								s->Load(fin);
								g_shapes.push_back(s);
							}
							else if (key == "bezier")
							{
								s = new Bezier();//make a default constructor in classes
								s->Load(fin);
								g_shapes.push_back(s);
							}
							else if (key == "point")
							{

								p = new Point();
								p->Load(fin);
								g_points.push_back(p);
								}
							else{
								std::cerr << "error";
								
							}
						}
						fin.close();

					}
					used = true;
				}
			}
		if (!used){
			if (mode == CIRCLE_MODE){
				color = new Color(g_red, g_green, g_blue);
				p = new Point (xdisplay, ydisplay, *color);
				g_points.push_back(p);
				//distance formula to calculate the radius
				if (g_points.size() == 2){
					double x2 = (g_points[0]->x - g_points[1]->x) * (g_points[0]->x - g_points[1]->x);
					double y2 = (g_points[0]->y - g_points[1]->y) * (g_points[0]->y - g_points[1]->y);
					double radius = sqrt(x2 + y2);
					cir = new Circle(g_points[0]->x, g_points[0]->y, radius, *color);
					g_shapes.push_back(cir);
					g_points.clear();
					delete color;
				}
			}
			if (mode == RECTANGLE_MODE){
				color = new Color(g_red, g_green, g_blue);
				p = new Point(xdisplay, ydisplay, *color);
				g_points.push_back(p);
				if (g_points.size() == 2){
					rect = new Rectangle(g_points[0]->x, g_points[0]->y, g_points[1]->x, g_points[1]->y, *color);
					g_shapes.push_back(rect);
					g_points.clear();
					delete color;
				}
			}
			if (mode == TRIANGLE_MODE){
				color = new Color(g_red, g_green, g_blue);
				p = new Point(xdisplay, ydisplay, *color);
				g_points.push_back(p);
				if (g_points.size() == 3){
					tri = new Triangle(g_points[0]->x, g_points[0]->y, g_points[1]->x, g_points[1]->y, g_points[2]->x, g_points[2]->y, *color);
					g_shapes.push_back(tri);
					g_points.clear();
					delete color;
				}
			}
			if (mode == BEZIER_MODE) {
				color = new Color(g_red, g_green, g_blue);
				p = new Point(xdisplay, ydisplay, *color);
				g_points.push_back(p);
				if (g_points.size() == 3) {
					bez = new Bezier(g_points[0]->x, g_points[0]->y, g_points[1]->x, g_points[1]->y, g_points[2]->x, g_points[2]->y,/* g_points[3]->x, g_points[3]->y,*/ *color);
					g_shapes.push_back(bez);
					g_points.clear();
					delete color;
				}
			}
			if (mode == SELECT_MODE) {
				for (int i = 0; i < g_shapes.size(); i++) {
					gpoint = g_shapes[i]->Clicked(xdisplay, ydisplay);
					if (gpoint >= 0) {
						gselect = i;
						break;
					}
				}
			}
		}
	}
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (mode == SELECT_MODE && gselect >= 0) {
			g_shapes[gselect]->SetPrevX(0);
			g_shapes[gselect]->SetPrevY(0);
			//gselect = -1;
			gpoint = -1;
			gPrevX = 0;
			gPrevY = 0;
		}
		for (int i = UNDO; i <= QUIT; i++){
				g_buttons[i]->SetState(false);
				}
		if (g_buttons[QUIT]->Clicked(g_buttons[QUIT], xdisplay, ydisplay)){
			std::vector<Shape *>::const_iterator sit;
			for (sit = g_shapes.begin(); sit != g_shapes.end(); sit++)
			{
				delete (*sit);
			}
			std::vector<Button *>::const_iterator bit;
			for (bit = g_buttons.begin(); bit != g_buttons.end(); bit++)
			{
				delete (*bit);
			}
			std::vector<Shape *>::const_iterator oit;
			for (oit = g_old_shapes.begin(); oit != g_old_shapes.end(); oit++)
			{
				delete (*oit);
			}
			std::vector<Point *>::const_iterator pit;
			for (pit = g_points.begin(); pit != g_points.end(); oit++)
			{
				delete (*pit);
			}
			g_shapes.clear();
			g_points.clear();
			g_buttons.clear();
			g_old_shapes.clear();
			exit(0);
		}
		
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
	{
	}
	glutPostRedisplay();
}

void InitializeMyStuff()
{
	Button *b;
	Color *c;
	c = new Color(g_red, g_green, g_blue);
	b = new Button(5, 470, 25, 100, "Circle", false, *c);
	g_buttons.push_back(b);
	b = new Button(5, 440, 25, 100, "Rectangle", false, *c);
	g_buttons.push_back(b);
	b = new Button(5, 410, 25, 100, "Triangle", false, *c);
	g_buttons.push_back(b);
	b = new Button(5, 380, 25, 100, "Bezier", false, *c);
	g_buttons.push_back(b);
	b = new Button(5, 350, 25, 100, "REDS", false, *c);
	g_buttons.push_back(b);
	b = new Button(5, 320, 25, 100, "GREENS", false, *c);
	g_buttons.push_back(b);
	b = new Button(5, 290, 25, 100, "BLUES", false, *c);
	g_buttons.push_back(b);
	b = new Button(5, 260, 25, 100, "Undo", false, *c);
	g_buttons.push_back(b);
	b = new Button(5, 230, 25, 100, "Clear", false, *c);
	g_buttons.push_back(b);
	b = new Button(5, 200, 25, 100, "Redo", false, *c);
	g_buttons.push_back(b);
	b = new Button(5, 170, 25, 100, "Save", false, *c);
	g_buttons.push_back(b);
	b = new Button(5, 140, 25, 100, "Load", false, *c);
	g_buttons.push_back(b);
	b = new Button(5, 110, 25, 100, "Quit", false, *c);
	g_buttons.push_back(b);
	b = new Button(5, 80, 25, 100, "Select", false, *c);
	g_buttons.push_back(b);
	b = new Slider(55, 350, 25, 5, "", false, *c);
	g_buttons.push_back(b);
	b = new Slider(35, 320, 25, 5, "", false, *c);
	g_buttons.push_back(b);
	b = new Slider(75, 290, 25, 5, "", false, *c);
	g_buttons.push_back(b);
	for (int i = 0; i < g_buttons.size(); i++){
		g_buttons[i]->SetColor(g_buttons[i], g_red, g_green, g_blue);
	}
	delete c;

}

//motion function to handle the drag mouse
void motion(int x, int y){
	double xdisplay = x;
	double ydisplay = screen_y - y;
		for (int j = RED; j < UNDO; j++){
			if (g_buttons[j]->Clicked(g_buttons[j], xdisplay, ydisplay)){
				g_buttons[j+10]->SetX(xdisplay);
				if (j == RED){
					g_red = xdisplay / 100;
				}
				if (j == GREEN){
					g_green = xdisplay / 100;
				}
				if (j == BLUE){
					g_blue = xdisplay / 100;
				}
				for (int i = 0; i < g_buttons.size(); i++){
					g_buttons[i]->SetColor(g_buttons[i], g_red, g_green, g_blue);
				}
				if (mode == SELECT_MODE && gselect >= 0) {
					g_shapes[gselect]->SetColor(g_red, g_green, g_blue);
				}
				else if (g_shapes.size() > 0) {
					g_shapes[g_shapes.size() - 1]->SetColor(g_red, g_green, g_blue);
				}
			}
		}
		if (select_mode && gselect >= 0) {
					if (gPrevX > 0) {
						g_shapes[gselect]->SetPrevX(gPrevX);
						g_shapes[gselect]->SetPrevY(gPrevY);
					}
					g_shapes[gselect]->SetX(xdisplay, gpoint - 1);
					g_shapes[gselect]->SetY(ydisplay, gpoint - 1);
					gPrevX = xdisplay;
					gPrevY = ydisplay;
				}
	glutPostRedisplay();
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screen_x, screen_y);
	glutInitWindowPosition(50, 50);

	int fullscreen = 0;
	if (fullscreen)
	{
		glutGameModeString("800x600:32");
		glutEnterGameMode();
	}
	else
	{
		glutCreateWindow("Shapes Illustrator");
	}
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glColor3d(0, 0, 0); // forground color
	glClearColor(1, 1, 1, 0); // background color
	// Get current flag
	int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);

	// Turn on leak-checking bit.
	tmpFlag |= _CRTDBG_LEAK_CHECK_DF;

	// Set flag to the new value.
	_CrtSetDbgFlag(tmpFlag);
	InitializeMyStuff();
	glutMainLoop();
	return 0;
}