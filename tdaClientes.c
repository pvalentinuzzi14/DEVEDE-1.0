#include "tdaClientes.h"
#define arUsuarios "usuarios.dat"
#define arProductos "productos.dat"
#define arVentas "ventas.dat"

const char* monthsLarge[]= {"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};
const char* daysLarge[]= {"Domingo","Lunes","Martes","Miercoles","Jueves","Viernes","Sabado"};

void fGetNow(char date[])
{
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    strftime(date,128,"%Y-%m-%d %H:%M",tlocal);
}

int usuarioExistente(char nombreUsuario[])   ///Funcion que busca si un usuario esta o no esta en el archivo
{
    stUsuarios a;
    int flag=(-1);
    FILE *pArchUsuario = fopen(arUsuarios,"rb");
    if(pArchUsuario!=NULL)
    {
        while((fread(&a,sizeof(stUsuarios),1,pArchUsuario)>0)&&(flag==-1))
        {
            if(strcmp(nombreUsuario,a.usuario)==0)
            {
                flag=1;

            }
        }
        fclose(pArchUsuario);
    }
    return flag;
}
void generarUsuarios() ///Funcion que genera un usuario nuevo y valida los campos
{
    char opcion=0;
    int i=0;
    stUsuarios a;
    int usuarioID=-1;
    char nombreUsuario[30];
    char pass[20];
    char ciudad[20];
    int idCiudad=0;
    int ciudadExiste=-1;
    int condicion=0;
    int usuarioExiste=0; ///CHEQUEAR QUE NO EXISTA YA ESE USUARIO

    do
    {
        a.idUsuario=buscarUltimoIDUsuarios();
        a.idUsuario++;
        do
        {
            color(15);
            printf("\n Nombre de Usuario: ");
            color(3);
            fflush(stdin);
            scanf("%s",nombreUsuario);
            usuarioExiste=usuarioExistente(nombreUsuario); /// CONTROLA QUE EL USUARIO SE REGISTRE CON UN NOMBRE VALIDO
            if(usuarioExiste==(-1))
            {
                strcpy(a.usuario,nombreUsuario);
            }
            else
            {
                color(2);
                printf("\nEl usuario %s, ya existe. Ingrese nuevo usuario\n",nombreUsuario);
                system("pause");
            }
        }
        while(usuarioExiste==1);
        color(15);
        printf("\n Password (SOLO NUMEROS Y LETRAS): ");
        color(3);
        fflush(stdin);
        gets(a.password);
        color(15);
        printf("\n NOMBRE: ");
        fflush(stdin);
        color(3);
        gets(a.nombre);
        color(15);
        printf("\n APELLIDO: ");
        fflush(stdin);
        color(3);
        gets(a.apellido);
        color(15);
        printf("\n EDAD: ");
        fflush(stdin);
        color(3);
        scanf("%d",&a.edad);
        color(15);
        printf("\n TELEFONO: ");
        fflush(stdin);
        color(3);
        gets(a.telefono);
        color(15);
        printf("\n CIUDAD: ");
        fflush(stdin);
        color(3);
        gets(ciudad);
        ciudadExiste=buscarCiudad(ciudad);
        strcpy(a.ciudad,ciudad);
        if(ciudadExiste==-1)
        {
            idCiudad=buscarUltimoIdCiudad();
            idCiudad++;
            a.idCiudad=idCiudad;
        }
        else
        {
            a.idCiudad=ciudadExiste;
        }
        color(15);
        printf("\n DIRECCION: ");
        color(3);
        fflush(stdin);
        gets(a.direccion);
        color(15);
        printf("\n E-MAIL: ");
        color(3);
        fflush(stdin);
        gets(a.email);
        while(condicion!=1 && condicion!=2)
        {
            color(15);
            printf("\n CONDICION ( 1-MAYORISTA  //  (2) MINORISTA ) : ");
            color(3);
            fflush(stdin);
            scanf("%d",&condicion);
            if(condicion==1 || condicion==2)
            {
                a.condicion=condicion;
            }
            else
            {
                color(15);
                printf("\nCONDICION NO VALIDA");
                system("pause");
                //LimpiaPantallaParcial(0,3);
            }
        }
        condicion=0;
        if(a.idUsuario==0)
        {
            a.admin=1; /// UTILIZADO PARA QUE EL PRIMER USUARIO REGISTRADO SEA ADMINISTRADOR
        }
        else
        {
            a.admin=0;
        }
        a.eliminado=0;

        guardarUsuario(a); ///PARA GUARDAR EL USUARIO en el archivo de USUARIOS
        printf("\n\n\tESC PARA REGISTRARTE");
        opcion=getch();

    }
    while(opcion!=27);
}


void muestraUsuarioPerfil(stUsuarios a)  ///FUNCION Q MUESTRA UN USUARIO
{
    color(3);///color cyan/ fondo negro
    int cm;
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
    printf("\n%c >PERFIL           %c\n",186,186);
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
    Color(7);
    printf("\n ID............................: %d",a.idUsuario);
    printf("\n USUARIO.......................: %s",a.usuario);
    printf("\n PASSWORD......................: %s",a.password);
    printf("\n NOMBRE........................: %s",a.nombre);
    printf("\n APELLIDO......................: %s",a.apellido);
    printf("\n DIRECCION.....................: %s",a.direccion);
    printf("\n CIUDAD........................: %s",a.ciudad);
    printf("\n TELEFONO......................: %s",a.telefono);
    printf("\n EMAIL.........................: %s",a.email);
    ///printf("\n ELIMINADO.....................: %d",a.eliminado);
    (a.condicion==1)?printf("\n CONDICION.....................: MAYORISTA"):0;
    (a.condicion==2) ? printf("\n CONDICION.....................: MINORISTA"):0;
    (a.admin==1)? printf("\n ADMINISTRADOR"):0;
    (a.eliminado==1)? printf("\n USUARIO ELIMINADO"):0;
    printf("\n_____________________________________\n");
    system("pause");
}
void muestraUsuario(stUsuarios a)  ///FUNCION Q MUESTRA UN USUARIO
{
    Color(7);
    printf("\n ID............................: %d",a.idUsuario);
    printf("\n USUARIO.......................: %s",a.usuario);
    printf("\n PASSWORD......................: %s",a.password);
    printf("\n NOMBRE........................: %s",a.nombre);
    printf("\n APELLIDO......................: %s",a.apellido);
    printf("\n DIRECCION.....................: %s",a.direccion);
    printf("\n TELEFONO......................: %s",a.telefono);
    printf("\n EMAIL.........................: %s",a.email);
    ///printf("\n ELIMINADO.....................: %d",a.eliminado);
    (a.condicion==1)?printf("\n CONDICION.....................: MAYORISTA"):0;
    (a.condicion==2) ? printf("\n CONDICION.....................: MINORISTA"):0;
    (a.admin==1)? printf("\n ADMINISTRADOR"):0;
    (a.eliminado==1)? printf("\n USUARIO ELIMINADO"):0;
    printf("\n_____________________________________\n");
}

void mostrarListadoUsuarios()  ///FUNCION MODULARIZADA QUE LLAMA A LA FUNCION DE  UESTRA A USUARIO HASTA QUE NO HALLA DATOS EN EL ARCHIVO
{
    stUsuarios a;
    FILE * pArchUsuarios = fopen(arUsuarios,"rb");
    if(pArchUsuarios!=NULL)
    {
        while(fread(&a,sizeof(stUsuarios),1,pArchUsuarios)>0)
        {
            muestraUsuario(a);
        }
    }
}


void guardarUsuario(stUsuarios a)///FUNCION PARA GUARDAR USUARIOS
{
    FILE*pArchiUsuarios=fopen(arUsuarios,"ab");
    if(pArchiUsuarios)
    {
        fwrite(&a,sizeof(stUsuarios),1,pArchiUsuarios);
        fclose(pArchiUsuarios);
    }
}


int buscarUltimoIDUsuarios() ///FUNCION QUE BUSCA Y RETORNA EL ULTIMO ID DEL USUARIO
{
    stUsuarios a;
    int id=-1;
    FILE *pArchUsuario = fopen(arUsuarios,"rb");
    if(pArchUsuario!=NULL)
    {
        fseek(pArchUsuario,sizeof(stUsuarios)*(-1),SEEK_END);
        while(fread(&a,sizeof(stUsuarios),1,pArchUsuario)>0)
        {
            id=a.idUsuario;
        }
        fclose(pArchUsuario);
    }

    return id;
}

void verPerfil(stUsuarios usuario)///FUNCION PARA VER EL PERFIL
{
    //LimpiaPantallaParcial(0,3);
    muestraUsuario(usuario);
}
stUsuarios consultaClientes(int idCliente) ///FUNCIONN QUE BUSCA UN CLIENTE POR ID Y DEVUELVE LA ESTRUCTURA DEL MISMO ENCONTRADO
{
    stUsuarios a;
    stUsuarios buscado;
    FILE*pArchUsuarios = fopen(arUsuarios,"rb");
    if(pArchUsuarios)
    {
        while(fread(&a,sizeof(stUsuarios),1,pArchUsuarios)>0)
        {
            if(a.idUsuario == idCliente)
            {
                buscado=a;
            }
        }
        fclose(pArchUsuarios);
    }
    return buscado;
}

/*funciones para el manejo de admin*/

void altaBajaUsuario(int idUsuario) ///fUNCION PARA EL MANEJO DE ADMIN DONDE SE DA DE ALTA O BAJA A UN USUARIO
{
    stUsuarios a;
    char eleccion;
    FILE *pArchi=fopen(arUsuarios,"r+b");
    if(pArchi!=NULL)
    {
        fseek(pArchi,sizeof(stUsuarios)*idUsuario,SEEK_SET);
        fread(&a,sizeof(stUsuarios),1,pArchi);
        muestraUsuario(a);
        printf("\n ESTA SEGURO QUE DESEA CAMBIAR EL ESTADO DE ESTE USUARIO ? S/N");
        fflush(stdin);
        eleccion=tolower(getch());
        if(eleccion=='s')
        {
            if(a.eliminado==0)
            {
                a.eliminado=1;
            }
            else
            {
                a.eliminado=0;
            }
        }
        fseek(pArchi,sizeof(stUsuarios)*idUsuario,SEEK_SET);
        fwrite(&a,sizeof(stUsuarios),1,pArchi);
        fclose(pArchi);
    }
}


void altaAdmin(int idUsuario) /// Funcion para dar de alta a un admin
{
    stUsuarios a;
    char eleccion;
    FILE *pArchUsuarios=fopen(arUsuarios,"r+b");
    if(pArchUsuarios!=NULL)
    {
        fseek(pArchUsuarios,sizeof(stUsuarios)*idUsuario,SEEK_SET);
        fread(&a,sizeof(stUsuarios),1,pArchUsuarios);
        muestraUsuario(a);
        printf("\n DESEA MODIFICAR EL ASIGNAMIENTO DEL USUARIO ? S/N");
        eleccion=getch();
        if(eleccion==115)
        {
            if(a.admin==0)
            {
                a.admin=1;
            }
            else
            {
                a.admin=0;
            }
        }
        fseek(pArchUsuarios,sizeof(stUsuarios)*idUsuario,SEEK_SET);
        fwrite(&a,sizeof(stUsuarios),1,pArchUsuarios);
        fclose(pArchUsuarios);
    }
}

int buscarUltimoIdCiudad() ///Funcion que te busca el ultimo id de la ciudad y te lo retorna
{
    stUsuarios p;
    int rta=-1;
    FILE*pArch=fopen(arUsuarios,"rb");
    if(pArch)
    {
        while(fread(&p,sizeof(stUsuarios),1,pArch)>0)
        {
            if(p.idCiudad>rta)
            {
                rta=p.idCiudad;
            }
        }
        fclose(pArch);
    }
    return rta;
}

int buscarCiudad(char ciudad[]) ///Funcion que te vusca una ciudad con su nombre
{
    stUsuarios p;
    int rta=-1;
    FILE*pArch=fopen(arUsuarios,"rb");
    if(pArch)
    {
        while(fread(&p,sizeof(stUsuarios),1,pArch)>0 && rta==-1)
        {
            if(strcmpi(p.ciudad,ciudad)==0)
            {
                rta=p.idCiudad;
            }
        }
        fclose(pArch);
    }
    return rta;
}

void modifDatos(int idUsuario,int opcionModificacion) ///Funcion para modificiar datos
{
    stUsuarios a;
    char nombre[20];
    char apellido[20];
    char direccion[30];
    char telefono[11];
    char email[30];
    FILE *pArchUsuarios=fopen(arUsuarios,"r+b");
    if(pArchUsuarios)
    {
        fseek(pArchUsuarios,sizeof(stUsuarios)*idUsuario,SEEK_SET);
        fread(&a,sizeof(stUsuarios),1,pArchUsuarios);
        switch(opcionModificacion)
        {
        case 1:
            printf("NOMBRE: ");
            fflush(stdin);
            gets(nombre);
            strcpy(a.nombre,nombre);
            break;
        case 2:
            printf("APELLIDO: ");
            fflush(stdin);
            gets(apellido);
            strcpy(a.apellido,apellido);
            break;
        case 3:
            printf("TELEFONO: ");
            fflush(stdin);
            gets(telefono);
            strcpy(a.telefono,telefono);
            break;
        case 4:
            printf("EMAIL: ");
            fflush(stdin);
            gets(email);
            strcpy(a.email,email);
            break;
        }

        fseek(pArchUsuarios,sizeof(stUsuarios)*idUsuario,SEEK_SET);
        fwrite(&a,sizeof(stUsuarios),1,pArchUsuarios);
        fclose(pArchUsuarios);
    }
}
///funcion para el inicio de secion de usuarios
int validacionUsuario(char nombreUsuario[],char password[])
{
    int flag = (-1);
    stUsuarios a;
    FILE *pArch = fopen(arUsuarios, "rb");
    if(pArch != NULL)///si el puntero es nulo, el archivo no se abriò
    {
        while((fread(&a, sizeof(stUsuarios), 1, pArch)>0)&&(flag == (-1)))
        {
            if((strcmp(a.usuario,nombreUsuario)==0)&&(strcmp(a.password,password)==0))
            {
                flag = a.idUsuario;
            }
        }
        fclose(pArch);
    }
    return flag;
}
int validacionUsuarioParaConsultar(char nombreUsuario[])  ///funcion para la consulta de usuario
{
    int flag = (-1);
    stUsuarios a;
    FILE *pArch = fopen(arUsuarios, "rb");
    if(pArch != NULL)///si el puntero es nulo, el archivo no se abriò
    {
        while((fread(&a, sizeof(stUsuarios), 1, pArch)>0)&&(flag == (-1)))
        {
            if((strcmp(a.usuario,nombreUsuario)==0))
            {
                flag = a.idUsuario;
            }
        }
        fclose(pArch);
    }
    return flag;
}

int validacionAdmin(char nombreUsuario[],char password[])///funcion similiar a la anterior pero para el uso de admin
{
    int flag = (-1);
    stUsuarios a;
    FILE *pArchUsuario = fopen(arUsuarios, "rb");
    if(pArchUsuario != NULL)///si el puntero es nulo, el archivo no se abriò
    {
        while((fread(&a, sizeof(stUsuarios), 1, pArchUsuario)>0)&&(flag == (-1)))
        {
            if((strcmp(a.usuario,nombreUsuario)==0)&&(strcmp(a.password,password)==0)&&(a.admin==1))
            {
                flag = a.idUsuario;
            }
        }
        fclose(pArchUsuario);
    }
    return flag;
}

///FUNCIONES PARA GENERAR ARREGLO DE ARBOL CON CIUDAD Y USUARIOS;
nodoArbol * crearNodoArbol(stUsuarios usuario)     ///crear nodo arbol
{
    nodoArbol * nuevo = (nodoArbol*)malloc(sizeof(nodoArbol));
    nuevo->dato = usuario;
    nuevo->izquierda = NULL;
    nuevo->derecha = NULL;
    return nuevo;
}

nodoArbol * insertar(nodoArbol *arbol, nodoArbol * nuevo)  ///funcion para insertar el nodoo en un  arbol
{
    if(!arbol)
    {
        arbol = nuevo;
    }
    else
    {
        if(nuevo->dato.edad >= 25)
        {
            arbol->derecha = insertar(arbol->derecha,nuevo);
        }
        else
        {
            arbol->izquierda = insertar(arbol->izquierda,nuevo);
        }
    }
    return arbol;
}

int cargarArregloCiudad(celdaCiudad **celda)    ///si el arreglo lo queres ver desde fuera tiene q ser puntero doble
{
    FILE *pArchUsuario = fopen(arUsuarios,"rb");
    stUsuarios registro,usuario;
    int i,comprobarDato, j=-1;
    if(pArchUsuario)
    {
        (*celda)=malloc(50*sizeof(celda));
        int dimension = 50;

        while(fread(&registro,sizeof(stUsuarios),1,pArchUsuario)>0)
        {
            if(registro.eliminado == 0)
            {
                if(registro.idCiudad > dimension)
                {
                    celdaCiudad(*celda)= realloc(celda,20);
                    dimension = dimension+20;
                }
                comprobarDato = comprobar(celda,registro.idCiudad,j);       //funcion para comprobar si ya existe la celda(1 exsiste - 0 no existe)
                if(comprobarDato == 0)
                {
                    i = registro.idCiudad;
                    (*celda)[i].idCiudad = registro.idCiudad;
                    strcpy((*celda)[i].ciudad,registro.ciudad);
                    (*celda)[i].arbolito = NULL;
                }
                else
                {
                    i = registro.idCiudad;
                    j--;
                }
                ///carga del arbol dentro de la celda;
                usuario.idUsuario = registro.idUsuario;
                strcpy(usuario.usuario,registro.usuario);
                strcpy(usuario.password,registro.password);
                strcpy(usuario.nombre,registro.nombre);
                strcpy(usuario.apellido,registro.apellido);
                strcpy(usuario.direccion,registro.direccion);
                strcpy(usuario.telefono,registro.telefono);
                usuario.condicion = registro.condicion;
                strcpy(usuario.email,registro.email);
                usuario.admin = registro.admin;
                usuario.edad = registro.edad;
                usuario.eliminado = registro.eliminado;

                nodoArbol * arbolNuevo = crearNodoArbol(usuario);
                (*celda)[i].arbolito = insertar((*celda)[i].arbolito,arbolNuevo);

                j++;
            }

        }
        fclose(pArchUsuario);
    }
    return j;
}
///FUNCION QUE COMPRUEBA EL ID DE LA CIUDAD PARA INSERTAR CORRECTAMENTE.

void mostrarCeldas(celdaCiudad *celda, int validos)
{
    for(int i =0; i<validos; i++)
    {
        printf("\nID CIUDAD:...%d",celda[i].idCiudad);
        printf(" CIUDAD:...%s",celda[i].ciudad);
        preOrder(celda[i].arbolito);
        printf("\n");
    }

}
int comprobar(celdaCiudad **celda, int dato, int validos)
{
    int flag = 0;
    int i = 0;
    while(flag == 0 && i<validos)
    {
        if((*celda)[i].idCiudad == dato)
        {
            flag = 1;
        }
        i++;
    }
    return flag;
}

void preOrder(nodoArbol *arbol)
{
    if(arbol)
    {
        muestraUsuario(arbol->dato);
        preOrder(arbol->izquierda);
        preOrder(arbol->derecha);
    }
}

/*Funciones para los productos la logica aplicada es muy similar a la de clientes*/
int selecRubro()
{
    int r;
    r=-1;
    printf("INGRESE NUMERO DE RUBRO: ");
    printf("\n0. COMPUTACION");
    printf("\n1. TELEVISION");
    printf("\n2. AUDIO");
    printf("\n3. GAMING");
    printf("\n4. TELEFONIA");
    scanf("%d",&r);

    return r;
}

int selecSubRubro(int r)
{
    int sr;
    sr=(-1);
    switch(r)
    {
    case 0:

        system("cls");
        printf("RUBRO: COMPUTACION\n");
        printf("0. COMPUTADORAS\n");
        printf("1. SOFTWARE\n");
        printf("2. ACCESORIOS\n");
        do
        {
            printf("INGRESE UNA OPCION VALIDA: ");
            scanf("%d",&sr);
        }
        while((sr>=3) && (sr<0));
        break;
    case 1:
        system("cls");
        printf("RUBRO: TELEVISION\n");
        printf("0. TELEVISORES\n");
        printf("1. ACCESORIOS\n");
        printf("2. DVD/BLU-RAY\n");
        do
        {
            printf("INGRESE UNA OPCION VALIDA: ");
            scanf("%d",&sr);
        }
        while((sr>=3) && (sr<0));
        break;
    case 2:
        system("cls");
        printf("RUBRO: AUDIO\n");
        printf("0. COMPONENTES\n");
        printf("1. AUTO-STEREO\n");
        printf("2. AURICULARES\n");
        do
        {
            printf("INGRESE UNA OPCION VALIDA: ");
            scanf("%d",&sr);
        }
        while((sr>=3) && (sr<0));
        break;
    case 3:
        system("cls");
        printf("RUBRO: GAMING\n");
        printf("0. CONSOLAS\n");
        printf("1. ACCESORIOS\n");
        printf("2. JUEGOS\n");
        do
        {
            printf("INGRESE UNA OPCION VALIDA: ");
            scanf("%d",&sr);
        }
        while((sr>=3) && (sr<0));
        break;
    case 4:
        system("cls");
        printf("RUBRO: TELEFONIA\n");
        printf("0. CELULARES\n");
        printf("1. ACCESORIOS\n");
        printf("2. TELEFONIA FIJA\n");
        do
        {
            printf("INGRESE UNA OPCION VALIDA: ");
            scanf("%d",&sr);
        }
        while((sr>=3) && (sr<0));
        break;

    }

    return sr;
}


void cargaProductos() ///funcion para cargar un producto
{
    char opcion=0;
    int i=0;
    stProductos a;
    char nombreProduc[30];
    a.idProducto=0;
    int codigoparcial=-1;
    int producExiste=0; ///CHEQUEAR QUE NO EXISTA YA ESE USUARIO

    do
    {
        printf("\n\t  << Carga de Articulos >> \n");

        a.rubro=selecRubro();///ELIJO UN RUBRO
        a.subrubro=selecSubRubro(a.rubro);///ELIJO UN RUBRO
        a.idProducto=buscarUltimoIDArticulo(); /// GENERA ID DE SISTEMA PARA EL NUEVO PRODUCTO
        a.idProducto++; /// GENERA ID DE SISTEMA PARA EL NUEVO PRODUCTO
        printf("\n Descripcion: ");
        fflush(stdin);
        gets(nombreProduc); ///CARGA DE DESCRIPCION
        strcpy(a.descripcion,nombreProduc);
        printf("\n PRECIO LISTA: ");
        fflush(stdin);
        scanf("%d",&a.precio.precioLista); ///INGRESO PRECIO
        a.precio.minorista=a.precio.precioLista*(1.21);
        printf("\n STOCK: ");
        fflush(stdin);
        scanf("%d",&a.stock);
        system("pause");
        codigoparcial=generarCodigoProducto(a.rubro,a.subrubro);
        printf("%d",codigoparcial);
        a.codigoProducto=buscarUltimoIDRubro(codigoparcial);///BUSCA EN ESE RUBRO/SUBRUBRO EL ULTIMO Y LE SUMA UNO
        a.eliminado=0;

        guardarProducto(a); ///PARA GUARDAR EL USUARIO en el archivo de PRODUCTOS
        printf("\n\n\tESC PARA SALIR");
        opcion=getch();

    }
    while(opcion!=27);
}


void guardarProducto(stProductos a)
{
    FILE*pArchiProductos=fopen(arProductos,"ab");
    if(pArchiProductos)
    {
        fwrite(&a,sizeof(stProductos),1,pArchiProductos);
        fclose(pArchiProductos);
    }
}

int generarCodigoProducto(int a,int b)
{
    int rubro=1000;
    int primerosDos=0;
    switch(a)
    {

    case 0:
        primerosDos=primerosDos+(0*rubro);
        primerosDos=calculaSubRubro(b,primerosDos);
        break;
    case 1:
        primerosDos=primerosDos+(1*rubro);
        primerosDos=calculaSubRubro(b,primerosDos);
        break;
    case 2:
        primerosDos=primerosDos+(2*rubro);
        primerosDos=calculaSubRubro(b,primerosDos);
        break;
    case 3:
        primerosDos=primerosDos+(3*rubro);
        primerosDos=calculaSubRubro(b,primerosDos);
        break;
    case 4:
        primerosDos=primerosDos+(4*rubro);
        primerosDos=calculaSubRubro(b,primerosDos);
        break;
    }
    return primerosDos;
}

int calculaSubRubro(int a,int primerosDos)
{
    int parcial=0;
    int subrubro=100;
    switch(a)
    {
    case 0:
        parcial=primerosDos+(0*subrubro);
        break;
    case 1:
        parcial=primerosDos+(1*subrubro);
        break;
    case 2:
        parcial=primerosDos+(2*subrubro);
        break;
    case 3:
        parcial=primerosDos+(3*subrubro);
        break;
    }
    return parcial;
}


void muestraProducto(stProductos a)
{
    printf("\n ID PRODUCTO.................: %d",a.idProducto);
    printf("\n CODIGO PRODUCTO...............: %d",a.codigoProducto);
    printf("\n DESCRIPCION...................: %s",a.descripcion);
    printf("\n STOCK.........................: %d",a.stock);
    printf("\n PRECIO MAYORISTA..............: $ %d",a.precio.precioLista);
    printf("\n PRECIO MINORISTA..............: $ %d",a.precio.minorista);
    printf("\n RUBRO.........................: (%d) ",a.rubro);
    getRubro(a.rubro);
    printf("\n SUBRUBRO......................: (%d) ",a.subrubro);
    getSubRubro(a.subrubro,a.rubro);
    (a.eliminado==1)?printf("\n PRODUCTO ELIMINADO"):0;
    printf("\n_____________________________________\n");

}

void recorrerArchivoProductos()
{
    stProductos a;
    FILE*pArchiProduc=fopen(arProductos,"rb");
    if(pArchiProduc)
    {
        while(fread(&a,sizeof(stProductos),1,pArchiProduc)>0)
        {
            muestraProducto(a);
        }
        fclose(pArchiProduc);
    }
}


int buscarUltimoIDArticulo()
{
    stProductos a;
    int id=-1;
    FILE *pArchiProductos = fopen(arProductos,"rb");
    if(pArchiProductos!=NULL)
    {
        fseek(pArchiProductos,sizeof(stProductos)*(-1),SEEK_END);
        while(fread(&a,sizeof(stProductos),1,pArchiProductos)>0)
        {
            id=a.idProducto;
        }
        fclose(pArchiProductos);
    }

    return id;
}


int buscarUltimoIDRubro(int codigoProducto)
{
    stProductos a;
    int parametro=codigoProducto+100;
    int id=-1;
    FILE *pArchiProductos = fopen(arProductos,"rb");
    if(pArchiProductos!=NULL)
    {
        while(fread(&a,sizeof(stProductos),1,pArchiProductos)>0)
        {

            if((a.codigoProducto>=codigoProducto)&&(a.codigoProducto<parametro))
            {

                if(a.codigoProducto>id)
                {

                    id=a.codigoProducto;
                }
            }
        }
        fclose(pArchiProductos);
    }
    if(id==(-1))
    {
        id=codigoProducto-1;
    }

    return id+1;
}


void getRubro(int idRubro)
{
    char nombre[12];
    switch(idRubro)
    {
    case 0:
        printf("COMPUTACION");
        break;
    case 1:
        printf("TELEVISION");
        break;
    case 2:
        printf("AUDIO");
        break;
    case 3:
        printf("GAMING");
        break;
    case 4:
        printf("TELEFONIA");
        break;
    }
}

void getSubRubro(int subrubro,int idRubro)
{
    char nombre[12];
    switch(idRubro)
    {
    case 0:

        switch(subrubro)
        {
        case 0:
            printf("COMPUTADORAS");
            break;
        case 1:
            printf("SOFTWARE");
            break;
        case 2:
            printf("ACCESORIOS");
            break;
        }
        break;
    case 1:
        switch(subrubro)
        {
        case 0:
            printf("TELEVISORES");
            break;
        case 1:
            printf("ACCESORIOS");
            break;
        case 2:
            printf("DVD / BLU-RAY");
            break;
        }
        break;
    case 2:
        switch(subrubro)
        {
        case 0:
            printf("COMPONENTES");
            break;
        case 1:
            printf("AUTO-STEREO");
            break;
        case 2:
            printf("AURICULARES");
            break;
        }
        break;
    case 3:

        switch(subrubro)
        {
        case 0:
            printf("CONSOLAS");
            break;
        case 1:
            printf("ACCESORIOS");
            break;
        case 2:
            printf("JUEGOS");
            break;
        }
        break;
    case 4:
        switch(subrubro)
        {
        case 0:
            printf("CELULARES");
            break;
        case 1:
            printf("ACCESORIOS");
            break;
        case 2:
            printf("TELEFONIA FIJA");
            break;
        }
        break;
    }
}

void mostrarListaProductos(nodoSubRubros*subLista)
{
    nodoProducto*seg=subLista->lista;
    //stProductos producto;
    while(seg!=NULL)
    {
        muestraProducto(seg->dato);
        seg=seg->siguiente;

    }
}

nodoProducto*inicListaProductos()
{
    return NULL;
}

nodoSubRubros*inicListaSubRubros()
{
    return NULL;
}


nodoProducto* crearNodoProducto(stProductos a)
{
    nodoProducto*nuevo=(nodoProducto*)malloc(sizeof(nodoProducto));
    nuevo->dato=a;
    nuevo->siguiente=NULL;

    return nuevo;
}

nodoSubRubros * agregarPpioSubListas (nodoSubRubros*lista,nodoSubRubros*nuevo)
{
    nodoSubRubros * seg=lista;
    nuevo->siguiente=seg;
    lista=nuevo;
    return lista;
}

nodoProducto * buscarUltimoProducto (nodoProducto*lista)
{
    nodoProducto * seg=lista;
    while(seg->siguiente !=NULL)
    {
        seg=seg->siguiente;
    }

    return seg;
}

nodoSubRubros*agregarOrdenadoSublistas(nodoSubRubros*nuevo,nodoSubRubros*subListas)
{
    nodoSubRubros*buscadora=NULL;
    nodoSubRubros*seg=subListas;
    if(seg==NULL)
    {
        seg=nuevo;
    }
    else
    {
        nodoSubRubros * ante = subListas;
        nodoSubRubros * seg = subListas->siguiente;
        while( (seg != NULL)&&((nuevo->subRubro)>(seg->subRubro)))
        {
            ante = seg;
            seg = seg->siguiente;
        }
        // inserto el nuevo nodo en el lugar indicado.
        nuevo->siguiente = seg;
        ante->siguiente = nuevo;
    }
    return seg;
}

nodoProducto*agregarFinalListaProductos(nodoProducto*nuevo,nodoProducto*lista)
{
    nodoProducto*buscadora=NULL;
    nodoProducto*seg=lista;
    if(seg==NULL)
    {
        seg=nuevo;
    }
    else
    {
        buscadora=buscarUltimoProducto(seg);
        buscadora->siguiente=nuevo;
    }
    return seg;
}


nodoSubRubros*crearNodoSubrubros(stProductos a)
{
    nodoSubRubros*nuevo=(nodoSubRubros*)malloc(sizeof(nodoSubRubros));
    nuevo->siguiente=inicListaSubRubros();
    nuevo->subRubro=a.subrubro;
    nuevo->lista=inicListaProductos();

    return nuevo;
}

nodoSubRubros*buscarSubrubros(nodoProducto*nuevoProducto,nodoSubRubros*lista)
{
    nodoSubRubros*seg=inicListaSubRubros();
    seg=lista;
    while((seg!=NULL)&&(seg->subRubro!=nuevoProducto->dato.subrubro))
    {
        seg=seg->siguiente;
    }

    return seg;
}

void iniciarCeldas(celdaRubros*arregloRubros,int dimension)
{
    for(int i=0; i<dimension; i++)
    {
        arregloRubros[i].rubro=i; /// DETERMINO EL ID DE LA CELDA
        arregloRubros[i].subListas = inicListaSubRubros(); ///INICIALIZANDO LISTAS DE SUBRUBROS
    }
}

int crearArregloRubros(celdaRubros**arregloRubros)
{

    FILE*pArchProductos=fopen(arProductos,"rb");
    int i=0;
    stProductos producto;
    char nombres[10];
    int dimension=5;
    nodoSubRubros*buscaSublistas=inicListaSubRubros();
    nodoSubRubros*retorno=inicListaSubRubros();
    nodoProducto*nuevoProducto=inicListaProductos();

    (*arregloRubros)=malloc(sizeof(celdaRubros)*dimension);
    iniciarCeldas((*arregloRubros),dimension);
    if(pArchProductos)
    {
        while(fread(&producto,sizeof(stProductos),1,pArchProductos)>0)
        {
            if(producto.eliminado==0)
            {
                nuevoProducto=crearNodoProducto(producto);
                i=producto.rubro;
                if((*arregloRubros)[i].subListas==NULL)
                {
                    (*arregloRubros)[i].subListas=crearNodoSubrubros(producto);///HAY QUE HACERLO SI NO EXISTE
                    (*arregloRubros)[i].subListas->lista=agregarFinalListaProductos(nuevoProducto,(*arregloRubros)[i].subListas->lista);
                }
                else
                {
                    buscaSublistas=buscarSubrubros(nuevoProducto,(*arregloRubros)[i].subListas);
                    if(buscaSublistas==NULL)
                    {
                        retorno=crearNodoSubrubros(producto);
                        (*arregloRubros)[i].subListas=agregarOrdenadoSublistas(retorno,(*arregloRubros)[i].subListas);
                        retorno->lista=agregarFinalListaProductos(nuevoProducto,retorno->lista);
                    }
                    else
                    {
                        buscaSublistas->lista=agregarFinalListaProductos(nuevoProducto,buscaSublistas->lista);
                    }
                }
            }
        }
        fclose(pArchProductos);
    }
    return dimension;
}


void sumaTotalProductos()
{
    stProductos a;
    int totalArticulos=0;
    int montoTotalArticulos=0;
    int gananciaEstimada=0;
    FILE*pArchiProduc=fopen(arProductos,"rb");
    if(pArchiProduc)
    {
        while(fread(&a,sizeof(stProductos),1,pArchiProduc)>0)
        {
            montoTotalArticulos=montoTotalArticulos+(a.precio.precioLista*a.stock);
            totalArticulos++;
        }
        fclose(pArchiProduc);
    }
    gananciaEstimada=(montoTotalArticulos*0.4);
    printf("\n-------------TOTALES---------------\n");
    printf("\nCANTIDAD DE ARTICULOS = %d",totalArticulos);
    printf("\nMONTO TOTAL DE ARTICULOS EN DEPOSITO = $%d",montoTotalArticulos);
    printf("\nGANANCIA ESTIMADA= $%d",gananciaEstimada);
    printf("\n-----------------------------------\n");
}

stProductos consultaProductos(celdaRubros arreglo[],int productoBuscado)
{
    stProductos buscado;
    int rubro=productoBuscado/1000;
    int subrubro=(productoBuscado/100)-(rubro*10);
    nodoSubRubros*listaSubRubro=buscarSubrubrosCuadro(arreglo[rubro].subListas,subrubro);
    nodoProducto*listaProductos=listaSubRubro->lista;
    nodoProducto*auxiliar=listaProductos;
    while((auxiliar!=NULL)&&(auxiliar->dato.codigoProducto!=productoBuscado))
    {
        auxiliar=auxiliar->siguiente;
    }
    if(auxiliar!=NULL)
    {
        buscado=auxiliar->dato;
    }

    return buscado;
}

stProductos consultaProductosArchivo(int productoBuscado)
{
    stProductos a;
    stProductos buscado;
    FILE*pArch = fopen(arProductos,"rb");
    if(pArch)
    {
        while(fread(&a,sizeof(stProductos),1,pArch)>0)
        {
            if(a.codigoProducto == productoBuscado)
            {
                buscado=a;
            }
        }
        fclose(pArch);
    }
    return buscado;
}

int ultimoIDRubro()
{
    stProductos a;
    int total=0;
    int ultimoIDRubro=-1;
    int copiaIDrubro=-1;
    FILE*pArch = fopen(arProductos,"rb");
    if(pArch)
    {
        while(fread(&a,sizeof(stProductos),1,pArch)>0)
        {
            copiaIDrubro=a.rubro;
            if(copiaIDrubro>ultimoIDRubro)
            {
                ultimoIDRubro=copiaIDrubro;
            }
        }
        fclose(pArch);
    }
    return ultimoIDRubro;
}

int buscarXcodigoProducto(int codigoProducto)
{
    int idProducto=(-1);
    stProductos a;
    FILE*pArch = fopen(arProductos,"rb");
    if(pArch)
    {
        while((fread(&a,sizeof(stProductos),1,pArch)>0)&&(idProducto==(-1)))
        {
            if(codigoProducto==a.codigoProducto)
            {
                idProducto=a.idProducto;
            }
        }
        fclose(pArch);
    }
    return idProducto;
}

void modifDatosArticulos(int codigoProducto,int opcionModificacion)
{
    stProductos a;
    int idProducto=buscarXcodigoProducto(codigoProducto);
    char descripicion[40];
    int precio;
    int stock;
    FILE *pArch=fopen(arProductos,"r+b");
    if(pArch)
    {
        fseek(pArch,sizeof(stProductos)*idProducto,SEEK_SET);
        fread(&a,sizeof(stProductos),1,pArch);
        switch(opcionModificacion)
        {
        case 1:
            printf("Descripcion: ");
            fflush(stdin);
            gets(descripicion);
            strcpy(a.descripcion,descripicion);
            break;
        case 2:
            printf("Precio: ");
            fflush(stdin);
            scanf("%d",&precio);
            a.precio.precioLista=precio;
            a.precio.minorista=precio*(1.21);
            break;
        case 3:
            printf("Stock: ");
            fflush(stdin);
            scanf("%d",&stock);
            a.stock=stock;
            break;
        }

        fseek(pArch,sizeof(stProductos)*idProducto,SEEK_SET);
        fwrite(&a,sizeof(stProductos),1,pArch);
        fclose(pArch);
    }
}

void modifStock(int codigoProducto,int cantidad)
{
    stProductos a;
    int idProducto=buscarXcodigoProducto(codigoProducto);
    int stock;
    FILE *pArch=fopen(arProductos,"r+b");
    if(pArch)
    {
        fseek(pArch,sizeof(stProductos)*idProducto,SEEK_SET);
        fread(&a,sizeof(stProductos),1,pArch);
        a.stock=a.stock-cantidad;
        fseek(pArch,sizeof(stProductos)*idProducto,SEEK_SET);
        fwrite(&a,sizeof(stProductos),1,pArch);
        fclose(pArch);
    }
}


void altaBajaProducto(int idProducto)
{

    stProductos a;
    char eleccion;
    FILE *pArchi=fopen(arProductos,"r+b");
    if(pArchi!=NULL)
    {
        fseek(pArchi,sizeof(stProductos)*idProducto,SEEK_SET);
        fread(&a,sizeof(stProductos),1,pArchi);
        muestraProducto(a);
        printf("\n ESTA SEGURO QUE DESEA CAMBIAR EL ESTADO DE ESTE PRODUCTO ? S/N");
        fflush(stdin);
        eleccion=tolower(getch());
        if(eleccion=='s')
        {
            if(a.eliminado==0)
            {
                a.eliminado=1;
            }
            else
            {
                a.eliminado=0;
            }
        }
        fseek(pArchi,sizeof(stProductos)*idProducto,SEEK_SET);
        fwrite(&a,sizeof(stProductos),1,pArchi);
        fclose(pArchi);
    }
}
void pausaYlimpia()
{
    printf("\n\n");
    system("pause");
}

void replicante(int cantidad,char dato)
{
    int i=0;
    for(i=0; i<cantidad; i++)
    {
        printf("%c",dato);
    }
}

void LimpiaPantallaParcial(int x,int y)
{
    char titulo[]=" DVD GESTION ";
    system("cls");
    imprimirCabecera(titulo); /// PARA QUE LA CABECERA SE MANTENGA CONSTANTEMENTE
    gotoxy(x,y);
}
nodoSubRubros*buscarSubrubrosCuadro(nodoSubRubros*lista,int subrubro)
{
    nodoSubRubros*seg=inicListaSubRubros();
    seg=lista;
    while((seg!=NULL)&&(seg->subRubro!=subrubro))
    {
        seg=seg->siguiente;
    }

    return seg;
}


void crearCuadroProductos(int x,int y,celdaRubros arreglo[],int rubro,int subrubro)
{

    LimpiaPantallaParcial(0,3);

    nodoSubRubros*subLista=buscarSubrubrosCuadro(arreglo[rubro].subListas,subrubro);
    if(subLista!=NULL)
    {
        nodoProducto*listaProductos=subLista->lista;
        int u=0;
        int i=0;
        gotoxy(x,y);
        printf("%c",201);
        replicante(119,205);
        printf("%c\n",187);
        gotoxy(x,(y+1));
        printf("%c",186);
        printf("ID%3cCODIGO\%3cDESCRIPCION%43cSTOCK%4cPRECIO LISTA%4cMINORISTA%5cESTADO",' ',' ',' ',' ',' ',' ');
        printf("%7c\n",186);
        gotoxy(x,(y+2));

        while(listaProductos!=NULL)
        {

            gotoxy(x,y+u+2);
            printf("%c",186);

            gotoxy(x+1,y+u+2);
            printf("%d",listaProductos->dato.idProducto);
            gotoxy(x+6,y+u+2);
            printf("%d",listaProductos->dato.codigoProducto);
            gotoxy(x+15,y+u+2);
            printf("%s",listaProductos->dato.descripcion);
            gotoxy(x+69,y+u+2);
            printf("%d",listaProductos->dato.stock);
            gotoxy(x+79,y+u+2);
            printf("$%d",listaProductos->dato.precio.precioLista);
            gotoxy(x+95,y+u+2);
            printf("$%d",listaProductos->dato.precio.minorista);
            gotoxy(x+108,y+u+2);
            if(listaProductos->dato.eliminado==0)
            {
                printf("ACTIVO");
            }
            else
            {
                printf("INACTIVO");
            }
            gotoxy(x+120,y+u+2);
            printf("%c",186);

            u++;
            listaProductos=listaProductos->siguiente;
        }
        gotoxy(x,y+u+2);
        printf("%c",200);
        replicante(119,205);
        printf("%c\n",188);

    }
}


void crearCuadroProductosClientes(int x,int y,celdaRubros arreglo[],int rubro,int subrubro,stUsuarios usuario)
{

    LimpiaPantallaParcial(0,3);
    nodoSubRubros*subLista=buscarSubrubrosCuadro(arreglo[rubro].subListas,subrubro);
    if(subLista!=NULL)
    {
        nodoProducto*listaProductos=subLista->lista;
        int u=0;
        int i=0;
        gotoxy(x,y);
        printf("%c",201);
        replicante(100,205);
        printf("%c\n",187);
        gotoxy(x,(y+1));
        printf("%c",186);
        printf("ID%3cCODIGO\%3cDESCRIPCION%43cSTOCK%4cPRECIO %6cESTADO",' ',' ',' ',' ',' ',' ');
        printf("%5c\n",186);
        gotoxy(x,(y+2));

        while(listaProductos!=NULL)
        {

            gotoxy(x,y+u+2);
            printf("%c",186);

            gotoxy(x+1,y+u+2);
            printf("%d",listaProductos->dato.idProducto);
            gotoxy(x+6,y+u+2);
            printf("%d",listaProductos->dato.codigoProducto);
            gotoxy(x+15,y+u+2);
            printf("%s",listaProductos->dato.descripcion);
            gotoxy(x+69,y+u+2);
            printf("%d",listaProductos->dato.stock);
            gotoxy(x+79,y+u+2);
            ///
            if(usuario.condicion==1)
            {
                printf("$%d",listaProductos->dato.precio.precioLista);
            }
            else
            {
                printf("$%d",listaProductos->dato.precio.minorista);
            }

            gotoxy(x+90,y+u+2);
            if((listaProductos->dato.eliminado==0)&&(listaProductos->dato.stock!=0))
            {
                printf("DISPONIBLE");
            }
            else
            {
                printf("NO DISPONIBLE");
            }
            gotoxy(x+101,y+u+2);
            printf("%c",186);

            u++;
            listaProductos=listaProductos->siguiente;
        }
        gotoxy(x,y+u+2);
        printf("%c",200);
        replicante(100,205);
        printf("%c\n",188);

    }
}


void crearCuadroRecomendaciones(int x,int y,celdaRubros arreglo[],int validosRubro,stUsuarios usuario)
{
    int rubro=0;
    int subrubro=0;
    int u=0;
    int i=0;
    LimpiaPantallaParcial(0,3);
    while(rubro<validosRubro)
    {
        nodoSubRubros*subLista=buscarSubrubrosCuadro(arreglo[rubro].subListas,subrubro);
        nodoProducto*listaProductos=subLista->lista;

        gotoxy(x,y);
        printf("%c",201);
        replicante(100,205);
        printf("%c\n",187);
        gotoxy(x,(y+1));
        printf("%c",186);
        printf("ID%3cCODIGO\%3cDESCRIPCION%43cSTOCK%4cPRECIO %6cESTADO",' ',' ',' ',' ',' ',' ');
        printf("%5c\n",186);
        gotoxy(x,(y+2));

        while(listaProductos!=NULL)
        {
            if(listaProductos->dato.stock > 15)
            {
                gotoxy(x,y+u+2);
                printf("%c",186);

                gotoxy(x+1,y+u+2);
                printf("%d",listaProductos->dato.idProducto);
                gotoxy(x+6,y+u+2);
                printf("%d",listaProductos->dato.codigoProducto);
                gotoxy(x+15,y+u+2);
                printf("%s",listaProductos->dato.descripcion);
                gotoxy(x+69,y+u+2);
                printf("%d",listaProductos->dato.stock);
                gotoxy(x+79,y+u+2);
                if(usuario.condicion==1)
                {
                    printf("$%d",listaProductos->dato.precio.precioLista);
                }
                else
                {
                    printf("$%d",listaProductos->dato.precio.minorista);
                }
                gotoxy(x+90,y+u+2);
                if((listaProductos->dato.eliminado==0)&&(listaProductos->dato.stock!=0))
                {
                    printf(" ACTIVO");
                }
                else
                {
                    printf("INACTIVO");
                }
                gotoxy(x+101,y+u+2);
                printf("%c",186);

                u++;
            }
            listaProductos=listaProductos->siguiente;

        }
        rubro++;
    }

    gotoxy(x,y+u+2);
    printf("%c",200);
    replicante(100,205);
    printf("%c\n",188);
    system("pause");
}


void imprimirCabecera(char cabecera[])
{
    int i;
    printf("%c", 201);
    for(i=0; i<118; i++)
    {
        printf("%c",205);
    }
    printf("%c\n", 187);
    printf("%c%63s%56c\n", 186,cabecera,186);
    printf("%c", 200);
    for(i=0; i<118; i++)
    {
        printf("%c",205);
    }
    printf("%c\n", 188);
}
void modifDatos2(int idUsuario,int opcionModificacion) ///Funcion para modificiar datos
{
    stUsuarios a;
    char nombre[20];
    char apellido[20];
    char pass[20];
    char telefono[11];
    char email[30];
    FILE *pArchUsuarios=fopen(arUsuarios,"r+b");
    if(pArchUsuarios)
    {
        fseek(pArchUsuarios,sizeof(stUsuarios)*idUsuario,SEEK_SET);
        fread(&a,sizeof(stUsuarios),1,pArchUsuarios);
        switch(opcionModificacion)
        {
        case 1:
            printf("NOMBRE: ");
            fflush(stdin);
            gets(nombre);
            strcpy(a.nombre,nombre);
            break;
        case 2:
            printf("APELLIDO: ");
            fflush(stdin);
            gets(apellido);
            strcpy(a.apellido,apellido);
            break;
        case 3:
            printf("TELEFONO: ");
            fflush(stdin);
            gets(telefono);
            strcpy(a.telefono,telefono);
            break;
        case 4:
            printf("EMAIL: ");
            fflush(stdin);
            gets(email);
            strcpy(a.email,email);
            break;
        case 5:
            printf("PASSWORD: ");
            fflush(stdin);
            gets(pass);
            strcpy(a.password,pass);
            break;
        }

        fseek(pArchUsuarios,sizeof(stUsuarios)*idUsuario,SEEK_SET);
        fwrite(&a,sizeof(stUsuarios),1,pArchUsuarios);
        fclose(pArchUsuarios);
    }
}
void modifUsuarioAdmin(int idUsuario,int opcionModificacion) ///Funcion para modificiar datos
{
    int idCiudad = -1, ciudadExiste = -1;
    stUsuarios a;
    char ciudad[20];
    int nuevaCondicion;
    char direccion[30];
    FILE *pArchUsuarios=fopen(arUsuarios,"r+b");
    if(pArchUsuarios)
    {
        fseek(pArchUsuarios,sizeof(stUsuarios)*idUsuario,SEEK_SET);
        fread(&a,sizeof(stUsuarios),1,pArchUsuarios);
        switch(opcionModificacion)
        {
        case 1:
            printf("\n CIUDAD: ");
            fflush(stdin);
            color(3);
            gets(ciudad);
            ciudadExiste=buscarCiudad(ciudad);
            strcpy(a.ciudad,ciudad);
            if(ciudadExiste==-1)
            {
                idCiudad=buscarUltimoIdCiudad();
                idCiudad++;
                a.idCiudad=idCiudad;
            }
            else
            {
                a.idCiudad=ciudadExiste;
            }
            break;
        case 2:
            while(nuevaCondicion!=1 && nuevaCondicion!=2)
            {
                color(15);
                printf("\n CONDICION ( 1-MAYORISTA  //  (2) MINORISTA ) : ");
                color(3);
                fflush(stdin);
                scanf("%d",&nuevaCondicion);
                if(nuevaCondicion==1 || nuevaCondicion==2)
                {
                    a.condicion=nuevaCondicion;
                }
                else
                {
                    color(15);
                    printf("\nCONDICION NO VALIDA");
                    system("pause");
                    //LimpiaPantallaParcial(0,3);
                }
            }
            break;
        case 3:
            printf("DIRECCION: ");
            fflush(stdin);
            gets(direccion);
            strcpy(a.direccion,direccion);
            break;
        }

        fseek(pArchUsuarios,sizeof(stUsuarios)*idUsuario,SEEK_SET);
        fwrite(&a,sizeof(stUsuarios),1,pArchUsuarios);
        fclose(pArchUsuarios);
    }
}

/////////////////////////////////////////////////////////////////////////////
int buscarUltimoIDVenta()
{
    stVentas a;
    int id=-1;
    FILE *pArchiVentas = fopen(arVentas,"rb");
    if(pArchiVentas!=NULL)
    {
        fseek(pArchiVentas,sizeof(stVentas)*(-1),SEEK_END);
        while(fread(&a,sizeof(stVentas),1,pArchiVentas)>0)
        {
            id=a.idVenta;
        }
        fclose(pArchiVentas);
    }

    return id+1;
}


void generarVenta(int x,int y,celdaRubros arregloRubros[],stUsuarios usuario)
{
    srand(time(NULL));

    char date[128];         /// Variable usada para almacenar una cadena Fecha y hora

    int rubro=selecRubro();
    int subrubro=selecSubRubro(rubro);
    int codigoProducto=(-1);
    int i =0;
    int j =0;
    int cantidad =999999;
    stProductos producto;
    stVentas venta;
    char confirmaCompra='x';
    char confirmaArticulo='x';

    while(confirmaCompra!='s')
    {
        while(confirmaArticulo!='s')
        {
            crearCuadroProductosClientes(0,3,arregloRubros,rubro,subrubro,usuario);
            printf("\n\t INGRESE EL CODIGO DEL PRODUCTO QUE DESEA AGREGAR A SU COMPRA: ");
            scanf("%d",&codigoProducto);
            producto=consultaProductos(arregloRubros,codigoProducto);
            muestraProducto(producto);
            printf("\n\t CONFIRMA QUE ES EL PRODUCTO CORRECTO ? (S/N):    ");
            fflush(stdin);
            scanf("%c",&confirmaArticulo);
        }
        venta.producVentas.codigoProducto=codigoProducto;
        do
        {
            printf("\n\t INGRESE LA CANTIDAD DE ARTICULOS A RETIRAR: ");
            scanf("%d",&venta.producVentas.cantidad);
            cantidad=venta.producVentas.cantidad;
        }
        while(cantidad>producto.stock);
        i++;
        printf("\n\t DESEA FINALIZAR LA COMPRA ? (S/N):    ");
        fflush(stdin);
        scanf("%c",&confirmaCompra);
        if(confirmaCompra!='s')
        {
            confirmaArticulo='x';
        }
    }
    if(confirmaCompra=='s')
    {
        fGetNow(date);
        strcpy(venta.date,date);
        venta.idCliente=usuario.idUsuario;
        muestraUsuario(usuario);
        system("pause");
        printf("%d",venta.idCliente);
        system("pause");
        venta.idVenta=buscarUltimoIDVenta();
        venta.cobro=0;
        modifStock(venta.producVentas.codigoProducto,venta.producVentas.cantidad);
        FILE*pArchiVentas=fopen(arVentas,"ab");
        if(pArchiVentas)
        {
            muestraVentas(venta,arregloRubros,usuario);
            system("pause");
            fwrite(&venta,sizeof(stVentas),1,pArchiVentas);
            fclose(pArchiVentas);
        }
    }
    LimpiaPantallaParcial(0,3);
    printf("GRACIAS POR SU COMPRA !");

}

void muestraCobro(int cobro)
{
    if(cobro==0)
    {
        printf("\n SIN COBRAR");
    }
    else
    {
        if(cobro==1)
        {
            printf("\n COBRADO");
        }
    }
}

int calculaPrecioVenta(stVentas venta,celdaRubros arregloRubros[],stUsuarios usuario)
{
    int precio=0;
    stProductos producto;
    producto=consultaProductos(arregloRubros,venta.producVentas.codigoProducto);
    if(usuario.condicion==1)
    {
        precio=(venta.producVentas.cantidad)*(producto.precio.precioLista);
    }
    else
    {
        precio=(venta.producVentas.cantidad)*(producto.precio.minorista);
    }
    return precio;
}

void muestraVentas(stVentas venta,celdaRubros arregloRubros[])
{
    stUsuarios cliente=consultaClientes(venta.idCliente);
    stProductos producto=consultaProductos(arregloRubros,venta.producVentas.codigoProducto);
    int precio=calculaPrecioVenta(venta,arregloRubros,cliente);
    printf("%c",201);
    replicante(65,205);
    printf("%c",187);
    printf("\n%1cVENTA X0001 - 00000%d %7cFecha: %s\n%c",' ',venta.idVenta,' ',venta.date,' ');
    replicante(65,205);
    printf("\n%1cCliente: N%d    MONTO: $%d",' ',venta.idCliente,precio);
    printf("\n%1cDescripcion: (%d) x %s\n",' ',venta.producVentas.cantidad,producto.descripcion);

    muestraCobro(venta.cobro);
    printf("\n%c",200);
    replicante(65,205);
    printf("%c",188);
    printf("\n");
}

void recorrerArchivoVentas(celdaRubros arregloRubros[])
{
    stVentas a;
    stUsuarios usuario;
    FILE*pArchiVentas=fopen(arVentas,"rb");
    if(pArchiVentas)
    {
        while(fread(&a,sizeof(stVentas),1,pArchiVentas)>0)
        {
            usuario=consultaClientes(a.idCliente);
            muestraVentas(a,arregloRubros);
        }
        system("pause");

        fclose(pArchiVentas);
    }
}

int buscaProductoXsector(int x,int y,celdaRubros arregloRubros[],stUsuarios usuario)
{
    int rubro=selecRubro();
    int subrubro=selecSubRubro(rubro);
    int codigoProducto=(-1);
    stProductos producto;
    char confirmaCompra='x';

    while(confirmaCompra!='s')
    {
        crearCuadroProductos(0,3,arregloRubros,rubro,subrubro);
        printf("\n\t INGRESE EL CODIGO DEL PRODUCTO QUE DESEA MODIFICAR: ");
        scanf("%d",&codigoProducto);
        producto=consultaProductos(arregloRubros,codigoProducto);
        muestraProducto(producto);
        printf("\n\t CONFIRMA QUE ES EL PRODUCTO CORRECTO ? (S/N):    ");
        fflush(stdin);
        scanf("%c",&confirmaCompra);
    }

    return codigoProducto;
}

void recorrerArchivoVentasxUsuario(celdaRubros arregloRubros[],stUsuarios usuario)
{
    stVentas a;
    FILE*pArchiVentas=fopen(arVentas,"rb");
    if(pArchiVentas)
    {
        while(fread(&a,sizeof(stVentas),1,pArchiVentas)>0)
        {

            if(a.idCliente==usuario.idUsuario)
            {
                muestraVentas(a,arregloRubros);
            }
        }

        fclose(pArchiVentas);
    }
}

int deudaVentasxUsuario(celdaRubros arregloRubros[],stUsuarios usuario)
{
    stVentas a;
    int precioIndividual=0;
    int acumulado=0;
    FILE*pArchiVentas=fopen(arVentas,"rb");
    if(pArchiVentas)
    {
        while(fread(&a,sizeof(stVentas),1,pArchiVentas)>0)
        {

            if((a.idCliente==usuario.idUsuario)&&(a.cobro==0))
            {
                precioIndividual=calculaPrecioVenta(a,arregloRubros,usuario);
                acumulado=acumulado+precioIndividual;

            }
        }
        fclose(pArchiVentas);
    }
    return acumulado;
}
void generarCobro(celdaRubros arregloRubros[])
{
    char nombre[20];
    int opcion=0;
    char confirmacion=0;
    stUsuarios usuario;
    stVentas venta;
    while(confirmacion!=13)
    {
        Color(3);
        printf("Ingrese nombre de usuario que queres buscar\n");
        Color(11);
        fflush(stdin);
        gets(nombre);
        int idcliente = validacionUsuarioParaConsultar(nombre);
        usuario=consultaClientes(idcliente);
        recorrerArchivoVentasxUsuario(arregloRubros,usuario);
        Color(3);
        printf("\nIngrese numero de venta X0001 - 00000\n");
        scanf("%d",&opcion);
        printf("\n");
        FILE*pArchiVentas=fopen(arVentas,"r+b");
        if(pArchiVentas)
        {
            fseek(pArchiVentas,(opcion)*sizeof(stVentas),SEEK_SET);
            fread(&venta,sizeof(stVentas),1,pArchiVentas);
            printf("/nINGRESE ENTER SI DESEA REALIZAR EL COBRO/n");
            confirmacion=getch();
            if(confirmacion==13)
            {
            venta.cobro = 1;
            fseek(pArchiVentas,(opcion)*sizeof(stVentas),SEEK_SET);
            fwrite(&venta,sizeof(stVentas),1,pArchiVentas);
            }
            fclose(pArchiVentas);

        }
    }
}














