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
	pinza = new Pinza();
	pata = new Pata();
	cuerpo = new Esfera(20, 50);
	aguijon = new Cono(20, 50);
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
		case 0:
			// Movimiento de apertura y cierre de las pinzas
			pinzas = 45.0*sin(0.5*(2.0*M_PI*valor_na));
			break;
		case 1:
			// Movimiento de las patas
			pata1 = 22.0*sin(0.5*(2.0*M_PI*valor_na));
			break;
		case 2:
			pata2 = 22.0*sin(0.5*(2.0*M_PI*valor_na));
			break;
		case 3:
			pata3 = 22.0*sin(0.5*(2.0*M_PI*valor_na));
			break;
		case 4:
			pata4 = 22.0*sin(0.5*(2.0*M_PI*valor_na));
			break;
		case 5:
			pata5 = 22.0*sin(0.5*(2.0*M_PI*valor_na));
			break;
		case 6:
			pata6 = 22.0*sin(0.5*(2.0*M_PI*valor_na));
			break;
		case 7:
			pata7 = 22.0*sin(0.5*(2.0*M_PI*valor_na));
			break;
		case 8:
			pata8 = 22.0*sin(0.5*(2.0*M_PI*valor_na));
			break;
		case 9:
			andar = sin(0.5*(2.0*M_PI*valor_na));
			break;
	}
}

void GrafoParam::movPinzas(const float angulo, const int p_modo_vis, const bool p_usar_diferido)
{
	glPushMatrix();
		glRotatef(angulo, 0.0, 1.0, 0.0);
		pinza->draw(p_modo_vis, p_usar_diferido);
	glPopMatrix();
}

void GrafoParam::movPatas(const float angulo, const int p_modo_vis, const bool p_usar_diferido)
{
	glPushMatrix();
		glRotatef(angulo, 0.0, 1.0, 0.0);
		pata->draw(p_modo_vis, p_usar_diferido);
	glPopMatrix();
}

// -----------------------------------------------------------------------------
// visualización del objeto Jerárquico con OpenGL,
// mediante llamadas a los métodos 'draw' de los sub-objetos

void GrafoParam::draw( const int p_modo_vis, const bool p_usar_diferido )
{
	// asegurarnos que está inicializado ok

	assert(pinza != nullptr);
	assert(pata != nullptr);
	assert(cuerpo != nullptr);
	assert(aguijon != nullptr);

	// guardar parametros de visualización para esta llamada a 'draw'
	// (modo de visualización, modo de envío)

	modo_vis = p_modo_vis ;
	usar_diferido = p_usar_diferido ;

	// dibujar objetos

	// Para que la araña ande hacia delante y detrás
	glTranslatef(andar, 0.0, 0.0);

	glPushMatrix();
		glRotatef(90, 0.0, 1.0, 0.0);

		//Pintamos el cuerpo
		glPushMatrix();
			glColor3f(0.0, 0.0, 0.0);
			glScalef(1.0, 1.0, 1.7);
			cuerpo->draw(p_modo_vis, p_usar_diferido);
		glPopMatrix();

		// Pintamos la cabeza
		glPushMatrix();
			glColor3f(0.0, 0.0, 0.0);
			glTranslatef(0.0, 0.0, 2.2);
			glScalef(0.5, 0.5, 0.5);
			cuerpo->draw(p_modo_vis, p_usar_diferido);
		glPopMatrix();

		// Añadimos las dos pinzas
		glPushMatrix();
			glTranslatef(0.3, 0.0, 2.5);
			glRotatef(-90, 0.0, 1.0, 0.0);
			glScalef(0.5, 0.5, 0.5);
			movPinzas(pinzas, p_modo_vis, p_usar_diferido);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.3, 0.0, 2.5);
			glRotatef(90, 0.0, 1.0, 0.0);
			glRotatef(180, 0.0, 0.0, 1.0);
			glScalef(0.5, 0.5, 0.5);
			movPinzas(pinzas, modo_vis, usar_diferido);
		glPopMatrix();

		// Añadimos las ocho patas
		// Patas parte derecha
		glPushMatrix();
			glTranslatef(1.0, 0, 0.34);
			glScalef(0.5, 0.5, 0.5);
			movPatas(pata1, modo_vis, usar_diferido);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(1.0, 0, -0.34);
			glScalef(0.5, 0.5, 0.5);
			movPatas(pata2, modo_vis, usar_diferido);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.7, 0, 1.34);
			glScalef(0.5, 0.5, 0.5);
			movPatas(pata3, modo_vis, usar_diferido);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.7, 0, -1.34);
			glScalef(0.5, 0.5, 0.5);
			movPatas(pata4, modo_vis, usar_diferido);
		glPopMatrix();

		// Patas parte izquierda
		glPushMatrix();
			glTranslatef(-1.0, 0, 0.34);
			glRotatef(180, 0.0, 1.0, 0.0);
			glScalef(0.5, 0.5, 0.5);
			movPatas(pata5, modo_vis, usar_diferido);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-1.0, 0, -0.34);
			glRotatef(180, 0.0, 1.0, 0.0);
			glScalef(0.5, 0.5, 0.5);
			movPatas(pata6, modo_vis, usar_diferido);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.7, 0, 1.34);
			glRotatef(180, 0.0, 1.0, 0.0);
			glScalef(0.5, 0.5, 0.5);
			movPatas(pata7, modo_vis, usar_diferido);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.7, 0, -1.34);
			glRotatef(180, 0.0, 1.0, 0.0);
			glScalef(0.5, 0.5, 0.5);
			movPatas(pata8, modo_vis, usar_diferido);
		glPopMatrix();

		// Añadimos el aguijón
		glPushMatrix();
			glColor3f(0.6, 0.0, 0.0);
			glTranslatef(0.0, 0, -1.7);
			glRotatef(-90, 1.0, 0.0, 0.0);
			glScalef(0.2, 0.5, 0.2);
			aguijon->draw(p_modo_vis, p_usar_diferido);
		glPopMatrix();
	glPopMatrix();
}

