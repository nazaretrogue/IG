#include "aux.h"

// *****************************************************************************
//
// Clase Luces
//
// *****************************************************************************

class Luces
{
    public:

        Luces();
        void drawLights();
        void luzMagenta();
        void luzBlanca();
        void actualizarValorEfe(const float valor_na);

    private:

        GLfloat luz_ambiente[4] = {0.1, 0.0, 0.1, 1.0};
    	GLfloat luz_espec[4] = {1.0, 0.0, 1.0, 1.0};
    	GLfloat luz_difusa[4] = {0.7, 0.0, 0.7, 1.0};
    	GLfloat pos[4] = {0.0, 1.0, 1.0, 1.0};
        GLfloat dir[4] = {0.0, 0.0, 1.0, 0.0};

        float giro_x, giro_y, giro_z;
};
