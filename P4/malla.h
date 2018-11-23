// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: ObjMallaIndexada.h
// -- declaraciones de clase ObjMallaIndexada (mallas indexadas) y derivados
//
// #############################################################################

#ifndef OBJETOS_H_INCLUDED
#define OBJETOS_H_INCLUDED

#include "aux.h"
#include "luces.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class ObjMallaIndexada
{
	public:

	// constructor
	ObjMallaIndexada();

	// dibuja el objeto en modo inmediato
	void draw_ModoInmediato(int mode);

	// dibuja el objeto en modo diferido (usando VBOs)
	void draw_ModoDiferido(int mode);

	// dibuja el objeto en modo ajedrez
	void pintarAjedrez();

	// dibuja con iluminacion
	void drawLuces();

	// función que redibuja el objeto
	// está función llama a 'draw_MI' (modo inmediato)
	// o bien a 'draw_MD' (modo diferido, VBOs)
	void draw(int mode, bool dibujo) ;

	// función para crear los VBOs
	GLuint crearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid *puntero_ram);

	protected:

	void calcularNormales() ; // calcula tabla de normales de vértices (práctica 3)
	void habilitarLuz();

	// completar: tabla de colores, tabla de normales de vértices

	std::vector<Tupla3f> vertices ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
	std::vector<Tupla3i> triangulos ; // una terna de 3 enteros por cada cara o triángulo

	std::vector<Tupla3f> n_caras; // vector para las normales de las caras
	std::vector<Tupla3f> n_vertices; // vector para las normales de los vértices

	Luces luz;

	GLfloat mb[4] = {0.0, 0.0, 1.0, 1.0}; // material azul, para ambiente
	GLfloat mg[4] = {0.2, 0.8, 0.2, 1.0}; // material verde oscuro, para difuso
	GLfloat mw[4] = {0.5, 0.5, 0.5, 1.0}; // material blanco, para especular
	float brillo = 0.5;

	private:

	GLuint id_vbo_vert;
	GLuint id_vbo_tri;
} ;

// *****************************************************************************
//
// clases derivadas de ObjMallaIndexada (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad
// (tiene 9 vertices y 6 caras)

class Cubo : public ObjMallaIndexada
{
   public:
   Cubo();

} ;

/******************************************************************************/
// Tetraedro

class Tetraedro : public ObjMallaIndexada
{
	public:
	Tetraedro();
};

// *****************************************************************************
// objeto leído de un archivo PLY

class ObjPLY : public ObjMallaIndexada
{
   public:
      ObjPLY( const std::string & nombre_archivo );

} ;

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

class ObjRevolucion : public ObjMallaIndexada
{
	public:
		ObjRevolucion();
		ObjRevolucion(const std::string & nombre_ply_perfil, bool tapa_sup, bool tapa_inf);

	protected:
		void crearMalla(const std::vector<Tupla3f> &perfil_original, const int num_instancias_perf, bool tapa_sup, bool tapa_inf);
} ;

/******************************************************************************/
// Cilindro

class Cilindro : public ObjRevolucion
{
	public:
		Cilindro(const int num_vert_perfil, const int num_instancias_perf);
};

/******************************************************************************/
// Cono

class Cono : public ObjRevolucion
{
	public:
		Cono(const int num_vert_perfil, const int num_instancias_perf);
};

/******************************************************************************/
// Esfera

class Esfera : public ObjRevolucion
{
	public:
		Esfera(const int num_vert_perfil, const int num_instancias_perf);
};


#endif
