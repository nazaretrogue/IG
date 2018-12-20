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
        void drawLights(int giro);
        void luzMagenta();
        void luzBlanca();
        void luzCeleste();
        void luzMarron();

    private:

        GLfloat luz_ambiente[4] = {0.1, 0.0, 0.1, 1.0};
    	GLfloat luz_espec[4] = {1.0, 0.0, 1.0, 1.0};
    	GLfloat luz_difusa[4] = {0.7, 0.0, 0.7, 1.0};

    	GLfloat pos[4] = {11.0, 11.0, 11.0, 1.0};
        GLfloat dir[4] = {-1.0, 1.0, 1.0, 0.0};

        GLfloat marron_amb[4] = {0.2, 0.2, 0.05, 1.0};
    	GLfloat marron_espec[4] = {0.7, 0.5, 0.3, 1.0};
    	GLfloat marron_dif[4] = {0.7, 0.5, 0.3, 1.0};

        GLfloat celeste_amb[4] = {0.1, 0.1, 0.1, 1.0};
    	GLfloat celeste_espec[4] = {0.4, 0.8, 1.0, 1.0};
    	GLfloat celeste_dif[4] = {0.4, 0.8, 1.0, 1.0};
};
