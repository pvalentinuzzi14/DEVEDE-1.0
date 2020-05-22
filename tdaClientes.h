#ifndef TDACLIENTES_H_INCLUDED
#define TDACLIENTES_H_INCLUDED
#define AUMENTO 1.25
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
///Declaro estructuras para el uso de los productos
typedef struct
{
   int precioLista;
   int minorista;
   int mayorista;
}stPrecio;

typedef struct
{

    int idProducto;
    int codigoProducto;
    char descripcion[40];
    int stock;
    int eliminado; // 0 para activo, 1 para eliminado
    stPrecio precio;
    int rubro;
    int subrubro;

}stProductos;

typedef struct _nodoProducto
{
    stProductos dato;
    struct _nodoProducto *siguiente;
} nodoProducto; //2

typedef struct nodoSubRubros
{
    int subRubro;
    char nombreSubRubro[14];
    struct nodoSubRubros*siguiente;
    nodoProducto*lista;
} nodoSubRubros; //1

typedef struct
{
    int rubro;
    struct nodoSubRubros*subListas;
} celdaRubros;

///Declaro estructuras para el uso de usuarios.
typedef struct
{
    int idUsuario;
    char usuario[20];
    char password[20];
    char nombre[20];
    char apellido[20];
    char direccion[30];
    char ciudad[20];
    int idCiudad;
    char telefono[11];
    int condicion; // 1 PARA MAYORISTA - 2 PARA MINORISTA
    char email[30];
    int admin; // 0 para usuario - 1 para admin
    int eliminado; // determina si esta activo o no este cliente
    int edad;
}stUsuarios;

typedef struct{
    stUsuarios dato;
    struct nodoArbol * derecha;
    struct nodoArbol * izquierda;
}nodoArbol;

typedef struct
{
    int idCiudad;
    char ciudad[30];
    nodoArbol * arbolito;
}celdaCiudad;


typedef struct
{
    int cantidad;
    int codigoProducto;

}stProductoVentas;

typedef struct
{
    char date[128];
    int idCliente;
    stProductoVentas producVentas ;
    int idVenta;
    int cobro;

}stVentas;

///FUNCIONES PARA EL MANEJO DE PRODUCTOS
int selecRubro();
int selecSubRubro(int r);
void cargaProductos();
void guardarProducto(stProductos a);
int generarCodigoProducto(int a,int b);
int calculaSubRubro(int a,int primerosDos);
void muestraProducto(stProductos a);
void recorrerArchivoProductos();
int buscarUltimoIDArticulo();
int buscarUltimoIDRubro(int codigoProducto);
void getRubro(int idRubro);
void getSubRubro(int subrubro,int idRubro);
void mostrarListaProductos(nodoSubRubros*subLista);
nodoProducto*inicListaProductos();
nodoSubRubros*inicListaSubRubros();
nodoProducto* crearNodoProducto(stProductos a);
nodoSubRubros * agregarPpioSubListas (nodoSubRubros*lista,nodoSubRubros*nuevo);
nodoProducto * buscarUltimoProducto (nodoProducto*lista);
nodoSubRubros*agregarOrdenadoSublistas(nodoSubRubros*nuevo,nodoSubRubros*subListas);
nodoProducto*agregarFinalListaProductos(nodoProducto*nuevo,nodoProducto*lista);
nodoSubRubros*crearNodoSubrubros(stProductos a);
nodoSubRubros*buscarSubrubros(nodoProducto*nuevoProducto,nodoSubRubros*lista);
void iniciarCeldas(celdaRubros*arregloRubros,int dimension);
int crearArregloRubros(celdaRubros**arregloRubros);
void sumaTotalProductos();
stProductos consultaProductos(celdaRubros arreglo[],int productoBuscado);
int buscarXcodigoProducto(int codigoProducto);
void modifDatosArticulos(int codigoProducto,int opcionModificacion);
void altaBajaProducto(int idProducto);
stProductos consultaProductosArchivo(int productoBuscado);

///FUNCIONES PARA EL MANEJO DE USUARIOS

void preOrder(nodoArbol *arbol);
int comprobar(celdaCiudad **celda, int dato, int validos);
void mostrarCeldas(celdaCiudad *celda, int validos);
int cargarArregloCiudad(celdaCiudad **celda);
nodoArbol * insertar(nodoArbol *arbol, nodoArbol * nuevo);
nodoArbol * crearNodoArbol(stUsuarios usuario);
int usuarioExistente (char nombreUsuario[]);
void generarUsuarios();
void muestraUsuario(stUsuarios a);
void mostrarListadoUsuarios();
void guardarUsuario(stUsuarios a);
int buscarUltimoIDUsuarios();
void verPerfil(stUsuarios usuario);
stUsuarios consultaClientes(int idCliente);
void altaBajaUsuario(int idUsuario);
void altaAdmin(int idUsuario);
int buscarUltimoIdCiudad();
int buscarCiudad(char ciudad[]);

nodoSubRubros*buscarSubrubrosCuadro(nodoSubRubros*lista,int subrubro);
void crearCuadroProductos(int x,int y,celdaRubros arreglo[],int rubro,int subrubro);

void fGetNow(char date[]);


#endif // TDACLIENTES_H_INCLUDED
