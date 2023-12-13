#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <sstream>
#include <limits>

using namespace std;

//Cambiar las structuras cosa que sea char(?)
struct Empleado {
    int CI;
    char puesto[30];
    char nombre[50];
    double sueldo;
};

struct Cliente {
    int CI;
    char nombre[50];
};

struct Plato {
    int codigo;
    char nombre[100];
    double precio;
};

struct Ingredientes {
    int codigoIngrediente;
    char nombre[50];
    int cantidad;
    double precio;
};

struct Receta {
    int codigoPlato;
    int CodigoIngrediente;
    int cantidad;
};

struct Factura {
    int CI;
    char nombreCliente[50];
    vector<Plato> platos;
    double total;
    double dineroRecibido;
    double cambio;
    char fecha[10];
};

struct Reserva{
    int CI;
    char nombreCliente[50];
    char fecha[10];
};

struct Finanzas{
    long double totalVentas = 0.0, gastosIngredientes = 0.0;
};

const char* GERENTE_USUARIO = "gerente";
const char* GERENTE_CONTRASENA = "54321";
const char* CAJERO_USUARIO = "cajero";
const char* CAJERO_CONTRASENA = "12345";
const char* ARCHIVO_EMPLEADOS = "empleados.bin";
const char* ARCHIVO_CLIENTES = "clientes.bin";
const char* ARCHIVO_MENU = "menu.bin";
const char* ARCHIVO_INGREDIENTES = "ingredientes.bin";
const char* ARCHIVO_RECETAS = "recetas.bin";
const char* ARCHIVO_FACTURA = "factura.bin";
const char* ARCHIVO_FINANZAS = "finanzas.bin";
const char* ARCHIVO_RESERVA = "reservas.bin";

const char* ARCHIVO_TEMPORAL = "temporal.bin";

const double IMPUESTO = 0.13;


// funciones
void inicializarArchivos();
void pantallaAcceso();

void menuGerente();
void menuCajero();

Empleado nuevoEmpleado();
Cliente nuevoCliente();
Plato nuevoPlato(int);
Reserva nuevaReserva();

void escribirArchivo(Empleado);
void escribirArchivo(Cliente);
void escribirArchivo(Plato);
void escribirArchivo(Factura);
void escribirArchivo(Reserva);

void eliminarDeArchivo(const char*, int);
void modificarArchivo(int, Empleado);
void modificarArchivo(int, Cliente);
void modificarArchivo(int, Plato);
void modificarArchivo(int, Reserva);
void mostrar(const char*);

void gestionarEmpleados();
void gestionarClientes();
void gestionarMenu();
void IngredienteNuevo();
void AgregarReceta (int, int);
void AniadirIngredientesReceta(int);
void gestionarFacturas();
void gestionarIngredientes();
void gestionarReservas(int);

bool verificarCodigo(int);
Cliente nombreCliente(int);
Plato devolverPlato(int);
void ActualizarInredientes(int);
double calcularTotal(vector<Plato>);
Factura nuevaFactura();
void imprimirFactura(Factura);
void gestionarFinanzas();

void menuCliente(int);

int obtenerEnteroDesdeEntrada();
double obtenerDoubleDesdeEntrada();

// Función principal la bonita aaaaaaaaaaaaaaaaaaa
int main() {
    //inicializarArchivos();
    //pantallaAcceso();
    obtenerEnteroDesdeEntrada();
    return 0;
}

void inicializarArchivos() {
    ofstream archivoEmpleados;
    archivoEmpleados.open(ARCHIVO_EMPLEADOS, ios::app | ios::binary);
    archivoEmpleados.close();

    ofstream archivoClientes;
    archivoClientes.open(ARCHIVO_CLIENTES, ios::app | ios::binary);
    archivoClientes.close();

    ofstream archivoMenu;
    archivoMenu.open(ARCHIVO_MENU, ios::app | ios::binary);
    archivoMenu.close();

    ofstream archivoFactura;
    archivoFactura.open(ARCHIVO_FACTURA, ios::app | ios::binary);
    archivoFactura.close();

    ofstream archivoFinanzas;
    archivoFinanzas.open(ARCHIVO_FINANZAS, ios::app | ios::binary);
    archivoFinanzas.close();
    
    cout << ">> Archivos inicializados." << endl;
}

// Implementación de funciones
void pantallaAcceso() {
    string usuario, contrasena, seleccion;

    system("cls");
    cout << "\nBIENVENIDO A TYPICA!" << endl;
    cout << "====================" << endl;
    cout << "\n\t[1] Iniciar sesion\n\t[2] Ver menu\n\t[3] Salir\n\n--> ";
    cin >> seleccion;

    if(seleccion == "1"){
        for(int i = 0; i < 3; i++){
            system("cls");
            cout << "\nINICIO DE SESION" << endl;
            cout << "================" << endl;
            cout << "\n\tUsuario: ";
            cin >> usuario;
            cout << "\tContraseña: ";
            cin >> contrasena;

            if (usuario == GERENTE_USUARIO && contrasena == GERENTE_CONTRASENA) {
                menuGerente();
                break;
            } else if (usuario == CAJERO_USUARIO && contrasena == CAJERO_CONTRASENA) {
                menuCajero();
                break;
            }
            else {
                if(i + 1 == 3){
                    cout << "\n>> Ha ingresado como cliente." << endl << endl;
                    system("pause");
                    menuCliente(0);
                }
                else{
                    cout << "\n>> Acceso no autorizado. Vuelva a intentar." << endl << endl;
                    system("pause");
                }
            }
        }
        
    }
    else if(seleccion == "2"){
        menuCliente(0);
        cout << "\n[1] Volver\t[2] Salir\n\n--> ";
        cin >> seleccion;

        if(seleccion == "1"){
            pantallaAcceso();
        }
        else{
            cout << "\n>> Salienedo del sistema." << endl;
            exit(0);
        }
    }
    else{
        cout << "\n>> Salienedo del sistema." << endl;
        exit(0);
    }
    
}

