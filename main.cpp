#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <cstdlib>
#include <thread>

using namespace std;
// incluimos los vectores que almacenaran en memoria los users y las passwords (les insertamos los valores de administrador manualmente)
vector<string> users = { "admin" };
vector<string> passwords = { "admin" };
vector<string> mainDirectory;
string creacionUserName; 
string creacionPassword;

//Funcion para limpiar las pantallas segun el sistema operativo en el que se corra el programa (misma funcion hecha por chatGPT en la practica pasada)
void screenClear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Panel de administrador

void gestionPanel() {  // Apunte durante desarrollo // Estado de la funcion: COMPLETADA

    cout << "Panel de gestion" << endl;
    cout << "\n" << endl;
    cout << "1. Crear usuario" << endl;
    cout << "2. Modificar password de un usuario" << endl;
    cout << "3. Eliminar usuarios" << endl;
    cout << "4. Cerrar sesion" << endl;

    int seleccion;

    cin >> seleccion;

    // Bloque de variables de los casos

    string deleteUser; // pese a que no queria declarar las estas variables con tal de no inicializarlas en caso de no ser necesario, las tengo que inicializar aqui porque sino da el siguiente error: transfer of control bypasses initialization of:C/C++(546)// 
    int modifyPass; // Este sera el valor del indice en el que se encuentran los usuarios en el vector, con tal de mas tarde poder modificar dicho vector
    string newpass; // Nueva password a insertar

    switch (seleccion) {

    case 1:
        screenClear();
        cout << "Menu de creacion de usuario" << endl;
        cout << "\n" << endl;
        cout << "Ingresa el nombre de usuario: ";
        cin >> creacionUserName;
        cout << "Ingresa password para el usuario: ";
        cin >> creacionPassword;

        if (creacionPassword == "" || creacionUserName == "") { // Unicamente verificamos que no haya dejado ninguna de las opciones en blanco
            cout << "Si hombre, se te ha olvidado dar nombre o poner contraseña al usuario, intentalo de nuevo listillo" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            screenClear();
            gestionPanel();
        }
        else {
            users.push_back(creacionUserName); // añadimos el usuario que ha insertado al final del vector "users"
            passwords.push_back(creacionPassword); // añadimos la password al final del vector "passwords"

            // se insertan al mismo tiempo porque se verifica que el password es el correspondiente al usuario viendo que ambos se encuentren en el mismo numero del indice del vector

            cout << "Nuevo usuario aniadido al sistema..." << endl;
            cout << "Volviendo al panel de aministrador..." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            screenClear();
            gestionPanel();
        }
        break;
    case 2:
        cout << "Menu de modificacion de password" << endl;
        cout << "\n" << endl;
        cout << "Usuarios Existentes:" << endl;
        for (int i = 0; i < users.size(); i++) { // recorremos el vector de usuarios de 1 en 1 imprimiendo los valores teniendo en cuenta que "i" siempre sera un numero = o < al tamaño total del vector
            cout << i << ": " << users[i] << endl;
        }
        cout << "Selecciona el usuario al que deseas realizar la modificacion: (numero)"<<endl;
        cin >> modifyPass;  // seleccion del usuario al que vamos a modificarle la contraseña

        if (modifyPass == 0) { // Avisaremos en caso que se intente cambiar el password de administrador
            cout << "Alerta, estas modificando el password del usuario administrador" << endl;
            cout << "Introduce la nueva contrasenia para ese usuario" << endl;
            cin >> newpass; // nueva password

            passwords[modifyPass] = newpass; // Para asegurarnos que hemos cambiado el valor correcto, usaremos la seleccion (que recordemos era el valor del usuario en el indice del vector) y lo insertaremos directamente en su espacio correspondiente en el vector passwords
        }
        else { // Exactamente lo mismo pero sin la necesidad de avisar sobre que se esta intentando cambiar la password del usuario administrador
            cout << "Introduce la nueva contrasenia para ese usuario" << endl;
            cin >> newpass;

            passwords[modifyPass] = newpass;// lo mismo de arriba

            cout << "Contrasenia del usuario: "<< users[modifyPass] << ", actualizada de manera exitosa..." << endl;
            cout << "Regresando al menu..." << endl;

            this_thread::sleep_for(chrono::seconds(2));
            screenClear();
            gestionPanel();
        }

        break;
    case 3:

        cout << "Menu de eliminacion de usuario" << endl;
        cout << "\n" << endl;
        // mostramos todo el vector users
        cout << "Usuarios:" << endl;
        for (const auto& user : users) { // declaramos la constante user con auto para que el compilador pueda detectar el tipo de dato que tiene el vector (gracias GPT por la ayuda en esto y ahorrarme sacar uno a uno los valores del vector)
            cout << user << endl;
        }

        cout << "Selecciona el usuario a eliminar: ";
        cin >> deleteUser;

        for (int i = 1; i < users.size(); i++) { // i = 1 ya que el admin no quiero que se pueda borrar
            if (deleteUser == "1" || deleteUser == "0") {
                cout << "Usuario administrador no modificable desde el programa, modifica el codigo fuente si realmente es que quieres borrarlo listo" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                screenClear();
                gestionPanel();
            }
            else {
                users.erase(users.begin() + i);
                passwords.erase(passwords.begin() + i);
                cout << "Usuario eliminado con exito" << endl;
                cout << "Volviendo al panel de administrador..." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                screenClear();
                gestionPanel();
            }
        }
        break;
    case 4:
        string user;
        string password;
        cout << "Usuario:";
        cin >> user;
        cout << "Contrasenia:";
        cin >> password;

        if (user == users[0] && password == passwords[0]) {
            cout << "Iniciando sesion como administrador" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            screenClear();
            gestionPanel();
        }
        else {
            for (int i = 1; i < users.size(); i++) { // bucle for que recorre los vectores saltando el primero (es el de admin)
                if (user == users[i] && password == passwords[i]) { // en caso que las credenciales user y password esten almacenadas en la misma posicion, acceso concedido
                    cout << "Iniciando sesion" << endl;
                    screenClear();
                    this_thread::sleep_for(chrono::seconds(2));
                    cout << "ENDPOINT PROVISIONAL" << endl;
                    break;
                }
            }
        }
        break;
    }
}

