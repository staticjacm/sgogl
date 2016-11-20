#include <stdlib.h>
#include "include/glfw3.h"
#define SDL_MAIN_HANDLED
#include "include/SDL2/sdl.h"
#include "include/soil.h"
#include <gl/gl.h>

float max_depth = 10.0f;
int screen_width, screen_height;
int use_texture_filtering = 1;
float screen_aspect, x_aspect_mod, y_aspect_mod;
float view_width, view_height, view_scale;
float view_left, view_right, view_bottom, view_top;
int mouse_x, mouse_y;
int bordered, fullscreen, mouse_grabbed;
int is_open = 0;
int init_error = 0;
SDL_Window* window;
SDL_GLContext opengl_context;
SDL_Event current_event;
int wait_event = 0;
const Uint8* keystates;
int mouse_left, mouse_middle, mouse_right;

/******************************/
/** Proxies for SDL values **/

/**
IERROR_SDL_WINDOW:
  "Conflicting window flags specified"
  "Window is too large."
  "No OpenGL support in video driver"
IERROR_SDL_GL
  "The specified window isn't an OpenGL window"
  
**/
enum {
  IERROR_SDL_NONE      = 0b000,
  IERROR_SDL_WINDOW    = 0b001,
  IERROR_SDL_GL        = 0b010
};

/**
Event codes
*/
enum {
  GR_NULL_EVENT,
  GR_KEY_EVENT,
  GR_WINDOW_EVENT,
  GR_QUIT_EVENT,
  GR_MOUSE_BUTTON_EVENT,
  GR_MOUSE_MOVE_EVENT,
  GR_MOUSE_WHEEL_EVENT
};

/**
Window event codes
*/
enum {                               
  GR_WINDOW_NONE           = 0,      
  GR_WINDOW_SHOWN          = 1,      
  GR_WINDOW_HIDDEN         = 2,      
  GR_WINDOW_EXPOSED        = 3,      
                                     
  GR_WINDOW_MOVED          = 4,      
                                     
  GR_WINDOW_RESIZED        = 5,      
  GR_WINDOW_SIZE_CHANGED   = 6,      
  GR_WINDOW_MINIMIZED      = 7,      
  GR_WINDOW_MAXIMIZED      = 8,      
  GR_WINDOW_RESTORED       = 9,      
                                     
  GR_WINDOW_ENTER          = 10,     
  GR_WINDOW_LEAVE          = 11,     
  GR_WINDOW_FOCUS_GAINED   = 12,     
  GR_WINDOW_FOCUS_LOST     = 13,     
  GR_WINDOW_CLOSE          = 14      
};

/**
Mouse button codes
*/
enum {
  GR_MOUSE_LEFT   = 1,
  GR_MOUSE_RIGHT  = 3,
  GR_MOUSE_MIDDLE = 2,
  GR_MOUSE_X1     = 4,
  GR_MOUSE_X2     = 5
};

/**
Key codes
*/
enum {
  GR_A                      = 97,
  GR_B                      = 98,
  GR_C                      = 99,
  GR_D                      = 100,
  GR_E                      = 101,
  GR_F                      = 102,
  GR_G                      = 103,
  GR_H                      = 104,
  GR_I                      = 105,
  GR_J                      = 106,
  GR_K                      = 107,
  GR_L                      = 108,
  GR_M                      = 109,
  GR_N                      = 110,
  GR_O                      = 111,
  GR_P                      = 112,
  GR_Q                      = 113,
  GR_R                      = 114,
  GR_S                      = 115,
  GR_T                      = 116,
  GR_U                      = 117,
  GR_V                      = 118,
  GR_W                      = 119,
  GR_X                      = 120,
  GR_Y                      = 121,
  GR_Z                      = 122,

  GR_0                      = 48,
  GR_1                      = 49,
  GR_2                      = 50,
  GR_3                      = 51,
  GR_4                      = 52,
  GR_5                      = 53,
  GR_6                      = 54,
  GR_7                      = 55,
  GR_8                      = 56,
  GR_9                      = 57,

  GR_MINUS                  = 45,
  GR_EQUALS                 = 61,
  GR_LBRACKET               = 91,
  GR_RBRACKET               = 93,
  GR_SLASH                  = 47,
  GR_BACKSLASH              = 92,
  GR_SEMICOLON              = 59,
  GR_APOSTROPHE             = 39,
  GR_GRAVE                  = 96,
  GR_COMMA                  = 44,
  GR_PERIOD                 = 46,
                            
