#include <iostream>
#include <fstream>

struct Plato {
    int codigo;
    char nombre[100];
    float precio;
};

// Función para escribir los datos en el archivo
void escribirMenu() {
    Plato menu[] = {
        {1, "Filete de res con salsa de champiñones", 120.0},
        {2, "Salmón a la parrilla con salsa de eneldo", 90.0},
        {3, "Pollo al curry con arroz basmati", 60.0},
        {4, "Pasta carbonara", 58.0},
        {5, "Tacos de carnitas con salsa verde", 30.0},
        {6, "Pizza margarita", 60.0},
        {7, "Ensalada César con pollo a la parrilla", 70.0},
        {8, "Sushi variado", 150.0},
        {9, "Risotto de champiñones", 90.0},
        {10, "Hamburguesa gourmet con queso azul y cebolla caramelizada", 70.0},
        {11, "Paella de mariscos", 180.0},
        {12, "Tortellini con salsa de tomate y albahaca", 60.0},
        {13, "Costillas de cerdo a la barbacoa", 120.0},
        {14, "Tartar de atún", 120.0},
        {15, "Lasaña de carne", 60.0},
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
        std::cout << "Código: " << plato.codigo << ", Nombre: " << plato.nombre << ", Precio: " << plato.precio << " BOB" << std::endl;
    }
}

int main() {
    escribirMenu();
    leerMenu();

    return 0;
}