void menuGerente() {
    while (true) {
        cout << "\nMENU GERENTE" << endl;
        cout << "============" << endl;
        cout << "\n\t1. Gestionar empleados." << endl;
        cout << "\t2. Gestionar clientes." << endl;
        cout << "\t3. Gestionar menu." << endl;
        cout << "\t4. Gestionar ingredientes."<<endl;
        cout << "\t5. Gestionar reservas." << endl;
        cout << "\t6. Generar factura." << endl;
        cout << "\t7. Reporte financiero." << endl;
        cout << "\t8. Cerrar sesion." << endl;

        int opcion;
        cout << "\n\t--> ";
        opcion = obtenerEnteroDesdeEntrada();

        switch (opcion) {
            case 1:
                gestionarEmpleados();
                break;
            case 2:
                gestionarClientes();
                break;
            case 3:
                gestionarMenu();
                break;
            case 4:
                gestionarIngredientes();
                break;
            case 5:
                gestionarReservas(0);
            case 6:
            {
                menuCliente(1);
                Factura f = nuevaFactura();
                escribirArchivo(f);
                cout << "\n>> Factura generada correctamente." << endl;
                imprimirFactura(f);
                break;
            }
                break;
            case 7:
                gestionarFinanzas();   
                break;
            case 8:
                pantallaAcceso();
            default:
                cout << "\n>> Intente de nuevo." << endl;
        }
    }
}

Empleado nuevoEmpleado(){
    Empleado e;
    cout << "\n\t- Ingrese el CI del empleado: ";
    e.CI = obtenerEnteroDesdeEntrada();
    cout << "\t- Ingrese el nombre del empleado: ";
    cin.ignore(256, '\n');
    cin.getline(e.nombre, 50);
    cout << "\t- Ingrese el puesto del empleado: ";
    cin.getline(e.puesto, 30);
    cout << "\t- Ingrese el sueldo del empleado: ";
    e.sueldo = obtenerDoubleDesdeEntrada();

    return e;
}

Cliente nuevoCliente(){
    Cliente c;
    cout << "\n\t- Ingrese el CI del cliente: ";
    c.CI = obtenerEnteroDesdeEntrada();
    cout << "\t- Ingrese el nombre del cliente: ";
    cin.ignore(256, '\n');
    cin.getline(c.nombre, 50);

    return c;
}

Plato nuevoPlato(int x){
    ifstream platos;
    platos.open(ARCHIVO_MENU, ios::binary);
    vector<Plato> pl;
    Plato p;
    while(platos.read((char*)&p, sizeof(Plato)))
        pl.push_back(p);
    platos.close();
    if(x==-1)
        p.codigo = pl[pl.size()-1].codigo+1;
    else
        p.codigo = x;
    cout << "\t- Ingrese el nombre del plato: ";
    cin.ignore(256, '\n');
    cin.getline(p.nombre, 100);
    cout << "\t- Ingrese el precio del plato: ";
    p.precio = obtenerDoubleDesdeEntrada();
    AniadirIngredientesReceta(p.codigo);
    return p;
}

void escribirArchivo(Empleado e){
    ofstream escritura;
    escritura.open(ARCHIVO_EMPLEADOS, ios::binary | ios::app);
    if(escritura.good()){
        escritura.write((char*)&e, sizeof(Empleado));
    }
    else{
        cout << "\n>> No se pudo abrir el archivo de empleados." << endl;
    }
    escritura.close();
}

void escribirArchivo(Cliente c){
    ofstream escritura;
    escritura.open(ARCHIVO_CLIENTES, ios::binary | ios::app);
    if(escritura.good()){
        escritura.write((char*)&c, sizeof(Cliente));
    }
    else{
        cout << "\n>> No se pudo abrir el archivo de clientes." << endl;
    }
    escritura.close();
}

void escribirArchivo(Plato p){
    ofstream escritura;
    escritura.open(ARCHIVO_MENU, ios::binary | ios::app);
    if(escritura.good()){
        escritura.write((char*)&p, sizeof(Plato));
    }
    else{
        cout << "\n>> No se pudo abrir el archivo de menu." << endl;
    }
    escritura.close();
}

