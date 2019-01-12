#include "aux.h"

// *****************************************************************************
//
// Clase Camara
//
// *****************************************************************************

class Camara
{
    public:

        Camara(bool camara_orto);
        void girar(GLfloat x, GLfloat y);
        void setObservador();
        void proyeccionOrto(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
        void proyeccionPerspectiva(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
        void iniciarCamaraOrto();
        void acercar();
        void alejar();
        bool esOrtogonal();

    private:

        GLfloat Observer_angle_x;
        GLfloat Observer_angle_y;
        GLfloat Observer_distance_pers, Observer_distance_ort;
        GLfloat right, left, bottom, top, near, far;
        bool orto;
};
