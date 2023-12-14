#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <sstream>
#include <limits>
#include <wchar.h>

using namespace std;

// Estructura para almacenar los datos de los empleados
struct Empleado {
    int CI;
    char puesto[30];
    char nombre[50];
    double sueldo;
};

// Estructura para almacenar los datos de los clientes
struct Cliente {
    int CI;
    char nombre[50];
};

// Estructura para almacenar los datos de los platos del menú
struct Plato {
    int codigo;
    char nombre[100];
    double precio;
};

// Estructura para almacenar los datos de los ingredientes
struct Ingredientes {
    int codigoIngrediente;
    char nombre[50];
    int cantidad;
    double precio;
};

// Estructura para almacenar los datos de las recetas de los platos del menú
struct Receta {
    int codigoPlato;
    int CodigoIngrediente;
    int cantidad;
};

// Estructura para almacenar los datos de las facturas
struct Factura {
    int CI;
    char nombreCliente[50];
    vector<Plato> platos;
    double total;
    double dineroRecibido;
    double cambio;
    char fecha[10];
};

// Estructura para almacenar los datos de las reservas
struct Reserva{
    int CI;
    char nombreCliente[50];
    char fecha[11];
};

// Estructura para almacenar los datos de las finanzas
struct Finanzas{
    long double totalVentas = 0.0, gastosIngredientes = 0.0;
};

// Estrcutura para almacenar datos de fechas
struct Date {
    int day, month, year;
};

// Datos de los usuarios y contraseñas del gerente y el cajero
const char* GERENTE_USUARIO = "gerente";
const char* GERENTE_CONTRASENA = "54321";
const char* CAJERO_USUARIO = "cajero";
const char* CAJERO_CONTRASENA = "12345";

// Nombres de los archivos utilizados
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


// Funciones
void pantallaAcceso();

void menuGerente();
void menuCajero();

Empleado nuevoEmpleado(int, int);
Cliente nuevoCliente(int, int);
Plato nuevoPlato(int);
Reserva nuevaReserva(int, int);

void escribirArchivo(Empleado);
void escribirArchivo(Cliente);
void escribirArchivo(Plato);
void escribirArchivo(Factura);
void escribirArchivo(Reserva);

void eliminarDeArchivo(const char*, int, char[11]);
void modificarArchivo(int, Empleado);
void modificarArchivo(int, Cliente);
void modificarArchivo(int, Plato);
void modificarArchivo(int, char[11], Reserva);
void mostrar(const char*, int);

void gestionarEmpleados();
void gestionarClientes();
void gestionarMenu();
void IngredienteNuevo();
void AgregarReceta (int, int);
void AniadirIngredientesReceta(int);
void gestionarIngredientes();
void gestionarReservas(int);

bool verificarEmpleado(int);
bool verificarCodigo(int);
bool verificarCliente(int);
bool verificarIngrediente(int);
bool verificarReserva(int, const char*);
bool isLeapYear(int);
bool validateDate(const string&);

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


int main() {
    setlocale(LC_ALL, "");
    pantallaAcceso();
    return 0;
}

// Pantalla inical, donde el usuario podrá iniciar sesión o ingresar como cliente y ver el menú
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
                    menuCliente(0);
                    cout << "\n\n[1] Volver\t[2] Salir\n\n--> ";
                    cin >> seleccion;

                    if(seleccion == "1"){
                        pantallaAcceso();
                    }
                    else{
                        cout << "\n>> Saliendo del sistema." << endl;
                        exit(0);
                    }
                }
                else{
                    cout << "\n>> Usuario o contraseña incorrectos. Vuelva a intentar." << endl << endl;
                    system("pause");
                }
            }
        }
        
    }
    else if(seleccion == "2"){
        menuCliente(0);
        cout << "\n\n[1] Volver\t[2] Salir\n\n--> ";
        cin >> seleccion;

        if(seleccion == "1"){
            pantallaAcceso();
        }
        else{
            cout << "\n>> Saliendo del sistema." << endl;
            exit(0);
        }
    }
    else{
        cout << "\n>> Saliendo del sistema." << endl;
        exit(0);
    }
    
}

