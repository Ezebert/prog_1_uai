////////////////////////////////////////////////////////////////////////////////
// ARCHIVO   : PE_TP11_BERTINAT.c
// AUTOR     : Affonso, Francisco
//             Bertinat, Ezequiel
// VERSI�N   : 1.0 
// FECHA     : 29/06/2014.
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definicion
#define true  1
#define false 0

#define AGREGAR 1
#define VER 2
#define DESCARTAR 3
#define LIMPIAR 4
#define SALIR 5

//DECLARACIONES DE ESTRUCTURAS
typedef struct STarea
{
  int numero;
  char titulo[100];
} Tarea;

typedef struct SCola
{ 
  int actual;  
  int cima;
  
  Tarea *tareas;
  
} Pila;


//DECLARACIONES DE FUNCIONES
void crear(Pila* pila, int size);
void liberar(Pila *pila);

int estaVacia(Pila *pila);
int estaLlena(Pila *pila);
int limpiar(Pila *pila);

void insertar(Pila *pila, int numero, char *titulo); //push
Tarea* tomar(Pila *pila);//pull
Tarea* ver(Pila *pila);//peek 

//funciones de menu:
int preguntarCantidadDeTareas();
int preguntarAccion();
void mostrarMensajeDeOpctionInvalida();
void obtenerTareaDesdeUsuario(Pila *pila);
void mostrarActual(Pila *pila);
void mostrarYDescargar(Pila *pila);
void limpiarPila(Pila *pila);

//codigo
int main(int argc, char *argv[])
{
    ////DECLARACIONES DE VARIABLES
  Pila pila; //Estructura pila
  int size; /
  int opcion;
  Tarea *tarea;
  
  size = preguntarCantidadDeTareas();
  
  // pedir tama�o por consola
  crear(&pila, size);
  //Menu de la consola, cierre con 5 - SALIR
  while( (opcion = preguntarAccion()) != SALIR ){
         switch(opcion) {
             case AGREGAR:
                 obtenerTareaDesdeUsuario(&pila);
                 break; 
             case VER:
                 mostrarActual(&pila);
                 break; 
             case DESCARTAR:
                 mostrarYDescargar(&pila);
                 break; 
             case LIMPIAR:
                 limpiarPila(&pila);
                 break;                  
             default : /* Optional */
                 if(opcion!=5)             
                   mostrarMensajeDeOpctionInvalida();             
         };//Fin switch

  }//Fin While
  liberar(&pila);
  return 0;
}//Fin Main()

