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
    char nombre[50];
};

struct Plato {
    int codigo;
    char nombre[50];
    double precio;
};

struct Ingredientes {
    int codigoIngrediente;
    char nombre[50];
    int cantidad;
    double precio;
};
struct Factura {
    int CI;
    char nombreCliente[50];
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
const char* ARCHIVO_INGREDIENTES = "ingredientes.bin";
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
Cliente nuevoCliente(int);
Plato nuevoPlato();

void escribirArchivo(Empleado);
void escribirArchivo(Cliente);
void escribirArchivo(Plato);
void escribirArchivo(Factura);

void eliminarDeArchivo(const char*, int);
void modificarArchivo(int, Empleado);
void modificarArchivo(int, Cliente);
void modificarArchivo(int, Plato);
void mostrar(const char*);

void gestionarEmpleados();
void gestionarClientes();
void gestionarMenu();
void PedidoDeIngredientes();
void gestionarFacturas();

bool verificarCodigo(int);
Cliente nombreCliente(int);
Plato devolverPlato(int);
double calcularTotal(vector<Plato>);
Factura nuevaFactura();
void imprimirFactura(Factura);
void imprimirFacturas();
void gestionarFinanzas();

void menuCliente(int);

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
    string usuario, contrasena, seleccion;

    system("cls");
    cout << "\nBIENVENIDO A TYPICA!" << endl;
    cout << "=====================" << endl;
    cout << "\n[1] Iniciar sesion\t[2] Ver menu\n\n--> ";
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
    else{
        menuCliente(0);
        cout << "\n[1] Volver\t[2] Salir\n\n--> ";
        cin >> seleccion;

        if(seleccion == "1"){
            pantallaAcceso();
        }
        else{
            exit(0);
        }
    }
    
}

