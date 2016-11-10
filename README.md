# sgogl
Simple Graphics - OpenGL
aka SGOGL

Just my shitty little 2D graphics library I made partly for fun and partly for a simple graphics library for other projects. I used GLFW and SOIl to make it

The design was very greatly influenced and inspired by BearLibTerminal (http://foo.wyrd.name/en:bearlibterminal). A truly great graphics library that is a beacon of simplicity

This, however, isn't BLT, it's SGOGL. Good luck trying to use it. I understand it because I made it and I don't care if anyone else can or can't understand it.

Its kind of just like a proxy for GLFW *and OpenGL* to make it easy(er) to make a window and start rendering 2D stuff

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

See [initialization](./documentation_initialization.md) for initialization info

## Contributing

Feel free to do whatever tf you want, just don't fck my sht up if you know what I mean. And remember that:

*1.* I don't usually work with graphics so forgive my stupidity

*2.* The goal of sgogl is to be as get-up-and-go fast as possible. ie: Just let me draw stuff to my screen, you know? The library should have a base case of operation first and let the user control everything afterwards. What I mean by that is like the about sample program: I don't have to go through a lengthy initialization process, I just call gr_open() and away I go; I can do more initialization through other functions later. If you want more examples of how it should operate just look up BearLibTerminal (its much better than sgogl tobh)

## Credits:

BLT: for inspiration

GLFW: because SGOGL uses it (and for the confidence I got from it to use a really shitty name)

SOIL: Simple Opengl Image Loading Library, or something like that. I also used it too. It's pretty cool

