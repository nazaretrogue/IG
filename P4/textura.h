#include "aux.h"

class Textura
{
    public:

        Textura();
        void readImage();
        void calcularTexels();

    private:

        GLuint id_tex;
};
