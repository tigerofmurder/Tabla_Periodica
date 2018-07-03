#include <allegro.h>
#include <tabla.h>
#include <iniciar.h>
#include <base.h>

using namespace std;


int main(){
    init(1280,730);
    tabla elemento(1280,730);
    elemento.start();
    elemento.destroyer();
    deinit();

    return 0;

}
END_OF_MAIN();
