#ifndef _INICIAR_H
#define _INICIAR_H

void init(int x=1280,int y=720){
    int depth,res;
    allegro_init();
    depth=desktop_color_depth();
    if(depth==0){
        depth=32;
    }
    set_color_depth(depth);
    res=set_gfx_mode(GFX_AUTODETECT_WINDOWED,x,y,0,0);
    if(res!=0){
        allegro_message(allegro_error);
        exit(-1);
    }

    install_timer();
    install_keyboard();
    install_mouse();
    enable_hardware_cursor();
    select_mouse_cursor (MOUSE_CURSOR_ARROW);
}

void deinit() {
	clear_keybuf();
}

#endif
