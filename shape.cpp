#include "shape.h"

Shape::Shape(){

}


Shape::Shape( const Color &color_in)
	:color(color_in)
{

}

void Shape::SetColor(double r, double g, double b){
	color.r = r;
	color.g = g;
	color.b = b;
}