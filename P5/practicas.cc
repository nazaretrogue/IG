//**************************************************************************
// Prácticas
//
// F.J. melero
//
// GPL
//**************************************************************************


#include "aux.h" // includes de OpenGL, windows, y librería std de C++
#include "escena.h"

// variable que contiene un puntero a la escena
Escena *escena = nullptr ;


//***************************************************************************
// Funcion principal que redibuja la escena
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void draw_scene(void)
{
    glDrawBuffer(GL_FRONT);

	if ( escena != nullptr )
      escena->dibujar();
	//glutSwapBuffers();
    glFlush();
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size( int newWidth, int newHeight )
{
	if ( escena != nullptr )
      escena->redimensionar(newWidth,newHeight);
	glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys( unsigned char tecla, int x, int y )
{
	int salir = 0;

   if ( escena!= nullptr )
      salir = escena->teclaPulsada( tecla, x, y );

	if ( salir )
   {
		delete escena;
      escena = nullptr ;
		exit(0);
	}
   else
		glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys( int tecla, int x, int y )
{
	if (escena!=NULL)
		escena->teclaEspecial( tecla, x, y );
	glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se desactivan las animaciones

//***************************************************************************

void funcion_desocupado()
{
	if(escena != NULL)
		escena->mgeDesocupado();

	glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se pulsan los botones el ratón
//***************************************************************************

void ratonMovido(int x, int y)
{
    escena->ratonMovido(x, y);
    glutPostRedisplay();
}

void clickRaton(int boton, int estado, int x, int y)
{using namespace std;
	if(boton == GLUT_RIGHT_BUTTON && estado == GLUT_DOWN)
	{
		if(escena != NULL)
			escena->activarMovimientoRaton(0);
	}

	else if(boton == 3)
	{
		if(escena != NULL)
        {
            escena->activarMovimientoRaton(1);
            escena->teclaEspecial(GLUT_KEY_PAGE_UP, x, y);
        }
	}

	else if(boton == 4)
	{
		if(escena != NULL)
        {
            escena->activarMovimientoRaton(2);
            escena->teclaEspecial(GLUT_KEY_PAGE_DOWN, x, y);
        }
	}

	else if(boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
	{
		if(escena != NULL)
        {
            escena->activarMovimientoRaton(3);
            escena->pickObjeto(x, y);
        }
	}

    else
    {
        if(escena != NULL)
            escena->activarMovimientoRaton(4);
    }

	glutPostRedisplay();
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main( int argc, char **argv )
{
   using namespace std ;

   // crear la escena (un puntero a la misma)
   escena = new Escena();

   // Incialización de GLUT

   // se llama a la inicialización de glut
   glutInit( &argc, argv );

   // se indica las caracteristicas que se desean para la visualización con OpenGL
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

   // variables que determninan la posicion y tamaño de la ventana X
   const int UI_window_pos_x  = 50,
             UI_window_pos_y  = 50,
             UI_window_width  = 500,
             UI_window_height = 500;

   // posicion de la esquina inferior izquierdad de la ventana
   glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

   // tamaño de la ventana (ancho y alto)
   glutInitWindowSize(UI_window_width,UI_window_height);

   // llamada para crear la ventana, indicando el titulo
   glutCreateWindow("Practicas IG: NAZARET ROMAN GUERRERO");

   // asignación de la funcion llamada "dibujar" al evento de dibujo
   glutDisplayFunc( draw_scene );

   // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
   glutReshapeFunc( change_window_size );

   // asignación de la funcion llamada "tecla_normal" al evento correspondiente
   glutKeyboardFunc( normal_keys );

   // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
   glutSpecialFunc( special_keys );

   glutMouseFunc(clickRaton);
   glutMotionFunc(ratonMovido);

   // inicialización de librería GLEW (solo en Linux)
   #ifdef LINUX
   const GLenum codigoError = glewInit();

   if ( codigoError != GLEW_OK ) // comprobar posibles errores
   {
      cout << "Imposible inicializar ’GLEW’, mensaje recibido: "
             << glewGetErrorString(codigoError) << endl ;
      exit(1) ;
   }
   #endif

   // funcion de inicialización de la escena (necesita que esté la ventana creada)
   escena->inicializar( UI_window_width, UI_window_height );

   // TEST

   // ejecutar del bucle de eventos
   glutMainLoop();

   return 0;
}