//******************************************************************************
//				               DEFINICION DE LAS FUNCIONES
//==============================================================================
// FUNCION   : int preguntarCantidadDeTareas()
// ACCION    : Ingreso de la cantidad de tareas a realizar
// PARAMETROS: NADA.
// DEVUELVE  : La cantidad de tareas a realizar
//..............................................................................
// NOTA:
//------------------------------------------------------------------------------
int preguntarCantidadDeTareas() {
    int size;
    
    printf( "Cuntas tareas (cima)?\n-");
    scanf("%d", &size);
    return size;
    getch();
}
//==============================================================================
// FUNCION   : int preguntarAccion()
// ACCION    : Muestra el complemento del menu principal
// PARAMETROS: NADA.
// DEVUELVE  : NADA.
//..............................................................................
// NOTA: Complemento del menu principal
//------------------------------------------------------------------------------
int preguntarAccion() {
    int accion;
  //  system("cls"); 
    printf( "\n\nSeleccione un accion?\n");
    printf( "- %d AGREGAR\n", AGREGAR);
    printf( "- %d VER\n", VER);
    printf( "- %d DESCARTAR\n", DESCARTAR);
    printf( "- %d LIMPIAR\n\n", LIMPIAR); 
    printf( "- %d SALIR\n", SALIR); 
    
    scanf("%d", &accion);
    
    return accion;
}
//==============================================================================
// FUNCION   : void mostrarMensajeDeOpctionInvalida()
// ACCION    : Indicador de msj opcion invalida 
// PARAMETROS: NADA.
// DEVUELVE  : NADA.
//..............................................................................
// NOTA: 
//------------------------------------------------------------------------------
void mostrarMensajeDeOpctionInvalida(){
    printf( "Opcion Invalida\n");
    getch();
}
//==============================================================================
// FUNCION   : void obtenerTareaDesdeUsuario(Pila *pila)
// ACCION    : Ingreso de datos 
// PARAMETROS: struct Pila -> Structura utilizada para laa funcion
// DEVUELVE  : NADA.
//..............................................................................
// NOTA: El ingreso de datos es mientras queda lugares libres en la pila
//------------------------------------------------------------------------------
void obtenerTareaDesdeUsuario(Pila *pila){
     
  int numero;
  char titulo[100];
  
   if(pilaLlena(pila) == false) {
      
    printf( "\n\nIngrese tarea\n nr texto\n");
    scanf("%d %s", &numero, titulo);
    
    insertar(pila, numero, titulo);
      
  } else {
    printf( "\n\nYa no se pueden cargar mas tareas\n");
    getch();
  }
  
}
//==============================================================================
// FUNCION   : void mostrarActual(Pila *pila)
// ACCION    : Muestra el contenido actual de la pila (ultimo)
// PARAMETROS: struct Pila -> Structura utilizada para laa funcion
// DEVUELVE  : NADA.
//..............................................................................
// NOTA: 
//------------------------------------------------------------------------------
void mostrarActual(Pila *pila) {
     
  Tarea *tarea;
  //test:
  if(pilaVacia(pila) == false) {
    printf( "\n\nTarea Actual:\n");
    tarea = ver(pila); //no la saca
    printf( "- %d %s\n", tarea->numero, tarea->titulo);
    getch();
    
  } else {
    printf( "\n\nSin tareas\n");
    getch();
  }
  
}
//==============================================================================
// FUNCION   : void mostrarYDescargar(Pila *pila)
// ACCION    : Muestra el contenido actual de la pila (ultimo)
// PARAMETROS: struct Pila -> Structura utilizada para laa funcion
// DEVUELVE  : NADA.
//..............................................................................
// NOTA: 
//------------------------------------------------------------------------------
void mostrarYDescargar(Pila *pila){
     
  Tarea *tarea;
  //test:
  if(pilaVacia(pila) == false) {  
                     
    printf( "\n\nDescartando:\n");
    mostrarActual(pila);
    tarea = tomar(pila); //l saca
  } else {
      printf( "\n\nSin tareas\n");
  }
  getch();
}
//==============================================================================
// FUNCION   : void crear(Pila* pila, int size){
// ACCION    : declaracion incial de la structura de pila
// PARAMETROS: struct Pila -> Structura utilizada para laa funcion
//             int size -> Tama�o de la pila
// DEVUELVE  : NADA.
//..............................................................................
// NOTA: Crea la pila con parametros como datos inciales 
//------------------------------------------------------------------------------
void crear(Pila* pila, int size){
     pila->actual = 0;
     pila->cima = size;
     
     pila->tareas = malloc(sizeof(Pila) * size);//calcula el total de regristro 
}
//==============================================================================
// FUNCION   : void limpiarPila(Pila *pila)
// ACCION    : Limpia la pila en su totalidad
// PARAMETROS: struct Pila -> Structura utilizada para laa funcion
// DEVUELVE  : NADA.
//..............................................................................
// NOTA: 
//------------------------------------------------------------------------------
void limpiarPila(Pila *pila) {
    pila->actual = 0;
    printf("\n\nPila Limpiada");
    getch();
}
//==============================================================================
// FUNCION   : void liberar(Pila *pila) 
// ACCION    : Libera la pila en su totalidad
// PARAMETROS: struct Pila -> Structura utilizada para laa funcion
// DEVUELVE  : NADA.
//..............................................................................
// NOTA: 
//------------------------------------------------------------------------------
void liberar(Pila *pila) {
     free( pila->tareas );//Liberacion de las tareas de pila
//     printf("\n\nPila Liberada");
}
//==============================================================================
// FUNCION   : void insertar(Pila *pila, int numero, char *titulo) 
// ACCION    : Ingreso de datos
// PARAMETROS: struct Pila -> Structura utilizada para laa funcion
//             int numero -> dato
//             char+titulo -> dato
// DEVUELVE  : NADA.
//..............................................................................
// NOTA: 
//------------------------------------------------------------------------------
void insertar(Pila *pila, int numero, char *titulo) {
     
     pila->actual++;//Incremnta 1 la pila1
     
     //por q es 0-based
     Tarea* tarea = &pila->tareas[pila->actual-1];
     
     tarea->numero = numero;
     
     strcpy( tarea->titulo, titulo);
     
}

Tarea* tomar(Pila *pila){
       //ver si esta bien esto
       Tarea *tarea = &pila->tareas[pila->actual-1];
       
       pila->actual--;
       
       return tarea;
}

Tarea* ver(Pila *pila) {
        return &pila->tareas[pila->actual-1]; 
}
//==============================================================================
// FUNCION   : int pilaVacia(Pila *pila) 
// ACCION    : Demuestra si la Pila esta vacia
// PARAMETROS: struct Pila -> Structura utilizada para laa funcion
// DEVUELVE  : false -> Pila contiene contenido
//           true-> Pila vacia
//..............................................................................
// NOTA: 
//------------------------------------------------------------------------------
int pilaVacia(Pila *pila) {
    if(pila->actual > 0) {
       return false;
     } 
     
     return true;
}
//==============================================================================
// FUNCION   : int pilaLlena(Pila *pila) 
// ACCION    : Demuestra si la Pila esta llena
// PARAMETROS: struct Pila -> Structura utilizada para laa funcion
// DEVUELVE  : true -> Pila llena
//             false -> Pila vacia
//..............................................................................
// NOTA: Pila llena solo si la cantidad de tareas es igual a su tope.
//------------------------------------------------------------------------------
int pilaLlena(Pila *pila) {
    if(pila->actual >= pila->cima) {
       return true;
     } 
     
     return false;
}