void escribirArchivo(Factura f){
    ofstream escritura;
    escritura.open(ARCHIVO_FACTURA, ios::binary | ios::app);
    if(escritura.good()){
        escritura.write((char*)&f, sizeof(Factura));
    }
    else{
        cout << "\n>> No se pudo abrir el archivo de facturas." << endl;
    }
    escritura.close();
}

void escribirArchivo(Reserva r){
    ofstream escritura;
    escritura.open(ARCHIVO_RESERVA, ios::binary | ios::app);
    if(escritura.good()){
        escritura.write((char*)&r, sizeof(Reserva));
    }
    else{
        cout << "\n>> No se pudo abrir el archivo de reservas." << endl;
    }
    escritura.close();
}

void eliminarDeArchivo(const char* archivo, int x){
    ifstream lectura;
    lectura.open(archivo, ios::binary);

    ofstream escritura;
    escritura.open(ARCHIVO_TEMPORAL, ios::binary);

    if(archivo == ARCHIVO_EMPLEADOS){
        Empleado e;
        while(lectura.read((char*)&e, sizeof(Empleado))){
            if(x != e.CI){
                escritura.write((char*)&e, sizeof(Empleado));
            }
        }
    }else if(archivo == ARCHIVO_CLIENTES){
        Cliente c;
        while(lectura.read((char*)&c, sizeof(Cliente))){
            if(x != c.CI){
                escritura.write((char*)&c, sizeof(Cliente));
            }
        }
    }else if(archivo == ARCHIVO_MENU){
        Plato p;
        while(lectura.read((char*)&p, sizeof(Plato))){
            if(x != p.codigo){
                escritura.write((char*)&p, sizeof(Plato));
            }
        }
    }else if(archivo == ARCHIVO_RESERVA){
        Reserva r;
        while(lectura.read((char*)&r, sizeof(Reserva))){
            if(x != r.CI){
                escritura.write((char*)&r, sizeof(Reserva));
            }
        }
    }

    lectura.close();
    escritura.close();

    remove(archivo);
    rename(ARCHIVO_TEMPORAL, archivo);
}

void modificarArchivo(int x, Empleado empleado){
    ifstream lectura;
    lectura.open(ARCHIVO_EMPLEADOS, ios::binary);

    ofstream escritura;
    escritura.open(ARCHIVO_TEMPORAL, ios::binary);

    Empleado e;

    while(lectura.read((char*)&e, sizeof(Empleado))){
        if(x != e.CI){
            escritura.write((char*)&e, sizeof(Empleado));
        }
        else{
            escritura.write((char*)&empleado, sizeof(Empleado));
        }
    }

    lectura.close();
    escritura.close();

    remove(ARCHIVO_EMPLEADOS);
    rename(ARCHIVO_TEMPORAL, ARCHIVO_EMPLEADOS);
}

void modificarArchivo(int x, Cliente cliente){
    ifstream lectura;
    lectura.open(ARCHIVO_CLIENTES, ios::binary);

    ofstream escritura;
    escritura.open(ARCHIVO_TEMPORAL, ios::binary);

    Cliente c;

    while(lectura.read((char*)&c, sizeof(Cliente))){
        if(x != c.CI){
            escritura.write((char*)&c, sizeof(Cliente));
        }
        else{
            escritura.write((char*)&cliente, sizeof(Cliente));
        }
    }

    lectura.close();
    escritura.close();

    remove(ARCHIVO_CLIENTES);
    rename(ARCHIVO_TEMPORAL, ARCHIVO_CLIENTES);
}

void modificarArchivo(int x, Plato plato){
    ifstream lectura;
    lectura.open(ARCHIVO_MENU, ios::binary);

    ofstream escritura;
    escritura.open(ARCHIVO_TEMPORAL, ios::binary);

    Plato p;

    while(lectura.read((char*)&p, sizeof(Plato))){
        if(x != p.codigo){
            escritura.write((char*)&p, sizeof(Plato));
        }
        else{
            escritura.write((char*)&plato, sizeof(Plato));
        }
    }

    lectura.close();
    escritura.close();

    remove(ARCHIVO_MENU);
    rename(ARCHIVO_TEMPORAL, ARCHIVO_MENU);
}

void modificarArchivo(int x, Reserva reserva){
    ifstream lectura;
    lectura.open(ARCHIVO_RESERVA, ios::binary);

    ofstream escritura;
    escritura.open(ARCHIVO_TEMPORAL, ios::binary);

    Reserva r;

    while(lectura.read((char*)&r, sizeof(Reserva))){
        if(x != r.CI){
            escritura.write((char*)&r, sizeof(Reserva));
        }
        else{
            escritura.write((char*)&reserva, sizeof(Reserva));
        }
    }

    lectura.close();
    escritura.close();

    remove(ARCHIVO_RESERVA);
    rename(ARCHIVO_TEMPORAL, ARCHIVO_RESERVA);
}

