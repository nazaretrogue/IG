#include "textura.h"

Textura::Textura()
{
    construirObjeto();
    calcularTexelsSkybox();
}

void Textura::readImageSkybox()
{
    // Cargamos la imagen
    CImg <unsigned char> image;
    image.load("./skybox.jpg");

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
    glGenTextures(1, &id_tex);
    glBindTexture(GL_TEXTURE_2D, id_tex);

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

void Textura::drawTextureSkybox()
{
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id_tex);

    glVertexPointer(3, GL_FLOAT, 0, vertices.data());
    glTexCoordPointer(2, GL_FLOAT, 0, coor_tex.data());

    glDrawElements(GL_TRIANGLES, 3*triangulos.size(), GL_UNSIGNED_INT, triangulos.data());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void Textura::calcularTexelsSkybox()
{
     coor_tex = {{0.25, 0.5},   // Textura del vértice 0
                 {0, 0.5},      // Textura del vértice 1
                 {0.25, 0.25},  // Textura del vértice 2
                 {0, 0.25},     // Textura del vértice 3
                 {0.5, 0.5},    // Textura del vértice 4
                 {0.75, 0.5},   // Textura del vértice 5
                 {0.5, 0.25},   // Textura del vértice 6
                 {0.75, 0.25},  // Textura del vértice 7
                 {1, 0.25},     // Textura del vértice 8
                 {1, 0.5},      // Textura del vértice 9
                 {0.25, 0},     // Textura del vértice 10
                 {0.5, 0},      // Textura del vértice 11
                 {0.25, 0.75},  // Textura del vértice 12
                 {0.5, 0.75}    // Textura del vértice 13
                };
}

void Textura::construirObjeto()
{
    // Hay que repetir vértices en este caso, a diferencia del cubo normal
    // ya que hay vértices con distintas coordenadas de textura

    vertices =  {  { -0.5, -0.5, -0.5 }, // 0
                   { -0.5, -0.5, +0.5 }, // 1
                   { -0.5, +0.5, -0.5 }, // 2
                   { -0.5, +0.5, +0.5 }, // 3
                   { +0.5, -0.5, -0.5 }, // 4
                   { +0.5, -0.5, +0.5 }, // 5
                   { +0.5, +0.5, -0.5 }, // 6
                   { +0.5, +0.5, +0.5 }, // 7
                   { -0.5, +0.5, +0.5 }, // 8
                   { -0.5, -0.5, +0.5 }, // 9
                   { -0.5, +0.5, +0.5 }, // 10
                   { +0.5, +0.5, +0.5 }, // 11
                   { -0.5, -0.5, +0.5 }, // 12
                   { +0.5, -0.5, +0.5 }  // 13
                };

    // inicializar la tabla de caras o triángulos:

    triangulos = { { 0, 2, 4 }, { 4, 2, 6 },
                   { 9, 5, 8 }, { 8, 5, 7 },
                   { 1, 3, 0 }, { 0, 3, 2 },
                   { 5, 4, 7 }, { 7, 4, 6 },
                   { 12, 0, 13 }, { 13, 0, 4 },
                   { 10, 11, 2 }, { 2, 11, 6 }
                 } ;
}
