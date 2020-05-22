#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "windows.h"
#include "time.h"
#include "Menu.h"
#include "tdaClientes.h"
void Color(int x){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
}
void menuPrincipal(){
    int colorNormal=15;  ///LETRA CELESTE
    int colorSobre=11;
    int candado=-1;                              ///hay que inicializaro en -1 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!KFAEAIEJFFAFASFASF
    char control='s';
    char opcion;

    ///CREACION DE ESTRUCTURA DE PRODUCTOS
    celdaRubros*arregloRubros=NULL;
    int validosArreglo=crearArregloRubros(&arregloRubros);
    nodoArbol * arbol;

    int y=7;
    int cm=0;
    do{
        system("cls");
        color(10);///letra verde/ fondo negro
        for(cm=0; cm<23; cm++)
        {
            if(cm==0)
            {
                printf("%c",201);
            }
            printf("%c",205);
            if(cm==22)
            {
                printf("%c",187);
            }
        }
        printf("\n%c....MENU PRINCIPAL.... %c\n",186,186);
        for(cm=0; cm<23; cm++)
        {
            if(cm==0)
            {
                printf("%c",200);
            }
            printf("%c",205);
            if(cm==22)
            {
                printf("%c",188);
            }
        }

        printf("\n\n\n");
        color(colorNormal);///letra celeste/ fondo negro
        if(y==7)
            color(colorSobre);
            printf(" .Registro\n");
            color(colorNormal);
        if(y==10)
            color(colorSobre);
            printf(" .Menu Cliente\n");
            color(colorNormal);
        if(y==13)
            color(colorSobre);
            printf(" .Menu Admin\n");
            color(colorNormal);
        if(y==16)
            color(colorSobre);
            printf(" .Salir");
        opcion=getch(); ///retorna el numero del codigo ascii de la tecla ingresada
        if(opcion==80)  ///tecla de abajo
        {
            if(y==16)
            {
                y=7;
            }
            else
            {
                y=y+3;
            }
        }
        if(opcion==72) ///tecla de arriba
        {
            if(y==7)
            {
                y=16;
            }
            else
            {
                y=y-3;
            }
        }
        if(opcion==13){    ///tecla ENTER
            system("cls");
            if(y == 16){
                control = PreguntarSalida();
                if(control!='s'){
                    menuPrincipal();
                }
                else
                {
                    system("cls");
                    color(2);
                    printf("------------->Fin del programa<-------------\n\n");
                    exit(1);
                }
            }
            if(y == 13){                ///LLamada al menu admin
               candado = iniciarSesionAdmin();
                if(candado == -1){
                    system("cls");
                    system("color 0c");
                    printf("Error! Se ha denegado su acceso.\n\nHa alcanzado el limites de intentos.\n\n");
                    system("pause");
                    menuPrincipal();
                }else{
                    menuAdmin(arbol,candado,arregloRubros);
                }
            }
            if(y == 10){
                ///llamada a la funcion Menu cliente
                candado = iniciarSesionUsuario();
                if(candado == -1){
                    system("cls");
                    system("color 0c");
                    printf("Error! Se ha denegado su acceso.\n\nHa alcanzado el limites de intentos.\n\n");
                    system("pause");
                    menuPrincipal();
                }else{
                    menuCliente(arregloRubros, candado,validosArreglo);
                }
            }
            if(y == 7){
                ///llamada a la funcion menu registro
                menuRegistro();
            }
        }
    }while(1);
}
char PreguntarSalida(){
    char control='s';
    system("cls");
    system("color 0c");
    printf("Seguro desea salir?(S/N): ");
    fflush(stdin);
    scanf("%c",&control);
    system("cls");
    system("color 07");
    return control;
}
void menuRegistro(){
        int cm;
        int colorNormal=15;  ///LETRA blanca
        int colorSobre=3;    ///LETRA cyan
        system("cls");
        char nombreUsuario[30];
        char clave[30];
        color(colorSobre);///letra cyan/ fondo negro
        for(cm=0; cm<16; cm++)
        {
            if(cm==0)
            {
                printf("%c",201);
            }
            printf("%c",205);
            if(cm==15)
            {
                printf("%c",187);
            }
        }
        printf("\n%c >REGISTRO      %c\n",186,186);
        for(cm=0; cm<16; cm++)
        {
            if(cm==0)
            {
                printf("%c",200);
            }
            printf("%c",205);
            if(cm==15)
            {
                printf("%c",188);
            }
        }
        printf("\n\n\n");

        generarUsuarios();
}
int iniciarSesionUsuario(){
        int cm, rta=-1, condicion = 0;
        int colorNormal=15;  ///LETRA blanca
        int colorSobre=3;    ///LETRA cyan
        system("cls");
        char nombreUsuario[30];
        char clave[30];
        color(colorSobre);///letra cyan/ fondo negro
        do{
        for(cm=0; cm<18; cm++)
        {
            if(cm==0)
            {
                printf("%c",201);
            }
            printf("%c",205);
            if(cm==17)
            {
                printf("%c",187);
            }
        }
        printf("\n%c >INICIAR SESION  %c\n",186,186);
        for(cm=0; cm<18; cm++)
        {
            if(cm==0)
            {
                printf("%c",200);
            }
            printf("%c",205);
            if(cm==17)
            {
                printf("%c",188);
            }
        }
        printf("\n\n\n");
        color(colorNormal);
        printf("Nombre de usuario: ");
        fflush(stdin);
        color(colorSobre);
        gets(nombreUsuario);

        color(colorNormal);
        printf("Clave: ");
        fflush(stdin);
        color(colorSobre);
        gets(clave);
        rta = validacionUsuario(nombreUsuario,clave);
        condicion++;
        if(rta ==-1 && condicion != 3){
            Color(2);
            printf("Error en el usuario contrasenia volve a ingresar te quedan %d intentos\n",3-condicion);
            system("pause");
            system("cls");
            Color(colorSobre);
        }
        }while(condicion != 3 && rta == -1);
        return rta;
}
int iniciarSesionAdmin(){
        int cm, rta=-1, condicion = 0;
        int colorNormal=15;  ///LETRA blanca
        int colorSobre=3;    ///LETRA cyan
        system("cls");
        char nombreUsuario[30];
        char clave[30];
        color(colorSobre);///letra cyan/ fondo negro
        do{
        for(cm=0; cm<18; cm++)
        {
            if(cm==0)
            {
                printf("%c",201);
            }
            printf("%c",205);
            if(cm==17)
            {
                printf("%c",187);
            }
        }
        printf("\n%c >INICIAR SESION  %c\n",186,186);
        for(cm=0; cm<18; cm++)
        {
            if(cm==0)
            {
                printf("%c",200);
            }
            printf("%c",205);
            if(cm==17)
            {
                printf("%c",188);
            }
        }
        printf("\n\n\n");
        color(colorNormal);
        printf("Nombre de usuario: ");
        fflush(stdin);
        color(colorSobre);
        gets(nombreUsuario);

        color(colorNormal);
        printf("Clave: ");
        fflush(stdin);
        color(colorSobre);
        gets(clave);
        rta = validacionAdmin(nombreUsuario,clave);
        condicion++;
        if(rta ==-1 && condicion != 3){
            Color(2);
            printf("Error en el usuario contrasenia volve a ingresar te quedan %d intentos\n",3-condicion);
            system("pause");
            system("cls");
            Color(colorSobre);
        }
        }while(condicion != 3 && rta == -1);
        return rta;
}
void menuCliente(celdaRubros arregloRubros[], int idCliente,int validosRubros){
    int cm ,y=7, candado = -1, opcionInt=0;
    int colorNormal=15;  //blanco
    int colorSobre=11;    //cyan
    stUsuarios buscado=consultaClientes(idCliente);
    char opcion, opcion2;
    srand(time(NULL));
    char date[128];
        do{
        validosRubros=crearArregloRubros(&arregloRubros);
        system("cls");
        color(3);///color cyan/ fondo negro
        for(cm=0; cm<19; cm++)
        {
            if(cm==0)
            {
                printf("%c",201);
            }
            printf("%c",205);
            if(cm==18)
            {
                printf("%c",187);
            }
        }
        printf("\n%c >MENU CLIENTE     %c\n",186,186);
        for(cm=0; cm<19; cm++)
        {
            if(cm==0)
            {
                printf("%c",200);
            }
            printf("%c",205);
            if(cm==18)
            {
                printf("%c",188);
            }
        }
        printf("\n\n\n");
        color(colorNormal);///letra celeste/ fondo negro
        if(y==7)
            color(colorSobre);
            printf(" .Ver Perfil\n");
            color(colorNormal);
        if(y==10)
            color(colorSobre);
            printf(" .Ver Catalogo\n");
            color(colorNormal);
        if(y==13)
            color(colorSobre);
            printf(" .Realizar una compra\n");
            color(colorNormal);
        if(y==16)
            color(colorSobre);
            printf(" .Articulos recomendados\n");
            color(colorNormal);
        if(y == 19)
            color(colorSobre);
            printf(" .Mostrar Estado de cuenta\n");
            color(colorNormal);
        if(y == 22)
            color(colorSobre);
            printf(" .Volver al menu principal\n");
            color(colorNormal);
        opcion=getch(); ///retorna el numero del codigo ascii de la tecla ingresada
        if(opcion==80)  ///tecla de abajo
        {
            if(y==22)
            {
                y=7;
            }
            else
            {
                y=y+3;
            }
        }
        if(opcion==72) ///tecla de arriba
        {
            if(y==7)
            {
                y=22;
            }
            else
            {
                y=y-3;
            }
        }
        if(opcion==13){    ///tecla ENTER
            system("cls");
            if(y == 22){
                menuPrincipal();
            }
            if(y == 19){
                ///llamar a funcion mostrar estado de cuenta
                recorrerArchivoVentasxUsuario(arregloRubros,buscado);
                int monto=deudaVentasxUsuario(arregloRubros,buscado);
                fGetNow(date);
                if(monto == 0){
                    Color(2);
                    printf("\n La deuda a la fecha(%s) es de : $ %d \n",date,monto);
                }else{
                    Color(4);
                    printf("\n La deuda a la fecha(%s) es de : $ %d \n",date,monto);
                }
                system("pause");
            }
            if(y == 16){
                buscado=consultaClientes(idCliente);
                crearCuadroRecomendaciones(0,3,arregloRubros,validosRubros,buscado);
            }
            if(y == 13){
                generarVenta(0,3,arregloRubros,buscado);
                system("pause");
            }
            if(y == 10){
               selecRubroMenu(arregloRubros,idCliente);
            }
            if(y == 7){
                ///llamada a la funcion ver perfil
                buscado = consultaClientes(idCliente);
                muestraUsuarioPerfil(buscado);
                Color(3);
                printf("\n1.Desea modificar algo s/n: ");
                fflush(stdin);
                scanf("%c",&opcion2);
                if(opcion2 == 's'){
                    printf("\n1.NOMBRE: ");
                    printf("\n2.APELLIDO: ");
                    printf("\n3.TELEFONO: ");
                    printf("\n4.EMAIL: ");
                    printf("\n5.PASSWORD: ");
                    printf("\nOpcion: ");
                    scanf("%d",&opcionInt);
                    modifDatos2(idCliente,opcionInt);
                    Color(2);
                    printf("\nSi desea realizar otra modificacion mande un email a compu@dev.com\n");
                    system("pause");
                }
            }
    }
  }while(candado == -1);
}

