// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParam.h
// -- declaraciones de clase para el objeto jerárquico de la práctica 3
//
// #############################################################################

#ifndef GRAFOPARAM_H_INCLUDED
#define GRAFOPARAM_H_INCLUDED

#include "malla.h" // añadir .h de cualquier objetos malla indexada usados....

constexpr int num_parametros = 10 ; // número de parámetros o grados de libertad
                                   // de este modelo

// Clase pinza

class Pinza
{
	public:

	Pinza();
	void draw(const int p_modo_vis, const bool p_usar_diferido);
	void drawPuntaPinza(const int p_modo_vis, const bool p_usar_diferido);

	private:

	// Mallas indexadas para formar una pinza
	Esfera *esfera1 = nullptr;
	Esfera *esfera2 = nullptr;
	Cilindro *cilindro = nullptr;
	Cono *cono = nullptr;
};

// Clase pata

class Pata
{
	public:

	Pata();
	void draw(const int p_modo_vis, const bool p_usar_diferido);
	void drawPataInferior(const int p_modo_vis, const bool p_usar_diferido);

	private:

	// Mallas indexadas para formar una pata
	Esfera *esfera1 = nullptr;
	Esfera *esfera2 = nullptr;
	Cilindro *cilindro1 = nullptr;
	Cilindro *cilindro2 = nullptr;
};

// -----------------------------------------------------------------------------
//
//
//								GRAFOPARAM
//
//
// -----------------------------------------------------------------------------

class GrafoParam
{
	public:

	// crea mallas indexadas (nodos terminales del grafo)
	GrafoParam();

	// función principal de visualización
	void draw( const int p_modo_vis, const bool p_usar_diferido );

	// actualizar valor efectivo de un parámetro (a partir de su valor no acotado)
	void actualizarValorEfe( const unsigned iparam, const float valor_na );

	// devuelve el número de parámetros
	unsigned numParametros() { return num_parametros ; }

	private:

	// métodos de dibujo de subgrafos
	void movPinzas(const float angulo, const int p_modo_vis, const bool p_usar_diferido);
	void movPatas(const float angulo, const int p_modo_vis, const bool p_usar_diferido);

	// objetos tipo malla indexada (nodos terminales)

	Pinza *pinza = nullptr;
	Pata *pata = nullptr;
	Esfera *cuerpo = nullptr;
	Cono *aguijon = nullptr;

	// parámetros de la llamada actual (o última) a 'draw'
	int modo_vis ;      // modo de visualización
	bool usar_diferido ; // modo de envío (true -> diferido, false -> inmediato)


	// valores efectivos de los parámetros (angulos, distancias, factores de
	// escala, etc.....) calculados a partir de los valores no acotados

	float pinzas, pata1, pata2, pata3, pata4, pata5, pata6, pata7, pata8;
	float andar = 0.0;
};

#endif
