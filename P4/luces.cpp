#include "luces.h"

Luces::Luces() {}

void Luces::drawLights()
{
	luzBlanca();
	habilitarLuz();
}

void Luces::habilitarLuz()
{
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luz_ambiente);

	glLightfv(GL_LIGHT1, GL_AMBIENT, luz_ambiente);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luz_difusa);
	glLightfv(GL_LIGHT1, GL_SPECULAR, luz_espec);
	glLightfv(GL_LIGHT1, GL_POSITION, dir);

	glEnable(GL_NORMALIZE);
	glEnable(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glShadeModel(GL_SMOOTH);
}

void Luces::luzBlanca()
{
	//glLightfv(GL_LIGHT0, GL_POSITION, dir);

	glEnable(GL_NORMALIZE);
	glEnable(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
}