int consultarUsuarioMenu(){
        int cm, rta=-1, condicion = 0;
        int colorNormal=15;  ///LETRA blanca
        int colorSobre=3;    ///LETRA cyan
        system("cls");
        char nombreUsuario[30];
        char clave[30];
        color(colorSobre);///letra cyan/ fondo negro
        for(cm=0; cm<18; cm++)
        {
            if(cm==0)
            {
                printf("%c",201);
            }
            printf("%c",205);
            if(cm==17)
            {
                printf("%c",187);
            }
        }
        printf("\n%c >CONSULTA USER   %c\n",186,186);
        for(cm=0; cm<18; cm++)
        {
            if(cm==0)
            {
                printf("%c ",200);
            }
            printf("%c",205);
            if(cm==17)
            {
                printf("%c",188);
            }
        }
        printf("\n\n\n");
        color(colorNormal);
        printf("Nombre de usuario: ");
        fflush(stdin);
        color(colorSobre);
        gets(nombreUsuario);
        rta = validacionUsuarioParaConsultar(nombreUsuario);

        return rta;
}

void menuAdmin(nodoArbol * arbol, int Idcliente,celdaRubros arregloRubros[]){
        int cm ,y=7, candado = -1;
        int colorNormal=15;  //blanco
        int colorSobre=11;    //cyan
        char control;
        char opcion;
            do{
            system("cls");
            color(3);///color cyan/ fondo negro
            for(cm=0; cm<19; cm++)
            {
                if(cm==0)
                {
                    printf("%c",201);
                }
                printf("%c",205);
                if(cm==18)
                {
                    printf("%c",187);
                }
            }
            printf("\n%c >MENU ADMIN       %c\n",186,186);
            for(cm=0; cm<19; cm++)
            {
                if(cm==0)
                {
                    printf("%c",200);
                }
                printf("%c",205);
                if(cm==18)
                {
                    printf("%c",188);
                }
            }
            printf("\n\n\n");
            color(colorNormal);///letra celeste/ fondo negro
            if(y==7)
                color(colorSobre);
                printf(" .Administracion Clientes\n");
                color(colorNormal);
            if(y==10)
                color(colorSobre);
                printf(" .Administracion Articulos\n");
                color(colorNormal);
            if(y==13)
                color(colorSobre);
                printf(" .Cerrar sesion\n");
                color(colorNormal);
                opcion=getch(); ///retorna el numero del codigo ascii de la tecla ingresada
            if(opcion==80)  ///tecla de abajo
            {
                if(y==13)
                {
                    y=7;
                }
                else
                {
                    y=y+3;
                }
            }
            if(opcion==72){ ///tecla de arriba
                if(y==7)
                {
                    y=13;
                }
                else
                {
                    y=y-3;
                }
            }
            if(opcion==13){    ///tecla ENTER
                system("cls");
                if(y == 7){
                    ///llamada a la funcion Menu administracion cliente
                    menuAdminCliente(arbol, Idcliente,arregloRubros);
                }
                if(y == 10){
                    ///llamada a la funcion Menu administracion Articulos
                    menuAdminArticulos();

                }
                if(y == 13){
                control = PreguntarSalida();
                if(control!='s'){
                    menuAdmin(arbol, Idcliente,arregloRubros);
                }
                else{
                    menuPrincipal();
                }
            }
        }

    }while(1);
}

