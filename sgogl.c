#include <stdlib.h>
// #define GLEW_STATIC
#include <glad/glad.h>
#include <glad/glad.c>
// #include <gl/gl.h>
#include <SDL2/sdl.h>
#include <SDL2/sdl_mixer.h>
#include <soil.h>
#include "sgogl.h"
// #include "include/glfw3.h"
#define SDL_MAIN_HANDLED

float max_depth = 10.0f;
int use_texture_filtering = 1;
int texture_filter = GL_LINEAR;
// aspect_ratio is determined by the window size
// window sizes ~= window size
// aspect mods are for modifying width, height after aspect_ratio is calculated
int default_window_width = 640, default_window_height = 480;
float window_aspect_ratio, window_x_aspect_mod, window_y_aspect_mod;
int window_width, window_height;
// screen sizes ~= internal rendering size
// aspect mods are for modifying screen_height, view_height after aspect_ratio is calculated
int screen_keep_window_aspect = 0; // should the screen automatically fit its size to match the window's aspect ratio?
int center_screen = 0; // if screen_keep_window_aspect is false then should the screen be placed centered in the window?
int stretch_screen = 0; // should the screen completely ignore aspect ratios and simply stretch to the window?
int default_screen_width = 640, default_screen_height = 480;
float screen_aspect_ratio;
float screen_x_aspect_mod, screen_y_aspect_mod;
int screen_width, screen_height;
// the sub viewport is where the screen is projected to in the viewport which is projected to the window
int sub_viewport_x0 = 0, sub_viewport_y0 = 0; // where is the screen situated in the window
int sub_viewport_x1 = 0, sub_viewport_y1 = 0; // where is the screen situated in the window
int sub_viewport_width, sub_viewport_height; // what size is the screen in the window
unsigned int framebuffer;
unsigned int renderbuffer_color, renderbuffer_depth;
// view sizes ~= camera in world size
float view_width, view_height, view_scale;
float view_left, view_right, view_bottom, view_top;
int mouse_x, mouse_y;
int mouse_x_delta, mouse_y_delta;
int bordered, fullscreen, mouse_grabbed;
int is_open = 0;
int init_error = 0;
SDL_Window* window;
SDL_GLContext opengl_context;
SDL_Event current_event;
int wait_event = 0;
const Uint8* keystates;
int mouse_left, mouse_middle, mouse_right;
Mix_Chunk** mix_chunk_list = NULL;
int mix_chunk_list_length = 0;

/******************/
/** Sub-Viewport **/

void update_sub_viewport(){
  if(stretch_screen){
    sub_viewport_width = window_width;
    sub_viewport_height = window_height;
    sub_viewport_x0 = 0;
    sub_viewport_y0 = 0;
    sub_viewport_x1 = window_width;
    sub_viewport_y1 = window_height;
  }
  else {
    if(screen_aspect_ratio > window_aspect_ratio){
      sub_viewport_width  = window_width;
      sub_viewport_height = (int)((float)window_width/screen_aspect_ratio);
      if(center_screen){
        sub_viewport_x0 = 0;
        sub_viewport_x1 = window_width;
        sub_viewport_y0 = (window_height - sub_viewport_height)/2;
        sub_viewport_y1 = (window_height + sub_viewport_height)/2;
      }
      else {
        sub_viewport_x0 = 0;
        sub_viewport_y0 = 0;
        sub_viewport_x1 = sub_viewport_width;
        sub_viewport_y1 = sub_viewport_height;
      }
    }
    else {
      sub_viewport_width  = (int)((float)window_height*screen_aspect_ratio);
      sub_viewport_height = window_height;
      if(center_screen){
        sub_viewport_x0 = (window_width - sub_viewport_width)/2;
        sub_viewport_x1 = (window_width + sub_viewport_width)/2;
        sub_viewport_y0 = 0;
        sub_viewport_y1 = window_height;
      }
      else {
        sub_viewport_x0 = 0;
        sub_viewport_y0 = 0;
        sub_viewport_x1 = sub_viewport_width;
        sub_viewport_y1 = sub_viewport_height;
      }
    }
  }
}

/*********************/
/** Window Resizing **/

void calc_window_aspect(){
  window_aspect_ratio = (float)window_width/(float)window_height;
  if(window_aspect_ratio > 1){
    window_x_aspect_mod = window_aspect_ratio;
    window_y_aspect_mod = 1;
  }
  else {
    window_x_aspect_mod = 1;
    window_y_aspect_mod = 1/window_aspect_ratio;
  }
}

