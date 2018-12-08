#include "cuadro.h"

Cuadro::Cuadro()
{
    construirChess();
    calcularTexelsChess();
}

void Cuadro::readImageChess()
{
    // Cargamos la imagen
    CImg <unsigned char> image;
    image.load("./chess.jpg");

    std::vector<unsigned char> data;

    // Cargamos los datos
    for(long y=0; y<image.height(); y++)
    {
        for(long x=0; x<image.width(); x++)
        {
            unsigned char *r = image.data(x, y, 0, 0);
            unsigned char *g = image.data(x, y, 0, 1);
            unsigned char *b = image.data(x, y, 0, 2);

            data.push_back(*r);
            data.push_back(*g);
            data.push_back(*b);
        }
    }

    // Generamos la textura
    glGenTextures(1, &id_tex_chess);
    glBindTexture(GL_TEXTURE_2D, id_tex_chess);

    // Activamos la textura para que funcione
    glActiveTexture(GL_TEXTURE0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(),
                 0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);

    // Desactivamos la generación de textura
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Cuadro::drawTextureChess()
{
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id_tex_chess);

    glVertexPointer(3, GL_FLOAT, 0, vertices_chess.data());
    glTexCoordPointer(2, GL_FLOAT, 0, coor_tex_chess.data());

    glDrawElements(GL_TRIANGLES, 3*triangulos_chess.size(), GL_UNSIGNED_INT, triangulos_chess.data());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void Cuadro::calcularTexelsChess()
{
    coor_tex_chess = {{0.0, 1.0},
                      {1.0, 1.0},
                      {0.0, 0.0},
                      {1.0, 0.0}
                     };
}

void Cuadro::construirChess()
{
    // inicializar la tabla de vértices
    vertices_chess = {  {-1.0, -1.0, +0.0},
                        {+1.0, -1.0, +0.0},
                        {-1.0, +1.0, +0.0},
                        {+1.0, +1.0, +0.0}
                     };

    // inicializar la tabla de caras o triángulos:
    // (es importante en cada cara ordenar los vértices en sentido contrario
    //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

    triangulos_chess = {{0, 2, 1}, {1, 2, 3}};
}