void menuAdminCliente(nodoArbol * arbol, int Idcliente,celdaRubros arregloRubros[]){
        stUsuarios buscado;
        int cm ,y=7, candado = -1, dimension =50;
        celdaCiudad *celdita;
        int colorNormal=15;  //blanco
        int colorSobre=11;    //cyan
        char opcion;
            do{
            system("cls");
            color(3);///color cyan/ fondo negro
            for(cm=0; cm<19; cm++)
            {
                if(cm==0)
                {
                    printf("%c",201);
                }
                printf("%c",205);
                if(cm==18)
                {
                    printf("%c",187);
                }
            }
            printf("\n%c >ADMIN CLIENTES   %c\n",186,186);
            for(cm=0; cm<19; cm++)
            {
                if(cm==0)
                {
                    printf("%c",200);
                }
                printf("%c",205);
                if(cm==18)
                {
                    printf("%c",188);
                }
            }
            printf("\n\n\n");
            color(colorNormal);///letra celeste/ fondo negro
            if(y==7)
                color(colorSobre);
                printf(" .Modificar cargo Admin\n");
                color(colorNormal);
            if(y==10)
                color(colorSobre);
                printf(" .Alta baja usuario\n");
                color(colorNormal);
            if(y==13)
                color(colorSobre);
                printf(" .Modificacion Usuario\n");
                color(colorNormal);
            if(y==16)
                color(colorSobre);
                printf(" .Consulta de clientes\n");
                color(colorNormal);
            if(y==19)
                color(colorSobre);
                printf(" .Listado de clientes\n");
                color(colorNormal);
            if(y==22)
                color(colorSobre);
                printf(" .Listado de ventas\n");
                color(colorNormal);
            if(y==25)
                color(colorSobre);
                printf(" .Realizar cobro\n");
                color(colorNormal);
            if(y==28)
                color(colorSobre);
                printf(" .Atras\n");
                color(colorNormal);
                opcion=getch(); ///retorna el numero del codigo ascii de la tecla ingresada
            if(opcion==80)  ///tecla de abajo
            {
                if(y==28)
                {
                    y=7;
                }
                else
                {
                    y=y+3;
                }
            }
            if(opcion==72){ ///tecla de arriba
                if(y==7)
                {
                    y=28;
                }
                else
                {
                    y=y-3;
                }
            }
            if(opcion==13){    ///tecla ENTER
                system("cls");
                if(y == 7){
                    ///LLAMAR A FUNCION Modificar cargo Admin
                    candado = consultarUsuarioMenu();
                    altaAdmin(candado);
                }
                if(y == 10){
                    ///LLAMAR A FUNCION Alta baja usuario
                    candado = consultarUsuarioMenu();
                    altaBajaUsuario(candado);
                }
                if(y == 13){
                    ///LLAMAR A FUNCION Modificacion Usuario
                    candado = consultarUsuarioMenu();
                    if(candado == -1){
                        Color(2);
                        printf("Usuario no existente\n");
                        system("pause");
                    }else{
                          Color(colorSobre);
                        int condicion = 0;
                        printf("1.Ciudad\n");
                        printf("2.Condicion\n");
                        printf("3.Direccion\n");
                        scanf("%d",&condicion);
                        modifUsuarioAdmin(candado,condicion);
                    }
                }
                if(y == 16){
                    ///LLAMAR A FUNCION Consulta de clientes
                    candado = consultarUsuarioMenu();
                    if(candado != -1){
                        buscado = consultaClientes(candado);
                        muestraUsuarioPerfil(buscado);
                    }else{
                       Color(11);
                       printf("El usuario buscado no existe") ;
                       system("pause");
                    }
                }
                if(y == 19){
                    ///LLAMAR A FUNCION Listado de clientes
                    int validos = cargarArregloCiudad(&celdita);
                    mostrarCeldas(celdita,validos);
                    system("pause");
                }
                if(y == 22){
                    ///LLAMAR A FUNCION Listado de ventas
                    recorrerArchivoVentas(arregloRubros);
                }
                if(y == 25){
                    ///LLamar a la funcion realizar cobro
                    generarCobro(arregloRubros);
                }
                if(y == 28){
                    menuAdmin(arbol, Idcliente,arregloRubros);
                }
            }

    }while(1);
}
void menuAdminArticulos(nodoArbol * arbol, int idCliente){
        int cm ,y=7, candado = -1, codigoProducto = 0, seccion=0, rubro=0, subrubro=0;
        int colorNormal=15;  //blanco
        int colorSobre=11;    //cyan
        stProductos buscado;
        celdaRubros *arreglo=NULL;
        int validos = crearArregloRubros(&arreglo);
        char opcion;
            do{
            int validos = crearArregloRubros(&arreglo);
            system("cls");
            color(3);///color cyan/ fondo negro
            for(cm=0; cm<19; cm++)
            {
                if(cm==0)
                {
                    printf("%c",201);
                }
                printf("%c",205);
                if(cm==18)
                {
                    printf("%c",187);
                }
            }
            printf("\n%c >ADMIN ARTICULOS  %c\n",186,186);
            for(cm=0; cm<19; cm++)
            {
                if(cm==0)
                {
                    printf("%c",200);
                }
                printf("%c",205);
                if(cm==18)
                {
                    printf("%c",188);
                }
            }
            printf("\n\n\n");
            color(colorNormal);///letra celeste/ fondo negro
            if(y==7)
                color(colorSobre);
                printf(" .Carga de articulos\n");
                color(colorNormal);
            if(y==10)
                color(colorSobre);
                printf(" .Alta baja articulos\n");
                color(colorNormal);
            if(y==13)
                color(colorSobre);
                printf(" .Modificacion articulos\n");
                color(colorNormal);
            if(y==16)
                color(colorSobre);
                printf(" .Consulta de articulos\n");
                color(colorNormal);
            if(y==19)
                color(colorSobre);
                printf(" .Listado de articulos\n");
                color(colorNormal);
            if(y==22)
                color(colorSobre);
                printf(" .Atras\n");
                color(colorNormal);
                opcion=getch(); ///retorna el numero del codigo ascii de la tecla ingresada
            if(opcion==80)  ///tecla de abajo
            {
                if(y==22)
                {
                    y=7;
                }
                else
                {
                    y=y+3;
                }
            }
            if(opcion==72){ ///tecla de arriba
                if(y==7)
                {
                    y=22;
                }
                else
                {
                    y=y-3;
                }
            }
            if(opcion==13){    ///tecla ENTER
                system("cls");
                if(y == 7){
                    ///LLAMAR A FUNCION Cargar de articulos
                    cargaProductos();
                }
                if(y == 10){
                    ///LLAMAR A FUNCION Alta baja articulos
                    Color(11);
                    printf("Ingrese codigo del producto a buscar");
                    scanf("%d",&codigoProducto);
                    buscado = consultaProductos(arreglo,codigoProducto);
                    int validos = crearArregloRubros(&arreglo);
                    altaBajaProducto(buscado.idProducto);
                }
                if(y == 13){
                    ///LLAMAR A FUNCION Modificacion articulos
                        Color(3);
                        codigoProducto=buscaProductoXsector(0,3,arreglo,buscado);
                        printf("\n1.Descripcion\n");
                        printf("2.Precio\n");
                        printf("3.Stock\n");
                        printf("Ingrese seccion a modificar: ");
                        scanf("%d",&seccion);

                        modifDatosArticulos(codigoProducto,seccion);
                }
                if(y == 16){
                    ///LLAMAR A FUNCION Consulta de articulos
                    int validos = crearArregloRubros(&arreglo);   ///llamo a la funcion para que se reinicen los datos
                    Color(3);
                    printf("Ingrese codigo del producto a buscar \n");
                    scanf("%d",&codigoProducto);
                    buscado = consultaProductosArchivo(codigoProducto);
                    if(buscado.eliminado == 1){
                        Color(2);
                        printf("Producto eliminado fuera de stock\n");
                        muestraProducto(buscado);
                        system("pause");
                    }else{
                        muestraProducto(buscado);
                    }
                }
                if(y == 19){
                    ///LLAMAR A FUNCION Listado de articulo
                    Color(3);
                    printf("INGRESE RUBRO A VER Y SUBRUBRO\n");
                    rubro=selecRubro();
                    subrubro=selecSubRubro(rubro);
                    crearCuadroProductos(0,3,arreglo,rubro,subrubro);
                    system("pause");
                }
                if(y == 22){
                int validos = crearArregloRubros(&arreglo);
                    menuAdmin(arbol,idCliente,arreglo);
                }
            }

    }while(1);
}


