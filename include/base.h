#ifndef _BASE_H
#define _BASE_H
#include <stdlib.h>
#include <string>
#include <sstream>
#include <mysql.h>
#include <mysqld_error.h>
#include <iostream>
using namespace std;
class base{
    private:
        base(){
                if(!(_mysql = mysql_init(0))){
                    cout << "Error" << endl;
                }
                else{
                    if(mysql_real_connect(_mysql, "localhost", "root", "", "banco", 3306, NULL, 0)){
                        cout << "CONECTADO" << endl;
                    }
                    else{
                        cout<< "NO CONECTADO" << endl;
                    }
                }
            }
        MYSQL * _mysql;
        int x;
        static base* instancia;
    public:
        static base *getinstacia(){
            if(instancia==NULL){
                instancia = new base();
            }
            return instancia;
        }
        int getnumber(int number){
            x=number;
            return x;
        }
        string int_to_string(int entero){
            string cadena = "";
            cadena = static_cast<ostringstream*>(&(ostringstream() << entero))->str();
            return cadena;
        }
        char * getnumero(){
            return extraer("numero");
        }

        char * getnombre(){
            return extraer("nombre");
        }
        char * getsimbolo(){
            return extraer("simbolo");
        }
        char * getpeso(){
            return extraer("peso");
        }
        char *getelectron(){
            return extraer("electron");
        }
        char *extraer(string cadena){
            string part2 = int_to_string(x);
            string part1 = "SELECT " + cadena + " FROM elementos WHERE numero = " + part2;
            char *sql = (char *)part1.c_str();
            int query = mysql_query(_mysql, sql);
            if (query != 0){
                cout << "ERROR" << endl;
            }
            else{
                MYSQL_RES * resultado = mysql_store_result(_mysql);
                unsigned long filas_afectadas = mysql_num_rows(resultado);
                MYSQL_ROW fila;
                fila = mysql_fetch_row(resultado);
                for (int x = 0; x < filas_afectadas; x++){
                    return fila[0];
                }
                mysql_free_result(resultado);
            }
            mysql_close(_mysql);
        }
};

#endif // _BASE_H_