void mostrar(const char* archivo){
    ifstream lectura;
    lectura.open(archivo, ios::binary);
    
    if(lectura.good()){
        if(archivo == ARCHIVO_EMPLEADOS){
            Empleado e;
            cout << "\n--> Lista de empleados:" << endl;
            while(lectura.read((char*)&e, sizeof(Empleado))){
                cout << "\n\tCarnet de Identidad: " << e.CI << endl;
                cout << "\tNombre: " << e.nombre << endl;
                cout << "\tPuesto: " << e.puesto << endl;
                cout << "\tSueldo: " << e.sueldo << " BOB al mes." << endl;
            }
        }else if(archivo == ARCHIVO_CLIENTES){
            Cliente c;
            cout << "\n--> Lista de clientes:" << endl;
            while(lectura.read((char*)&c, sizeof(Cliente))){
                cout << "\n\tCarnet de Identidad: " << c.CI << endl;
                cout << "\tNombre: " << c.nombre << endl;
            }
        }else if(archivo == ARCHIVO_MENU){
            Plato p;
            cout << "\n--> Lista de platos:" << endl;
            while(lectura.read((char*)&p, sizeof(Plato))){
                cout << "\n\tCodigo: " << p.codigo << endl;
                cout << "\tNombre: " << p.nombre << endl;
                cout << "\tPrecio: " << p.precio << endl;
            }
        }else if(archivo == ARCHIVO_RESERVA){
            Reserva r;
            cout << "\n--> Lista de reservas:" << endl;
            while(lectura.read((char*)&r, sizeof(Reserva))){
                cout << "\n\tCarnet de identidad: " << r.CI << endl;
                cout << "\tNombre: " << r.nombreCliente << endl;
                cout << "\tFecha: " << r.fecha << endl;
            }
        }
    }
    else{
        cout << "\n>> No se pudo abrir el archivo " << archivo << "." << endl;
    }

    lectura.close();
}

void gestionarEmpleados() {
    cout << "\nGESTION DE EMPLEADOS" << endl;
    cout << "====================" << endl;

    do{
        cout << "\n\t1. Añadir empleado." << endl;
        cout << "\t2. Eliminar empleado." << endl;
        cout << "\t3. Modificar empleado." << endl;
        cout << "\t4. Mostrar lista de empleados." << endl;
        cout << "\t5. Volver." << endl;

        int opcion;
        cout << "\n\t-->  ";
        opcion = obtenerEnteroDesdeEntrada();

        switch(opcion){
            int ci;
            case 1:
                escribirArchivo(nuevoEmpleado());
                cout << "\n>> Se ha añadido al empleado." << endl;
                break;
            case 2:
                cout << "\nIngrese el CI del empleado a eliminar: ";
                cin >> ci;
                eliminarDeArchivo(ARCHIVO_EMPLEADOS, ci);
                cout << "\n>> Se ha eliminado al empleado." << endl;
                break;
            case 3:
                cout << "\nIngrese el CI del empleado a modificar: ";
                cin >> ci;
                modificarArchivo(ci, nuevoEmpleado());
                cout << "\n>> Se ha modificado al empleado." << endl;
                break;
            case 4:
                mostrar(ARCHIVO_EMPLEADOS);
                cout << endl;
                break;
            case 5:
                menuGerente();
            default:
                cout << "\n>> Intente de nuevo." << endl;
        }  
    }
    while(true);
}

void gestionarClientes() {
    cout << "\nGESTION DE CLIENTES" << endl;
    cout << "====================" << endl;

    do{
        cout << "\n\t1. Añadir cliente." << endl;
        cout << "\t2. Eliminar cliente." << endl;
        cout << "\t3. Modificar cliente." << endl;
        cout << "\t4. Mostrar lista de clientes." << endl;
        cout << "\t5. Volver." << endl;

        int opcion;
        cout << "\n\t-->  ";
        opcion = obtenerEnteroDesdeEntrada();

        switch(opcion){
            int ci;
            case 1:
                escribirArchivo(nuevoCliente());
                cout << "\n>> Se ha añadido al cliente" << endl;
                break;
            case 2:
                cout << "\nIngrese el CI del cliente a eliminar: ";
                cin >> ci;
                eliminarDeArchivo(ARCHIVO_CLIENTES, ci);
                cout << "\n>> Se ha eliminado al cliente." << endl;
                break;
            case 3:
                cout << "\nIngrese el CI del cliente a modificar: ";
                cin >> ci;
                modificarArchivo(ci, nuevoCliente());
                cout << "\n>> Se ha modificado al cliente." << endl;
                break;
            case 4:
                mostrar(ARCHIVO_CLIENTES);
                cout << endl;
                break;
            case 5:
                menuGerente();
            default:
                cout << "\n>> Intente de nuevo." << endl;
        }  
    }
    while(true);
}

void gestionarMenu() {
    cout << "\nGESTION DEL MENU" << endl;
    cout << "=================" << endl;

    do{
        cout << "\n\t1. Añadir plato." << endl;
        cout << "\t2. Eliminar plato." << endl;
        cout << "\t3. Modificar plato." << endl;
        cout << "\t4. Mostrar lista de platos." << endl;
        cout << "\t5. Volver." << endl;

        int opcion;
        cout << "\n\t-->  ";
        opcion = obtenerEnteroDesdeEntrada();

        switch(opcion){
            int codigo;
            case 1:
                escribirArchivo(nuevoPlato(-1));
                cout << "\n>> Se ha añadido el plato." << endl;
                break;
            case 2:
                cout << "\nIngrese el codigo del plato a eliminar: ";
                cin >> codigo;
                eliminarDeArchivo(ARCHIVO_MENU, codigo);
                cout << "\n>> Se ha eliminado el plato." << endl;
                break;
            case 3:
                cout << "\nIngrese el codigo del plato a modificar: ";
                cin >> codigo;
                modificarArchivo(codigo, nuevoPlato(codigo));
                cout << "\n>> Se ha modificado el plato." << endl;
                break;
            case 4:
                mostrar(ARCHIVO_MENU);
                cout << endl;
                break;
            case 5:
                menuGerente();
            default:
                cout << "\n>> Intente de nuevo." << endl;
        }  
    }
    while(true);
}