// Menú de opciones del gerente
void menuGerente() {
    while (true) {
        system("cls");
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
                cout << endl;
                system("pause");
                break;
            }
                break;
            case 7:
                gestionarFinanzas();   
                break;
            case 8:
                pantallaAcceso();
            default:
                cout << "\n>> Intente de nuevo." << endl << endl;
                system("pause");
        }
    }
}

// Permite ingresar la información de un empleado 
Empleado nuevoEmpleado(int x, int ci = 0){
    Empleado e;
    if(x == 0){
        cout << "\n\t- Ingrese el CI del empleado: ";
        e.CI = obtenerEnteroDesdeEntrada();
        cout << "\t- Ingrese el nombre del empleado: ";
        cin.ignore(256, '\n');
        cin.getline(e.nombre, 50);
        cout << "\t- Ingrese el puesto del empleado: ";
        cin.getline(e.puesto, 30);
        cout << "\t- Ingrese el sueldo del empleado: ";
        e.sueldo = obtenerDoubleDesdeEntrada();
    }
    else if(x == 1){
        e.CI = ci;
        cout << "\t- Ingrese el nombre del empleado: ";
        cin.ignore(256, '\n');
        cin.getline(e.nombre, 50);
        cout << "\t- Ingrese el puesto del empleado: ";
        cin.getline(e.puesto, 30);
        cout << "\t- Ingrese el sueldo del empleado: ";
        e.sueldo = obtenerDoubleDesdeEntrada();
    }
    
    return e;
}

// Permite ingresar la información de un cliente
Cliente nuevoCliente(int x, int ci = 0){
    Cliente c;
    if(x == 0){
        cout << "\n\t- Ingrese el CI del cliente: ";
        c.CI = obtenerEnteroDesdeEntrada();
        cout << "\t- Ingrese el nombre del cliente: ";
        cin.ignore(256, '\n');
        cin.getline(c.nombre, 50);
    }else if(x == 1){
        c.CI = ci;
        cout << "\t- Ingrese el nombre del cliente: ";
        cin.ignore(256, '\n');
        cin.getline(c.nombre, 50);
    }

    return c;
}

// Permite ingresar la información de un plato
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

// Escribe los datos de un empleado en el archivo de empleados
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

// Escribe los datos de un cliente en el archivo de clientes
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

// Escribe los datos de un platos en el archivo del menú
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

// Escribe los datos de un facturas en el archivo de facturas
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

// Escribe los datos de un reservas en el archivo de reservas
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

// Elimina los datos seleccionados del archivo seleccionado
void eliminarDeArchivo(const char* archivo, int x, char fecha[11] = {}){
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
            if(x != r.CI || strcmp(fecha, r.fecha) != 0){
                escritura.write((char*)&r, sizeof(Reserva));
            }
        }
    }

    lectura.close();
    escritura.close();

    remove(archivo);
    rename(ARCHIVO_TEMPORAL, archivo);
}

// Modifica los datos de un empleado del archivo de empleados
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

// Modifica los datos de un cliente del archivo de clientes
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

// Modifica los datos de un plato del archivo del menú
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

// Modifica los datos de una factura  del archivo de reservas
void modificarArchivo(int x, char fecha[11], Reserva reserva){
    ifstream lectura;
    lectura.open(ARCHIVO_RESERVA, ios::binary);

    ofstream escritura;
    escritura.open(ARCHIVO_TEMPORAL, ios::binary);

    Reserva r;

    while(lectura.read((char*)&r, sizeof(Reserva))){
        if(x == r.CI && strcmp(fecha, r.fecha) == 0){
            escritura.write((char*)&reserva, sizeof(Reserva));
        }
        else{
            escritura.write((char*)&r, sizeof(Reserva));
        }
    }

    lectura.close();
    escritura.close();

    remove(ARCHIVO_RESERVA);
    rename(ARCHIVO_TEMPORAL, ARCHIVO_RESERVA);
}

