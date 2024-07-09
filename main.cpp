#include <iostream>
#include <string>
#include "sqlite3.h"
#include <cstdlib>
#include <Windows.h>
using namespace std;

sqlite3* inDataBase(const char* name, int& check)
{
    sqlite3* DB;
    check = sqlite3_open(name, &DB);
    return DB;
}

bool createDataBase(sqlite3* DB)
{

    const char* scriptSQL =
        R"(
        BEGIN TRANSACTION;

        CREATE TABLE asignacion (
            usuario_id_usuario TEXT NOT NULL,
            tarea_id_tarea     TEXT NOT NULL,
            PRIMARY KEY(usuario_id_usuario, tarea_id_tarea)
        );

        CREATE TABLE tarea (
            id_tarea       TEXT NOT NULL PRIMARY KEY,
        titulo         TEXT,
        descripcion    TEXT,
        prioridad      INTEGER,
        fecha_creacion TEXT
        );

        CREATE TABLE usuario (
            id_usuario         TEXT NOT NULL PRIMARY KEY,
            nombre             TEXT,
            tareas_completadas INTEGER
        );

        CREATE INDEX asignacion_tarea_fk ON asignacion (tarea_id_tarea);
        CREATE INDEX asignacion_usuario_fk ON asignacion (usuario_id_usuario);

        COMMIT;)";

    char* errmsg = nullptr;

    if (sqlite3_exec(DB, scriptSQL, nullptr, nullptr, &errmsg) != SQLITE_OK)
        return false;

    return true;
}

bool fileExists(const char* filename) 
{
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

void showMainMenu()
{
    cout << endl;
    cout << "-------------------------------------------" << endl;
    cout << "SELECT OPTION:" << endl;
    cout << "1. Add task" << endl;
    cout << "2. Modify task" << endl;
    cout << "3. Add user" << endl;
    cout << "4. Modify user" << endl;
    cout << "5. Exit" << endl;
    cout << "-------------------------------------------" << endl;
    cout << endl;
}

int main()
{
    //INICIAMOS LA CONEXIÓN A LA BASE DE DATOS
    int check = 0;
    sqlite3* DB = inDataBase("todolist.db", check);
    if (check != SQLITE_OK)
    {
        cout << "ERROR CONNECTING TO DATA BASE" << endl;
        cout << sqlite3_errmsg(DB) << endl;
        sqlite3_close(DB);
        return 0;
    }

    //COMPROBAMOS SI LA BASE DE DATOS EXISTE, SI NO EXISTE ENTONCES LA CREAMOS
    bool exists = fileExists("todolist.db");

    if (!exists)
    {
        cout << "DATA BASE DOES NOT EXIST" << endl;
        cout << "CREATING DATA BASE" << endl;
        if (createDataBase(DB) == SQLITE_OK)
            cout << "DATA BASE CORRECTLY CREATED" << endl;
        else
            cout << "ERROR CREATING DATA BASE" << endl;
    }

    char option = NULL;
    
    while (option != '5')
    {
        showMainMenu();
        cin >> option;
        switch (option)
        {
        case '1':
            //addTask()
            break;
        case '2':
            //modifyTask()
            break;
        case '3':
            //addUser():
            break;
        case '4':
            //modifyUser()
            break;
        case '5':
            break;
        default:
            cout << "INVALID OPTION" << endl;
            Sleep(1000);
        }
        system("cls");
    }


    return 1;
}