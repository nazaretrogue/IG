#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "jerarquico.h"
#include "textura.h"
#include "cuadro.h"

class Escena
{
	private:

	Ejes ejes;

	// variables que definen la posicion de la camara en coordenadas polares
	GLfloat Observer_distance;
	GLfloat Observer_angle_x;
	GLfloat Observer_angle_y;

	// variables que controlan la ventana y la transformacion de perspectiva
	GLfloat Width, Height, Front_plane, Back_plane;

	void clear_window();
	void dibujar_objeto_actual();

	// Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();

	int objeto_actual = 0 , 	// objeto actual (el que se visualiza)
		num_objetos   = 0 , 	// número de objetos (actualizado al crear los objetos en el constructor)
		modo = 0;		   		// modo de visualización del objeto: puntos, líneas o relleno

	bool inmediato = true,		// modo de dibujo, inmediato o diferido
		 animaciones = false;	// true si las animaciones están activadas

	// Objetos de la escena
	Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'

	Tetraedro *tetraedro = nullptr;
	ObjPLY *objply = nullptr;
	ObjRevolucion *objrev = nullptr;
	Cilindro *cilindro = nullptr;
	Cono *cono = nullptr;
	Esfera *esfera = nullptr;
	ObjJerarquico *objjer = nullptr;

	Luces luz;
	int giro_luz = 0;
	int material = 0;

	// Material 1
	GLfloat mb[4] = {0.2, 0.8, 0.2, 1.0}; // material verde, para ambiente
	GLfloat mg[4] = {0.4, 0.8, 1.0, 1.0}; // material azul, para difuso
	GLfloat mw[4] = {1.0, 1.0, 1.0, 1.0}; // material blanco, para especular

	// Material 2
	GLfloat my[4] = {0.8, 0.6, 0.0, 1.0}; // material amarillo, para ambiente
	GLfloat mm[4] = {1.0, 1.0, 0.4, 1.0}; // material marrón, para difuso
	GLfloat mwh[4] = {1.0, 1.0, 1.0, 1.0}; // material blanco, para especular

	// Brillo
	float brillo = 100.0;

	Textura *tex = nullptr;
	Cuadro *cuadro = nullptr;

	public:

	Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

	// Para las animaciones
	void mgeDesocupado();

	private:
	void conmutarAnimaciones();

};
#endif
