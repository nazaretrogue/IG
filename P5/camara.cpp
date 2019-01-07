#include "camara.h"

Camara::Camara()
{
    Observer_angle_x = 0.0;
    Observer_angle_y = 0.0;
}

Camara::Camara(bool camara_orto)
{
    if(camara_orto)
    {
        left = -5.0;
        right = 5.0;
        bottom = -5.0;
        top = 5.0;
        near = 2.0;
        far = 12.0;
    }
}

void Camara::girar(int x, int y)
{
    Observer_angle_x += x;
    Observer_angle_y += y;
}

void Camara::setObservador()
{
    glRotatef(Observer_angle_x, 1.0, 0.0, 0.0);
    glRotatef(Observer_angle_y, 0.0, 1.0, 0.0);
}

void Camara::proyeccionOrto()
{
    glOrtho(left, right, bottom, top, near, far);
}