void arreglopass(char pass[20])         ///Arreglo para convertir el pass en *
{
    int pos=0, cont=0, cont2=0;
    int i=0;
    for(i=0; i<20; i++)
    {
        pass[i]=0;
    }
    pass[pos]=getch();
    if((pass[pos]!=13)&&(pass[pos]!=8))
    {
        printf("*");
    }
    while(pass[pos]!=13)
    {
        pos++;
        fflush(stdin);
        pass[pos]=getch();
        while((pos>0)&&(pass[pos]==8))
        {
            pass[pos]=0;
            pos=pos-1;
            printf("\b \b");
            pass[pos]=getch();
            while(pos==0&&pass[pos]==8)
            {
                pass[pos]=getch();
            }
        }
        if((pass[pos]!=13)&&(pass[pos]!=8))
        {
            printf("*");
            cont++;
        }
    }
}
void selecRubroMenu(celdaRubros arreglo[], int idCliente,int validosRubro){
        int cm ,y=7;
        int colorNormal=15;  //blanco
        int colorSobre=11;    //cyan
        char opcion;
            do{
            system("cls");
            color(3);///color cyan/ fondo negro
            for(cm=0; cm<19; cm++)
            {
                if(cm==0)
                {
                    printf("%c",201);
                }
                printf("%c",205);
                if(cm==18)
                {
                    printf("%c",187);
                }
            }
            printf("\n%c >CATALOGO         %c\n",186,186);
            for(cm=0; cm<19; cm++)
            {
                if(cm==0)
                {
                    printf("%c",200);
                }
                printf("%c",205);
                if(cm==18)
                {
                    printf("%c",188);
                }
            }
            printf("\n\n\n");
            color(colorNormal);///letra celeste/ fondo negro
            if(y==7)
                color(colorSobre);
                printf(" .Computacion\n");
                color(colorNormal);
            if(y==10)
                color(colorSobre);
                printf(" .Television\n");
                color(colorNormal);
            if(y==13)
                color(colorSobre);
                printf(" .Audio\n");
                color(colorNormal);
            if(y==16)
                color(colorSobre);
                printf(" .Gaming\n");
                color(colorNormal);
            if(y==19)
                color(colorSobre);
                printf(" .Telefonica\n");
                color(colorNormal);
            if(y==22)
                color(colorSobre);
                printf(" .Atras\n");
                color(colorNormal);
                opcion=getch(); ///retorna el numero del codigo ascii de la tecla ingresada
            if(opcion==80)  ///tecla de abajo
            {
                if(y==22)
                {
                    y=7;
                }
                else
                {
                    y=y+3;
                }
            }
            if(opcion==72){ ///tecla de arriba
                if(y==7)
                {
                    y=22;
                }
                else
                {
                    y=y-3;
                }
            }
            if(opcion==13){    ///tecla ENTER
                system("cls");
                if(y == 7){
                    subRubroComputacionMenu(arreglo,idCliente);
                }
                if(y == 10){
                    subRubroTelevisionMenu(arreglo,idCliente);
                }
                if(y == 13){
                    subRubroAudioMenu(arreglo,idCliente);
                }
                if(y == 16){
                    subRubroGamingMenu(arreglo,idCliente);
                }
                if(y == 19){
                    subRubroTelefoniaMenu(arreglo,idCliente);
                }
                if(y == 22){
                    menuCliente(arreglo,idCliente,validosRubro);
                }
            }

    }while(1);
}