void gr_set_window_max_size(int w, int h){ SDL_SetWindowMaximumSize(window, w, h); }
void gr_set_window_min_size(int w, int h){ SDL_SetWindowMinimumSize(window, w, h); }

void gr_set_window_size(int w, int h){
  window_width = w; window_height = h;
  if(window_width  < 1) window_width  = 1;
  if(window_height < 1) window_height = 1;
  SDL_SetWindowSize(window, w, h);
  calc_window_aspect();
  if(screen_keep_window_aspect){
    if(w > h){
      screen_width = w;
      screen_height = (int)((float)w/window_aspect_ratio);
    }
    else {
      screen_width = (int)((float)h*window_aspect_ratio);
      screen_height = h;
    }
    screen_aspect_ratio = window_aspect_ratio;
  }
  update_sub_viewport();
}

void sync_window_size(){
  SDL_GetWindowSize(window, &window_width, &window_height);
  calc_window_aspect();
  update_sub_viewport();
}

/*********************/
/** Screen Resizing **/

void calc_screen_aspect(){
  screen_aspect_ratio = (float)screen_width/(float)screen_height;
  if(screen_aspect_ratio > 1){
    screen_x_aspect_mod = screen_aspect_ratio;
    screen_y_aspect_mod = 1;
  }
  else {
    screen_x_aspect_mod = 1;
    screen_y_aspect_mod = 1/screen_aspect_ratio;
  }
}

void gr_set_screen_size(int w, int h){
  if(screen_keep_window_aspect){
    if(w > h){
      screen_width = w;
      screen_height = (int)((float)w/window_aspect_ratio);
    }
    else {
      screen_width = (int)((float)h*window_aspect_ratio);
      screen_height = h;
    }
  }
  else {
    screen_width = w;
    screen_height = h;
  }
  if(screen_width  < 1) screen_width  = 1;
  if(screen_height < 1) screen_height = 1;
  /*
  From the opengl.org wiki:
  "
  calling this function [glRenderbufferStorage] on a renderbuffer that has already had this function called on it will cause it to deallocate any resources associated with the previous call and allocate new storage.
  Note: You are strongly advised not to do this. If you need a new renderbuffer, just delete the old object and create a new one. Recreating a renderbuffer with the same object name can cause completeness problems, particularly if it is attached to another object at the time.
  "
  I'm not sure what a 'completeness problem' is but I know these renderbuffers are only used wrt renderbuffer_color and renderbuffer_depth
  */
  glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer_color);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, screen_width, screen_height);
  glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer_depth);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, screen_width, screen_height);
  calc_screen_aspect();
  update_sub_viewport();
}

/**********/
/** View **/

void gr_view(float x, float y, float s, float ang){
  glMatrixMode(GL_PROJECTION);
  float sp = 1/s;
  glLoadIdentity();
  view_scale = s;
  view_width = s*screen_x_aspect_mod; view_height = s*screen_y_aspect_mod;
  view_left = x; view_right = x + view_width;
  view_bottom = y; view_top = y + view_height;
  glOrtho(view_left, view_right, view_bottom, view_top, 0, -max_depth);
  glRotatef(ang, 0, 0, 1);
}

void gr_view_centered(float x, float y, float s, float ang){
  glMatrixMode(GL_PROJECTION);
  float sp = 1/s;
  glLoadIdentity();
  view_scale = s;
  view_width = s*screen_x_aspect_mod; view_height = s*screen_y_aspect_mod;
  view_left = x - view_width/2; view_right = x + view_width/2;
  view_bottom = y - view_height/2; view_top = y + view_height/2;
  glOrtho(view_left, view_right, view_bottom, view_top, 0, -max_depth);
  glRotatef(ang, 0, 0, 1);
}

// These should be called gr_window_to_world_*
float gr_screen_to_world_x(int x){
  return view_left + view_width * ((float)(x - sub_viewport_x0) / (float)sub_viewport_width);
}
float gr_screen_to_world_y(int y){
  return view_top -  view_height * ((float)(y - sub_viewport_y0) / (float)sub_viewport_height);
}


/*******************/
/** Informational **/

int gr_screen_width(){ return screen_width; }
int gr_screen_height(){ return screen_height; }
float gr_screen_x_aspect_mod(){ return screen_x_aspect_mod; }
float gr_screen_y_aspect_mod(){ return screen_y_aspect_mod; }

