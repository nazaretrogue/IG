#include "textura.h"
#include <fstream>
#include <stdlib.h>

Textura::Textura()
{
    glGenTextures(1, &id_tex);
    glBindTexture(GL_TEXTURE_2D, id_tex);

    readImage();
}

void Textura::readImage()
{
    using namespace std;

    ifstream imagen("./skybox.jpg", ios::in|ios::binary);

    if(!imagen.is_open())
    {
        std::cerr << "Error al abrir la imagen" << std::endl;
        exit(1);
    }

    //calcularTexels();

    imagen.close();
}