void subRubroComputacionMenu(celdaRubros arreglo[], int idCliente,int validosRubro){
        int cm ,y=7;
        int colorNormal=15;  //blanco
        int colorSobre=11;    //cyan
        stUsuarios usuario=consultaClientes(idCliente);
        char opcion;
            do{
            system("cls");
            color(3);///color cyan/ fondo negro
            for(cm=0; cm<19; cm++)
            {
                if(cm==0)
                {
                    printf("%c",201);
                }
                printf("%c",205);
                if(cm==18)
                {
                    printf("%c",187);
                }
            }
            printf("\n%c RUBRO: COMPUTACION%c\n",186,186);
            for(cm=0; cm<19; cm++)
            {
                if(cm==0)
                {
                    printf("%c",200);
                }
                printf("%c",205);
                if(cm==18)
                {
                    printf("%c",188);
                }
            }
             printf("\n\n\n");
            color(colorNormal);///letra celeste/ fondo negro
            if(y==7)
                color(colorSobre);
                printf(" .Computadoras\n");
                color(colorNormal);
            if(y==10)
                color(colorSobre);
                printf(" .Software\n");
                color(colorNormal);
            if(y==13)
                color(colorSobre);
                printf(" .Accesorios\n");
                color(colorNormal);
            if(y==16)
                color(colorSobre);
                printf(" .Atras\n");
                color(colorNormal);
                opcion=getch();
            if(opcion==80)  ///tecla de abajo
            {
                if(y==16)
                {
                    y=7;
                }
                else
                {
                    y=y+3;
                }
            }
            if(opcion==72){ ///tecla de arriba
                if(y==7)
                {
                    y=16;
                }
                else
                {
                    y=y-3;
                }
            }
            if(opcion==13){    ///tecla ENTER
                system("cls");
                if(y == 7){
                    crearCuadroProductosClientes(0,3,arreglo,0,0,usuario);
                    system("pause");
                    subRubroComputacionMenu(arreglo, idCliente,validosRubro);

                }
                if(y == 10){
                    crearCuadroProductosClientes(0,3,arreglo,0,1,usuario);
                    system("pause");
                    subRubroComputacionMenu(arreglo, idCliente,validosRubro);
                }
                if(y == 13){
                    crearCuadroProductosClientes(0,3,arreglo,0,2,usuario);

                    system("pause");
                    subRubroComputacionMenu(arreglo, idCliente,validosRubro);
                }
                if(y == 16){
                    selecRubroMenu(arreglo,idCliente,validosRubro);
                }
            }

    }while(1);

}