int gr_window_width(){ return window_width; }
int gr_window_height(){ return window_height; }
float gr_width_window_aspect_mod(){ return window_x_aspect_mod; }
float gr_height_window_aspect_mod(){ return window_y_aspect_mod; }

float gr_view_scale(){ return view_scale; }
float gr_view_width(){ return view_width; }
float gr_view_height(){ return view_height; }
float gr_view_left(){ return view_left; }
float gr_view_right(){ return view_right; }
float gr_view_bottom(){ return view_bottom; }
float gr_view_top(){ return view_top; }

float gr_max_depth(){ return max_depth; }

int gr_get_window_width(){
  sync_window_size;
  return window_width;
}
int gr_get_window_height(){
  sync_window_size;
  return window_height;
}

/************************************/
/** Setting Variables / Parameters **/

void gr_set_keep_window_aspect(int value){
  screen_keep_window_aspect = value;
  update_sub_viewport();
}

void gr_set_center_screen(int value){
  center_screen = value;
  update_sub_viewport();
}

void gr_set_stretch_screen(int value){
  stretch_screen = value;
  update_sub_viewport();
}

void gr_activate_events(int val){
  if(val)
    SDL_InitSubSystem(SDL_INIT_EVENTS);
  else
    SDL_QuitSubSystem(SDL_INIT_EVENTS);
}

void gr_set_max_depth(float depth){
  max_depth = depth;
}

void gr_activate_transparency(int blend){
  if(blend){
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST); // alpha testing - wew lad
  }
  else{
    glDisable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);
  }
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  glAlphaFunc(GL_GREATER, 0.1f);
}

void gr_activate_linear_filtering(int filtering){
  if(filtering){
    use_texture_filtering = 1;
    texture_filter = GL_LINEAR;
  }
  else {
    use_texture_filtering = 0;
    texture_filter = GL_NEAREST;
  }
}

void gr_activate_dithering(int dither){
  if(dither)
    glEnable(GL_DITHER);
  else
    glDisable(GL_DITHER);
}

void gr_set_opengl_doublebuffering(int buffering){
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, buffering);
}

enum {
  DT_NEVER    = GL_NEVER, 
  DT_LESS     = GL_LESS, 
  DT_EQUAL    = GL_EQUAL, 
  DT_LEQUAL   = GL_LEQUAL, 
  DT_GREATER  = GL_GREATER, 
  DT_NOTEQUAL = GL_NOTEQUAL, 
  DT_GEQUAL   = GL_GEQUAL, 
  DT_ALWAYS   = GL_ALWAYS
};
void gr_activate_depth_testing(int deptht){
  if(deptht)
    glEnable(GL_DEPTH_TEST);
  else
    glDisable(GL_DEPTH_TEST);
  glDepthFunc(DT_LESS);
}

void gr_toggle_window_bordered(){ bordered = !bordered; SDL_SetWindowBordered(window, bordered); }
void gr_set_window_brightness(float b){ SDL_SetWindowBrightness(window, b); }
void gr_set_window_fullscreen(){ fullscreen = GR_WINDOW_FULLSCREEN; SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN); }
void gr_set_window_fullscreen_desktop(){ fullscreen = GR_WINDOW_FULLSCREEN_DESKTOP; SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP); }
void gr_set_window_windowed(){ fullscreen = GR_WINDOW_WINDOWED; SDL_SetWindowFullscreen(window, 0); }
void gr_toggle_mouse_grabbed(){ mouse_grabbed = !mouse_grabbed; SDL_SetWindowGrab(window, mouse_grabbed); }
int  gr_set_window_icon(char* file){
  SDL_Surface* icon = SDL_LoadBMP(file);
  if(icon != NULL){
    SDL_SetWindowIcon(window, icon);
    return 0;
  }
  return 1;
}
//Tested: Doesn't work?
void gr_set_input_focus(){
  //SDL_SetWindowInputFocus(window);
  SDL_RaiseWindow(window);
}

void gr_set_window_position(int x, int y){ SDL_SetWindowPosition(window, x, y); }
void gr_set_window_title(char* title){ SDL_SetWindowTitle(window, title); }

void gr_popup_error(char* message){ SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "error", message, window); }
void gr_popup_warning(char* message){ SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "warning", message, window); }
void gr_popup_info(char* message){ SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "info", message, window); }

/************/
/** Colors **/

void gr_color(float r, float g, float b, float a){
  glColor4f(r, g, b, a);
}

