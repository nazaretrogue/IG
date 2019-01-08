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

	if(mode < 3)
	{
		glVertexPointer(3, GL_FLOAT, 0, vertices.data());

		glDrawElements(GL_TRIANGLES, 3*triangulos.size(), GL_UNSIGNED_INT, triangulos.data());
	}

	else if(mode == 3)
		pintarAjedrez();

	else
	{
		glEnableClientState(GL_NORMAL_ARRAY);

		if (mode == 4)
			drawLucesFlat();

		else
			drawLucesSmooth();

		glDisableClientState(GL_NORMAL_ARRAY);
	}

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

	glVertexPointer(3, GL_FLOAT, 0, vertices.data());

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
// Función de visualización con Luces flat

void ObjMallaIndexada::drawLucesFlat()
{
	if(n_vertices.size() == 0)
		calcularNormales();

	glEnable(GL_FLAT);
	glShadeModel(GL_FLAT);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glBegin(GL_TRIANGLES);

	for(int i=0; i<triangulos.size(); i++)
	{
		glNormal3fv(n_caras[i]);

		glVertex3fv(vertices[triangulos[i](0)]);
		glVertex3fv(vertices[triangulos[i](1)]);
		glVertex3fv(vertices[triangulos[i](2)]);
	}

	glEnd();

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
}

// -----------------------------------------------------------------------------
// Función de visualización con Luces smooth

