#include <tabla.h>
#include <iostream>
#ifndef _STATE_H
#define _STATE_H

class Game;
class Encendido;
class Apagado;

class State{
public:
    static Encendido on;
    static Apagado off;

    virtual ~State() {
        std::cout << "el estado esta destruido" << std::endl;
    }
    virtual void handleinput(Game& game, int arbitary) {}
    virtual void update(Game& game) {}

};
tabla elemento(1280,730);
class Game{

    public:
        Game(){
            elemento.start();
        }
        ~Game(){
            elemento.destroyer();
        }
        virtual void handleinput(int arbitary){
            state_->handleinput(*this, arbitary);
        }
        virtual void update(){
            state_->update(*this);
        }

    //private:
        State* state_;
};

class Encendido : public State{
public:
    Encendido(){
        std::cout << "CONECTADO" << std::endl;
    }
    virtual void handleinput(Game& game, int arbitary);
    virtual void update(Game& game) {}
};
class Apagado : public State{
public:
    Apagado()   {
        std::cout << "DESCONECTADO" << std::endl;
    }
    virtual void handleinput(Game& game, int arbitary);
    virtual void update(Game& game) {}
};

void Encendido::handleinput(Game& game, int arbitary)
{
    if (arbitary == 1)
        game.state_ = &State::off;
}

void Apagado::handleinput(Game& game, int arbitary)
{
    if (arbitary == 0)
        game.state_ = &State::on;
}

Encendido State::on;
Apagado State::off;





#endif