// Muestra los datos de un archivo seleccionado
void mostrar(const char* archivo, int ci = 0){
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
            if(ci == 0){
                Reserva r;
                cout << "\n--> Lista de reservas:" << endl;
                while(lectura.read((char*)&r, sizeof(Reserva))){
                    cout << "\n\tCarnet de identidad: " << r.CI << endl;
                    cout << "\tNombre: " << r.nombreCliente << endl;
                    cout << "\tFecha: " << r.fecha << endl;
                }
            }else{
                Reserva r;
                cout << "\n--> Lista de reservas para el cliente con el CI " << ci << ":" << endl;
                while(lectura.read((char*)&r, sizeof(Reserva))){
                    if(ci == r.CI){
                        cout << "\n\tCarnet de identidad: " << r.CI << endl;
                        cout << "\tNombre: " << r.nombreCliente << endl;
                        cout << "\tFecha: " << r.fecha << endl;
                    }
                }
            }
            
        }
    }
    else{
        cout << "\n>> No se pudo abrir el archivo " << archivo << "." << endl;
    }

    lectura.close();
}

// Le permite al gerente gestionar los empleados
void gestionarEmpleados() {
    do{
        system("cls");
        cout << "\nGESTION DE EMPLEADOS" << endl;
        cout << "====================" << endl;
        cout << "\n\t1. Añadir empleado." << endl;
        cout << "\t2. Eliminar empleado." << endl;
        cout << "\t3. Modificar empleado." << endl;
        cout << "\t4. Mostrar lista de empleados." << endl;
        cout << "\t5. Volver." << endl;

        int opcion;
        cout << "\n\t-->  ";
        opcion = obtenerEnteroDesdeEntrada();

        switch(opcion){
            Empleado e;
            bool flag;
            case 1:
            {
                cout << "\n\t- Ingrese el CI del empleado: ";
                e.CI = obtenerEnteroDesdeEntrada();
                flag = verificarEmpleado(e.CI);
                if(!flag){
                    escribirArchivo(nuevoEmpleado(1, e.CI));
                    cout << "\n>> Se ha añadido al empleado." << endl << endl;
                }
                else{
                    cout << "\n>> El empleado con el CI " << e.CI << " ya ha sido registrado." << endl << endl;
                }
                
                system("pause");
                break;
            }
            case 2:
            {
                cout << "\nIngrese el CI del empleado a eliminar: ";
                e.CI = obtenerEnteroDesdeEntrada();
                flag = verificarEmpleado(e.CI);
                if(flag){
                    eliminarDeArchivo(ARCHIVO_EMPLEADOS, e.CI);
                    cout << "\n>> Se ha eliminado al empleado." << endl << endl;
                }
                else{
                    cout << "\n>> El empleado con el CI " << e.CI << " no ha sido registrado." << endl << endl;
                }
                
                system("pause");
                break;
            }
            case 3:
            {
                cout << "\nIngrese el CI del empleado a modificar: ";
                e.CI = obtenerEnteroDesdeEntrada();
                flag = verificarEmpleado(e.CI);
                if(flag){
                    modificarArchivo(e.CI, nuevoEmpleado(0));
                    cout << "\n>> Se ha modificado al empleado." << endl << endl;
                }
                else{
                    cout << "\n>> El empleado con el CI " << e.CI << " no ha sido registrado." << endl << endl;
                }
                
                system("pause");
                break;
            }
            case 4:
            {
                mostrar(ARCHIVO_EMPLEADOS);
                cout << endl << endl;
                system("pause");
                break;
            }
            case 5:
                menuGerente();
            default:
                cout << "\n>> Intente de nuevo." << endl << endl;
                system("pause");
        }  
    }
    while(true);
}

