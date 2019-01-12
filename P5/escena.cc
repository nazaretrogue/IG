

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
	Front_plane = 0.1;
	Back_plane = 2000.0;
	Observer_angle_x  = 0.0;
	Observer_angle_y  = 0.0;
	Observer_distance = 2.0;

	ejes.changeAxisSize( 5000 );

	Camara persp(false);
	camaras.push_back(persp); // Cámara original, en perspectiva

	Camara ortog(true);
	camaras.push_back(ortog); // Cámara ortogonal

	// crear los objetos de las prácticas: Mallas o Jerárquicos....
	cubo = new Cubo();
	tetraedro = new Tetraedro();
	objply = new ObjPLY("./plys/ant.ply");
	objrev = new ObjRevolucion("./plys/peon.ply", true, true);
	cilindro = new Cilindro(45, 20);
	cono = new Cono(45, 20);
	esfera = new Esfera(45, 20);
	objjer = new ObjJerarquico();
	tex = new Textura();
	cuadro = new Cuadro();
	molino = new ObjSeleccion();

	num_objetos = 11; // se usa al pulsar la tecla 'O' (rotar objeto actual)
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST ); // se habilita el z-bufer

	redimensionar( UI_window_width, UI_window_height );

	tex->readImageSkybox();
	cuadro->readImageChess();
}

// **************************************************************************
// Funcion que dibuja el objeto activo actual, usando su método 'draw'
// (llamada desde Escena::dibujar)
// ***************************************************************************