void gr_color_alpha(float a){
  glColor4f(a, a, a, a);
}

/************/
/** Images **/

unsigned int gr_load_image_ram(const unsigned char* const data, unsigned int id, int width, int height, int channels, unsigned int flags){
  return SOIL_create_OGL_texture(data, width, height, channels, id, flags);
}

unsigned int gr_load_image_ext(char* file, unsigned int id, unsigned int soil_load_flag, unsigned int soil_flags){
  // Use id = 0 for new id
  return SOIL_load_OGL_texture(file, soil_load_flag, id, soil_flags);
}

unsigned int gr_load_image(char* file, unsigned int id){
  return SOIL_load_OGL_texture(file, SOIL_LOAD_AUTO, id, SOIL_FLAG_MULTIPLY_ALPHA);
}

void gr_unload_image(unsigned int id){
  if(glIsTexture(id)){
    unsigned int idl[1];
    idl[0] = id;
    glDeleteTextures(1, idl);
   }
}

int gr_screenshot(char* file){
  SOIL_save_screenshot(file, SOIL_SAVE_TYPE_BMP, 0, 0, screen_width, screen_height);
} 

/***********/
/** Audio **/

void resize_mix_chunk_list(int size){
  // I hope this does what I think it does otherwise there will be MEMORY LEAKS right here
  if(size < mix_chunk_list_length)
    for(int i = size; i < mix_chunk_list_length; i++){
      if(mix_chunk_list[i] != NULL)
        Mix_FreeChunk(mix_chunk_list[i]);
      mix_chunk_list[i] = NULL;
    }
  mix_chunk_list = (Mix_Chunk**)realloc(mix_chunk_list, size * sizeof(Mix_Chunk*));
  mix_chunk_list_length = size;
  for(int i = size; i < mix_chunk_list_length; i++)
    mix_chunk_list[i] = NULL;
}

int find_available_mix_chunk_list_id(){
  // Search the list for a null list location
  // There may be a better (faster) way to do this, but it probably isn't necessary
  for(int i = 0; i < mix_chunk_list_length; i++){
    if(mix_chunk_list[i] == NULL)
      return i;
  }
  // If it reaches here a location wasn't found. So, create one by resizing the list:
  resize_mix_chunk_list(mix_chunk_list_length * 2);
  return mix_chunk_list_length;
}

int gr_load_wav(char* file, int id){
  // Use id = 0 for new id
  if(id < 0)
    return -1;
  if(id == 0){
    int true_id = find_available_mix_chunk_list_id();
    mix_chunk_list[true_id] = Mix_LoadWAV(file);
    if(mix_chunk_list[true_id] != NULL)
      return true_id;
  }
  // id is greated than mix_chunk_list_length
  else if(mix_chunk_list_length <= id){
    resize_mix_chunk_list(mix_chunk_list_length * 2);
    mix_chunk_list[id] = Mix_LoadWAV(file);
    if(mix_chunk_list[id] != NULL)
      return id;
  }
  // List location is free
  else if(mix_chunk_list[id] == NULL){
    mix_chunk_list[id] = Mix_LoadWAV(file);
    if(mix_chunk_list[id] != NULL)
      return id;
  }
  // List location is in use - must be freed
  else {
    /* 
    Here I quote the sdl_mixer devs:
      Do not use chunk after this without loading a new sample to it. 
      Note: It's a bad idea to free a chunk that is still being played... 
    */
    Mix_FreeChunk(mix_chunk_list[id]);
    mix_chunk_list[id] = Mix_LoadWAV(file);
    if(mix_chunk_list[id] != NULL)
      return id;
  }
  return -1;
}
void gr_unload_audio(int id){
  if( 0 < id && id < mix_chunk_list_length && mix_chunk_list[id] != NULL)
    Mix_FreeChunk(mix_chunk_list[id]);
}

void gr_set_channel_number(int number){
  Mix_AllocateChannels(number);
}

// Warning: using an id not explicitly registered using one of the above functions
// produces undefined behavior. Bounds checks et al are left out for speed
int gr_play_once(int id){
  return Mix_PlayChannel(-1, mix_chunk_list[id], 0);
}
int gr_play_once_on(int id, int channel){
  return Mix_PlayChannel(channel, mix_chunk_list[id], 0);
}
int gr_play(int id, int loops){
  return Mix_PlayChannel(-1, mix_chunk_list[id], loops);
}
int gr_play_on(int id, int loops, int channel){
  return Mix_PlayChannel(channel, mix_chunk_list[id], loops);
}
int gr_play_timed(int id, int time_ms){
  return Mix_PlayChannelTimed(-1, mix_chunk_list[id], -1, time_ms);
}
int gr_play_timed_on(int id, int channel, int time_ms){
  return Mix_PlayChannelTimed(channel, mix_chunk_list[id], -1, time_ms);
}

