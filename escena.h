#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "jerarquico.h"

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

   int objeto_actual = 0 , // objeto actual (el que se visualiza)
       num_objetos   = 0 , // número de objetos (actualizado al crear los objetos en el constructor)
	   modo = 0,		   // modo de visualización del objeto: puntos, líneas o relleno
	   modo_dibujo = 0;	   // modo de dibujo, inmediato o diferido

   // Objetos de la escena
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'

   // completar: añadir punteros a tetraedro u otros (práctica 1),
   //            y a un objeto PLY y de revolución (práctica 2),
   //           y a un objeto jerarquico (práctica 3).
   // ......

	Tetraedro *tetraedro = nullptr;
	ObjPLY *objply = nullptr;
	ObjRevolucion *objrev = nullptr;
	Cilindro *cilindro = nullptr;
	Cono *cono = nullptr;
	Esfera *esfera = nullptr;

   public:

   Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

};
#endif
