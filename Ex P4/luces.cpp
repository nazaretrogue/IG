#include "luces.h"

Luces::Luces() {}

void Luces::drawLights(int giro)
{
	float movimiento = (float)giro;
	/*luzBlanca();

	glPushMatrix();
		glRotatef(giro, 0.0, 1.0, 0.0);
		luzMagenta();
	glPopMatrix();*/

	luzCeleste();

	glPushMatrix();
		glTranslatef(0.0, 0.0, movimiento);
		luzMarron();
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

void Luces::luzMarron()
{
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, marron_amb);

	glLightfv(GL_LIGHT1, GL_AMBIENT, marron_amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, marron_dif);
	glLightfv(GL_LIGHT1, GL_SPECULAR, marron_espec);
	glLightfv(GL_LIGHT1, GL_POSITION, pos);

	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
}

void Luces::luzCeleste()
{
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, celeste_amb);

	glLightfv(GL_LIGHT2, GL_AMBIENT, celeste_amb);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, celeste_dif);
	glLightfv(GL_LIGHT2, GL_SPECULAR, celeste_espec);
	glLightfv(GL_LIGHT2, GL_POSITION, dir);

	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT2);
}