void gr_pause(int channel){
  Mix_Pause(channel);
}
void gr_resume(int channel){
  Mix_Resume(channel);
}
int gr_paused(int channel){
  return Mix_Paused(channel);
}
void gr_stop(int channel){
  Mix_HaltChannel(channel);
}
int gr_stopped(int channel){
  // -1 -> number of channels playing
  return Mix_Playing(channel);
}

void gr_set_volume(int channel, int volume){
  // Use -1 for all channels
  Mix_Volume(channel, volume);
}
void gr_set_panning(int channel, int v_left, int v_right){
  Mix_SetPanning(channel, v_left, v_right);
}
void gr_set_mono(int channel){
  Mix_SetPanning(channel, 255, 255);
}
void gr_set_attenuation(int channel, int distance){
  Mix_SetDistance(channel, distance);
}
void gr_set_no_attenuation(int channel){
  Mix_SetDistance(channel, 0);
}

/*************/
/** Drawing **/

void gr_draw(unsigned int tex, float x, float y, float z, float anx, float any, float angle, float sx, float sy){
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  // Before rot -> sets center / global transforms / global frame
  // After  rot -> sets pivot / local transforms / rotated frame
  glTranslatef(x, y, z);
  glRotatef(angle, 0.0f, 0.0f, 1.0f);
  glScalef(sx, sy, 1.0);
  glTranslatef(-anx, -any, 0.0f);
  
  glEnable(GL_TEXTURE_2D);
  // if(use_texture_filtering)
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // else
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture_filter);
  glBindTexture(GL_TEXTURE_2D, tex);
  glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 0.0, 0.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 0.0, 0.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 1.0, 0.0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  // glFlush();
}

void gr_draw_centered(unsigned int tex, float x, float y, float z, float angle, float sx, float sy){
  gr_draw(tex, x, y, z, 0.5f, 0.5f, angle, sx, sy);
}

void gr_point_size(float s){
  glPointSize(s);
}

void gr_draw_point(float x, float y, float z){
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glBegin(GL_POINTS);
    glVertex3f(x, y, z);
  glEnd();
  // glFlush();
}

void gr_draw_line(float x0, float y0, float x1, float y1, float z){
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glBegin(GL_LINES);
    glVertex3f(x0, y0, z);
    glVertex3f(x1, y1, z);
  glEnd();
  // glFlush();
}

void gr_draw_line_sp(float x0, float y0, float z0, float x1, float y1, float z1){
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glBegin(GL_LINES);
    glVertex3f(x0, y0, z0);
    glVertex3f(x1, y1, z1);
  glEnd();
  // glFlush();
}

/***************************/
/** Refreshing / Clearing **/

void gr_refresh(){
  // printf("gr_refresh screen %d %d window %d %d\n", screen_width, screen_height, window_width, window_height);
  glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  glBlitFramebuffer(0, 0, screen_width, screen_height, 
                    sub_viewport_x0, sub_viewport_y0, 
                    sub_viewport_x1, sub_viewport_y1, 
                    GL_COLOR_BUFFER_BIT, GL_NEAREST);
  glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
  SDL_GL_SwapWindow(window);
  glViewport(0, 0, screen_width, screen_height);
  // SDL_UpdateWindowSurface(window);
}