// Le permite al gerente gestionar los clientes
void gestionarClientes() {
    do{
        system("cls");
        cout << "\nGESTION DE CLIENTES" << endl;
        cout << "====================" << endl;
        cout << "\n\t1. Añadir cliente." << endl;
        cout << "\t2. Eliminar cliente." << endl;
        cout << "\t3. Modificar cliente." << endl;
        cout << "\t4. Mostrar lista de clientes." << endl;
        cout << "\t5. Volver." << endl;

        int opcion;
        cout << "\n\t-->  ";
        opcion = obtenerEnteroDesdeEntrada();

        switch(opcion){
            Cliente c;
            bool flag;
            case 1:
            {
                cout << "\n\t- Ingrese el CI del cliente: ";
                c.CI = obtenerEnteroDesdeEntrada();
                flag =  verificarCliente(c.CI);
                if(!flag){
                    escribirArchivo(nuevoCliente(1, c.CI));
                    cout << "\n>> Se ha añadido al cliente" << endl << endl;
                }
                else{
                    cout << "\n>> El cliente con el CI " << c.CI << " ya ha sido registrado." << endl << endl;
                }
                
                system("pause");
                break;
            }
            case 2:
            {
                cout << "\nIngrese el CI del cliente a eliminar: ";
                c.CI = obtenerEnteroDesdeEntrada();
                flag =  verificarCliente(c.CI);
                if(flag){
                    eliminarDeArchivo(ARCHIVO_CLIENTES, c.CI);
                    cout << "\n>> Se ha eliminado al cliente." << endl << endl;
                }
                else{
                    cout << "\n>> El cliente con el CI " << c.CI << " no ha sido registrado." << endl << endl;
                }
                
                system("pause");
                break;
            }
            case 3:
            {
                cout << "\nIngrese el CI del cliente a modificar: ";
                c.CI = obtenerEnteroDesdeEntrada();
                flag =  verificarCliente(c.CI);
                if(flag){
                    modificarArchivo(c.CI, nuevoCliente(0));
                    cout << "\n>> Se ha modificado al cliente." << endl << endl;
                }
                else{
                    cout << "\n>> El cliente con el CI " << c.CI << " no ha sido registrado." << endl << endl;
                }
                
                system("pause");
                break;
            }
            case 4:
                mostrar(ARCHIVO_CLIENTES);
                cout << endl << endl;
                system("pause");
                break;
            case 5:
                menuGerente();
            default:
                cout << "\n>> Intente de nuevo." << endl << endl;
                system("pause");
        }  
    }
    while(true);
}

// Le permite al gerente gestionar el menú
void gestionarMenu() {
    do{
        system("cls");
        cout << "\nGESTION DEL MENU" << endl;
        cout << "=================" << endl;
        cout << "\n\t1. Añadir plato." << endl;
        cout << "\t2. Eliminar plato." << endl;
        cout << "\t3. Modificar plato." << endl;
        cout << "\t4. Mostrar lista de platos." << endl;
        cout << "\t5. Volver." << endl;

        int opcion;
        cout << "\n\t-->  ";
        opcion = obtenerEnteroDesdeEntrada();

        switch(opcion){
            Plato p;
            bool flag;
            case 1:
                escribirArchivo(nuevoPlato(-1));
                cout << "\n>> Se ha añadido el plato." << endl << endl;
                system("pause");
                break;
            case 2:
                cout << "\n\t- Ingrese el codigo del plato a eliminar: ";
                p.codigo = obtenerEnteroDesdeEntrada();
                flag =  verificarCodigo(p.codigo);
                if(flag){
                    eliminarDeArchivo(ARCHIVO_MENU, p.codigo);
                    cout << "\n>> Se ha eliminado el plato." << endl << endl;
                }
                else{
                    cout << "\n>> El plato con el código " << p.codigo << " no ha sido registrado." << endl << endl;
                }
                
                system("pause");
                break;
            case 3:
                cout << "\n\t- Ingrese el codigo del plato a modificar: ";
                p.codigo = obtenerEnteroDesdeEntrada();
                flag =  verificarCodigo(p.codigo);
                if(flag){
                    modificarArchivo(p.codigo, nuevoPlato(p.codigo));
                    cout << "\n>> Se ha modificado el plato." << endl << endl;
                }
                else{
                    cout << "\n>> El plato con el código " << p.codigo << " no ha sido registrado." << endl << endl;
                }
                
                system("pause");
                break;
            case 4:
                mostrar(ARCHIVO_MENU);
                cout << endl << endl;
                system("pause");
                break;
            case 5:
                menuGerente();
            default:
                cout << "\n>> Intente de nuevo." << endl << endl;
                system("pause");
        }  
    }
    while(true);
}

// Muestra los ingredientes del inventario y los almacena en un vector
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

