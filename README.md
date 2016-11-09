# sgogl
Simple Graphics - OpenGL
aka SGOGL

Just my shitty little graphics library I made partly for fun and partly for a simple graphics library for other projects. I used GLFW and SOIl to make it

The design was very greatly influenced and inspired by BearLibTerminal (http://foo.wyrd.name/en:bearlibterminal). A truly great graphics library that is a beacon of simplicity
This, however, isn't BLT, it's SGOGL. Good luck trying to use it. I understand it because I made it and I don't care if anyone else can or can't understand it.

Its kind of just like a proxy for GLFW to make it easy(er) to make a window and start rendering stuff

## Use:

Here is a bare minimum program to get something on the screen:

```c
#include "sgogl.h"

int running = 1;
void window_close_cb(){
  running = 0;
}

void main(){

  gr_open();
  gr_window_close_function(&window_close_cb);

  while(running){
    gr_clear();
    gr_poll_events();
    gr_view_centered(0.0, 0.0, 1.0, 0.0);
    gr_draw_point(0.0f, 0.0f, 2.0f);
    gr_refresh();
  }
}
```

Then you just need to link to your libsgogl.a (or whatever you called it) lib file and the libglfw3.a lib file... And that's it, you should have a 1 pixel point on your screen

## Credits:

BLT: for inspiration

GLFW: because SGOGL uses it (and for the confidence I got from it to use a really shitty name)

SOIL: Simple Opengl Image Loading Library, or something like that. I also used it too. It's pretty cool

