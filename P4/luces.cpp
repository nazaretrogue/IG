#include "luces.h"

Luces::Luces() {}

void Luces::drawLights(int giro)
{
	luzBlanca();

	glPushMatrix();
		glRotatef(giro, 0.0, 1.0, 0.0);
		luzMagenta();
	glPopMatrix();
}

void Luces::luzMagenta()
{
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luz_ambiente);

	glLightfv(GL_LIGHT1, GL_AMBIENT, luz_ambiente);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luz_difusa);
	glLightfv(GL_LIGHT1, GL_SPECULAR, luz_espec);
	glLightfv(GL_LIGHT1, GL_POSITION, pos);

	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
}

void Luces::luzBlanca()
{
	glLightfv(GL_LIGHT0, GL_POSITION, dir);

	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}