// -----------------------------------------------------------------------------
//
//
//								CLASE PINZA
//
//
// -----------------------------------------------------------------------------

Pinza::Pinza()
{
	esfera1 = new Esfera(20, 50);
	esfera2 = new Esfera(20, 50);
	cilindro = new Cilindro(20, 50);
	cono = new Cono(20, 50);
}

void Pinza::draw(const int p_modo_vis, const bool p_usar_diferido)
{
	glPushMatrix();
		glColor3f(0.6, 0.0, 0.0);
		glScalef(0.2, 0.2, 0.2);
		esfera1->draw(p_modo_vis, p_usar_diferido);
	glPopMatrix();

	glRotatef(45, 0.0, 1.0, 0.0);

	glPushMatrix();
		glColor3f(0.6, 0.0, 0.0);
		glTranslatef(0.2, 0.0, 0.0 );
		glRotatef( -90, 0.0, 0.0, 1.0 );
		glScalef(0.2, 0.4, 0.2);
		cilindro->draw(p_modo_vis, p_usar_diferido);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.6, 0.0, 0.0);
		glTranslatef(0.8, 0.0, 0.0 );
		glRotatef(-45, 0.0, 1.0, 0.0);
		drawPuntaPinza(p_modo_vis, p_usar_diferido);
	glPopMatrix();
}

void Pinza::drawPuntaPinza(const int p_modo_vis, const bool p_usar_diferido)
{
	glPushMatrix();
		glScalef(0.2, 0.2, 0.2);
		esfera2->draw(p_modo_vis, p_usar_diferido);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.6, 0.0, 0.0);
		glTranslatef(0.2, 0.0, 0.0);
		glRotatef(-90, 0.0, 0.0, 1.0);
		glScalef(0.2, 0.5, 0.2);
		cono->draw(p_modo_vis, p_usar_diferido);
	glPopMatrix();
}

// -----------------------------------------------------------------------------
//
//
//								CLASE PATA
//
//
// -----------------------------------------------------------------------------

Pata::Pata()
{
	esfera1 = new Esfera(20, 50);
	esfera2 = new Esfera(20, 50);
	cilindro1 = new Cilindro(20, 50);
	cilindro2 = new Cilindro(20, 50);
}

void Pata::draw(const int p_modo_vis, const bool p_usar_diferido)
{
	glPushMatrix();
		glColor3f(0.6, 0.0, 0.0);
		glScalef(0.2, 0.2, 0.2);
		esfera1->draw(p_modo_vis, p_usar_diferido);
	glPopMatrix();

	glRotatef(60, 0.0, 0.0, 1.0);

	glPushMatrix();
		glColor3f(0.6, 0.0, 0.0);
		glTranslatef(0.2, 0.0, 0.0);
		glRotatef(-90, 0.0, 0.0, 1.0);
		glScalef(0.2, 0.6, 0.2);
		cilindro1->draw(p_modo_vis, p_usar_diferido);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.6, 0.0, 0.0);
		glTranslatef(1.0, 0.0, 0.0);
		glRotatef(-90, 0.0, 0.0, 1.0);
		drawPataInferior(p_modo_vis, p_usar_diferido);
	glPopMatrix();
}

void Pata::drawPataInferior(const int p_modo_vis, const bool p_usar_diferido)
{
	glPushMatrix();
		glScalef(0.2, 0.2, 0.2);
		esfera2->draw(p_modo_vis, p_usar_diferido);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.6, 0.0, 0.0);
		glTranslatef(0.2, 0.0, 0.0);
		glRotatef(-125, 0.0, 0.0, 1.0);
		glScalef(0.2, 3.7, 0.2);
		cilindro2->draw(p_modo_vis, p_usar_diferido);
	glPopMatrix();
}
