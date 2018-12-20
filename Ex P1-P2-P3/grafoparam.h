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

// Clase arania

class Arania
{
	public:

	Arania();
	void draw(const int p_modo_vis, const bool p_usar_diferido, float a, float b, float d);
	void drawPataInferior(const int p_modo_vis, const bool p_usar_diferido, float altura);

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
	void movPatas2(const int p_modo_vis, const bool p_usar_diferido);

	// objetos tipo malla indexada (nodos terminales)

	Arania *ar = nullptr;
	Esfera *centro = nullptr;

	// parámetros de la llamada actual (o última) a 'draw'
	int modo_vis ;      // modo de visualización
	bool usar_diferido ; // modo de envío (true -> diferido, false -> inmediato)


	// valores efectivos de los parámetros (angulos, distancias, factores de
	// escala, etc.....) calculados a partir de los valores no acotados
	//float andar = 0.0;
	float a, b, d;
};

#endif
