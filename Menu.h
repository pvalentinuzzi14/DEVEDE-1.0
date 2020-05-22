#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "tdaClientes.h"

///Prototipado
char PreguntarSalida();
void menuPrincipal();
void Color(int x);
char PreguntarSalida();
void menuRegistro();
int iniciarSecion();
void menuCliente(celdaRubros arregloRubros[], int idCliente,int validosRubros);
void menuAdmin(nodoArbol * arbol, int Idcliente,celdaRubros arregloRubros[]);
void menuAdminCliente(nodoArbol * arbol, int Idcliente,celdaRubros arregloRubros[]);
void menuAdminArticulos();
void arreglopass(char pass[20]);

#endif // MENU_H_INCLUDED
