

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
	Observer_distance = 2.0;
	Observer_angle_x  = 0.0;
	Observer_angle_y  = 0.0;

	ejes.changeAxisSize( 5000 );

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
	cubo_ex = new Cubo();

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
		case 1:
		case 2:
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_ex_especular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ex_ambiente_difuso);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_ex_ambiente_difuso);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo_ex);
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
		if(cubo_ex != nullptr)
		{
			// En este cubo ponemos las luces que hemos hecho en el examen,
			// es decir, la celeste y la marrón. En el resto de objetos
			// hay activa una única luz blanca para poder apreciar los materiales
			// de los restantes ejercicios del examen
			glEnable(GL_LIGHT1);
			glEnable(GL_LIGHT2);
			glDisable(GL_LIGHT0);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mwh);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mwh);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mwh);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);
			cubo_ex->draw(modo, inmediato);
		}
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
		giro_luz = (giro_luz + 15)%30;
		break;
	case 'j':
	case 'J':
		giro_luz = (giro_luz - 15)%30;
		break;
	case 't':
	case 'T':
		material = (material+1)%3;
		break;
	case 'b':
	case 'B':
		if(brillo_ex < 100.0)
			brillo_ex = 120.0;
		else
			brillo_ex = 60.0;
		break;
	case 'd':
	case 'D':
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT1);
		glEnable(GL_LIGHT0);
		if(mat_ex_ambiente_difuso[0] == 0.0)
		{
			// Material carne dorada
			mat_ex_ambiente_difuso[0] = 0.91;
			mat_ex_ambiente_difuso[1] = 0.706;
			mat_ex_ambiente_difuso[2] = 0.451;
		}
		else
		{
			// Material turquesa
			mat_ex_ambiente_difuso[0] = 0.247;
			mat_ex_ambiente_difuso[1] = 0.541;
			mat_ex_ambiente_difuso[2] = 0.608;
		}
		break;
	case 'e':
	case 'E':
		if(mat_ex_especular[0] == 0.8)
		{
			// Material especular carne dorada
			mat_ex_especular[0] = 0.25;
			mat_ex_especular[1] = 0.25;
			mat_ex_especular[2] = 0.25;
		}
		else
		{
			// Material especular turquesa
			mat_ex_especular[0] = 0.8;
			mat_ex_especular[1] = 0.8;
			mat_ex_especular[2] = 0.8;
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
		Observer_angle_y--;
		break;
	case GLUT_KEY_RIGHT:
		Observer_angle_y++;
		break;
	case GLUT_KEY_UP:
		Observer_angle_x--;
		break;
	case GLUT_KEY_DOWN:
		Observer_angle_x++;
		break;
	case GLUT_KEY_PAGE_UP:
		Observer_distance *= 1.2;
		break;
	case GLUT_KEY_PAGE_DOWN:
		Observer_distance /= 1.2;
		break;
	}

	//std::cout << Observer_distance << std::endl;
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
	glFrustum( -wx, +wx, -wy, +wy, Front_plane, Back_plane );
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

void Escena::change_observer()
{
	// posicion del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef( 0.0, 0.0, -Observer_distance );
	glRotatef( Observer_angle_x, 1.0,0.0, 0.0 );
	glRotatef( Observer_angle_y, 0.0, 1.0, 0.0 );
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