void subRubroTelevisionMenu(celdaRubros arreglo[], int idCliente,int validosRubro){
        int cm ,y=7;
        int colorNormal=15;  //blanco
        int colorSobre=11;    //cyan
        stUsuarios usuario=consultaClientes(idCliente);
        char opcion;
            do{
            system("cls");
            color(3);///color cyan/ fondo negro
            for(cm=0; cm<19; cm++)
            {
                if(cm==0)
                {
                    printf("%c",201);
                }
                printf("%c",205);
                if(cm==18)
                {
                    printf("%c",187);
                }
            }
            printf("\n%c RUBRO: TELEVISION %c\n",186,186);
            for(cm=0; cm<19; cm++)
            {
                if(cm==0)
                {
                    printf("%c",200);
                }
                printf("%c",205);
                if(cm==18)
                {
                    printf("%c",188);
                }
            }
             printf("\n\n\n");
            color(colorNormal);///letra celeste/ fondo negro
            if(y==7)
                color(colorSobre);
                printf(" .Televisores\n");
                color(colorNormal);
            if(y==10)
                color(colorSobre);
                printf(" .Accesorios\n");
                color(colorNormal);
            if(y==13)
                color(colorSobre);
                printf(" .Dvd/Blu-ray\n");
                color(colorNormal);
            if(y==16)
                color(colorSobre);
                printf(" .Atras\n");
                color(colorNormal);
                opcion=getch();
            if(opcion==80)  ///tecla de abajo
            {
                if(y==16)
                {
                    y=7;
                }
                else
                {
                    y=y+3;
                }
            }
            if(opcion==72){ ///tecla de arriba
                if(y==7)
                {
                    y=16;
                }
                else
                {
                    y=y-3;
                }
            }
            if(opcion==13){    ///tecla ENTER
                system("cls");
                if(y == 7){
                    crearCuadroProductosClientes(0,3,arreglo,1,0,usuario);
                    system("pause");
                    subRubroTelevisionMenu(arreglo, idCliente,validosRubro);

                }
                if(y == 10){
                    crearCuadroProductosClientes(0,3,arreglo,1,1,usuario);
                    system("pause");
                    subRubroTelevisionMenu(arreglo, idCliente,validosRubro);
                }
                if(y == 13){
                    crearCuadroProductosClientes(0,3,arreglo,1,2,usuario);
                    system("pause");
                    subRubroTelevisionMenu(arreglo, idCliente,validosRubro);
                }
                if(y == 16){
                    selecRubroMenu(arreglo,idCliente,validosRubro);
                }
            }

    }while(1);
}
void subRubroAudioMenu(celdaRubros arreglo[], int idCliente,int validosRubro){
        int cm ,y=7;
        int colorNormal=15;  //blanco
        int colorSobre=11;    //cyan
        stUsuarios usuario=consultaClientes(idCliente);
        char opcion;
            do{
            system("cls");
            color(3);///color cyan/ fondo negro
            for(cm=0; cm<19; cm++)
            {
                if(cm==0)
                {
                    printf("%c",201);
                }
                printf("%c",205);
                if(cm==18)
                {
                    printf("%c",187);
                }
            }
            printf("\n%c RUBRO: AUDIO      %c\n",186,186);
            for(cm=0; cm<19; cm++)
            {
                if(cm==0)
                {
                    printf("%c",200);
                }
                printf("%c",205);
                if(cm==18)
                {
                    printf("%c",188);
                }
            }
             printf("\n\n\n");
            color(colorNormal);///letra celeste/ fondo negro
            if(y==7)
                color(colorSobre);
                printf(" .Componentes\n");
                color(colorNormal);
            if(y==10)
                color(colorSobre);
                printf(" .Auto-Stereo\n");
                color(colorNormal);
            if(y==13)
                color(colorSobre);
                printf(" .Auriculares\n");
                color(colorNormal);
            if(y==16)
                color(colorSobre);
                printf(" .Atras\n");
                color(colorNormal);
                opcion=getch();
            if(opcion==80)  ///tecla de abajo
            {
                if(y==16)
                {
                    y=7;
                }
                else
                {
                    y=y+3;
                }
            }
            if(opcion==72){ ///tecla de arriba
                if(y==7)
                {
                    y=16;
                }
                else
                {
                    y=y-3;
                }
            }
            if(opcion==13){    ///tecla ENTER
                system("cls");
                if(y == 7){
                    crearCuadroProductosClientes(0,3,arreglo,2,0,usuario);
                    system("pause");
                    subRubroAudioMenu(arreglo, idCliente,validosRubro);

                }
                if(y == 10){
                    crearCuadroProductosClientes(0,3,arreglo,2,1,usuario);
                    system("pause");
                    subRubroAudioMenu(arreglo, idCliente,validosRubro);
                }
                if(y == 13){
                    crearCuadroProductosClientes(0,3,arreglo,2,2,usuario);
                    system("pause");
                    subRubroAudioMenu(arreglo, idCliente,validosRubro);
                }
                if(y == 16){
                    selecRubroMenu(arreglo,idCliente,validosRubro);
                }
            }

    }while(1);
}
void subRubroGamingMenu(celdaRubros arreglo[], int idCliente,int validosRubro){
        int cm ,y=7;
        int colorNormal=15;  //blanco
        int colorSobre=11;    //cyan
        stUsuarios usuario=consultaClientes(idCliente);
        char opcion;
            do{
            system("cls");
            color(3);///color cyan/ fondo negro
            for(cm=0; cm<19; cm++)
            {
                if(cm==0)
                {
                    printf("%c",201);
                }
                printf("%c",205);
                if(cm==18)
                {
                    printf("%c",187);
                }
            }
            printf("\n%c RUBRO: GAMING     %c\n",186,186);
            for(cm=0; cm<19; cm++)
            {
                if(cm==0)
                {
                    printf("%c",200);
                }
                printf("%c",205);
                if(cm==18)
                {
                    printf("%c",188);
                }
            }
             printf("\n\n\n");
            color(colorNormal);///letra celeste/ fondo negro
            if(y==7)
                color(colorSobre);
                printf(" .Consolas\n");
                color(colorNormal);
            if(y==10)
                color(colorSobre);
                printf(" .Accesorios\n");
                color(colorNormal);
            if(y==13)
                color(colorSobre);
                printf(" .Juegos\n");
                color(colorNormal);
            if(y==16)
                color(colorSobre);
                printf(" .Atras\n");
                color(colorNormal);
                opcion=getch();
            if(opcion==80)  ///tecla de abajo
            {
                if(y==16)
                {
                    y=7;
                }
                else
                {
                    y=y+3;
                }
            }
            if(opcion==72){ ///tecla de arriba
                if(y==7)
                {
                    y=16;
                }
                else
                {
                    y=y-3;
                }
            }
            if(opcion==13){    ///tecla ENTER
                system("cls");
                if(y == 7){
                    crearCuadroProductosClientes(0,3,arreglo,3,0,usuario);
                    system("pause");
                    subRubroGamingMenu(arreglo, idCliente,validosRubro);

                }
                if(y == 10){
                    crearCuadroProductosClientes(0,3,arreglo,3,1,usuario);
                    system("pause");
                    subRubroGamingMenu(arreglo, idCliente,validosRubro);
                }
                if(y == 13){
                    crearCuadroProductosClientes(0,3,arreglo,3,2,usuario);
                    system("pause");
                    subRubroGamingMenu(arreglo, idCliente,validosRubro);
                }
                if(y == 16){
                    selecRubroMenu(arreglo,idCliente,validosRubro);
                }
            }

    }while(1);
}
void subRubroTelefoniaMenu(celdaRubros arreglo[], int idCliente,int validosRubro){
        int cm ,y=7;
        int colorNormal=15;  //blanco
        int colorSobre=11;    //cyan
        stUsuarios usuario=consultaClientes(idCliente);
        char opcion;
            do{
            system("cls");
            color(3);///color cyan/ fondo negro
            for(cm=0; cm<19; cm++)
            {
                if(cm==0)
                {
                    printf("%c",201);
                }
                printf("%c",205);
                if(cm==18)
                {
                    printf("%c",187);
                }
            }
            printf("\n%c RUBRO: TELOFIA    %c\n",186,186);
            for(cm=0; cm<19; cm++)
            {
                if(cm==0)
                {
                    printf("%c",200);
                }
                printf("%c",205);
                if(cm==18)
                {
                    printf("%c",188);
                }
            }
             printf("\n\n\n");
            color(colorNormal);///letra celeste/ fondo negro
            if(y==7)
                color(colorSobre);
                printf(" .Celulares\n");
                color(colorNormal);
            if(y==10)
                color(colorSobre);
                printf(" .Accesorios\n");
                color(colorNormal);
            if(y==13)
                color(colorSobre);
                printf(" .Telefonia fija\n");
                color(colorNormal);
            if(y==16)
                color(colorSobre);
                printf(" .Atras\n");
                color(colorNormal);
                opcion=getch();
            if(opcion==80)  ///tecla de abajo
            {
                if(y==16)
                {
                    y=7;
                }
                else
                {
                    y=y+3;
                }
            }
            if(opcion==72){ ///tecla de arriba
                if(y==7)
                {
                    y=16;
                }
                else
                {
                    y=y-3;
                }
            }
            if(opcion==13){    ///tecla ENTER
                system("cls");
                if(y == 7){
                    crearCuadroProductosClientes(0,3,arreglo,4,0,usuario);
                    system("pause");
                    subRubroTelefoniaMenu(arreglo, idCliente,validosRubro);

                }
                if(y == 10){
                    crearCuadroProductosClientes(0,3,arreglo,4,1,usuario);
                    system("pause");
                    subRubroTelefoniaMenu(arreglo, idCliente,validosRubro);
                }
                if(y == 13){
                    crearCuadroProductosClientes(0,3,arreglo,4,2,usuario);
                    system("pause");
                    subRubroTelefoniaMenu(arreglo, idCliente,validosRubro);
                }
                if(y == 16){
                    selecRubroMenu(arreglo,idCliente,validosRubro);
                }
            }

    }while(1);
}