vector <Ingredientes> MostrarIngreDientes()
{
    ifstream archivo;
    archivo.open(ARCHIVO_INGREDIENTES, ios::binary);

    cout << "\n>> Lista de ingredientes: " << endl;

    Ingredientes ing;
    vector<Ingredientes> ingre;

    while(archivo.read((char*)&ing, sizeof(Ingredientes)))
    {
        cout << setfill(' ') << "\n- Codigo: " << setw(6) << left << ing.codigoIngrediente;
        cout << "Nombre: " << setw(22) << left << ing.nombre;
        cout << "Cantidad: "<< setw(12) << left << ing.cantidad;
        cout << "Precio: " << ing.precio << " BOB." << endl;
        ingre.push_back(ing);
    }
    archivo.close();
    return ingre;
}
void AniadirIngredientesReceta(int codigoPlato)
{
    int opcion;
    cout<<"\tANIADIR INGREDIENTES A LAS RECETAS"<<endl;
    cout<<"\t==================================="<<endl;
    cout<<"\t\t1. Ingrediente existente."<<endl;
    cout<<"\t\t2. Ingrediente nuevo."<<endl;
    cout<<"\t\t3. Volver."<<endl;
    opcion = obtenerEnteroDesdeEntrada();
    switch (opcion){
        case 1:{
            vector<Ingredientes> ingre = MostrarIngreDientes();
            int codigoing = -1;
            while(codigoing != 0){
                cout<<"Ingrese el codigo del ingrediente a agregar al platillo (0 para salir): ";
                codigoing = obtenerEnteroDesdeEntrada();
                if(codigoing==0)
                    break;
                AgregarReceta(codigoPlato, codigoing);
            }
            break;
        }
        case 2:
        {
            IngredienteNuevo();
            vector<Ingredientes> ingre = MostrarIngreDientes();
            AgregarReceta(codigoPlato, ingre[ingre.size()-1].codigoIngrediente);
        }
        case 3:
            gestionarMenu();
            break;
        default:
            cout<<"Opcion no valida"<<endl;
    }
}

void IngredienteNuevo()
{
    ifstream archivo;
    archivo.open(ARCHIVO_INGREDIENTES, ios::binary);
    cout << "Lista de ingredientes: " << endl;
    Ingredientes ing;
    vector<Ingredientes> ingre;
    while(archivo.read((char*)&ing, sizeof(Ingredientes)))
        ingre.push_back(ing);
    fflush(stdin);
    cout << "Ingrese el nombre del ingrediente nuevo: ";
    cin.getline(ing.nombre, 50);
    cout << "Ingrese el precio del ingrediente nuevo: ";
    ing.precio = obtenerDoubleDesdeEntrada();
    cout << "ingrese de cuantos ingredientes sera el pedido: ";
    ing.cantidad = obtenerEnteroDesdeEntrada();
    ofstream aniadir;
    aniadir.open(ARCHIVO_INGREDIENTES, ios::binary | ios::app);
    ing.codigoIngrediente = ingre[ingre.size()-1].codigoIngrediente+1;
    aniadir.write((char*)&ing, sizeof(Ingredientes));
    aniadir.close();
}
void AgregarReceta (int codigoPlato, int codigoing)
{
    cout<<"Ingrese la cantidad del ingrediente que entra a la receta: ";
    int can;
    cin>>can;
    ofstream recet;
    recet.open(ARCHIVO_RECETAS, ios::binary | ios:: app);
    Receta r;
    r.codigoPlato = codigoPlato;
    r.CodigoIngrediente = codigoing;
    r.cantidad = can;
    recet.write((char*)&r, sizeof(Receta));
    recet.close();
}

