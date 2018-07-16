#ifndef _MOL_H
#define _MOL_H
#include <iostream>
#include <vector>
#include <gl/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265


using namespace std;

float rotacion_molecula = 0.0;

int rotacion = 0;
int traslacion = 0;


class Molecula{
public:
    virtual void trabajar()=0;
    virtual void cargaAcciones(vector<int> accion)=0;
};

Molecula *Mol;
Molecula *Molecul;

class MoleculaI : public Molecula {
public:
    vector<int> acciones;
    MoleculaI(){}
    void cargaAcciones(vector<int> accion){
        this->acciones=accion;
    }
    void trabajar(){
        for(int i=0;i<this->acciones.size();i++){
            if(this->acciones[i]==1) this->getCompuesto();
            else cout<<"No puedo realizar esta accion"<<endl;
        }
    }
private:
    void iniciar(){
        cout<<"Iniciando la Composicion"<<endl;
    }
    void getCompuesto(){
        glPushMatrix();
        glRotatef(rotacion_molecula,0,0,1.0);
        glColor3f(1.0,1.0,0.0);
        glutWireSphere(1,30,30);
        glPopMatrix();
    }
};

class MoleculaS : public Molecula {
public:
    vector<int> acciones;
    MoleculaS(){}
    void cargaAcciones(vector<int> accion){
        this->acciones=accion;
    }
    void trabajar(){
        for(int i=0;i<this->acciones.size();i++){
            if(this->acciones[i]==1) this->getParts(dist_mol_e,grade,z);
            else cout<<"No puedo realizar esta accion"<<endl;
        }
    }
private:
    int dist_mol_e;float grade;int z;
    void start(){
        cout<<"Starting Molecula Auxiliar"<<endl;
    }
    void getParts(int dist_mol,float grad,int z1){
        dist_mol_e=dist_mol;grade=grad;z=z1;
        glPushMatrix();
        glTranslatef (dist_mol_e*cos(grade*PI/180),dist_mol_e*sin(grade*PI/180),z);
        glRotatef(0.0,0,0,1.0);
        glColor3f(0,1,-1);
        glutWireSphere(0.5,25,25);
        glPopMatrix();
    }
};

class Builder{
public:
    Molecula *molecula;
    vector<int> acciones;
    Builder(){

    }
    void setMolecula(int i){
        if(i==1) this->molecula = new MoleculaI;
        else if (i==2) this->molecula = new MoleculaS;
    }
    void addGetCompuesto(){
        this->acciones.push_back(1);
    }
    /*void addformar(){
        this->acciones.push_back(2);
    }
    void addRevisar(){
        this->acciones.push_back(3);
    }
    void addImposible(){
        this->acciones.push_back(100);
    }*/
    Molecula *getMolecula(){
        this->molecula->cargaAcciones(this->acciones);
        return this->molecula;
    }
};

int mainWindow;
int cantidad;
class COMPUESTO{

    public:
        COMPUESTO(){}
        void text(string a,int b){
            cantidad=b;
            std::cout<<b;
        }
        static void resize(int ancho, int alto){
            const float aux = (float)ancho/(float)alto;
            glViewport(0,0,ancho,alto);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(6,-6,5,-5,10,-10);//GENERA LA ESFERA DE FORMA CIRCULAR izq,der,arr,ab,espacio de vision
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
        }


        static void display(void){

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glColor3d(1,0,0);

            //MOLECULA
            //MOLECULA a;
            Builder *a= new Builder;
            a->setMolecula(1);
            a->addGetCompuesto();
            Molecula *Molecula = a->getMolecula();
            Molecula->trabajar();

            for (int i=0;i<cantidad-1;i++){
                if(i<4){
                    Builder *aix= new Builder;
                    aix->setMolecula(2);
                    aix->addGetCompuesto();
                    //Molecula *Mol ;
                    //Mol = b->getParts(2,90*i,0);
                    Mol = aix->getMolecula();
                    Mol->trabajar();
                }
                else{
                    Builder *c= new Builder;
                    c->setMolecula(2);
                    c->addGetCompuesto();
                    //Molecula *Molecul = c->getParts(0,90*i,2);
                    Molecul = c->getMolecula();
                    Molecul->trabajar();
                }
            }
            glutSwapBuffers();
        }
        static void idle(void){
            glutPostRedisplay();
        }
        static void timer(int x){
            if(rotacion==1){
                rotacion_molecula += 5.0;
            }
            glutTimerFunc(25, timer,0);
        }

        static void Movimiento(unsigned char key, int x, int y){
            switch (key){
                case 'n':
                    if(traslacion==0 || rotacion==0){
                        rotacion=1;
                        traslacion=1;
                    }
                    else{
                        rotacion=0;
                        traslacion=0;
                    }
                case 27:
                    glutDestroyWindow(mainWindow);
                    break;
            }
            glutPostRedisplay();
        }


        static void Control(int key, int x, int y) {
          switch (key) {
            case GLUT_KEY_UP :
              glRotatef(-1.0, 1.0, 0.0, 0.0);
            break;

            case GLUT_KEY_DOWN :
              glRotatef(1.0, 1.0, 0.0, 0.0);
            break;

            case GLUT_KEY_LEFT :
              glRotatef(-1.0, 0.0, 1.0, 0.0);
            break;

            case GLUT_KEY_RIGHT :
              glRotatef(1.0, 0.0, 1.0, 0.0);
            break;
          }
          glutPostRedisplay();
        }


        void iniciar()
        {
            glutInitWindowSize(720,480);
            glutInitWindowPosition(0,0);
            glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);


            mainWindow=glutCreateWindow("MOLECULAS");
            glutSetWindow (mainWindow);
            glutReshapeFunc(resize);
            glutDisplayFunc(display);
            glutKeyboardFunc(Movimiento);
            glutSpecialFunc(Control);
            glutIdleFunc(idle);
            glutTimerFunc(25,timer,0);
            glClearColor(0,0,0,0);
            glEnable(GL_DEPTH_TEST);
            glutMainLoop();


        }
        void salir(){
            glutDestroyWindow(mainWindow);
            EXIT_SUCCESS;
        }
};



#endif
