#include "luces.h"

Luces::Luces()
{
	giro_x = 0.0;
	giro_y = 0.0;
	giro_z = 0.0;
}

void Luces::drawLights()
{
	luzBlanca();

	actualizarValorEfe(giro_x);
	actualizarValorEfe(giro_y);
	glPushMatrix();
		glRotatef(giro_x, 1.0, 0.0, 0.0);
		glRotatef(giro_y, 0.0, 1.0, 0.0);
		habilitarLuz();
	glPopMatrix();
}

void Luces::habilitarLuz()
{
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luz_ambiente);

	glLightfv(GL_LIGHT1, GL_AMBIENT, luz_ambiente);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luz_difusa);
	glLightfv(GL_LIGHT1, GL_SPECULAR, luz_espec);
	glLightfv(GL_LIGHT1, GL_POSITION, dir);

	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
}

void Luces::luzBlanca()
{
	//glLightfv(GL_LIGHT0, GL_POSITION, dir);

	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void Luces::actualizarValorEfe(const float valor_na)
{
	giro_x = 180 + 180*cos(0.5*(2.0*M_PI*valor_na));
	giro_y = 180 + 180*sin(0.5*(2.0*M_PI*valor_na));
	giro_z = 0.0;
}
