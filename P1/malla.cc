#include "aux.h"
#include "ply_reader.h"
#include "malla.h"

// *****************************************************************************
//
// Clase ObjMallaIndexada
//
// *****************************************************************************

// Constructor

ObjMallaIndexada::ObjMallaIndexada()
{
	id_vbo_vert = 0;
	id_vbo_tri = 0;
}

// Visualización en modo inmediato con 'glDrawElements'

void ObjMallaIndexada::draw_ModoInmediato(int mode)
{
 	glEnableClientState(GL_VERTEX_ARRAY); // Activar array vértices

	if(mode != 3)
	{
		// Se activan los vértices
		glVertexPointer(3, GL_FLOAT, 0, vertices.data());

		glDrawElements(GL_TRIANGLES, 3*triangulos.size(), GL_UNSIGNED_INT, triangulos.data());
	}

	else
		pintarAjedrez();

	glDisableClientState(GL_VERTEX_ARRAY); // Desactivar array vértices
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs) 

void ObjMallaIndexada::draw_ModoDiferido(int mode)
{
	if(id_vbo_vert == 0)
		id_vbo_vert = crearVBO(GL_ARRAY_BUFFER, 3*vertices.size()*sizeof(float), vertices.data());

	if(id_vbo_tri == 0)
		id_vbo_tri = crearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*triangulos.size()*sizeof(int), triangulos.data());

	// Se activa el VBO de vértices, se le da formato y se desactiva
	glBindBuffer(GL_ARRAY_BUFFER, id_vbo_vert);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	// Se activa el array de vértices
	glEnableClientState(GL_VERTEX_ARRAY);

	// Se activa el VBO de índices, se pinta y se desactiva
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);

	if(mode != 3)
		glDrawElements(GL_TRIANGLES, 3*triangulos.size(), GL_UNSIGNED_INT, 0);

	else
		pintarAjedrez();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Desactivamos el array de vértices
	glDisableClientState(GL_VERTEX_ARRAY);
}

// -----------------------------------------------------------------------------
// Función de creación de los VBO's

GLuint ObjMallaIndexada::crearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid *puntero_ram)
{
	GLuint id_vbo;
	glGenBuffers(1, &id_vbo);
	glBindBuffer(tipo_vbo, id_vbo);

	glBufferData(tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW);

	glBindBuffer(tipo_vbo, 0);

	return id_vbo;
}

// -----------------------------------------------------------------------------
// Función de visualización en modo ajedrez

void ObjMallaIndexada::pintarAjedrez()
{
	std::vector<Tupla3i> caras_pares;
	std::vector<Tupla3i> caras_impares;

	for(int num_caras=0; num_caras<triangulos.size(); num_caras++)
	{
		if(num_caras%2 == 0)
			caras_pares.push_back(triangulos[num_caras]);

		else
			caras_impares.push_back(triangulos[num_caras]);
	}

	glColor3ub(255, 255, 0);
	glDrawElements(GL_TRIANGLES, 3*caras_pares.size(), GL_UNSIGNED_INT, caras_pares.data());

	glColor3ub(255, 0, 255);
	glDrawElements(GL_TRIANGLES, 3*caras_impares.size(), GL_UNSIGNED_INT, caras_impares.data());
}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void ObjMallaIndexada::draw(int mode, int dibujo)
{
	if(dibujo == 0)
	{
		std::cout << "Pintando en modo inmediato" << std::endl;
		draw_ModoInmediato(mode);
	}
	else
	{
		std::cout << "Pintando en modo diferido" << std::endl;
		draw_ModoDiferido(mode);
	}
}
// -----------------------------------------------------------------------------
// Recalcula la tabla de normales de vértices (el contenido anterior se pierde)

void ObjMallaIndexada::calcular_normales()
{
   // completar .....(práctica 2)
}

// *****************************************************************************
//
// Clase Cubo (práctica 1)
//
// *****************************************************************************

Cubo::Cubo()
{

   // inicializar la tabla de vértices
   vertices =  {  { -0.5, -0.5, -0.5 }, // 0
                  { -0.5, -0.5, +0.5 }, // 1
                  { -0.5, +0.5, -0.5 }, // 2
                  { -0.5, +0.5, +0.5 }, // 3
                  { +0.5, -0.5, -0.5 }, // 4
                  { +0.5, -0.5, +0.5 }, // 5
                  { +0.5, +0.5, -0.5 }, // 6
                  { +0.5, +0.5, +0.5 }  // 7
               };

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   triangulos = { { 0, 2, 4 }, { 4, 2, 6 },
                  { 1, 5, 3 }, { 3, 5, 7 },
                  { 1, 3, 0 }, { 0, 3, 2 },
                  { 5, 4, 7 }, { 7, 4, 6 },
                  { 1, 0, 5 }, { 5, 0, 4 },
                  { 3, 7, 2 }, { 2, 7, 6 }
                } ;
}

// *****************************************************************************
//

Tetraedro::Tetraedro()
{
	vertices = {{0, 4.47, 0},			// 0
                {-4.47, -4.47, -4.47},  // 1
                {0, -4.47, 4.47}, 		// 2
                {4.47, -4.47, -4.47}};  // 3

	triangulos = {{1, 2, 3}, {0, 3, 1}, {3, 0, 2}, {0, 1, 2}};			
}
//
// *****************************************************************************

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, vertices, triangulos );
}

// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion(const std::string & nombre_ply_perfil)
{
	std::vector<Tupla3f> perfil_original;

	ply::read_vertices(nombre_ply_perfil, perfil_original);
	crearMalla(perfil_original, 1000);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

void ObjRevolucion::crearMalla(const std::vector<Tupla3f> &perfil_original,
							   const int num_instancias_perf)
{
	int size = perfil_original.size();
	int a, b;

	for(int i=0; i<size; i++)
		vertices.push_back(perfil_original[i]);

	for(int i=0; i<num_instancias_perf; i++)
	{
		for(int j=0; j<size; j++)
			vertices.push_back(perfil_original[j]*((2*i*M_PI)/size));

		for(int j=0; j<size-1; j++)
		{
			a = size*i+j;
			b = size*((i+1)%num_instancias_perf)+j;

			triangulos.push_back({a, b, b+1});
			triangulos.push_back({a, b+1, a+1});
		}
	}
}
















