#include "aux.h"

// *****************************************************************************
//
// Clase Camara
//
// *****************************************************************************

class Camara
{
    public:

        Camara();
        Camara(bool camara_orto);
        void girar(int x, int y);
        void setObservador();
        void proyeccionOrto();

    private:

        float Observer_angle_x;
        float Observer_angle_y;
        GLfloat right, left, bottom, top, near, far;
};
