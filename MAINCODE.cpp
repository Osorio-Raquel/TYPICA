#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <cstring>

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
    string nombre;
};

struct Plato {
    int codigo;
    string nombre;
    double precio;
};

struct Factura {
    int CI;
    string nombreCliente;
    vector<Plato> platos;
    double total;
    double dineroRecibido;
    double cambio;
    string fecha;
};

const char* GERENTE_USUARIO = "gerente";
const char* GERENTE_CONTRASENA = "54321";
const char* CAJERO_USUARIO = "cajero";
const char* CAJERO_CONTRASENA = "12345";
const char* ARCHIVO_EMPLEADOS = "empleados.bin";
const char* ARCHIVO_CLIENTES = "clientes.bin";
const char* ARCHIVO_MENU = "menu.bin";
const char* ARCHIVO_FACTURA = "factura.bin";
const char* ARCHIVO_FINANZAS = "finanzas.bin";

const char* ARCHIVO_TEMPORAL = "temporal.bin";

const double IMPUESTO = 0.13;


// funciones
void inicializarArchivos();
void pantallaAcceso();

void menuGerente();
void menuCajero();

Empleado nuevoEmpleado();
Cliente nuevoCliente();
Plato nuevoPlato();
Factura nuevaFactura();

void escribirArchivo(Empleado);
void escribirArchivo(Cliente);
void escribirArchivo(Plato);
void escribirArchivo(Factura);

void eliminarDeArchivo(const char*, int);
void modificarArchivo(int, Empleado);
void mostrar(const char*);

void gestionarEmpleados();
void gestionarClientes();
void gestionarMenu();
void generarFactura();
void gestionarFinanzas();

void menuCliente();

// Función principal la bonita aaaaaaaaaaaaaaaaaaa
int main() {
    //inicializarArchivos();
    pantallaAcceso();
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
    string usuario, contrasena;

    for(int i = 0; i < 3; i++){
        system("cls");
        cout << "\nBIENVENIDO A TYPICA!" << endl;
        cout << "=====================" << endl;
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
        } else if (usuario == "0" && contrasena == "0"){
            menuCliente();
            break;
        }
        else {
            if(i + 1 == 3){
                cout << "\n>> Ha ingresado como cliente." << endl << endl;
                system("pause");
                menuCliente();
            }
            else{
                cout << "\n>> Acceso no autorizado. Vuelva a intentar." << endl << endl;
                system("pause");
            }
        }
    }
    
}

void menuGerente() {
    while (true) {
        cout << "\nMENU GERENTE" << endl;
        cout << "=============" << endl;
        cout << "\n\t1. Gestionar empleados." << endl;
        cout << "\t2. Gestionar clientes." << endl;
        cout << "\t3. Gestionar menu." << endl;
        cout << "\t4. Generar factura." << endl;
        cout << "\t5. Gestionar finanzas." << endl;
        cout << "\t6. Salir." << endl;

        int opcion;
        cout << "\n\tSeleccione una opcion: ";
        cin >> opcion;

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
                generarFactura();
                break;
            case 5:
                gestionarFinanzas();
                break;
            case 6:
                exit(0);
            default:
                cout << "\n>> Intente de nuevo." << endl;
        }
    }
}

