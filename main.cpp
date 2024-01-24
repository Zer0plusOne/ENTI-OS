#include <iostream> //Libreria de entrada y salida
#include <vector> //Libreria de vectores para almacenar datos
#include <thread> //Libreria de hilos
#include <chrono> //Libreria de tiempo
#include <string> //Libreria de strings

using namespace std;

//generamos los vectores que almacenaran los usuarios y las contraseñas
vector<string> users;
vector<string> passwords;

string adminUser = "admin";
string adminPass = "admin";

bool adminLogin(){
    //Pedimos los datos de usuario y contrasenia;
    cout<< "Username:";
    cin>> adminUser;
    cout<<"Password:";
    cin>> adminPass;

    if(adminUser == "admin" && adminPass == "admin"){
        cout << "Bienvenido administrador" << endl;
        return true;
    }
    else{
        cout << "Usuario o contrasenia incorrecta, blyat" << endl;
        adminLogin();
    }
}
void adminPanel(){
            string userName;
            string userPswd;

            string acutalAdminPass = adminPass;
            cout<< "ADMIN PANEL" << endl;
            cout<< "1. Crear usuario" << endl;
            cout<< "2. Modificar conrasenia de administrador" << endl;
            cout<< "3. Eliminar usuario" << endl;
            cout<< "4. Volver" << endl;

            int option;

            cin >> option;

            switch (option){
                case 1:
                // Damos al admin la posibilidad de crear un nuevo usuario
                    cout<<"Username:";
                    cin>> userName;
                    cout<<"Password:";
                    cin>> userPswd;

                    //Agregamos el nuevo usuario y la contrasenia a los vectores
                    users.push_back(userName);
                    passwords.push_back(userPswd);

                    cout<<"Usuario y contraseña creado exitosamente" << endl;
                    cout<< "Regresando al menu principal..."<<endl;
                    this_thread::sleep_for(chrono::seconds(2)); // Tiempo de espera
                    break;
                case 2:
                    cout<<"ingresa la contraseña actual:";
                    cin>> acutalAdminPass;
                    break;  
                case 3:
                    break;
                case 4:
                    break;
            }
}
void menuAdmin(){
    cout << "1. ADMIN PANEL" << endl;
    cout << "2. Gestionar usuarios" << endl;
    cout << "3. Cambiar usuario" << endl;
    cout << "4. Gestionar directorios" << endl;
    cout << "5. Gestionar tareas" << endl;
    cout << "6. Salir" << endl;

    int option;

    cin >> option;

    switch (option){
        case 1:
            adminPanel();
            break;            
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
    }
}

void menu(){
    cout << "1. " << endl;
    cout << "2. Cargar archivo" << endl;
    cout << "3. Salir" << endl;
}


int main() {
    adminLogin();
    if (adminLogin()) {
        menu();
    }

    menu();

    return 0;
}