  GR_F1                     = 1073741882,
  GR_F2                     = 1073741883,
  GR_F3                     = 1073741884,
  GR_F4                     = 1073741885,
  GR_F5                     = 1073741886,
  GR_F6                     = 1073741887,
  GR_F7                     = 1073741888,
  GR_F8                     = 1073741889,
  GR_F9                     = 1073741890,
  GR_F10                    = 1073741891,
  GR_F11                    = 1073741892,
  GR_F12                    = 1073741893,
                            
  GR_CTRL                   = 1073742048,
  GR_SHIFT                  = 1073742049,
  GR_ALT                    = 1073742050,
  GR_CAPSLOCK               = 1073741881,
                              
  GR_ESCAPE                 = 13,
  GR_RETURN                 = 8,
  GR_BACKSPACE              = 1073741896,
                            
  GR_PAUSE                  = 1073741897,
  GR_INSERT                 = 1073741898,
  GR_HOME                   = 1073741899,
  GR_PAGEUP                 = 1073741902,
  GR_PAGEDOWN               = 127,
  GR_DELETE                 = 1073741922,
                            
  GR_KP_0                   = 1073741913,
  GR_KP_1                   = 1073741914,
  GR_KP_2                   = 1073741915,
  GR_KP_3                   = 1073741916,
  GR_KP_4                   = 1073741917,
  GR_KP_5                   = 1073741918,
  GR_KP_6                   = 1073741919,
  GR_KP_7                   = 1073741920,
  GR_KP_8                   = 1073741921,
  GR_KP_9                   = 1073741908,
                            
  GR_KP_DIVIDE              = 1073741909,
  GR_KP_MULTIPLY            = 1073741911,
  GR_KP_PLUS                = 1073741923,
  GR_KP_PERIOD              = 1073741912,
  GR_KP_ENTER               = 1073741904,
                            
  GR_LEFT                   = 1073741905,
  GR_DOWN                   = 1073741903,
  GR_RIGHT                  = 1073741906,
  GR_UP                     = 0,
};

/**
Flipping codes
*/
enum {
  GR_FLIP_NONE         = 0,
  GR_FLIP_VERTICALLY   = 2,
  GR_FLIP_HORIZONTALLY = 1,
};

enum {
  GR_WINDOW_WINDOWED,
  GR_WINDOW_FULLSCREEN,
  GR_WINDOW_FULLSCREEN_DESKTOP
};


/*********************/
/** Window Resizing **/

void calc_aspect(){
  screen_aspect = (float)screen_width/(float)screen_height;
  glViewport(0, 0, screen_width, screen_height);
  if(screen_aspect > 1){
    x_aspect_mod = screen_aspect;
    y_aspect_mod = 1;
  }
  else {
    x_aspect_mod = 1;
    y_aspect_mod = 1/screen_aspect;
  }
}

/*******************/
/** Informational **/

int gr_width(){ return screen_width; }
int gr_height(){ return screen_height; }
float gr_width_aspect_mod(){ return x_aspect_mod; }
float gr_height_aspect_mod(){ return y_aspect_mod; }

float gr_view_scale(){ return view_scale; }
float gr_view_width(){ return view_width; }
float gr_view_height(){ return view_height; }
float gr_view_left(){ return view_left; }
float gr_view_right(){ return view_right; }
float gr_view_bottom(){ return view_bottom; }
float gr_view_top(){ return view_top; }

float gr_max_depth(){ return max_depth; }

/************************************/
/** Setting Variables / Parameters **/

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
  use_texture_filtering = filtering;
}

void gr_activate_dithering(int dither){
  if(dither)
    glEnable(GL_DITHER);
  else
    glDisable(GL_DITHER);
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
void gr_set_window_max_size(int w, int h){ SDL_SetWindowMaximumSize(window, w, h); }
void gr_set_window_min_size(int w, int h){ SDL_SetWindowMinimumSize(window, w, h); }
void gr_set_window_position(int x, int y){ SDL_SetWindowPosition(window, x, y); }
void gr_set_window_size(int w, int h){ screen_width = w; screen_height = h; SDL_SetWindowSize(window, w, h); }
void gr_set_window_title(char* title){ SDL_SetWindowTitle(window, title); }

void gr_popup_error(char* message){ SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "error", message, window); }
void gr_popup_warning(char* message){ SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "warning", message, window); }
void gr_popup_info(char* message){ SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "info", message, window); }

