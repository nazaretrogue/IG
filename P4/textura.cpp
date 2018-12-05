#include "textura.h"

Textura::Textura()
{
    readImage();
}

void Textura::readImage()
{
    // Cargamos la imagen
    CImg <unsigned char> image;
    image.load("skybox.jpg");

    unsigned char *r, *g, *b;
    std::vector<unsigned char> data;

    // Cargamos los datos
    for(long y=0; y<image.height(); y++)
    {
        for(long x=0; x<image.width(); x++)
        {
            r = image.data(x, y, 0, 0);
            g = image.data(x, y, 0, 1);
            b = image.data(x, y, 0, 2);

            data.push_back(*r);
            data.push_back(*g);
            data.push_back(*b);
        }
    }

    // Generamos la textura_id
    glGenTextures(1, &id_tex);
    glBindTexture(GL_TEXTURE_2D, id_tex);

    // Activamos la textura para que funcione
    glActiveTexture(GL_TEXTURE0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(),
                 0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);
}

void Textura::drawTexture()
{

}
