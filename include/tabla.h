#ifndef _TABLA_H
#define _TABLA_H
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>
#include <mysql.h>
#include <mysqld_error.h>
#include <base.h>



#define MAX_ROW 10
#define MAX_COL 18
int mapa[MAX_ROW][MAX_COL]={
    1,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,2,
    3,4,00,00,00,00,00,00,00,00,00,00,5,6,7,8,9,10,
    11,12,00,00,00,00,00,00,00,00,00,00,13,14,15,16,17,18,
    19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,
    37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,
    55,56,00,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,
    87,88,00,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,
    00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
    00,00,00,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,
    00,00,00,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,
};

base *base::instancia=NULL;

using namespace std;
class tabla{
    private:
        int vx,vy;
        int x;
        int y;
        bool button_down=false;
        string text_console;
        BITMAP *buffer;
        PALLETE pallete;
        FONT *myfuente=load_font("font/simbolo.pcx",pallete,NULL);
        FONT *lnom=load_font("font/nombre.pcx",pallete,NULL);
        FONT *lnum=load_font("font/numero.pcx",pallete,NULL);
        FONT *lconso=load_font("font/consola.pcx",pallete,NULL);
        BITMAP *mundo = load_bitmap("background/background.bmp",NULL);
        BITMAP *console = load_bitmap("background/console.bmp",NULL);
        BITMAP *ptr;

    public:
        tabla(int tx, int ty){
            x=tx;
            y=ty;
            buffer = create_bitmap(x,y);
            show_mouse(buffer);
            position_mouse(32,692);
        }
        void start(){
            BITMAP *exit=load_bitmap("background/exit.bmp",NULL);
            BITMAP *clean=load_bitmap("background/clear.bmp",NULL);
            bool salir=false;
            while (!salir){
                masked_blit(console,buffer,0,0,0,0,1280,730);
                blit(buffer,screen,0,0,0,0,1280,730);
                if(mouse_x>29 && mouse_x<113 &&
                   mouse_y>664 && mouse_y<695){
                    blit(exit,buffer,0,0,0,0,1280,730);
                    if (mouse_b & 1){
                        salir=true;
                    }
                }
                else if(mouse_x>29 && mouse_x<113 &&
                   mouse_y>605 && mouse_y<640){
                    blit(clean,buffer,0,0,0,0,1280,730);
                    if(mouse_b & 1){
                        text_console="";
                        clear_bitmap(console);
                        //masked_blit(console,buffer,0,0,0,0,1280,730);
                    }
                }

                else if(mouse_x>0 && mouse_x<1280 &&
                    mouse_y>0 && mouse_y<730){
                    vx=mouse_x-25;
                    vy=mouse_y-34;
                    int resultado=mapa[vy/75][vx/67];
                    if (resultado<118 && resultado>=1){

                        if (!button_down){
                            if(mouse_b&1){
                                base::Instancia()->getnumber(resultado);
                                textout_ex(console,lconso,textoff(resultado),164,220,0xFFFFFF,0x000000);
                                button_down=true;
                            }
                        }
                        else{
                            if(!(mouse_b&1)){
                                button_down=false;
                            }
                        }
                    }
                }
                else{
                    blit(mundo,buffer,0,0,0,0,1280,730);
                }



                //--------------------------------------------------
                //masked_blit(cursor,buffer,0,0,mouse_x,mouse_y,13,22);
                //masked_blit(console,buffer,0,0,0,0,1280,730);
                //blit(buffer,screen,0,0,0,0,1280,730);
            }
        }
        void destroyer(){
            destroy_bitmap(buffer);
        }
        void creado(BITMAP *p,int x){
            base::Instancia()->getnumber(x);
            textout_ex(p,lnum,base::Instancia()->getnumero(),240,100,0x000000,0xFFFFFF);
            textout_ex(p,lnom,base::Instancia()->getnombre(),240,160,0x000000,0xFFFFFF);
            textout_ex(p,myfuente,base::Instancia()->getsimbolo(),260,110,0x000000,0xFFFFFF);
            masked_blit(p,buffer,0,0,0,0,1280,730);
            if (!button_down){
                if(mouse_b&1){
                    textout_ex(console,lconso,textoff(x),164,220,0xFFFFFF,0x000000);
                    button_down=true;
                }
            }
            else{
                if(!(mouse_b&1)){
                    button_down=false;
                }
            }
        }
        char *textoff(int x){
            base::Instancia()->getnumber(x);
            text_console=text_console + base::Instancia()->getsimbolo();
            char *ret = (char *)text_console.c_str();
            return ret;
        }
};

#endif // _TABLA_H
