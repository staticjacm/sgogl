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