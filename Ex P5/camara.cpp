#include "camara.h"

Camara::Camara(int camara_orto)
{
	Observer_angle_x = 0.0;
	Observer_angle_y = 0.0;
	Observer_distance_pers = 2.0;

	if(camara_orto == 0)
	{
		orto = false;
		ex = false;
	}

	if(camara_orto == 1)
	{
		ex = true;
		orto = false;
	}

	if(camara_orto == 2)
	{
		Observer_distance_ort = 15.0;
		left = right = bottom = top = near = far = 0.0;
		orto = true;
		ex = false;
	}
}

void Camara::girar(GLfloat x, GLfloat y)
{
	if(!orto)
	{
		Observer_angle_x += x;
		Observer_angle_y += y;
	}
}

void Camara::setObservador()
{
	if(!orto)
	{
		glTranslatef(0.0, 0.0, -Observer_distance_pers);
		glRotatef(Observer_angle_x, 1.0, 0.0, 0.0);
		glRotatef(Observer_angle_y, 0.0, 1.0, 0.0);
	}
}

void Camara::acercar()
{
	if(!orto)
    	Observer_distance_pers /= 1.2;

	else
	{
		Observer_distance_ort /= 1.2;
		iniciarCamaraOrto();
	}
}

void Camara::alejar()
{
	if(!orto)
    	Observer_distance_pers *= 1.2;

	else
	{
		Observer_distance_ort *= 1.2;
		iniciarCamaraOrto();
	}
}

void Camara::proyeccionPerspectiva(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f)
{
    glFrustum(l, r, b, t, n, f);
}

void Camara::proyeccionOrto(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f)
{
	left = l;
	right = r;
	bottom = b;
	top = t;
	near = n;
	far = f;

	glOrtho(Observer_distance_ort*left, Observer_distance_ort*right,
			Observer_distance_ort*bottom, Observer_distance_ort*top, near, far);
}

void Camara::iniciarCamaraOrto()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(Observer_distance_ort*left, Observer_distance_ort*right,
			Observer_distance_ort*bottom, Observer_distance_ort*top, near, far);
}

bool Camara::esOrtogonal()
{
	return orto;
}

bool Camara::examen()
{
	return ex;
}

void Camara::cambiarVisualizacion()
{
	glTranslatef(0.0, 0.0, -Observer_distance_pers);
	gluLookAt(0, -1, 5, 0, 1, 0, 0.25, 1, 0);
}

void Camara::rotarEnZ(int angulo)
{
	Observer_angle_z += angulo;

	if(!orto && !ex)
		glRotatef(Observer_angle_z, 0.0, 0.0, 1.0);
}

void Camara::derechaEnY()
{
	glTranslatef(0.0, -1.0, 0.0);
}

void Camara::izquierdaEnY()
{
	glTranslatef(0.0, 1.0, 0.0);
}
