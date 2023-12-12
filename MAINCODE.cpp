#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

//Cambiar las structuras cosa que sea char(?)
struct Empleado {
    string puesto;
    string nombre;
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

const string GERENTE_USUARIO = "gerente";
const string GERENTE_CONTRASENA = "54321";
const string CAJERO_USUARIO = "cajero";
const string CAJERO_CONTRASENA = "12345";
const string ARCHIVO_EMPLEADOS = "empleados.bin";
const string ARCHIVO_CLIENTES = "clientes.bin";
const string ARCHIVO_MENU = "menu.bin";
const string ARCHIVO_FACTURA = "factura.bin";
const string ARCHIVO_FINANZAS = "finanzas.bin";
const double IMPUESTO = 0.13;

void inicializarArchivos() {
    ofstream archivoEmpleados(ARCHIVO_EMPLEADOS, ios::app | ios::binary);
    archivoEmpleados.close();

    ofstream archivoClientes(ARCHIVO_CLIENTES, ios::app | ios::binary);
    archivoClientes.close();

    ofstream archivoMenu(ARCHIVO_MENU, ios::app | ios::binary);
    archivoMenu.close();

    ofstream archivoFactura(ARCHIVO_FACTURA, ios::app | ios::binary);
    archivoFactura.close();

    ofstream archivoFinanzas(ARCHIVO_FINANZAS, ios::app | ios::binary);
    archivoFinanzas.close();
    cout << "Archivos inicializados" << endl;
}


// funciones
void pantallaAcceso();
void menuGerente();
void menuCajero();
void gestionarEmpleados();
void gestionarClientes();
void gestionarMenu();
void generarFactura();
void gestionarFinanzas();
void menuCliente();

// Función principal la bonita aaaaaaaaaaaaaaaaaaa
int main() {
    pantallaAcceso();
    return 0;
}

// Implementación de funciones
void pantallaAcceso() {
    string usuario, contrasena;
    cout << "Bienvenido al sistema de typica? typican't" << endl;
    cout << "Usuario: ";
    cin >> usuario;
    cout << "Contraseña: ";
    cin >> contrasena;

    if (usuario == GERENTE_USUARIO && contrasena == GERENTE_CONTRASENA) {
        menuGerente();
    } else if (usuario == CAJERO_USUARIO && contrasena == CAJERO_CONTRASENA) {
        menuCajero();
    } else if (usuario == "0" && contrasena == "0"){
        menuCliente();
    }
    else {
        cout << "Acceso no autorizado. go away >:c." << endl;
    }
}

void menuGerente() {
    while (true) {
        cout << "\nMenu Gerente:" << endl;
        cout << "1. Gestionar empleados" << endl;
        cout << "2. Gestionar clientes" << endl;
        cout << "3. Gestionar menu" << endl;
        cout << "4. Generar factura" << endl;
        cout << "5. Gestionar finanzas" << endl;
        cout << "6. Salir" << endl;

        int opcion;
        cout << "Seleccione una opcion: ";
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
                cout << "Intente nuevamente" << endl;
        }
    }
}

void gestionarEmpleados() {
    fstream archivoEmpleados(ARCHIVO_EMPLEADOS, ios::in | ios::out | ios::binary);

    if (!archivoEmpleados) {
        cerr << "Error" << endl;
        return;
    }

    vector<Empleado> empleados;

    // Leer i think
    while (!archivoEmpleados.eof()) {
        Empleado empleado;
        archivoEmpleados.read(reinterpret_cast<char*>(&empleado), sizeof(Empleado));
        if (!archivoEmpleados.eof()) {
            empleados.push_back(empleado);
        }
    }

    // Mostrar
    cout << "\nLista de empleados:" << endl;
    for (const auto& empleado : empleados) {
        cout << "Puesto: " << empleado.puesto << ", Nombre: " << empleado.nombre << ", Sueldo: " << empleado.sueldo << " BOB al mes" << endl;
    }

    //añadir o eliminar empleados
    cout << "\n1. Añadir empleado" << endl;
    cout << "2. Eliminar empleado" << endl;
    cout << "3. Volver al menu principal" << endl;

    int opcion;
    cout << "Seleccione una opcion: ";
    cin >> opcion;

    switch (opcion) {
        case 1: {
            Empleado nuevoEmpleado;
            cout << "Ingrese el puesto del nuevo empleado: ";
            //nose aca no toma la linea entera
            cin >> nuevoEmpleado.puesto;
            cout << "Ingrese el nombre del nuevo empleado: ";
            cin >> nuevoEmpleado.nombre;
            cout << "Ingrese el sueldo del nuevo empleado: ";
            cin >> nuevoEmpleado.sueldo;

            empleados.push_back(nuevoEmpleado);

            // Guardar
            archivoEmpleados.seekp(0, ios::end);
            archivoEmpleados.write(reinterpret_cast<char*>(&nuevoEmpleado), sizeof(Empleado));

            cout << "Empleado añadido correctamente." << endl;
            break;
        }
        case 2: {
            int indice;
            cout << "Ingrese el indice del empleado a eliminar: ";
            cin >> indice;

            if (indice >= 0 && indice < empleados.size()) {
                // Eliminar empleado del vector
                empleados.erase(empleados.begin() + indice);

                // Sobrescribir el archivo con el nuevo vector de empleados
                archivoEmpleados.close();
                archivoEmpleados.open(ARCHIVO_EMPLEADOS, ios::out | ios::binary);
                for (const auto& empleado : empleados) {
                    archivoEmpleados.write(reinterpret_cast<const char*>(&empleado), sizeof(Empleado));
                }

                cout << "Empleado eliminado correctamente." << endl;
            } else {
                cout << "NO" << endl;
            }
            break;
        }
        case 3:
            break;
        default:
            cout << "Opción no valida" << endl;
    }

    archivoEmpleados.close();
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