void menuGerente() {
    while (true) {
        cout << "\nMENU GERENTE" << endl;
        cout << "============" << endl;
        cout << "\n\t1. Gestionar empleados." << endl;
        cout << "\t2. Gestionar clientes." << endl;
        cout << "\t3. Gestionar menu." << endl;
        cout << "\t4. Gestionar facturas." << endl;
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
                PedidoDeIngredientes();
                break;
            case 5:
                gestionarFacturas();
                break;
            case 6:
                gestionarFinanzas();
                break;
            case 7:
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

Cliente nuevoCliente(){
    Cliente c;
    cout << "\n\tIngrese el CI del cliente: ";
    cin >> c.CI;
    cout << "\tIngrese el nombre del cliente: ";
    cin.ignore(256, '\n');
    cin.getline(c.nombre, 50);

    return c;
}

Cliente nuevoCliente(int ci){
    Cliente c;
    c.CI = ci;
    cout << "\tIngrese el nombre del cliente: ";
    cin.ignore(256, '\n');
    cin.getline(c.nombre, 50);

    return c;
}

Plato nuevoPlato(){
    Plato p;
    cout << "\n\tIngrese el codigo del plato: ";
    cin >> p.codigo;
    cout << "\tIngrese el nombre del plato: ";
    cin.ignore(256, '\n');
    cin.getline(p.nombre, 50);
    cout << "\tIngrese el precio del plato: ";
    cin >> p.precio;

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
    cout << "\nGESTION DE CLIENTES" << endl;
    cout << "====================" << endl;

    do{
        cout << "\n\t1. Añadir cliente." << endl;
        cout << "\t2. Eliminar cliente." << endl;
        cout << "\t3. Modificar cliente." << endl;
        cout << "\t4. Mostrar lista de clientes." << endl;
        cout << "\t5. Volver." << endl;

        int opcion;
        cout << "\n\tSeleccione una opcion: ";
        cin >> opcion;

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
        cout << "\n\tSeleccione una opcion: ";
        cin >> opcion;

        switch(opcion){
            int codigo;
            case 1:
                escribirArchivo(nuevoPlato());
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
                modificarArchivo(codigo, nuevoPlato());
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

void PedidoDeIngredientes()
{
    cout<<"\n1. Pedido de ingrediente antiguo"<<endl;
    cout<<"2. Pedido de ingrediente nuevo"<<endl;
    cout<<"3. Volver am menu principal"<<endl;
    int opcion;
    cout<<"Opcion a elegir: ";
    cin>>opcion;
    switch(opcion)
    {
        case 1:
        {
            ifstream archivo;
            archivo.open(ARCHIVO_INGREDIENTES, ios::binary);
            cout<<"Lista de ingredientes: "<<endl;
            Ingredientes ing;
            vector<Ingredientes> ingre;
            while(archivo.read((char*)&ing, sizeof(Ingredientes)))
            {
                cout << "Codigo: " << ing.codigoIngrediente << ", Nombre: " << ing.nombre <<" Cantidad: "<< ing.cantidad << ", Precio: " << ing.precio << " BOB" << endl;
                ingre.push_back(ing);
            }
            archivo.close();
            cout<<"Ingrese el codigo de que ingrediente desea hacer el pedido: ";
            int codigoing;
            cin>>codigoing;
            cout<<"Ingrese de cuantos ingredientes sera el pedido: ";
            int cantidad;
            cin>>cantidad;
            for(unsigned int i=0; i<ingre.size(); i++)
            {
                if(ingre[i].codigoIngrediente == codigoing)
                    ingre[i].cantidad += cantidad;
            }
            ofstream sobreescribir;
            sobreescribir.open(ARCHIVO_INGREDIENTES, ios::binary);
            for(unsigned int i=0; i<ingre.size(); i++)
            sobreescribir.write((char*)&ingre[i], sizeof(Ingredientes));
            sobreescribir.close();
            break;
        }
        case 2:
        {
            ifstream archivo;
            archivo.open(ARCHIVO_INGREDIENTES, ios::binary);
            cout<<"Lista de ingredientes: "<<endl;
            Ingredientes ing;
            vector<Ingredientes> ingre;
            while(archivo.read((char*)&ing, sizeof(Ingredientes)))
                ingre.push_back(ing);
            fflush(stdin);
            cout<<"Ingrese el nombre del ingrediente nuevo: ";
            cin.getline(ing.nombre, 50);
            cout<<"Ingrese el precio del ingrediente nuevo: ";
            cin>>ing.precio;
            cout<<"ingrese de cuantos ingredientes sera el pedido: ";
            cin>>ing.cantidad;
            ofstream aniadir;
            aniadir.open(ARCHIVO_INGREDIENTES, ios::binary | ios::app);
            ing.codigoIngrediente = ingre[ingre.size()-1].codigoIngrediente+1;
            aniadir.write((char*)&ing, sizeof(Ingredientes));
            aniadir.close();
            break;
        }
        case 3:
            break;
        default:
        cout<<"Opcion no valida"<<endl;
        break;
    }
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
            return p;
        }
    }
    lectura.close();
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
    cout << "\n\tIngrese el CI del cliente: ";
    cin >> f.CI;

    bool bandera = verificarCliente(f.CI);
    if(bandera){
        cout << "\n>> El cliente ya ha sido registrado. Autocompletando informacion." << endl << endl;
        Cliente c = nombreCliente(f.CI);
        strcpy(f.nombreCliente, c.nombre);
    }
    else{
        Cliente c = nuevoCliente(f.CI);
        escribirArchivo(c);
    }

    time_t t = time(nullptr);
    tm* now = localtime(&t);
    stringstream fechaSS;
    fechaSS << now->tm_year + 1900 << '-' << now->tm_mon + 1 << '-' << now->tm_mday;
    f.fecha = fechaSS.str();

    int codigo = -1;
    while(codigo != 0){
        cout << "\tIngrese el codigo del plato (0 para finalizar): ";
        cin >> codigo;

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

    cout << "\n\tIngrese el dinero recibido: ";
    cin >> f.dineroRecibido;
    f.cambio = f.dineroRecibido - f.total;
   
    return f;
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

void imprimirFacturas(){
    Factura f;
    ifstream lectura;
    lectura.open(ARCHIVO_FACTURA, ios::binary);
    while(lectura.read((char*)&f, sizeof(Factura))){
        imprimirFactura(f);
    }
    lectura.close();
}

void gestionarFacturas(){
    cout << "\nGESTION DEL FACTURAS" << endl;
    cout << "====================" << endl;

    do{
        cout << "\n\t1. Generar factura." << endl;
        cout << "\t2. Mostrar lista de facturas." << endl;
        cout << "\t3. Volver." << endl;

        int opcion;
        cout << "\n\tSeleccione una opcion: ";
        cin >> opcion;

        switch(opcion){
            case 1:
                {
                    menuCliente(1);
                    Factura f = nuevaFactura();
                    escribirArchivo(f);
                    cout << "\n>> Factura generada correctamente." << endl;
                    imprimirFactura(f);
                    break;
                }
            case 2:
                cout << "\n>> Lista de facturas" << endl;
                imprimirFacturas();
                break;
            case 3:
                menuGerente();
            default:
                cout << "\n>> Intente de nuevo." << endl;
        }  
    }
    while(true);
}

void menuCajero(){
    while (true) {
        cout << "\nMENU CAJERO" << endl;
        cout << "=============" << endl;
        cout << "\t1. Ver menu." << endl;
        cout << "\t2. Generar factura." << endl;
        cout << "\t3. Salir." << endl;

        int opcion;
        cout << "\n\tSeleccione una opcion: ";
        cin >> opcion;

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
                exit(0);
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
            cout << endl << "\t" << p.nombre << " ........" << p.precio << endl;
        }
    }
    else if(x == 1){
        while(lectura.read((char*)&p, sizeof(Plato))){
            cout << endl << "\t" << p.codigo << "......" << p.nombre << "......" << p.precio << endl;
        }
    }
    

    lectura.close();
}