// Ingresa los ingredientes de la receta de un plato
void AniadirIngredientesReceta(int codigoPlato)
{
    int opcion;
    cout<<"\nAÑADIR INGREDIENTES A LA RECETA"<<endl;
    cout<<"==================================="<<endl;
    cout<<"\n\t1. Ingrediente existente."<<endl;
    cout<<"\t2. Ingrediente nuevo."<<endl;
    cout<<"\t3. Volver."<<endl;
    opcion = obtenerEnteroDesdeEntrada();
    switch (opcion){
        case 1:{
            vector<Ingredientes> ingre = MostrarIngreDientes();
            int codigoing = -1;
            while(codigoing != 0){
                cout<<"\n- Ingrese el codigo del ingrediente a agregar al platillo (0 para salir): ";
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
            cout<<"\n>> Intente de nuevo."<<endl;
    }
}

// Permite añadir un ingrediente nuevo al inventario
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

// Escribe la receta de un plato en el archivo de recetas
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

// Le permite al gerente gestionar los ingredientes del inventario
void gestionarIngredientes()
{
    do{
        system("cls");
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

                cout << "\n\t- Ingrese el codigo de que ingrediente desea hacer el pedido: ";
                int codigoing;
                codigoing = obtenerEnteroDesdeEntrada();
                bool flag = verificarIngrediente(codigoing);
                
                if(flag){
                    cout << "\n\t- Ingrese de cuantos ingredientes sera el pedido: ";
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
                }
                else{
                    cout << "\n>> El plato con el código " << codigoing << " no ha sido registrado." << endl << endl;
                }
                cout << endl;
                system("pause");
                break;
            }
            case 2:
            {
                IngredienteNuevo();
                cout << "\n>> Se ha añadido el nuevo ingrediente." << endl << endl;
                system("pause");
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
                cout << endl;
                system("pause");
                break;
            }
            case 4:
                menuGerente();
            default:
                cout << "\n>> Intente de nuevo." << endl << endl;
                system("pause");
            break;
        }
    }
    while(true);
}

// Le permite al gerente gestionar las reservas
void gestionarReservas(int x){
    do{
        system("cls");
        cout << "\nGESTION DE RESERVAS" << endl;
        cout << "===================" << endl;
        cout << "\n\t1. Añadir reserva." << endl;
        cout << "\t2. Eliminar reserva." << endl;
        cout << "\t3. Modificar reserva." << endl;
        cout << "\t4. Mostrar lista de reservas." << endl;
        cout << "\t5. Volver." << endl;

        int opcion;
        cout << "\n\t--> ";
        opcion = obtenerEnteroDesdeEntrada();

        switch(opcion){
            Reserva r;
            bool flag;
            case 1:
                escribirArchivo(nuevaReserva(0, 0));
                cout << "\n>> Se ha añadido la reserva." << endl << endl;
                system("pause");
                break;
            case 2:
            {
                cout << "\nIngrese el CI de la reserva del cliente a eliminar: ";
                r.CI = obtenerEnteroDesdeEntrada();
                flag = verificarReserva(r.CI, ARCHIVO_RESERVA);
                if(flag){
                    mostrar(ARCHIVO_RESERVA, r.CI);
                    cin.ignore(256, '\n');
                    do{
                        cout << "\n\t- Ingrese la fecha de la reserva a eliminar (dd/mm/yyyy): ";
                        cin.getline(r.fecha, 11);
                        flag = verificarReserva(r.CI, r.fecha);
                        if(flag){
                            eliminarDeArchivo(ARCHIVO_RESERVA, r.CI, r.fecha);
                            cout << "\n>> Se ha eliminado la reserva." << endl << endl;
                            break;
                        }else{
                            cout << "\n>> El cliente no tiene una reserva en la fecha ingresada." << endl;
                        }
                    }while(!flag);
                }else{
                    cout << "El cliente con el CI " << r.CI << " no tiene reservas." << endl << endl;
                }
                
                system("pause");
                break;
            }
            case 3:
            {
                cout << "\nIngrese el CI de la reserva del cliente a modificar: ";
                r.CI = obtenerEnteroDesdeEntrada();
                flag = verificarReserva(r.CI, ARCHIVO_RESERVA);
                if(flag){
                    mostrar(ARCHIVO_RESERVA, r.CI);
                    cout << "\n\t- Ingrese la fecha de la reserva a modificar (dd/mm/yyyy): ";
                    cin.ignore(256, '\n');
                    cin.getline(r.fecha, 11);
                    flag = verificarReserva(r.CI, r.fecha);
                    if(flag){
                        modificarArchivo(r.CI, r.fecha, nuevaReserva(0, 0));
                        cout << "\n>> Se ha modificado la reserva." << endl << endl;
                    }else{
                        cout << "\n>> El cliente no tiene una reserva en la fecha ingresada." << endl << endl;
                    }
                }else{
                    cout << "El cliente con el CI " << r.CI << " no tiene reservas." << endl << endl;
                }
                
                system("pause");
                break;
            }
            case 4:
                mostrar(ARCHIVO_RESERVA);
                cout << endl << endl;
                system("pause");
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
                cout << "\n>> Intente de nuevo." << endl << endl;
                system("pause");
        }  
    }
    while(true);
}

