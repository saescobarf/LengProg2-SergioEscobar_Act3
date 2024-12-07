// sergioescobar_actividad2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.


#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    SQLRETURN ret;
    // Asignar un gestor de entorno
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
    // Asignar un gestor de conexión
    ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);
    // Conectarse a la base de datos
    ret = SQLConnect(hDbc, (SQLWCHAR*)L"sqlserver", SQL_NTS, (SQLWCHAR*)L"Username", SQL_NTS, (SQLWCHAR*)L"Password", SQL_NTS);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        cout << "Conectado a la base de datos exitosamente." << endl;
        
        
        SQLHSTMT hStmt;
        ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

        /*
        wcout << L"+------+-----------------+-------------+------------+-----------+------------+-----+-----------+-----------+-----------+ " << endl;
        wcout << L"| No.  | Nombre          | apellido p. | apellido m.| fecha nac.| num_centro | rfc | id_puesto | directivo | fechaAlta | " << endl;
        wcout << L"+------+-----------------+-------------+------------+-----------+------------+-----+-----------+-----------+-----------+ " << endl;
        wcout << L"|      |                 |             |            |           |            |     |           |           |           | " << endl;
        wcout << L"+------+-----------------+-------------+------------+-----------+------------+-----+-----------+-----------+-----------+ " << endl;

        wcout << L"+------------+------------+-----------+ " << endl;
        wcout << L"| num_centro | nom_centro | ciudad    | " << endl;
        wcout << L"+------------+------------+-----------+ " << endl;
        wcout << L"|            |            |           | " << endl;
        wcout << L"+------------+------------+-----------+ " << endl;

        wcout << L"+------------+------------+---------------+ " << endl;
        wcout << L"| id_puesto  |   puesto   |  desc_puesto  | " << endl;
        wcout << L"+------------+------------+---------------+ " << endl;
        wcout << L"|            |            |               | " << endl;
        wcout << L"+------------+------------+---------------+ " << endl;

        wcout << L"+--------------+----------------+-------------------+ " << endl;
        wcout << L"| num_empleado | num_centro_sup | combustible_apoyo | " << endl;
        wcout << L"+--------------+----------------+-------------------+ " << endl;
        wcout << L"|              |                |                   | " << endl;
        wcout << L"+--------------+----------------+-------------------+ " << endl;
        */
  

        
        //Select a la base de datos
        ret = SQLExecDirect(hStmt, (SQLWCHAR*)L"SELECT * FROM empleados", SQL_NTS);
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            int num_empleado;
            SQLWCHAR name[50];
            while (SQLFetch(hStmt) == SQL_SUCCESS) {
                SQLGetData(hStmt, 1, SQL_C_LONG, &num_empleado, 0, NULL);
                SQLGetData(hStmt, 2, SQL_C_WCHAR, name, sizeof(name), NULL);
                wcout << "   " << num_empleado << "      " << name << endl;
            }
            wcout << L"+------+--------------------------------+" << endl;
        }
        // Liberar el manejador de conexión
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    }
    else {
        cout << "Falló la conexion a la base de datos" << endl;
    }
    // Desconectar y liberar gestores de entorno
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
    return 0;
}