void Escena::dibujar_objeto_actual()
{
	using namespace std;

	glColor3ub(0, 0, 0);
	glShadeModel(GL_FLAT);
	glPointSize(5);
	glDisable(GL_CULL_FACE);

	switch(modo)
	{
		case 0:
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			break;
		case 1:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case 2:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case 3:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case 4:
		case 5:
			luz.drawLights(giro_luz);
			break;
	}

	switch (material)
	{
		case 0:
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mw);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mb);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mg);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);
			break;

		case 1:
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mwh);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, my);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mm);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);
			break;
	}

	// (2) dibujar el objeto actual usando método 'draw' del objeto asociado al
	// valor entero en 'objeto_actual'

	switch( objeto_actual )
	{
		case 0:
			if (cubo != nullptr)
				cubo->draw(modo, inmediato);
				break;

		case 1:
			if(tetraedro != nullptr)
				tetraedro->draw(modo, inmediato);
				break;

		case 2:
			if(objply != nullptr)
				objply->draw(modo, inmediato);
				break;

		case 3:
			if(objrev != nullptr)
				objrev->draw(modo, inmediato);
				break;

		case 4:
			if(cilindro != nullptr)
				cilindro->draw(modo, inmediato);
				break;

		case 5:
			if(cono != nullptr)
				cono->draw(modo, inmediato);
				break;

		case 6:
			if(esfera != nullptr)
				esfera->draw(modo, inmediato);
				break;

		case 7:
			if(objjer != nullptr)
				objjer->draw(modo, inmediato);
				break;

		case 8:
			if(tex != nullptr)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				tex->drawTextureSkybox();
			}
				break;

		case 9:
			if(cuadro != nullptr)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				cuadro->drawTextureChess();
			}
				break;

		case 10:
			if(molino != nullptr)
				drawBufferDelantero();
				break;

		default:
			cout << "draw_object: el número de objeto actual (" << objeto_actual << ") es incorrecto." << endl;
			break;
	}
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
	ejes.draw();
	dibujar_objeto_actual();

	if(objeto_actual == 10)
	{
		glDrawBuffer(GL_BACK);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		change_observer();
		drawBufferTrasero();
		glDrawBuffer(GL_FRONT);
	}

	//glFlush();
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
	using namespace std;
	cout << "Tecla pulsada: '" << tecla << "'" << endl;

	switch(tecla)
	{
		case 'Q':
		case 'q':
			// salir
			return true;
			break;
		case 'O':
		case 'o':
			// activar siguiente objeto
			objeto_actual = (objeto_actual + 1) % num_objetos;
			cout << "objeto actual == " << objeto_actual << endl;
			break;
		case 'M':
		case 'm':
			// cambiar de modo de visualización
			modo = (modo + 1) % 6;
			break;
		case 'V':
		case 'v':
			// cambiar entre modo de dibujo inmediato y diferido
			inmediato = !inmediato;
			break;
		case 'P':
		case 'p':
			// cambiar de parámetro del objeto jerárquico
			objjer->siguienteParametro();
			break;
		case 'A':
		case 'a':
			// cambiar entre animaciones sí o no
			conmutarAnimaciones();
			break;
		case 'Z':
			// incrementa el valor del parámetro actual si hay animaciones
			objjer->incrementaParamAct();
			break;
		case 'z':
			// decrementa el valor del parámetro actual si hay animaciones
			objjer->decrementaParamAct();
			break;
		case '>':
			// incrementa el parámetro usado en las animaciones
			objjer->acelerar();
			break;
		case '<':
			// decrementa el parámetro usado en las animaciones
			objjer->decelerar();
			break;
		case 'l':
		case 'L':
			giro_luz = (giro_luz + 15)%360;
			break;
		case 't':
		case 'T':
			material = (material+1)%2;
			break;
		case 'c':
		case 'C':
		{
			camara_activa = (camara_activa+1)%2;
			redimensionar(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		}
			break;
	}
	return false;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
	switch ( Tecla1 )
	{
		case GLUT_KEY_LEFT:
			yant--;
			camaras[camara_activa].girar(0.0, -1.0);
			break;
		case GLUT_KEY_RIGHT:
			yant++;
			camaras[camara_activa].girar(0.0, 1.0);
			break;
		case GLUT_KEY_UP:
			xant--;
			camaras[camara_activa].girar(-1.0, 0.0);
			break;
		case GLUT_KEY_DOWN:
			xant++;
			camaras[camara_activa].girar(+1.0, 0.0);
			break;
		case GLUT_KEY_PAGE_UP:
			camaras[camara_activa].acercar();
			break;
		case GLUT_KEY_PAGE_DOWN:
			camaras[camara_activa].alejar();
			break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Función para comprobar los movimientos del ratón

void Escena::activarMovimientoRaton(int num)
{
	if(num == 0)
		raton = MOVER;

	else if(num == 1)
		raton = ACERCAR;

	else if(num == 2)
		raton = ALEJAR;

	else if(num == 3)
		raton = PICK;

	else
		raton = IDLE;
}

void Escena::ratonMovido(int x, int y)
{
	if(raton == MOVER)
	{
		camaras[camara_activa].girar(x-xant, y-yant);
		xant = x;
		yant = y;
	}
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	const float wy = 0.84 * Front_plane,
		    	wx = ratio_xy * wy;
	if(!camaras[camara_activa].esOrtogonal())
		camaras[camara_activa].proyeccionPerspectiva(-wx, +wx, -wy, +wy, Front_plane, Back_plane);
	else
		camaras[camara_activa].proyeccionOrto(-wx, +wx, -wy, +wy, -20.0, 20.0);
}
//***************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
	Width = newWidth;
	Height = newHeight;
	change_projection( float(Width) / float(Height) );
	glViewport( 0, 0, Width, Height );
}

//***************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

/*void Escena::change_observer()
{
	// posicion del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef( 0.0, 0.0, -Observer_distance );
	glRotatef( Observer_angle_x, 1.0,0.0, 0.0 );
	glRotatef( Observer_angle_y, 0.0, 1.0, 0.0 );
}*/

void Escena::change_observer()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camaras[camara_activa].setObservador();
}
//***************************************************************************
// Función para las animaciones (idle)
//***************************************************************************

void Escena::mgeDesocupado()
{
	objjer->actualizarEstado();
	glutPostRedisplay();
}

//***************************************************************************
// Función para activar/desactivar las animaciones
//***************************************************************************

void Escena::conmutarAnimaciones()
{
	if(objeto_actual != 7)
		std::cout << "Error en las animaciones: no es un objeto jerárquico" << std::endl;

	else
	{
		animaciones = !animaciones;

		if(animaciones)
		{
			objjer->inicioAnimaciones();
			glutIdleFunc(funcion_desocupado);
		}

		else
			glutIdleFunc(nullptr);
	}
}