// Devuelve la estructura del cliente a partir de su carnet de identidad
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

// Verifica si el empleado ha sido registrado en el archivo de empleados
bool verificarEmpleado(int ci){
    ifstream lectura;
    lectura.open(ARCHIVO_EMPLEADOS, ios::binary);

    Empleado e;

    while(lectura.read((char*)&e, sizeof(Empleado))){
        if(ci == e.CI){
            lectura.close();
            return true;
        }
    }
    lectura.close();
    return false;
}

// Verifica si el cliente ha sido registrado en el archivo de clientes
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

// Verifica si el codigo de un plato ha sido registrado en el menú
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

// Verifica si el codigo de un ingrediente ha sido registrado en el archivo de ingredientes
bool verificarIngrediente(int codigo){
    ifstream lectura;
    lectura.open(ARCHIVO_INGREDIENTES, ios::binary);

    Ingredientes i;
    while(lectura.read((char*)&i, sizeof(Ingredientes))){
        if(codigo == i.codigoIngrediente){
            lectura.close();
            return true;
        }
    }
    lectura.close();
    return false;
}

// Verifica si el codigo de un ingrediente ha sido registrado en el archivo de ingredientes
bool verificarReserva(int ci, const char* fecha = ARCHIVO_RESERVA){
    ifstream lectura;
    lectura.open(ARCHIVO_RESERVA, ios::binary);

    Reserva r;
    if(fecha == ARCHIVO_RESERVA){
        while(lectura.read((char*)&r, sizeof(Reserva))){
            if(ci == r.CI){
                lectura.close();
                return true;
            }
        }
    }else{
        while(lectura.read((char*)&r, sizeof(Reserva))){
            if(ci == r.CI && strcmp(fecha, r.fecha) == 0){
                lectura.close();
                return true;
            }
        }
    }
    
    lectura.close();
    return false;
}

// Verifica si el año es bisiesto
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Valida la fecha
bool validateDate(const string& a) {
    Date date;

    istringstream b(a);
    char d;

    b >> date.day >> d >> date.month >> d >> date.year;

    if (b.fail() || b.bad()) {
        cout << "\n>> Formato no valido." << endl << endl;
        return false;
    }

    int daysInMonth;

    if (date.month < 1 || date.month > 12) {
        cout << "\n>> Mes no valido" << endl << endl;
        return false;
    }

    switch (date.month) {
        case 2:
            daysInMonth = isLeapYear(date.year) ? 29 : 28;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            daysInMonth = 30;
            break;
        default:
            daysInMonth = 31;
            break;
    }

    if (date.day < 1 || date.day > daysInMonth) {
        cout << "\n>> Dia no valido para el mes ingresado" << endl << endl;
        return false;
    }

    return true;
}

// Devuelve la estructura de un plato a partir de su código
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

// Actualiza el inventario de ingrediente de acuerdo a un plato vendido
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

// Calcula el total de una venta
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

// Llena los datos necesarios de una factura
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

