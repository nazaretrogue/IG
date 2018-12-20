#define cimg_display 0
#include "CImg.h"
#include "aux.h"

using namespace cimg_library;

class Textura
{
    public:

        Textura();

        // Métodos para el skybox
        void readImageSkybox();
        void calcularTexelsSkybox();
        void drawTextureSkybox();
        void construirObjeto();

    private:

        // Atributos del skybox
        GLuint id_tex;
        std::vector<Tupla3f> vertices;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
    	std::vector<Tupla3i> triangulos; // una terna de 3 enteros por cada cara o triángulo
        std::vector<Tupla2f> coor_tex;   // coordenadas de textura
};
