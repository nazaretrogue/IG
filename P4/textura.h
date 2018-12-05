#define cimg_display 0
#include "CImg.h"
#include "aux.h"

using namespace cimg_library;


class Textura
{
    public:

        Textura();
        void readImage();
        void calcularTexels();
        void drawTexture();
        
    private:

        GLuint id_tex;
};