void ObjMallaIndexada::drawLucesSmooth()
{
	if(n_vertices.size() == 0)
		calcularNormales();

	glEnable(GL_SMOOTH);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glVertexPointer(3, GL_FLOAT, 0, vertices.data());
	glNormalPointer(GL_FLOAT, 0, n_vertices.data());

	glDrawElements(GL_TRIANGLES, 3*triangulos.size(), GL_UNSIGNED_INT, triangulos.data());

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void ObjMallaIndexada::draw(int mode, bool dibujo)
{
	if(dibujo)
	{
		// std::cout << "Pintando en modo inmediato" << std::endl;
		draw_ModoInmediato(mode);
	}
	else
	{
		// std::cout << "Pintando en modo diferido" << std::endl;
		draw_ModoDiferido(mode);
	}
}
// -----------------------------------------------------------------------------
// Recalcula la tabla de normales de vértices (el contenido anterior se pierde)

void ObjMallaIndexada::calcularNormales()
{
	Tupla3f vect1, vect2, tmp;
	Tupla3f tupla_0 = {0, 0, 0};

	n_caras.assign(triangulos.size(), tupla_0);
	n_vertices.assign(3*triangulos.size(), tupla_0);

	for(int i=0; i<triangulos.size(); i++)
	{
		vect1 = vertices[triangulos[i](0)] - vertices[triangulos[i](1)];
		vect2 = vertices[triangulos[i](1)] - vertices[triangulos[i](2)];

		tmp = vect1.cross(vect2);

		float mod = sqrt(pow(tmp(0), 2) + pow(tmp(1), 2) + pow(tmp(2), 2));
		n_caras[i] = tmp/mod;

		n_vertices[triangulos[i](0)] = n_vertices[triangulos[i](0)] + n_caras[i];
		n_vertices[triangulos[i](1)] = n_vertices[triangulos[i](1)] + n_caras[i];
		n_vertices[triangulos[i](2)] = n_vertices[triangulos[i](2)] + n_caras[i];
	}
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
// Clase tetraedro
//
// *****************************************************************************

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
// Clase ObjSeleccion
//
// *****************************************************************************

ObjSeleccion::ObjSeleccion()
{
	aspa1 = new Aspa();
	aspa2 = new Aspa();
	aspa3 = new Aspa();
	aspa4 = new Aspa();

	draw(3, false);
}

void ObjSeleccion::draw(int mode, bool dibujo)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if(r == 204)
	{
  		glColor3ub(51, 204, 255);
		r = 51;
	}

	else
	{
		glColor3ub(204, 102, 255);
		r = 204;
	}

	glPushMatrix();
		glPushMatrix();
			aspa1->draw(mode, dibujo);
		glPopMatrix();

		glPushMatrix();
			glRotatef(-90, 0.0, 0.0, 1.0);
			aspa2->draw(mode, dibujo);
		glPopMatrix();

		glPushMatrix();
			glRotatef(-180, 0.0, 0.0, 1.0);
			aspa3->draw(mode, dibujo);
		glPopMatrix();

		glPushMatrix();
			glRotatef(-270, 0.0, 0.0, 1.0);
			aspa4->draw(mode, dibujo);
		glPopMatrix();
	glPopMatrix();
}

Aspa* ObjSeleccion::getAspa(int num)
{
	Aspa *a;

	if(num == 1)
		a = aspa1;

	else if(num == 2)
		a = aspa2;

	else if(num == 3)
		a = aspa3;

	else
		a = aspa4;

	return a;
}

Aspa::Aspa()
{
	vertices =  {{+0.0, +0.0, +0.0}, // 0
				 {-0.5, -1.0, -0.5}, // 1
				 {-0.5, -1.0, +0.5}, // 2
				 {+0.5, -1.0, +0.5}, // 3
				 {+0.5, -1.0, -0.5}  // 4
				};

	// Se crean las caras de la pirámide
	triangulos = {{0, 1, 2}, {0, 2, 3},
				  {0, 3, 4}, {0, 4, 1},
				  {2, 1, 4}, {3, 2, 4}
				 };
}

void Aspa::draw(int modo, bool dibujo)
{
	glEnableClientState(GL_VERTEX_ARRAY); // Activar array vértices

	glVertexPointer(3, GL_FLOAT, 0, vertices.data());
	glDrawElements(GL_TRIANGLES, 3*triangulos.size(), GL_UNSIGNED_INT, triangulos.data());

	glDisableClientState(GL_VERTEX_ARRAY); // Desactivar array vértices
}

// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************
// Constructor por defecto

ObjRevolucion::ObjRevolucion() {}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion(const std::string & nombre_ply_perfil, bool tapa_sup, bool tapa_inf)
{
	std::vector<Tupla3f> perfil_original;

	ply::read_vertices(nombre_ply_perfil, perfil_original);
	crearMalla(perfil_original, 20, tapa_sup, tapa_inf);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

void ObjRevolucion::crearMalla(const std::vector<Tupla3f> &perfil_original,
							   const int num_instancias_perf,
							   bool tapa_sup, bool tapa_inf)
{
	int M = perfil_original.size();
	int a, b;
	Tupla3f vert;
	int indice_tapa_sup, indice_tapa_inf;

	// Se calculan los vértices
	for(int i=0; i<num_instancias_perf; i++)
	{
		for(int j=0; j<M; j++)
		{
			vert(0) = perfil_original[j](0)*cos((2*i*M_PI)/num_instancias_perf);
			vert(1) = perfil_original[j](1);
			vert(2) = perfil_original[j](0)*sin((2*i*M_PI)/num_instancias_perf);

			vertices.push_back(vert);
		}
	}

	// Se calculan los triángulos
	for(int i=0; i<num_instancias_perf; i++)
	{
		for(int j=0; j<M-1; j++)
		{
			a = M*i+j;
			b = M*((i+1)%num_instancias_perf)+j;

			triangulos.push_back({a, b+1, b});
			triangulos.push_back({a, a+1, b+1});
		}
	}

	// Se calculan los polos si se quieren las tapas

	if(tapa_inf)
	{
		// Polo sur
		vert(0) = 0;
		vert(1) = vertices[0](1);
		vert(2) = 0;
		vertices.push_back(vert);
		indice_tapa_inf = (int)vertices.size()-1;
	}

	if(tapa_sup)
	{
		// Polo norte
		vert(0) = 0;
		vert(1) = vertices[vertices.size()-2](1);
		vert(2) = 0;
		vertices.push_back(vert);
		indice_tapa_sup = (int)vertices.size()-1;
	}

	if(tapa_inf)
	{
		// Se calculan las tapas: tapa inferior
		for(int i=0; i<num_instancias_perf; i++)
		{
			// Posición de los vértices que forman parte del triángulo
			a = (M*i)%(M*num_instancias_perf);
			b = (M*i+M)%(M*num_instancias_perf);

			// Se introduce el triángulo
			triangulos.push_back({a, b, indice_tapa_inf});
		}
	}

	if(tapa_sup)
	{
		// Tapa superior
		for(int i=0; i<num_instancias_perf; i++)
		{
			// Posición de los vértices que forman parte del triángulo
			a = (M*i+M-1)%(M*num_instancias_perf);
			b = (M*i+M-1+M)%(M*num_instancias_perf);

			// Se introduce el triángulo
			triangulos.push_back({indice_tapa_sup, b, a});
		}
	}
}

// *****************************************************************************
//
// Clase Cilindro
//
// *****************************************************************************

Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf)
{
	std::vector<Tupla3f> perfil;
	Tupla3f tupla;

	// Inicializamos la coordenada 'y' a 0 para que comience en el origen
	tupla(1) = 0.0-(1.0/num_vert_perfil);

	// Vértices del perfil inicial
	for(int i=0; i<=num_vert_perfil; i++)
	{
		tupla(0) = 1;
		tupla(1) += (1.0/num_vert_perfil);
		tupla(2) = 0;

		perfil.push_back(tupla);
	}

	// Se crea el cilindro
	crearMalla(perfil, num_instancias_perf, true, true);
}

// *****************************************************************************
//
// Clase Cono
//
// *****************************************************************************

Cono::Cono(const int num_vert_perfil, const int num_instancias_perf)
{
	std::vector<Tupla3f> perfil;
	Tupla3f tupla;

	// Inicializamos las coordenadas 'x' e 'y'
	tupla(0) = 1.0+(1.0/num_vert_perfil);
	tupla(1) = 0.0-(1.0/num_vert_perfil);

	// Vértices del perfil inicial
	for(int i=0; i<=num_vert_perfil; i++)
	{
		tupla(0) -= (1.0/num_vert_perfil);
		tupla(1) += (1.0/num_vert_perfil);
		tupla(2) = 0;

		perfil.push_back(tupla);
	}

	// Se crea el cono
	crearMalla(perfil, num_instancias_perf, false, true);
}

// *****************************************************************************
//
// Clase Esfera
//
// *****************************************************************************

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf)
{
	std::vector<Tupla3f> perfil;
	Tupla3f tupla;

	// Vértices del perfil inicial
	for(int i=0; i<=num_vert_perfil; i++)
	{
		tupla(0) = cos(-M_PI/2.0+i*(M_PI/(float)num_vert_perfil));
		tupla(1) = sin(-M_PI/2.0+i*(M_PI/(float)num_vert_perfil));
		tupla(2) = 0.0;

		perfil.push_back(tupla);
	}

	// Se crea la esfera
	crearMalla(perfil, num_instancias_perf, false, false);
}

// Calculo de las normales para la esfera

void Esfera::calcularNormales()
{
	Tupla3f vect1, vect2, tmp;
	Tupla3f tupla_0 = {0, 0, 0};

	n_caras.assign(triangulos.size(), tupla_0);
	n_vertices.assign(3*triangulos.size(), tupla_0);

	for(int i=0; i<triangulos.size(); i++)
	{
		vect1 = vertices[triangulos[i](0)] - vertices[triangulos[i](1)];
		vect2 = vertices[triangulos[i](1)] - vertices[triangulos[i](2)];

		tmp = vect1.cross(vect2);

		float mod = sqrt(pow(tmp(0), 2) + pow(tmp(1), 2) + pow(tmp(2), 2));
		n_caras[i] = tmp/mod;

		n_vertices[i] = vertices[i] - tupla_0;
	}
}