void gestionarIngredientes()
{
    cout << "\nGESTION DE INGREDIENTES" << endl;
    cout << "=======================" << endl;
    cout << "\n\t1. Realizar pedido de un ingrediente ya existente." << endl;
    cout << "\t2. Realizr pedido de un ingrediente nuevo." << endl;
    cout << "\t3. Mostrar inventario." << endl;
    cout << "\t4. Volver." << endl;

    int opcion;
    cout << "\n\t-->  ";
    opcion = obtenerEnteroDesdeEntrada();
    switch(opcion)
    {
        case 1:
        {
            ifstream archivo;
            archivo.open(ARCHIVO_INGREDIENTES, ios::binary);

            cout << "\n>> Lista de ingredientes: " << endl;

            Ingredientes ing;
            vector<Ingredientes> ingre;

            while(archivo.read((char*)&ing, sizeof(Ingredientes)))
            {
                cout << setfill(' ') << "\n- Codigo: " << setw(6) << left << ing.codigoIngrediente;
                cout << "Nombre: " << setw(22) << left << ing.nombre;
                cout << "Cantidad: "<< setw(12) << left << ing.cantidad;
                cout << "Precio: " << ing.precio << " BOB." << endl;
                ingre.push_back(ing);
            }
            archivo.close();

            cout << "\n>> Ingrese el codigo de que ingrediente desea hacer el pedido: ";
            int codigoing;
            codigoing = obtenerEnteroDesdeEntrada();

            cout << "\n>> Ingrese de cuantos ingredientes sera el pedido: ";
            int cantidad;
            cantidad = obtenerEnteroDesdeEntrada();

            double totalCompra = 0;

            for(unsigned int i=0; i < ingre.size(); i++)
            {
                if(ingre[i].codigoIngrediente == codigoing){
                    ingre[i].cantidad += cantidad;
                    totalCompra = ingre[i].precio * cantidad;
                    cout << "\n>> Se han comprado " << cantidad << " " << ingre[i].nombre << "s a " << totalCompra << " BOB." << endl;
                }
            }

            ofstream sobreescribir;
            sobreescribir.open(ARCHIVO_INGREDIENTES, ios::binary);
            for(unsigned int i=0; i<ingre.size(); i++)
            sobreescribir.write((char*)&ingre[i], sizeof(Ingredientes));
            sobreescribir.close();

            ifstream lectura;
            ofstream escritura;
            Finanzas fin;
            lectura.open(ARCHIVO_FINANZAS, ios::binary);
            escritura.open(ARCHIVO_TEMPORAL, ios::binary);
            lectura.read((char*)&fin, sizeof(Finanzas));
            fin.gastosIngredientes += totalCompra;
            escritura.write((char*)&fin, sizeof(Finanzas));
            lectura.close();
            escritura.close();
            remove(ARCHIVO_FINANZAS);
            rename(ARCHIVO_TEMPORAL, ARCHIVO_FINANZAS);
            break;
        }
        case 2:
        {
            IngredienteNuevo();
            break;
        }
        case 3:
        {
            ifstream archivo;
            archivo.open(ARCHIVO_INGREDIENTES, ios::binary);

            cout << "\n>> Lista de ingredientes: " << endl;

            Ingredientes ing;

            while(archivo.read((char*)&ing, sizeof(Ingredientes)))
            {
                cout << setfill(' ') << "\n- Codigo: " << setw(6) << left << ing.codigoIngrediente;
                cout << "Nombre: " << setw(22) << left << ing.nombre;
                cout << "Cantidad: "<< setw(12) << left << ing.cantidad;
                cout << "Precio: " << ing.precio << " BOB." << endl;
            }
            archivo.close();
            break;
        }
        case 4:
            menuGerente();
        default:
            cout << "\n>> Intente de nuevo." << endl;
        break;
    }
}

void gestionarReservas(int x){
    cout << "\nGESTION DE RESERVAS" << endl;
    cout << "===================" << endl;

    do{
        cout << "\n\t1. Añadir reserva." << endl;
        cout << "\t2. Eliminar reserva." << endl;
        cout << "\t3. Modificar reserva." << endl;
        cout << "\t4. Mostrar lista de reservas." << endl;
        cout << "\t5. Volver." << endl;

        int opcion;
        cout << "\n\t--> ";
        opcion = obtenerEnteroDesdeEntrada();

        switch(opcion){
            int CI;
            case 1:
                escribirArchivo(nuevaReserva());
                cout << "\n>> Se ha añadido la reserva." << endl;
                break;
            case 2:
                cout << "\nIngrese el CI de la reserva del cliente a eliminar: ";
                cin >> CI;
                eliminarDeArchivo(ARCHIVO_RESERVA, CI);
                cout << "\n>> Se ha eliminado la reserva." << endl;
                break;
            case 3:
                cout << "\nIngrese el CI de la reserva del cliente a modificar: ";
                cin >> CI;
                modificarArchivo(CI, nuevaReserva());
                cout << "\n>> Se ha modificado la reserva." << endl;
                break;
            case 4:
                mostrar(ARCHIVO_RESERVA);
                cout << endl;
                break;
            case 5:
            {
                if(x == 0){
                    menuGerente();
                }else if(x == 1){
                    menuCajero();
                }
            } 
            default:
                cout << "\n>> Intente de nuevo." << endl;
        }  
    }
    while(true);
}

Cliente nombreCliente(int ci){
    ifstream lectura;
    lectura.open(ARCHIVO_CLIENTES, ios::binary);

    Cliente c;

    while(lectura.read((char*)&c, sizeof(Cliente))){
        if(ci == c.CI){
            lectura.close();
            return c;
        }
    }
    lectura.close();
    return c;
}

bool verificarCliente(int ci){
    ifstream lectura;
    lectura.open(ARCHIVO_CLIENTES, ios::binary);

    Cliente c;

    while(lectura.read((char*)&c, sizeof(Cliente))){
        if(ci == c.CI){
            lectura.close();
            return true;
        }
    }
    lectura.close();
    return false;
}