int gr_get_window_width(){
  int w;
  SDL_GetWindowSize(window, &w, NULL);
  return w;
}
int gr_get_window_height(){
  int h;
  SDL_GetWindowSize(window, NULL, &h);
  return h;
}

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


/**
  TAKEN FROM SOIL.h (see http://www.lonesock.net/soil.html)
  
	flags you can pass into SOIL_load_OGL_texture()
	and SOIL_create_OGL_texture().
	(note that if SOIL_FLAG_DDS_LOAD_DIRECT is used
	the rest of the flags with the exception of
	SOIL_FLAG_TEXTURE_REPEATS will be ignored while
	loading already-compressed DDS files.)

	SOIL_FLAG_POWER_OF_TWO: force the image to be POT
	SOIL_FLAG_MIPMAPS: generate mipmaps for the texture
	SOIL_FLAG_TEXTURE_REPEATS: otherwise will clamp
	SOIL_FLAG_MULTIPLY_ALPHA: for using (GL_ONE,GL_ONE_MINUS_SRC_ALPHA) blending
	SOIL_FLAG_INVERT_Y: flip the image vertically
	SOIL_FLAG_COMPRESS_TO_DXT: if the card can display them, will convert RGB to DXT1, RGBA to DXT5
	SOIL_FLAG_DDS_LOAD_DIRECT: will load DDS files directly without _ANY_ additional processing
	SOIL_FLAG_NTSC_SAFE_RGB: clamps RGB components to the range [16,235]
	SOIL_FLAG_CoCg_Y: Google YCoCg; RGB=>CoYCg, RGBA=>CoCgAY
	SOIL_FLAG_TEXTURE_RECTANGE: uses ARB_texture_rectangle ; pixel indexed & no repeat or MIPmaps or cubemaps
**/
enum
{
	IMG_POWER_OF_TWO       = SOIL_FLAG_POWER_OF_TWO,
	IMG_MIPMAPS            = SOIL_FLAG_MIPMAPS,
	IMG_TEXTURE_REPEATS    = SOIL_FLAG_TEXTURE_REPEATS,
	IMG_MULTIPLY_ALPHA     = SOIL_FLAG_MULTIPLY_ALPHA,
	IMG_INVERT_Y           = SOIL_FLAG_INVERT_Y,
	IMG_COMPRESS_TO_DXT    = SOIL_FLAG_COMPRESS_TO_DXT,
	IMG_DDS_LOAD_DIRECT    = SOIL_FLAG_DDS_LOAD_DIRECT,
	IMG_NTSC_SAFE_RGB      = SOIL_FLAG_NTSC_SAFE_RGB,
	IMG_COCG_Y             = SOIL_FLAG_CoCg_Y,
	IMG_TEXTURE_RECTANGLE  = SOIL_FLAG_TEXTURE_RECTANGLE
};

/**
	Creates a 2D OpenGL texture from raw image data.  Note that the raw data is
	_NOT_ freed after the upload (so the user can load various versions).
	\param data the raw data to be uploaded as an OpenGL texture
	\param gr_width the gr_width of the image in pixels
	\param gr_height the gr_height of the image in pixels
	\param channels the number of channels: 1-luminous, 2-luminous/alpha, 3-RGB, 4-RGBA
	\param reuse_texture_ID 0-generate a new texture ID, otherwise reuse the texture ID (overwriting the old texture)
	\param flags can be any of SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
	\return 0-failed, otherwise returns the OpenGL texture handle
**/
/**
unsigned int
	SOIL_create_OGL_texture
	(
		const unsigned char *const data,
		int gr_width, int gr_height, int channels,
		unsigned int reuse_texture_ID,
		unsigned int flags
	);

**/