void gr_clear_depth(){
  glClear(GL_DEPTH_BUFFER_BIT);
}
void gr_clear(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void gr_clear_all(){
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
}
void gr_clear_color(float r, float g, float b, float a){
  glClearColor(r, g, b, a);
}
void gr_clear_colored(float r, float g, float b, float a){
  glClearColor(r, g, b, a);
  gr_clear();
}
void gr_wait_for_render(){
  glFinish();
}

/*************/
/** Events **/

/**
gr_register_events should be called before:
  graphics_has_event
  graphics_read_event
*/
void gr_register_events(){
  SDL_PumpEvents();
}

int gr_has_event(){
  return SDL_HasEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
}

/**
Call gr_read_mouse() to update the mouse values then called the getters
*/
void gr_read_mouse(){
  SDL_GetRelativeMouseState(&mouse_x_delta, &mouse_y_delta);
  uint32_t field = SDL_GetMouseState(&mouse_x, &mouse_y);
  mouse_left   = SDL_BUTTON(SDL_BUTTON_LEFT);
  mouse_middle = SDL_BUTTON(SDL_BUTTON_MIDDLE);
  mouse_right  = SDL_BUTTON(SDL_BUTTON_RIGHT);
}
int gr_mouse_x(){ return mouse_x; }
int gr_mouse_y(){ return mouse_y; }
int gr_mouse_left(){ return mouse_left; }
int gr_mouse_middle(){ return mouse_middle; }
int gr_mouse_right(){ return mouse_right; }

void gr_set_wait_event(int value){
  wait_event = value;
}
int gr_read(){
  if(wait_event)
    SDL_WaitEvent(&current_event);
  else
    SDL_PollEvent(&current_event);
  switch(current_event.type){
    case SDL_QUIT:
      return GR_CLOSE;
    case SDL_KEYDOWN:
    case SDL_KEYUP:
      return GR_KEY_EVENT;
    case SDL_WINDOWEVENT:
      if(current_event.window.event == GR_WINDOW_RESIZED){
        sync_window_size();
      }
      return GR_WINDOW_EVENT;
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
      return GR_MOUSE_BUTTON_EVENT;
    case SDL_MOUSEMOTION:
      return GR_MOUSE_MOVE_EVENT;
    case SDL_MOUSEWHEEL:
      return GR_MOUSE_WHEEL_EVENT;
    default:
      return GR_NULL_EVENT;
  }
  return GR_NULL_EVENT;
}


/**
Key event functions
*/
int gr_key_repeated(){
  return current_event.key.repeat;
}

int gr_key_pressed(){
  return current_event.key.state;
}

int gr_key(){
  return current_event.key.keysym.sym;
}

int gr_scancode(){
  return current_event.key.keysym.scancode;
}

/**
Mouse button event functions
*/
int gr_mouse_button(){
  return current_event.button.button;
}
int gr_mouse_state(){
  // returns what type of button event it was (press, release)
  return current_event.button.state;
}

int gr_mouse_clicks(){
  return current_event.button.clicks;
}

int gr_mouse_button_x(){
  return current_event.button.x;
}

int gr_mouse_button_y(){
  return current_event.button.y;
}

/**
Mouse movement event functions
*/
int gr_mouse_move_x(){
  return current_event.motion.x;
}
int gr_mouse_move_y(){
  return current_event.motion.y;
}

int gr_mouse_move_xrel(){
  return current_event.motion.xrel;
}
int gr_mouse_move_yrel(){
  return current_event.motion.yrel;
}

/**
Mouse wheel event functions
*/
int gr_wheel(){
  return current_event.wheel.y;
}

/**
Window event functions
*/
int gr_window_event(){
  return current_event.window.event;
}

/***********************************/
/** Initialization / Finalization **/

int gr_open(){
  if(!is_open){
    is_open = 1;
    init_error = 0;
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    Mix_Init(0);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
    resize_mix_chunk_list(64);
    
    window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                              default_window_width, default_window_height, 
                              SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if(window == NULL)
      init_error = init_error | IERROR_SDL_WINDOW;
    opengl_context = SDL_GL_CreateContext(window);
    if(opengl_context == NULL)
      init_error = init_error | IERROR_SDL_GL;
    if(!gladLoadGL()){
      printf("glad failed to load\n");
    }
    
    // Creating FBO and RBOs
    glGenRenderbuffers(1, &renderbuffer_color);
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer_color);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, default_screen_width, default_screen_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    
    glGenRenderbuffers(1, &renderbuffer_depth); 
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer_depth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, default_screen_width, default_screen_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);   

    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderbuffer_color);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderbuffer_depth);

    gr_activate_transparency(1);
    gr_activate_depth_testing(1);
    // glEnable(GL_CULL_FACE);
    // glEnable(GL_BLEND
    
    // SDL_GetWindowSize(window, &window_width, &window_height);
    sync_window_size;
    gr_set_screen_size(default_screen_width, default_screen_height);
    gr_set_window_size(default_window_width, default_window_height);
  }
  return init_error;
}

void gr_close(){
  if(is_open){
    is_open = 0;
    init_error = 0;
    SDL_GL_DeleteContext(opengl_context);
    SDL_DestroyWindow(window);
    SDL_Quit;
  }
}