bool verificarCodigo(int codigo){
    ifstream lectura;
    lectura.open(ARCHIVO_MENU, ios::binary);

    Plato p;

    while(lectura.read((char*)&p, sizeof(Plato))){
        if(codigo == p.codigo){
            lectura.close();
            return true;
        }
    }
    lectura.close();
    return false;
}

Plato devolverPlato(int codigo){
    ifstream lectura;
    lectura.open(ARCHIVO_MENU, ios::binary);

    Plato p;

    while(lectura.read((char*)&p, sizeof(Plato))){
        if(codigo == p.codigo){
            lectura.close();
            ActualizarInredientes(codigo);
            return p;
        }
    }
    lectura.close();
    return p;
}

void ActualizarInredientes(int codigo)
{
    ifstream ingredientesarchivolectura;
    vector<Ingredientes> ingre;
    Ingredientes i;
    ingredientesarchivolectura.open(ARCHIVO_INGREDIENTES, ios::binary);
    while(ingredientesarchivolectura.read((char*)&i, sizeof(Ingredientes)))
        ingre.push_back(i);
    ingredientesarchivolectura.close();
    ifstream recetitas;
    recetitas.open(ARCHIVO_RECETAS, ios::binary);
    Receta r;
    while(recetitas.read((char*)&r, sizeof(Receta)))
    {
        if(r.codigoPlato == codigo)
        {
            for(unsigned int i = 0; i < ingre.size(); i++)
            {
                if(r.CodigoIngrediente == ingre[i].codigoIngrediente)
                    ingre[i].cantidad -= r.cantidad;
            }
        }
    }
    recetitas.close();
    ofstream IngrecientesArchivoEscritura;
    IngrecientesArchivoEscritura.open(ARCHIVO_INGREDIENTES, ios::binary);
    IngrecientesArchivoEscritura.write(reinterpret_cast<char*>(ingre.data()), ingre.size()*sizeof(Ingredientes));
    IngrecientesArchivoEscritura.close();
}

double calcularTotal(vector<Plato> platos){
    ifstream lectura;

    Plato p;
    double total = 0;

    for(unsigned int i = 0; i < platos.size(); i++){
        lectura.open(ARCHIVO_MENU, ios::binary);
        while(lectura.read((char*)&p, sizeof(Plato))){
            if(platos[i].codigo == p.codigo){
                total += p.precio;
            }
        }
        lectura.close();
    }
    return total;
}

Factura nuevaFactura(){
    Factura f;
    cout << "\n\t- Ingrese el CI del cliente (0: sin datos): ";
    f.CI = obtenerEnteroDesdeEntrada();

    if(f.CI != 0){
        bool bandera = verificarCliente(f.CI);
        if(bandera){
            cout << "\n>> El cliente ya ha sido registrado. Autocompletando informacion." << endl << endl;
            Cliente c = nombreCliente(f.CI);
            strcpy(f.nombreCliente, c.nombre);
        }
        else{
            Cliente c;
            cout << "\t- Ingrese el nombre del cliente: ";
            cin.ignore(256, '\n');
            cin.getline(f.nombreCliente, 50);
            c.CI = f.CI;
            strcpy(c.nombre, f.nombreCliente);
            escribirArchivo(c);
        }
    }
    else{
        strcpy(f.nombreCliente, "SIN DATOS");
    }
    

    time_t t = time(nullptr);
    tm* now = localtime(&t);
    stringstream fechaSS;
    fechaSS << now->tm_year + 1900 << '/' << now->tm_mon + 1 << '/' << now->tm_mday;
    string tmp = fechaSS.str();
    strcpy(f.fecha, tmp.c_str());

    int codigo = -1;
    while(codigo != 0){
        cout << "\t- Ingrese el codigo del plato (0: finalizar): ";
        codigo = obtenerEnteroDesdeEntrada();

        bool bandera = verificarCodigo(codigo);

        if(bandera){
            f.platos.push_back(devolverPlato(codigo));
        }
        else{
            if(codigo != 0){
                cout << "\n>> El plato no ha sido registrado en el menu. Intente de nuevo." << endl << endl;
            }
        }
    }

    f.total = calcularTotal(f.platos);
    cout << "\n>> El total de la compra es de " << f.total << " BOB." << endl;

    ifstream lectura;
    ofstream escritura;
    Finanzas fin;
    lectura.open(ARCHIVO_FINANZAS, ios::binary);
    escritura.open(ARCHIVO_TEMPORAL, ios::binary);
    lectura.read((char*)&fin, sizeof(Finanzas));
    fin.totalVentas += f.total;
    escritura.write((char*)&fin, sizeof(Finanzas));
    lectura.close();
    escritura.close();
    remove(ARCHIVO_FINANZAS);
    rename(ARCHIVO_TEMPORAL, ARCHIVO_FINANZAS);

    cout << "\n\t-Ingrese el dinero recibido: ";
    f.dineroRecibido = obtenerDoubleDesdeEntrada();
    f.cambio = f.dineroRecibido - f.total;
   
    return f;
}