unsigned int gr_load_image_ram(const unsigned char* const data, unsigned int id, int gr_width, int gr_height, int channels, unsigned int flags){
  return SOIL_create_OGL_texture(data, gr_width, gr_height, channels, id, flags);
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
  if(use_texture_filtering)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  else
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D, tex);
  glBegin(GL_QUADS);
    /*glTexCoord2f(0.0, 0.0);*/ /*glTexCoord2f(1.0, 1.0);*/ glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 0.0, 0.0);
    /*glTexCoord2f(1.0, 0.0);*/ /*glTexCoord2f(0.0, 1.0);*/ glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 0.0, 0.0);
    /*glTexCoord2f(1.0, 1.0);*/ /*glTexCoord2f(0.0, 0.0);*/ glTexCoord2f(1.0, 0.0); glVertex3f(1.0, 1.0, 0.0);
    /*glTexCoord2f(0.0, 1.0);*/ /*glTexCoord2f(1.0, 0.0);*/ glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 1.0, 0.0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glFlush();
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
  glFlush();
}

void gr_draw_line(float x0, float y0, float x1, float y1, float z){
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glBegin(GL_LINES);
    glVertex3f(x0, y0, z);
    glVertex3f(x1, y1, z);
  glEnd();
  glFlush();
}

void gr_draw_line_sp(float x0, float y0, float z0, float x1, float y1, float z1){
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glBegin(GL_LINES);
    glVertex3f(x0, y0, z0);
    glVertex3f(x1, y1, z1);
  glEnd();
  glFlush();
}

void gr_refresh(){
  // glfwSwapBuffers(window);
  SDL_GL_SwapWindow(window);
}

void gr_clear_depth(){
  glClear(GL_DEPTH_BUFFER_BIT);
}
void gr_clear(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void gr_clear_color(float r, float g, float b, float a){
  glClearColor(r, g, b, a);
}
void gr_clear_colored(float r, float g, float b, float a){
  glClearColor(r, g, b, a);
  gr_clear();
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
  // uint32_t field = SDL_GetRelativeMouseState(&mouse_x, &mouse_y);
  uint32_t field = SDL_GetMouseState(&mouse_x, &mouse_y);
  // uint32_t field = SDL_GetMouseState(&mouse_x, &mouse_y);
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
      return GR_QUIT_EVENT;
    case SDL_KEYDOWN:
    case SDL_KEYUP:
      return GR_KEY_EVENT;
    case SDL_WINDOWEVENT:
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

/**
Mouse button event functions
*/
int gr_mouse_button(){
  return current_event.button.button;
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

/**********/
/** View **/

void gr_view(float x, float y, float s, float ang){
  glMatrixMode(GL_PROJECTION);
  float sp = 1/s;
  glLoadIdentity();
  view_scale = s;
  view_width = s*x_aspect_mod; view_height = s*y_aspect_mod;
  view_left = x; view_right = x + view_width;
  view_bottom = y; view_top = y + view_height;
  glOrtho(view_left, view_right, view_bottom, view_top, 0, -max_depth);
  // glScalef(sp, sp, 1);
  glRotatef(ang, 0, 0, 1);
  // glTranslatef(x, y, 0);
}

void gr_view_centered(float x, float y, float s, float ang){
  glMatrixMode(GL_PROJECTION);
  float sp = 1/s;
  glLoadIdentity();
  view_scale = s;
  view_width = s*x_aspect_mod; view_height = s*y_aspect_mod;
  view_left = x - view_width/2; view_right = x + view_width/2;
  view_bottom = y - view_height/2; view_top = y + view_height/2;
  glOrtho(view_left, view_right, view_bottom, view_top, 0, -max_depth);
  // glScalef(sp, sp, 1);
  glRotatef(ang, 0, 0, 1);
  // glTranslatef(x, y, 0);
}

float gr_screen_to_world_x(int x){
  return view_left + view_width * ( (float)x / (float)screen_width);
}
float gr_screen_to_world_y(int y){
  return view_top - view_height * ( (float)y / (float)screen_height);
}

/********************/
/** Initialization **/

int gr_open(){
  if(!is_open){
    is_open = 1;
    init_error = 0;
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    
    window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if(window == NULL)
      init_error = init_error | IERROR_SDL_WINDOW;
    opengl_context = SDL_GL_CreateContext(window);
    if(opengl_context == NULL)
      init_error = init_error | IERROR_SDL_GL;
    SDL_GetWindowSize(window, &screen_width, &screen_height);
    calc_aspect();
    
    gr_activate_transparency(1);
    gr_activate_depth_testing(1);
    // glEnable(GL_CULL_FACE);
    // glEnable(GL_BLEND);
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
