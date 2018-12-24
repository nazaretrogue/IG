#include "camara.h"

Camara::Camara()
{
    Observer_angle_x = 0.0;
    Observer_angle_y = 0.0;
}

void Camara::girar(int x, int y)
{
    if(x < Observer_angle_x)
		Observer_angle_x--;
	else if(x > Observer_angle_x)
		Observer_angle_x++;

	else if(y < Observer_angle_y)
		Observer_angle_y--;
	else if(y > Observer_angle_y)
		Observer_angle_y++;
}

void Camara::setObservador()
{
    glRotatef(Observer_angle_x, 1.0, 0.0, 0.0);
    glRotatef(Observer_angle_y, 0.0, 1.0, 0.0);
}