Empleado nuevoEmpleado(){
    Empleado e;
    cout << "\n\tIngrese el CI del empleado: ";
    cin >> e.CI;
    cout << "\tIngrese el nombre del empleado: ";
    cin.ignore(256, '\n');
    cin.getline(e.nombre, 50);
    cout << "\tIngrese el puesto del empleado: ";
    cin.getline(e.puesto, 30);
    cout << "\tIngrese el sueldo del empleado: ";
    cin >> e.sueldo;

    return e;
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

Cliente nuevoCliente(){
    Cliente c;
    cout << "\tIngrese el CI del cliente: ";
    cin >> c.CI;
    cout << "\n\tIngrese el nombre del cliente: ";
    getline(cin, c.nombre);

    return c;
}

void escribirArchivo(Cliente c){
    ofstream escritura;
    escritura.open(ARCHIVO_EMPLEADOS, ios::binary | ios::app);
    if(escritura.good()){
        escritura.write((char*)&c, sizeof(Cliente));
    }
    else{
        cout << "\n>> No se pudo abrir el archivo de empleados." << endl;
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

void mostrar(const char* archivo){
    cout << "\n--> Lista de empleados:" << endl;

    ifstream lectura;
    lectura.open(archivo, ios::binary);
    
    if(lectura.good()){
        if(archivo == ARCHIVO_EMPLEADOS){
            Empleado e;
            while(lectura.read((char*)&e, sizeof(Empleado))){
                cout << "\n\tCarnet de Identidad: " << e.CI << endl;
                cout << "\tNombre: " << e.nombre << endl;
                cout << "\tPuesto: " << e.puesto << endl;
                cout << "\tSueldo: " << e.sueldo << " BOB al mes." << endl;
            }
        }else if(archivo == ARCHIVO_CLIENTES){
            Cliente c;
            while(lectura.read((char*)&c, sizeof(Cliente))){
                cout << "\n\tCarnet de Identidad: " << c.CI << endl;
                cout << "\tNombre: " << c.nombre << endl;
            }
        }
    }
    else{
        cout << "\n>> No se pudo abrir el archivo de empleados." << endl;
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
        cout << "\t5. Volver al menu principal." << endl;

        int opcion;
        cout << "\n\tSeleccione una opcion: ";
        cin >> opcion;

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
    fstream archivoClientes(ARCHIVO_CLIENTES, ios::in | ios::out | ios::binary);

    if (!archivoClientes) {
        cerr << "Error" << endl;
        return;
    }

    vector<Cliente> clientes;

    while (!archivoClientes.eof()) {
        Cliente cliente;
        archivoClientes.read(reinterpret_cast<char*>(&cliente), sizeof(Cliente));
        if (!archivoClientes.eof()) {
            clientes.push_back(cliente);
        }
    }

    cout << "\nLista de clientes:" << endl;
    for (const auto& cliente : clientes) {
        cout << "CI: " << cliente.CI << ", Nombre: " << cliente.nombre << endl;
    }

    archivoClientes.close();
}

void gestionarMenu() {

    fstream archivoMenu(ARCHIVO_MENU, ios::in | ios::out | ios::binary);

    if (!archivoMenu) {
        cerr << "Error al abrir el archivo de menú." << endl;
        return;
    }

    vector<Plato> menu;

    while (!archivoMenu.eof()) {
        Plato plato;
        archivoMenu.read(reinterpret_cast<char*>(&plato), sizeof(Plato));
        if (!archivoMenu.eof()) {
            menu.push_back(plato);
        }
    }

    cout << "\nMenú del restaurante:" << endl;
    for (const auto& plato : menu) {
        cout << "COdigo: " << plato.codigo << ", Nombre: " << plato.nombre << ", Precio: " << plato.precio << " BOB" << endl;
    }

    // añadir o eliminar platos
    cout << "\n1. Añadir plato" << endl;
    cout << "2. Eliminar plato" << endl;
    cout << "3. Volver al menú principal" << endl;

    int opcion;
    cout << "Seleccione una opcion: ";
    cin >> opcion;

    switch (opcion) {
        case 1: {
            Plato nuevoPlato;
            cout << "Ingrese el nombre del nuevo plato: ";
            cin >> nuevoPlato.nombre;
            cout << "Ingrese el precio del nuevo plato: ";
            cin >> nuevoPlato.precio;

            // Asignar un codigo unicop
            if (!menu.empty()) {
                nuevoPlato.codigo = menu.back().codigo + 1;
            } else {
                nuevoPlato.codigo = 1;
            }

            menu.push_back(nuevoPlato);

            // Guardar platos en el archivo
            archivoMenu.seekp(0, ios::end);
            archivoMenu.write(reinterpret_cast<char*>(&nuevoPlato), sizeof(Plato));

            cout << "Plato añadido correctamente." << endl;
            break;
        }
        case 2: {
            int codigo;
            cout << "Ingrese el código del plato a eliminar: ";
            cin >> codigo;

             bool encontrado = false;

            for (auto it = menu.begin(); it != menu.end(); ++it) {
                if (it->codigo == codigo) {
                // Eliminar
                menu.erase(it);

                // Sobrescribir
                archivoMenu.close();
                archivoMenu.open(ARCHIVO_MENU, ios::out | ios::binary);
                for (const auto& plato : menu) {
                    archivoMenu.write(reinterpret_cast<const char*>(&plato), sizeof(Plato));
                    }

                cout << "Plato eliminado correctamente" << endl;
                encontrado = true;
                break;
                }
            }

            if (!encontrado) {
                cout << "no valido" << endl;
                }
            break;
        }

        case 3:
            break;
        default:
            cout << "Opción no valida" << endl;
    }

    archivoMenu.close();
}

void generarFactura() {
    // AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
}

void gestionarFinanzas() {

    fstream archivoFinanzas(ARCHIVO_FINANZAS, ios::in | ios::out | ios::binary);

    if (!archivoFinanzas) {
        cerr << "Error al abrir el archivo de finanzas." << endl;
        return;
    }


    double totalVentas = 0.0;
    archivoFinanzas.read(reinterpret_cast<char*>(&totalVentas), sizeof(double));

    double descuentos = totalVentas * IMPUESTO;

    double saldoFinal = totalVentas - descuentos;
    //añadir sacar los salarios para pagarlos

    cout << "\nResumen financiero:" << endl;
    cout << fixed << setprecision(2);
    cout << "Total de ventas: " << totalVentas << " BOB" << endl;
    cout << "Descuentos (13% de impuestos): " << descuentos << " BOB" << endl;
    cout << "Saldo final: " << saldoFinal << " BOB" << endl;

    archivoFinanzas.close();
}

void menuCajero() {
    ifstream archivoMenu(ARCHIVO_MENU, ios::binary);

    if (!archivoMenu) {
        cerr << "Error al abrir el archivo de menú." << endl;
        return;
    }
    vector<Plato> menu;
    while (!archivoMenu.eof()) {
        Plato plato;
        archivoMenu.read(reinterpret_cast<char*>(&plato), sizeof(Plato));
        if (!archivoMenu.eof()) {
            menu.push_back(plato);
        }
    }
    archivoMenu.close();

    cout << "\nMenú del restaurante:" << endl;
    for (const auto& plato : menu) {
        cout << "Código: " << plato.codigo << ", Nombre: " << plato.nombre << ", Precio: " << plato.precio << " BOB" << endl;
    }

    fstream archivoFactura(ARCHIVO_FACTURA, ios::in | ios::out | ios::binary);

    if (!archivoFactura) {
        cerr << "Error al abrir el archivo de factura." << endl;
        return;
    }

    Factura nuevaFactura;
    cout << "\nIngrese el CI del cliente: ";
    cin >> nuevaFactura.CI;

    ifstream archivoClientes(ARCHIVO_CLIENTES, ios::binary);
    vector<Cliente> clientes;

    Cliente cliente;
    while (archivoClientes.read(reinterpret_cast<char*>(&cliente), sizeof(Cliente))) {
        clientes.push_back(cliente);
    }
    archivoClientes.close();

    // Buscar al cliente
    bool clienteEncontrado = false;
    for (const auto& cliente : clientes) {
        if (cliente.CI == nuevaFactura.CI) {
            // si encuentra no
            nuevaFactura.nombreCliente = cliente.nombre;
            clienteEncontrado = true;
            break;
        }
    }

    if (!clienteEncontrado) {
        cout << "Cliente no encontrado. Ingrese el nombre del cliente: ";
        cin >> nuevaFactura.nombreCliente;

        // Agregar nuevo cliente
        ofstream archivoClientesNuevo(ARCHIVO_CLIENTES, ios::app | ios::binary);
        Cliente nuevoCliente = {nuevaFactura.CI, nuevaFactura.nombreCliente};
        archivoClientesNuevo.write(reinterpret_cast<const char*>(&nuevoCliente), sizeof(Cliente));
        archivoClientesNuevo.close();
    }

    while (true) {
        int codigoPlato;
        cout << "Ingrese el código del plato (0 para finalizar): ";
        cin >> codigoPlato;

        if (codigoPlato == 0) {
            break;
        }

        bool platoEncontrado = false;
        for (const Plato& plato : menu) {
            if (plato.codigo == codigoPlato) {
                nuevaFactura.platos.push_back(plato);
                nuevaFactura.total += plato.precio;
                platoEncontrado = true;
                break;
            }
        }

        if (!platoEncontrado) {
            cout << "Plato no encontrado. Intente nuevamente." << endl;
        }
    }


    cout << "Total de la factura: " << nuevaFactura.total << " BOB" << endl;
    cout << "Ingrese el dinero recibido: ";
    cin >> nuevaFactura.dineroRecibido;

    // Calcular cambio
    nuevaFactura.cambio = nuevaFactura.dineroRecibido - nuevaFactura.total;

    // FECGA
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    stringstream fechaSS;
    fechaSS << now->tm_year + 1900 << '-' << now->tm_mon + 1 << '-' << now->tm_mday;
    nuevaFactura.fecha = fechaSS.str();

    archivoFactura.seekp(0, ios::end);
    archivoFactura.write(reinterpret_cast<char*>(&nuevaFactura), sizeof(Factura));

    cout << "\nFactura generada correctamente:" << endl;
    cout << "Fecha: " << nuevaFactura.fecha << endl;
    cout << "CI del cliente: " << nuevaFactura.CI << endl;
    cout << "Nombre del cliente: " << nuevaFactura.nombreCliente << endl;
    cout << "Platos pedidos:" << endl;
    for (const auto& plato : nuevaFactura.platos) {
        cout << "  - " << plato.nombre << ", Precio: " << plato.precio << " BOB" << endl;
    }
    cout << "Total: " << nuevaFactura.total << " BOB" << endl;
    cout << "Dinero recibido: " << nuevaFactura.dineroRecibido << " BOB" << endl;
    cout << "Cambio: " << nuevaFactura.cambio << " BOB" << endl;

    archivoFactura.close();
}

void menuCliente(){
    ifstream archivoMenu(ARCHIVO_MENU, ios::binary);

    Plato plato;
    cout << "\nMenú del restaurante:" << endl;

    while (archivoMenu.read(reinterpret_cast<char*>(&plato), sizeof(Plato))) {
        cout << "Código: " << plato.codigo << ", Nombre: " << plato.nombre << ", Precio: " << plato.precio << " BOB" << endl;
    }

    archivoMenu.close();
}