// Le permite al gerente visualizar las finanzas de la tienda
void gestionarFinanzas() {
    system("cls");
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
    cout << "\tSaldo final: " << saldoFinal << " BOB." << endl << endl;

    system("pause");
}

// Imprime en consola una factura
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

// Llena los datos de una reserva
Reserva nuevaReserva(int x, int ci = 0){
    Reserva r;
    bool flag1, flag2;
    if(x == 0){
        cout << "\n\t- Ingrese el CI del cliente: ";
        r.CI = obtenerEnteroDesdeEntrada();

        bool bandera = verificarCliente(r.CI);
        
        if(bandera){
            cout << "\n>> El cliente ya ha sido registrado. Autocompletando informacion." << endl << endl;
            Cliente c = nombreCliente(r.CI);
            strcpy(r.nombreCliente, c.nombre);
        }
        else{
            cout << "\t- Ingrese el nombre del cliente: ";
            cin.ignore(256, '\n');
            cin.getline(r.nombreCliente, 50);

            Cliente c;
            c.CI = r.CI;
            strcpy(c.nombre, r.nombreCliente);
            escribirArchivo(c);
        }

        cin.ignore(256, '\n');
        do{
            cout << "\t- Ingrese la fecha de la reserva (dd/mm/yyyy): ";
            cin.getline(r.fecha, 11);
            flag1 = validateDate(r.fecha);
            if(flag1){
                flag2 = verificarReserva(r.CI, r.fecha);
                if(flag2){
                    cout << "\n>> El cliente ya tiene una reserva en la fecha ingresada." << endl << endl;
                }
            }
        }
        while(flag2);

    }else if(x == 1){
        r.CI = ci;

        bool bandera = verificarCliente(r.CI);
        
        if(bandera){
            cout << "\n>> El cliente ya ha sido registrado. Autocompletando informacion." << endl << endl;
            Cliente c = nombreCliente(r.CI);
            strcpy(r.nombreCliente, c.nombre);
        }
        else{
            cout << "\t- Ingrese el nombre del cliente: ";
            cin.ignore(256, '\n');
            cin.getline(r.nombreCliente, 50);

            Cliente c;
            c.CI = r.CI;
            strcpy(c.nombre, r.nombreCliente);
            escribirArchivo(c);
        }
        
        cin.ignore(256, '\n');
        do{
            cout << "\t- Ingrese la fecha de la reserva (dd/mm/yyyy): ";
            cin.getline(r.fecha, 11);
            flag1 = validateDate(r.fecha);
            if(flag1){
                flag2 = verificarReserva(r.CI, r.fecha);
                if(flag2){
                    cout << "\n>> El cliente ya tiene una reserva en la fecha ingresada." << endl << endl;
                }
            }else{
                cout << "\n>> Formato de fecha inválido." << endl << endl;
            }
        }
        while(flag2);
    }
    
    return r;
}

// Menú de opciones del cajero
void menuCajero(){
    while (true) {
        system("cls");
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
                cout << endl;
                system("pause");
                break;
            case 2:
            {
                menuCliente(1);
                Factura f = nuevaFactura();
                escribirArchivo(f);
                cout << "\n>> Factura generada correctamente." << endl;
                imprimirFactura(f);
                cout << endl;
                system("pause");
                break;
            }
            case 3:
                gestionarReservas(1);
            case 4:
                pantallaAcceso();
            default:
                cout << "\n>> Intente de nuevo." << endl << endl;
                system("pause");
        }
    }
}

// Despliega el menú
void menuCliente(int x){
    system("cls");
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

// Verifica la entrada de valores enteros
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
            cout << "\n>> Error. Por favor, ingresa un valor entero válido." << endl;
            cout << "\n\t--> ";
        }
    }
return entero;
}

// Verifica la entrada de valores double
double obtenerDoubleDesdeEntrada() 
{
    string entrada;
    double valorDouble;
    while (true) {
        cin >> entrada;
        istringstream iss(entrada);
        if (iss >> valorDouble && iss.eof()) {
            break;
        } else {
            cerr << "\n>> Error. Por favor, ingresa un valor double válido." << endl;
            cout << "\n\t--> ";
        }
    }
    return valorDouble;
}