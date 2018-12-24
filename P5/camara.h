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
        void girar(int x, int y);
        void setObservador();

    private:

        float Observer_angle_x;
        float Observer_angle_y;
};
