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
        void construirObjeto();

    private:

        GLuint id_tex;
        std::vector<Tupla3f> vertices;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
    	std::vector<Tupla3i> triangulos; // una terna de 3 enteros por cada cara o triángulo
        std::vector<Tupla2f> coor_tex;
};
