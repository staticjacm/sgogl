#include "sgogl.h"

int running = 1;

void main(){

  gr_open();
  
  while(running){
    gr_clear();
    gr_register_events();
    while(gr_has_event()){
      int event = gr_read();
      if(event == GR_CLOSE)
        running = 0;
    }
    gr_view_centered(0.0, 0.0, 1.0, 0.0);
    gr_draw_point(0.0f, 0.0f, 2.0f);
    gr_refresh();
  }
}