void gestionDirectoryAdmin() {

    cout << "Estas loggeado como ADMINISTRADOR" << endl;
    cout << "\n" << endl;
    cout << "1. Ver directorios" << endl;
    cout << "2. Crear directorios" << endl;
    cout << "3. Renombrar directorios" << endl;
    cout << "4. Eliminar directorio" << endl;
    cout << "5. Volver" << endl;

    int seleccion;

    cin >> seleccion;

    switch (seleccion) {
    case 1:
        for (int i = 0; i < mainDirectory.size(); i++) {
            cout << mainDirectory[i] << endl;
        }
        break;
    case 2:

        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    }
}


void adminMenu() {

    cout << "Estas loggeado como ADMINISTRADOR" << endl;
    cout << "\n" << endl;
    cout << "1. Gestionar usuarios" << endl;
    cout << "2. Cambiar usuario" << endl;
    cout << "3. Gestionar directorios" << endl;
    cout << "4. Gesttionar tareas" << endl;
    cout << "5. salir" << endl;

    int seleccion;

    cin >> seleccion;

    string user;
    string password;

    switch (seleccion) {
    case 1:
        screenClear();
        gestionPanel();
        break;
    case 2:
        cout << "Usuario:"; 
        cin >> user; 
        cout << "Contrasenia:"; 
        cin >> password; 

        if (user == users[0] && password == passwords[0]) { // en caso de ingresar las credenciales almacenadas en el punto 0 del vector, las cuales corresponden siempre al admin, inicia sesion como admin
            cout << "Iniciando sesion como administrador" << endl; 
            this_thread::sleep_for(chrono::seconds(2)); // timeout de 2 segundos  
            screenClear(); // Funcion para limpiar la pantalla 
            adminMenu(); 
        }
        else {
            for (int i = 1; i < users.size(); i++) { // bucle for que recorre los vectores saltando el primero (indice 0 ya que es el de admin) 
                if (user == users[i] && password == passwords[i]) { // en caso que las credenciales user y password esten almacenadas en la misma posicion, acceso concedido  
                    cout << "Iniciando sesion" << endl;
                    screenClear();  
                    this_thread::sleep_for(chrono::seconds(2)); 
                    cout << "ENDPOINT PROVISIONAL" << endl; 
                }
                else {
                    cout << "Usuario o contraseña incorrecto" << endl; 
                }
            }
        }
        break;
    case 3:
        gestionDirectoryAdmin();
        break;
    case 4:
        break;
    case 5:
        break;
    }

}


int main() {

    string user;
    string password;

    cout << "Usuario:";
    cin >> user;
    cout << "Contrasenia:";
    cin >> password;

    if (user == users[0] && password == passwords[0]) { // en caso de ingresar las credenciales almacenadas en el punto 0 del vector, las cuales corresponden siempre al admin, inicia sesion como admin
        cout << "Iniciando sesion como administrador" << endl;
        this_thread::sleep_for(chrono::seconds(2)); // timeout de 2 segundos 
        screenClear(); // Funcion para limpiar la pantalla
        adminMenu();
    }
    else {
        for (int i = 1; i < users.size(); i++) { // bucle for que recorre los vectores saltando el primero (indice 0 ya que es el de admin)
            if (user == users[i] && password == passwords[i]) { // en caso que las credenciales user y password esten almacenadas en la misma posicion, acceso concedido
                cout << "Iniciando sesion" << endl;
                screenClear();
                this_thread::sleep_for(chrono::seconds(2));
                cout << "ENDPOINT PROVISIONAL" << endl;
            }
            else {
                cout << "Usuario o contrasenia incorrecto" << endl;
            }
        }
    }
}
