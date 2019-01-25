#define cimg_display 0
#include "CImg.h"
#include "aux.h"

using namespace cimg_library;

class Cuadro
{
    public:

        Cuadro();

        // Métodos para el chess board
        void readImageChess();
        void calcularTexelsChess();
        void drawTextureChess();
        void construirChess();

    private:

        // Atributos del chess board
        GLuint id_tex_chess;
        std::vector<Tupla3f> vertices_chess;
        std::vector<Tupla3i> triangulos_chess;
        std::vector<Tupla2f> coor_tex_chess;
};
