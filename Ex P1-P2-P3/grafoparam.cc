// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParam.cc
// -- implementación del objeto jerárquico de la práctica 3
//
// #############################################################################


#include "grafoparam.h"

// -----------------------------------------------------------------------------
// constructor: crea mallas indexadas en los nodos terminales del grafo

GrafoParam::GrafoParam()
{
	ar = new Arania();
	centro = new Esfera(20, 25);
	a = b = d = 0.0;
}
// -----------------------------------------------------------------------------
// actualizar valor efectivo de un parámetro (a partir de su valor no acotado)

void GrafoParam::actualizarValorEfe( const unsigned iparam, const float valor_na )
{
	assert( iparam < num_parametros );

	using namespace std ;
	//cout << "GrafoParam::actualizarValorEfe( " << iparam << ", " << valor_na << " )" << endl ;

	switch(iparam)
	{
		// a = rotaciones de la pata completa
		case 0:
			a = 85.0 + 55.0*sin(0.5*(2.0*M_PI*valor_na));
			break;

		// b = rotaciones de la pata inferior
		case 1:
			b = 55.0 + 25.0*sin(0.8*(2.0*M_PI*valor_na));
			break;

		// d = altura de los cilindros
		case 2:
			d = 2.0 + 0.5*sin(0.8*(2.0*M_PI*valor_na));
			break;
	}
}

void GrafoParam::movPatas2(const int p_modo_vis, const bool p_usar_diferido)
{
	glPushMatrix();
		//glRotatef(a, 0.0, 1.0, 0.0);
		ar->draw(p_modo_vis, p_usar_diferido, a, b, d);
	glPopMatrix();
}

// -----------------------------------------------------------------------------
// visualización del objeto Jerárquico con OpenGL,
// mediante llamadas a los métodos 'draw' de los sub-objetos

void GrafoParam::draw( const int p_modo_vis, const bool p_usar_diferido )
{
	// Creamos la arania

	assert(ar != nullptr);
	assert(centro != nullptr);

	modo_vis = p_modo_vis ;
	usar_diferido = p_usar_diferido ;

	glPushMatrix();
		glPushMatrix();
			glColor3f(0.0, 0.0, 0.0);
			centro->draw(p_modo_vis, p_usar_diferido);
		glPopMatrix();

		// Añadimos las tres patas
		glPushMatrix();
			glScalef(0.5, 0.5, 0.5);
			movPatas2(modo_vis, usar_diferido);
		glPopMatrix();

		glPushMatrix();
			glRotatef(120, 0.0, 1.0, 0.0);
			glScalef(0.5, 0.5, 0.5);
			movPatas2(modo_vis, usar_diferido);
		glPopMatrix();

		glPushMatrix();
			glRotatef(240, 0.0, 1.0, 0.0);
			glScalef(0.5, 0.5, 0.5);
			movPatas2(modo_vis, usar_diferido);
		glPopMatrix();
	glPopMatrix();
}

// -----------------------------------------------------------------------------
//
//
//								CLASE ARANIA
//
//
// -----------------------------------------------------------------------------

Arania::Arania()
{
	esfera1 = new Esfera(20, 25);
	esfera2 = new Esfera(20, 25);
	cilindro1 = new Cilindro(20, 25);
	cilindro2 = new Cilindro(20, 25);
}

void Arania::draw(const int p_modo_vis, const bool p_usar_diferido, float a, float b, float d)
{
	glRotatef(a, -1.0, 0.0, 0.0);

	// Segmento 1
	glPushMatrix();
		glColor3f(0.6, 0.0, 0.0);
		glTranslatef(0.0, 0.0, -2.0);
		glRotatef(-90, 1.0, 0.0, 0.0);
		glScalef(0.4, d, 0.4);
		cilindro1->draw(p_modo_vis, p_usar_diferido);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.6, 0.0, 0.0);
		glTranslatef(0.0, 0.0, -d-2.4);
		glScalef(0.4, 0.4, 0.4);
		esfera1->draw(p_modo_vis, p_usar_diferido);
	glPopMatrix();

	// Segmento 2
	glPushMatrix();
		glColor3f(0.6, 0.0, 0.0);
		glTranslatef(0.0, 0.0, -d-2.8);
		glRotatef(b, 1.0, 0.0, 0.0);
		glRotatef(-90, 1.0, 0.0, 0.0);
		drawPataInferior(p_modo_vis, p_usar_diferido, d);
	glPopMatrix();
}

void Arania::drawPataInferior(const int p_modo_vis, const bool p_usar_diferido, float altura)
{
	glPushMatrix();
		glColor3f(0.6, 0.0, 0.0);
		glScalef(0.4, altura, 0.4);
		cilindro2->draw(p_modo_vis, p_usar_diferido);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, altura+0.4, 0.0);
		glScalef(0.4, 0.4, 0.4);
		esfera2->draw(p_modo_vis, p_usar_diferido);
	glPopMatrix();
}
