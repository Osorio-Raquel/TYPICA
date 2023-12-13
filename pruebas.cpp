#include <iostream>
#include <fstream>

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

// Función para escribir los datos en el archivo
void escribirMenu() {
    Plato menu[] = {
        {1, "Filete de res con salsa de champiniones", 120.0},
        {2, "Salmon a la parrilla con salsa de eneldo", 90.0},
        {3, "Pollo al curry con arroz basmati", 60.0},
        {4, "Pasta carbonara", 58.0},
        {5, "Tacos de carnitas con salsa verde", 30.0},
        {6, "Pizza margarita", 60.0},
        {7, "Ensalada Cesar con pollo a la parrilla", 70.0},
        {8, "Sushi variado", 150.0},
        {9, "Risotto de champiniones", 90.0},
        {10, "Hamburguesa gourmet con queso azul y cebolla caramelizada", 70.0},
        {11, "Paella de mariscos", 180.0},
        {12, "Tortellini con salsa de tomate y albahaca", 60.0},
        {13, "Costillas de cerdo a la barbacoa", 120.0},
        {14, "Tartar de atun", 120.0},
        {15, "Lasania de carne", 60.0},
        {16, "Ceviche de camarones", 90.0},
        {17, "Pato a la naranja", 150.0},
        {18, "Cordero asado con hierbas", 150.0},
        {19, "Fajitas de pollo con guarniciones", 58.0},
        {20, "Poke bowl", 90.0},
        {21, "Gnocchi con pesto", 60.0},
        {22, "Langosta a la parrilla con mantequilla de ajo", 210.0},
        {23, "Calamares a la romana", 60.0},
        {24, "Tacos de pescado con repollo y salsa de chipotle", 30.0},
        {25, "Ramen con cerdo desmenuzado", 70.0},
        {26, "Enchiladas de pollo con salsa roja", 58.0},
        {27, "Canelones de espinacas y ricotta", 60.0},
        {28, "Pollo a la naranja", 90.0},
        {29, "Arroz frito con verduras y gambas", 60.0},
        {30, "Parrillada mixta (carne y mariscos)", 180.0}
    };

    std::ofstream archivo("menu.bin", std::ios::binary);

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    archivo.write(reinterpret_cast<char*>(menu), sizeof(menu));
    archivo.close();
    std::cout << "Archivo 'menu.bin' creado correctamente." << std::endl;

    Ingredientes ingre [] = {{1, "Filete de res", 40, 20.0},
        {2, "Champiniones", 100, 5.0},
        {3, "Salmon", 40, 40.0},
        {4, "Eneldo", 35, 20.0},
        {5, "Pollo", 40, 30.0},
        {6, "Curry", 50, 25.0},
        {7, "Arroz basmati", 36, 23.0},
        {8, "Pasta", 150, 6.5},
        {9, "Crema", 150, 7.0},
        {10, "Carnitas", 40, 34.0},
        {11, "Salsa verde", 30, 28.0},
        {12, "Tomate", 200, 2.0},
        {13, "Queso", 48, 15.0},
        {14, "Cebolla", 160, 2.0},
        {15, "Langosta", 89, 39.0},
        {16, "Albahaca", 200, 10.0},
        {17, "Costillas de cerdo", 80, 60.0},
        {18, "Atun", 52, 50.0},
        {19, "Carne molida", 49, 40.0},
        {20, "Camarones", 70, 20.0},
        {21, "Arroz Risotto", 60, 15.0},
        {22, "Mantequilla de ajo", 45, 10.0},
        {23, "Gambas", 99, 9.0},
        {24, "Tortellini", 78, 7.0},
        {25, "Calamares", 30, 50.0},
        {26, "Repollo", 50, 3.5},
        {27, "Chipotle", 100, 3.0},
        {28, "Cerdo desmenuzado", 45, 45.0},
        {29, "Salsa roja", 70, 13.0},
        {30, "Espinacas", 230, 1.5},
        {31, "Ricotta", 34, 10.5},
        {32, "Naranja", 25, 10.0},
        {33, "Cordero", 44, 46.0},
        {34, "Hierbas", 53, 45.0},
        {35, "Pesto", 34, 20.0},
        {36, "Pan", 100, 1.0},
        {37, "Gnocchi", 98, 16.0},
        {38, "Arroz", 150, 7.0},
        {39, "Pato", 40, 40.0}
    };
    std::ofstream archivo1("ingredientes.bin", std::ios::binary);

    if (!archivo1.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    archivo1.write(reinterpret_cast<char*>(ingre), sizeof(ingre));
    archivo1.close();
    std::cout << "Archivo 'ingredientes.bin' creado correctamente." << std::endl;

    Receta recetas [] = {{1, 1, 1}, {1, 2, 2}, {1, 9, 1},
    {2, 3, 1}, {2, 4, 2}, {2, 38, 1},
    {3, 5, 1}, {3, 6, 2}, {3, 7, 1},
    {4, 8, 1}, {4, 9, 1}, {4, 10, 2},
    {5, 10, 2}, {5, 11, 1},
    {6, 12, 1}, {6, 13, 1}, {6, 14, 1}, {6, 16, 2},
    {7, 5, 1}, {7, 12, 1}, {7, 14, 1},
    {8, 38, 3}, {8, 3, 1}, {8, 15, 1}, {8, 20, 1}, {8, 20, 1}, {8, 15, 1},
    {9, 21, 1}, {9, 2, 2}, {9, 13, 1},
    {10, 19, 1}, {10, 13, 1}, {10, 14, 2}, {10, 36, 1},
    {11, 38, 1}, {11, 15, 1}, {11, 20, 3}, {11, 25, 1},
    {12, 24, 4}, {12, 12, 2}, {12, 16, 2},
    {13, 17, 2}, {13, 32, 1},
    {14, 18, 2}, {14, 22, 1},
    {15, 8, 3}, {15, 1, 1}, {15, 13, 1},
    {16, 15, 1}, {16, 20, 4},
    {17, 39, 1}, {17, 32, 2},
    {18, 33, 1}, {18, 34, 4},
    {19, 5, 1}, {19, 38, 1},
    {20, 38, 1}, {20, 3, 1}, {20, 14, 1},
    {21, 37, 2}, {21, 35, 2},
    {22, 15, 1}, {22, 22, 2},
    {23, 25, 1}, {23, 14, 1},
    {24, 3, 1}, {24, 26, 1}, {24, 27, 3},
    {25, 8, 2}, {25, 28, 1},
    {26, 5, 1}, {26, 29, 2},
    {27, 8, 1}, {27, 30, 2}, {27, 31, 2},
    {28, 5, 1}, {28, 32, 3},
    {29, 38, 1}, {29, 23, 2}, {29, 12, 2},
    {30, 1, 2}, {30, 15, 1}, {30, 20, 2}
    };
    std::ofstream archivo2("recetas.bin", std::ios::binary);

    if (!archivo2.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    archivo2.write(reinterpret_cast<char*>(recetas), sizeof(recetas));
    archivo2.close();
    std::cout << "Archivo 'irecetas.bin' creado correctamente." << std::endl;
}

// Función para leer y mostrar los datos del archivo
void leerMenu() {
    Plato menu[30];

    std::ifstream archivo("menu.bin", std::ios::binary);

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    archivo.read(reinterpret_cast<char*>(menu), sizeof(menu));
    archivo.close();

    std::cout << "Menu cargado desde 'menu.bin':" << std::endl;
    for (const auto& plato : menu) {
        std::cout << "Codigo: " << plato.codigo << ", Nombre: " << plato.nombre << ", Precio: " << plato.precio << " BOB" << std::endl;
    }
}

void leeringredientes()
{
    Ingredientes ingre [39];
    std::ifstream archivo("ingredientes.bin", std::ios::binary);

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    archivo.read(reinterpret_cast<char*>(ingre), sizeof(ingre));
    archivo.close();

    std::cout << "Ingredinetes cargados desde 'ingredientes.bin':" << std::endl;
    for (const auto& plato : ingre) {
        std::cout << "Codigo: " << plato.codigoIngrediente << ", Nombre: " << plato.nombre << ", Precio: " << plato.precio << " BOB Cantidad: " <<plato.cantidad << std::endl;
    }
}
void leerRecetas()
{
    Receta recetas [83];
    std::ifstream archivo("recetas.bin", std::ios::binary);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    archivo.read(reinterpret_cast<char*>(recetas), sizeof(recetas));
    archivo.close();

    std::cout << "Ingredinetes cargados desde 'recetas.bin':" << std::endl;
    for (const auto& plato : recetas) {
        std::cout << "Codigo Plato: " << plato.codigoPlato << ", Codigo Ingreciente: " << plato.CodigoIngrediente << " Cantidad: " <<plato.cantidad << std::endl;
    }
}
int main() {
    escribirMenu();
    leerMenu();
    leeringredientes();
    leerRecetas();
    return 0;
}