/******************************************************************************/
// Funciones para la selección con el ratón del objeto

/******************************************************************************/

/******************************************************************************/
// Pinta el buffer trasero con distintos tonos de gris para poder elegir el
// aspa que se va a cambiar de color

/******************************************************************************/

void Escena::drawBufferTrasero()
{
	glDisable(GL_DITHER);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glPushMatrix();
		glPushMatrix();
			glColor3ub(100, 100, 100);
			molino->draw(1, false, 100, 100, 100);
		glPopMatrix();

		glPushMatrix();
			glRotatef(-90, 0.0, 0.0, 1.0);
			molino->draw(2, false, 130, 130, 130);
		glPopMatrix();

		glPushMatrix();
			glRotatef(-180, 0.0, 0.0, 1.0);
			molino->draw(3, false, 160, 160, 160);
		glPopMatrix();

		glPushMatrix();
			glRotatef(-270, 0.0, 0.0, 1.0);
			molino->draw(4, false, 190, 190, 190);
		glPopMatrix();
	glPopMatrix();

	glEnable(GL_DITHER);
}

void Escena::drawBufferDelantero()
{
	glDisable(GL_DITHER);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glPushMatrix();
		glPushMatrix();
			molino->draw(1, false, r1, g1, b1);
		glPopMatrix();

		glPushMatrix();
			glRotatef(-90, 0.0, 0.0, 1.0);
			molino->draw(2, false, r2, g2, b2);
		glPopMatrix();

		glPushMatrix();
			glRotatef(-180, 0.0, 0.0, 1.0);
			molino->draw(3, false, r3, g3, b3);
		glPopMatrix();

		glPushMatrix();
			glRotatef(-270, 0.0, 0.0, 1.0);
			molino->draw(4, false, r4, g4, b4);
		glPopMatrix();
	glPopMatrix();

	glEnable(GL_DITHER);
}

/******************************************************************************/
// Se selecciona el aspa que se ha pulsado desde la función pick_color
/******************************************************************************/

void Escena::seleccionarAspa(unsigned char pixel[3])
{
	switch (pixel[0])
	{
		case 100:
		{
			if(r1 == 204)
			{
				glColor3ub(51, 204, 255);
				r1 = 51; g1 = 204; b1 = 255;
			}

			else
			{
				glColor3ub(204, 102, 255);
				r1 = 204; g1 = 102; b1 = 255;
			}
		}
			break;

		case 130:
		{
			if(r2 == 204)
			{
				glColor3ub(51, 204, 255);
				r2 = 51; g2 = 204; b2 = 255;
			}

			else
			{
				glColor3ub(204, 102, 255);
				r2 = 204; g2 = 102; b2 = 255;
			}
		}
			break;

		case 160:
		{
			if(r3 == 204)
			{
				glColor3ub(51, 204, 255);
				r3 = 51; g3 = 204; b3 = 255;
			}

			else
			{
				glColor3ub(204, 102, 255);
				r3 = 204; g3 = 102; b3 = 255;
			}
		}
			break;

		case 190:
		{
			if(r4 == 204)
			{
				glColor3ub(51, 204, 255);
				r4 = 51; g4 = 204; b4 = 255;
			}

			else
			{
				glColor3ub(204, 102, 255);
				r4 = 204; g4 = 102; b4 = 255;
			}
		}
			break;
	}
}

/******************************************************************************/
// Función que se llama al pulsar el botón del ratón
/******************************************************************************/

void Escena::pickObjeto(int x, int y)
{
	GLint viewport[4];
	unsigned char pixel_leido[3];

	glGetIntegerv(GL_VIEWPORT, viewport);
	glReadBuffer(GL_BACK);
	glReadPixels(x, viewport[3] - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, (GLubyte *) &pixel_leido[0]);
	printf("Coordenada(%d, %d)->Color(%d, %d, %d)\n", x, y, pixel_leido[0], pixel_leido[1], pixel_leido[2]);

	seleccionarAspa(pixel_leido);

	glutPostRedisplay();
}