void gestionarFinanzas() {
    ifstream lectura;
    lectura.open(ARCHIVO_EMPLEADOS, ios::binary);

    Empleado e;
    double totalSalarios = 0.0;

    while(lectura.read((char*)&e, sizeof(Empleado))){
        totalSalarios += e.sueldo;
    }

    lectura.close();

    Finanzas fin;
    lectura.open(ARCHIVO_FINANZAS, ios::binary);
    lectura.read((char*)&fin, sizeof(Finanzas));

    double descuentos = fin.totalVentas * IMPUESTO;

    double saldoFinal = fin.totalVentas - descuentos;

    cout << "\nREPORTE FINANCIERO" << endl;
    cout << "==================" << endl;
    cout << fixed << setprecision(2);
    cout << "\n\tTotal de ventas: " << fin.totalVentas << " BOB." << endl;
    cout << "\tDescuentos (13% de impuestos): " << descuentos << " BOB." << endl;
    cout << "\tGastos en salarios: " << totalSalarios << " BOB." << endl;
    cout << "\tGastos en ingredientes: " << fin.gastosIngredientes << " BOB." << endl;
    cout << "\tSaldo final: " << saldoFinal << " BOB." << endl;
}

void imprimirFactura(Factura f){
    cout << "\n\nFACTURA -----" << endl;
    cout << "\nFecha: " << f.fecha << endl;
    cout << "CI del cliente: " << f.CI << endl;
    cout << "Nombre del cliente: " << f.nombreCliente << endl;
    cout << "\nPlatos pedidos:" << endl;
    for (unsigned int i = 0; i < f.platos.size(); i++) {
        cout << "\t- " << f.platos[i].nombre << "........" << f.platos[i].precio << " BOB" << endl;
    }
    cout << "\nTotal: " << f.total << " BOB" << endl;
    cout << "Dinero recibido: " << f.dineroRecibido << " BOB" << endl;
    cout << "Cambio: " << f.cambio << " BOB" << endl;
}

Reserva nuevaReserva(){
    Reserva r;
    cout << "\n\tIngrese el CI del cliente: ";
    r.CI = obtenerEnteroDesdeEntrada();

    bool bandera = verificarCliente(r.CI);
    
    if(bandera){
        cout << "\n>> El cliente ya ha sido registrado. Autocompletando informacion." << endl << endl;
        Cliente c = nombreCliente(r.CI);
        strcpy(r.nombreCliente, c.nombre);
    }
    else{
        cout << "\tIngrese el nombre del cliente: ";
        cin.ignore(256, '\n');
        cin.getline(r.nombreCliente, 50);

        Cliente c;
        c.CI = r.CI;
        strcpy(c.nombre, r.nombreCliente);
        escribirArchivo(c);
    }

    
    cout << "\tIngrese la fecha de la reserva (dd/mm/yyyy): ";
    cin >> r.fecha;

    return r;
}

void menuCajero(){
    while (true) {
        cout << "\nMENU CAJERO" << endl;
        cout << "=============" << endl;
        cout << "\t1. Ver menu." << endl;
        cout << "\t2. Generar factura." << endl;
        cout << "\t3. Gestionar reservas." << endl;
        cout << "\t4. Cerrar sesion." << endl;

        int opcion;
        cout << "\n\tSeleccione una opcion: ";
        opcion = obtenerEnteroDesdeEntrada();

        switch(opcion){
            case 1:
                menuCliente(0);
                break;
            case 2:
            {
                menuCliente(1);
                Factura f = nuevaFactura();
                escribirArchivo(f);
                cout << "\n>> Factura generada correctamente." << endl;
                imprimirFactura(f);
                break;
            }
            case 3:
                gestionarReservas(1);
            case 4:
                pantallaAcceso();
            default:
                cout << "\n>> Intente de nuevo." << endl;
        }
    }
}

void menuCliente(int x){
    ifstream lectura;
    lectura.open(ARCHIVO_MENU, ios::binary);

    Plato p;
    cout << "\nMENU DEL RESTAURANTE" << endl;
    cout << "====================" << endl;

    if(x == 0){
        while(lectura.read((char*)&p, sizeof(Plato))){
            cout << endl << setfill('.') << setw(60) << left << p.nombre << p.precio << endl;
        }
    }
    else if(x == 1){
        while(lectura.read((char*)&p, sizeof(Plato))){
            cout << endl << p.codigo << ": " << setfill('.') << setw(60) << left << p.nombre << p.precio << endl;
        }
    }
    lectura.close();
}

int obtenerEnteroDesdeEntrada() 
{
    string entrada;
    int entero;

    while (true) {
        cin >> entrada;
        istringstream iss(entrada);
        if (iss >> entero && iss.eof()) {
            break;
        } else {
            cout << "Error. Por favor, ingresa un valor entero válido." << endl;
        }
    }
    return entero;
}

double obtenerDoubleDesdeEntrada() 
{
    string entrada;
    double valorDouble;
    while (true) {
        cout << "Ingresa un valor double: ";
        getline(cin, entrada);
        istringstream iss(entrada);
        if (iss >> valorDouble && iss.eof()) {
            break;
        } else {
            cerr << "Error. Por favor, ingresa un valor double válido." << endl;
        }
    }
    return valorDouble;
}