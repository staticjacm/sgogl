#include <stdlib.h>
#include "include/glfw3.h"
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
SDL_Window* window;
SDL_GLContext opengl_context;
SDL_Event current_event;
int wait_event = 0;
const Uint8* keystates;
int mouse_left, mouse_middle, mouse_right;

/******************************/
/** Proxies for SDL values **/


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


/*

enum {
                // The unknown key                                           
  GR_UNKNOWN             = GLFW_KEY_UNKNOWN            ,     
  
               // Printable keys
  GR_SPACE               = GLFW_KEY_SPACE              ,     
  GR_APOSTROPHE          = GLFW_KEY_APOSTROPHE         ,  // '      
  GR_COMMA               = GLFW_KEY_COMMA              ,  // ,      
  GR_MINUS               = GLFW_KEY_MINUS              ,  // -      
  GR_PERIOD              = GLFW_KEY_PERIOD             ,  // .      
  GR_SLASH               = GLFW_KEY_SLASH              ,  // /      
  GR_0                   = GLFW_KEY_0                  ,     
  GR_1                   = GLFW_KEY_1                  ,     
  GR_2                   = GLFW_KEY_2                  ,     
  GR_3                   = GLFW_KEY_3                  ,     
  GR_4                   = GLFW_KEY_4                  ,     
  GR_5                   = GLFW_KEY_5                  ,     
  GR_6                   = GLFW_KEY_6                  ,     
  GR_7                   = GLFW_KEY_7                  ,     
  GR_8                   = GLFW_KEY_8                  ,     
  GR_9                   = GLFW_KEY_9                  ,     
  GR_SEMICOLON           = GLFW_KEY_SEMICOLON          ,  // ;     
  GR_EQUAL               = GLFW_KEY_EQUAL              ,  // =     
  GR_A                   = GLFW_KEY_A                  ,     
  GR_B                   = GLFW_KEY_B                  ,     
  GR_C                   = GLFW_KEY_C                  ,     
  GR_D                   = GLFW_KEY_D                  ,     
  GR_E                   = GLFW_KEY_E                  ,     
  GR_F                   = GLFW_KEY_F                  ,     
  GR_G                   = GLFW_KEY_G                  ,     
  GR_H                   = GLFW_KEY_H                  ,     
  GR_I                   = GLFW_KEY_I                  ,     
  GR_J                   = GLFW_KEY_J                  ,     
  GR_K                   = GLFW_KEY_K                  ,     
  GR_L                   = GLFW_KEY_L                  ,     
  GR_M                   = GLFW_KEY_M                  ,     
  GR_N                   = GLFW_KEY_N                  ,     
  GR_O                   = GLFW_KEY_O                  ,     
  GR_P                   = GLFW_KEY_P                  ,     
  GR_Q                   = GLFW_KEY_Q                  ,     
  GR_R                   = GLFW_KEY_R                  ,     
  GR_S                   = GLFW_KEY_S                  ,     
  GR_T                   = GLFW_KEY_T                  ,     
  GR_U                   = GLFW_KEY_U                  ,     
  GR_V                   = GLFW_KEY_V                  ,     
  GR_W                   = GLFW_KEY_W                  ,     
  GR_X                   = GLFW_KEY_X                  ,     
  GR_Y                   = GLFW_KEY_Y                  ,     
  GR_Z                   = GLFW_KEY_Z                  ,     
  GR_LEFT_BRACKET        = GLFW_KEY_LEFT_BRACKET       ,  // [     
  GR_BACKSLASH           = GLFW_KEY_BACKSLASH          ,  // \     
  GR_RIGHT_BRACKET       = GLFW_KEY_RIGHT_BRACKET      ,  // ]     
  GR_GRAVE_ACCENT        = GLFW_KEY_GRAVE_ACCENT       ,  // `     
  GR_WORLD_1             = GLFW_KEY_WORLD_1            ,  // non-US #1     
  GR_WORLD_2             = GLFW_KEY_WORLD_2            ,  // non-US #2     
                         
          // Function keys
  GR_ESCAPE              = GLFW_KEY_ESCAPE             ,     
  GR_ENTER               = GLFW_KEY_ENTER              ,     
  GR_TAB                 = GLFW_KEY_TAB                ,     
  GR_BACKSPACE           = GLFW_KEY_BACKSPACE          ,     
  GR_INSERT              = GLFW_KEY_INSERT             ,     
  GR_DELETE              = GLFW_KEY_DELETE             ,     
  GR_RIGHT               = GLFW_KEY_RIGHT              ,     
  GR_LEFT                = GLFW_KEY_LEFT               ,     
  GR_DOWN                = GLFW_KEY_DOWN               ,     
  GR_UP                  = GLFW_KEY_UP                 ,     
  GR_PAGE_UP             = GLFW_KEY_PAGE_UP            ,     
  GR_PAGE_DOWN           = GLFW_KEY_PAGE_DOWN          ,     
  GR_HOME                = GLFW_KEY_HOME               ,     
  GR_END                 = GLFW_KEY_END                ,     
  GR_CAPS_LOCK           = GLFW_KEY_CAPS_LOCK          ,     
  GR_SCROLL_LOCK         = GLFW_KEY_SCROLL_LOCK        ,     
  GR_NUM_LOCK            = GLFW_KEY_NUM_LOCK           ,     
  GR_PRINT_SCREEN        = GLFW_KEY_PRINT_SCREEN       ,     
  GR_PAUSE               = GLFW_KEY_PAUSE              ,     
  GR_F1                  = GLFW_KEY_F1                 ,     
  GR_F2                  = GLFW_KEY_F2                 ,     
  GR_F3                  = GLFW_KEY_F3                 ,     
  GR_F4                  = GLFW_KEY_F4                 ,     
  GR_F5                  = GLFW_KEY_F5                 ,     
  GR_F6                  = GLFW_KEY_F6                 ,     
  GR_F7                  = GLFW_KEY_F7                 ,     
  GR_F8                  = GLFW_KEY_F8                 ,     
  GR_F9                  = GLFW_KEY_F9                 ,     
  GR_F10                 = GLFW_KEY_F10                ,     
  GR_F11                 = GLFW_KEY_F11                ,     
  GR_F12                 = GLFW_KEY_F12                ,     
  GR_F13                 = GLFW_KEY_F13                ,     
  GR_F14                 = GLFW_KEY_F14                ,     
  GR_F15                 = GLFW_KEY_F15                ,     
  GR_F16                 = GLFW_KEY_F16                ,     
  GR_F17                 = GLFW_KEY_F17                ,     
  GR_F18                 = GLFW_KEY_F18                ,     
  GR_F19                 = GLFW_KEY_F19                ,     
  GR_F20                 = GLFW_KEY_F20                ,     
  GR_F21                 = GLFW_KEY_F21                ,     
  GR_F22                 = GLFW_KEY_F22                ,     
  GR_F23                 = GLFW_KEY_F23                ,     
  GR_F24                 = GLFW_KEY_F24                ,     
  GR_F25                 = GLFW_KEY_F25                ,     
  GR_KP_0                = GLFW_KEY_KP_0               ,     
  GR_KP_1                = GLFW_KEY_KP_1               ,     
  GR_KP_2                = GLFW_KEY_KP_2               ,     
  GR_KP_3                = GLFW_KEY_KP_3               ,     
  GR_KP_4                = GLFW_KEY_KP_4               ,     
  GR_KP_5                = GLFW_KEY_KP_5               ,     
  GR_KP_6                = GLFW_KEY_KP_6               ,     
  GR_KP_7                = GLFW_KEY_KP_7               ,     
  GR_KP_8                = GLFW_KEY_KP_8               ,     
  GR_KP_9                = GLFW_KEY_KP_9               ,     
  GR_KP_DECIMAL          = GLFW_KEY_KP_DECIMAL         ,     
  GR_KP_DIVIDE           = GLFW_KEY_KP_DIVIDE          ,     
  GR_KP_MULTIPLY         = GLFW_KEY_KP_MULTIPLY        ,     
  GR_KP_SUBTRACT         = GLFW_KEY_KP_SUBTRACT        ,     
  GR_KP_ADD              = GLFW_KEY_KP_ADD             ,     
  GR_KP_ENTER            = GLFW_KEY_KP_ENTER           ,     
  GR_KP_EQUAL            = GLFW_KEY_KP_EQUAL           ,     
  GR_LEFT_SHIFT          = GLFW_KEY_LEFT_SHIFT         ,     
  GR_LEFT_CONTROL        = GLFW_KEY_LEFT_CONTROL       ,     
  GR_LEFT_ALT            = GLFW_KEY_LEFT_ALT           ,     
  GR_LEFT_SUPER          = GLFW_KEY_LEFT_SUPER         ,     
  GR_RIGHT_SHIFT         = GLFW_KEY_RIGHT_SHIFT        ,     
  GR_RIGHT_CONTROL       = GLFW_KEY_RIGHT_CONTROL      ,     
  GR_RIGHT_ALT           = GLFW_KEY_RIGHT_ALT          ,     
  GR_RIGHT_SUPER         = GLFW_KEY_RIGHT_SUPER        ,     
  GR_MENU                = GLFW_KEY_MENU               ,
  GR_LAST                = GLFW_KEY_MENU
};

enum {

  GR_SHIFT   = GLFW_MOD_SHIFT   ,
  GR_CONTROL = GLFW_MOD_CONTROL ,
  GR_ALT     = GLFW_MOD_ALT     ,
  GR_SUPER   = GLFW_MOD_SUPER   
};

enum {
  GR_MOUSE_1      = GLFW_MOUSE_BUTTON_1      ,
  GR_MOUSE_2      = GLFW_MOUSE_BUTTON_2      ,
  GR_MOUSE_3      = GLFW_MOUSE_BUTTON_3      ,
  GR_MOUSE_4      = GLFW_MOUSE_BUTTON_4      ,
  GR_MOUSE_5      = GLFW_MOUSE_BUTTON_5      ,
  GR_MOUSE_6      = GLFW_MOUSE_BUTTON_6      ,
  GR_MOUSE_7      = GLFW_MOUSE_BUTTON_7      ,
  GR_MOUSE_8      = GLFW_MOUSE_BUTTON_8      ,
  GR_MOUSE_LAST   = GLFW_MOUSE_BUTTON_LAST   ,
  GR_MOUSE_LEFT   = GLFW_MOUSE_BUTTON_LEFT   ,
  GR_MOUSE_RIGHT  = GLFW_MOUSE_BUTTON_RIGHT  ,
  GR_MOUSE_MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE 

};

enum {
  GR_FOCUSED        = GLFW_FOCUSED      ,
  GR_MINIMIZED      = GLFW_ICONIFIED    ,
  GR_RESIZABLE      = GLFW_RESIZABLE    ,
  GR_VISIBLE        = GLFW_VISIBLE      ,
  GR_DECORATED      = GLFW_DECORATED    ,
  GR_AUTO_MINIMIZE  = GLFW_AUTO_ICONIFY ,
  GR_FLOATING       = GLFW_FLOATING     ,
  GR_MAXIMIZED      = GLFW_MAXIMIZED    
};

*/

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

/***************/
/** Callbacks **/

/*

typedef void (*Key_cb)(int, int, int); // key, action, mods
typedef void (*Mouse_button_cb)(int, int, int); // button, action, mods
typedef void (*Mouse_move_cb)(double, double); // x offset, y offset
typedef void (*Mouse_enter_cb)(int); // enter/leave flag
typedef void (*Mouse_scroll_cb)(double, double); // x offset, y offset
// typedef void (*File_drop_cb)(int, const char**); // number files, paths
// typedef void (*Joystick_cb)(int, int); // joystick, event
typedef void (*Window_pos_cb)(int, int); // x offset, y offset
typedef void (*Window_size_cb)(int, int); // gr_width, gr_height
typedef void (*Window_close_cb)();
typedef void (*Window_refresh_cb)();
typedef void (*Window_focus_cb)(int); // enter/leave flag
typedef void (*Window_iconify_cb)(int); // true/false flag
typedef void (*Framebuffer_size_cb)(int, int); // gr_width, gr_height

Key_cb           key_cb;
Mouse_button_cb  mouse_button_cb;
Mouse_move_cb    mouse_move_cb;
Mouse_enter_cb   mouse_enter_cb;
Mouse_scroll_cb  mouse_scroll_cb;

Window_pos_cb        window_pos_cb;
Window_size_cb       window_size_cb;
Window_close_cb      window_close_cb;
Window_refresh_cb    window_refresh_cb;
Window_focus_cb      window_focus_cb;
Window_iconify_cb    window_iconify_cb;
Framebuffer_size_cb  framebuffer_size_cb;

// Keys / mouse
void glfw_key_cb(GLFWwindow* window, int key, int scancode, int action, int mods){ key_cb(key, action, mods); }
void glfw_mouse_button_cb(GLFWwindow* window, int button, int action, int mods){ mouse_button_cb(button, action, mods); }
void glfw_mouse_move_cb(GLFWwindow* window, double x, double y){
  mousex = (int)x; mousey = (int)y;
  mouse_move_cb(x, y);
}
void glfw_mouse_enter_cb(GLFWwindow* window, int entered){ mouse_enter_cb(entered); }
void glfw_mouse_scroll_cb(GLFWwindow* window, double x, double y){ mouse_scroll_cb(x, y); }

// Window / framebuffer
void glfw_window_pos_cb(GLFWwindow* window, int x, int y){ window_pos_cb(x, y); }
void glfw_window_size_cb(GLFWwindow* window, int gr_width, int gr_height){
  screen_width = gr_width;
  screen_height = gr_height;
  calc_aspect();
  window_size_cb(gr_width, gr_height);
}
void glfw_window_close_cb(GLFWwindow* window){ window_close_cb(); }
void glfw_window_refresh_cb(GLFWwindow* window){ window_refresh_cb(); }
void glfw_window_focus_cb(GLFWwindow* window, int focused){ window_focus_cb(focused); }
void glfw_window_iconify_cb(GLFWwindow* window, int iconifed){ window_iconify_cb(iconifed); }
void glfw_framebuffer_size_cb(GLFWwindow* window, int gr_width, int gr_height){ framebuffer_size_cb(gr_width, gr_height); }

// Keys / mouse
void gr_key_function(Key_cb cb){
  if(cb)
    glfwSetKeyCallback(window, glfw_key_cb);
  else
    glfwSetKeyCallback(window, NULL);
  key_cb = cb;
}
void gr_mouse_button_function(Mouse_button_cb cb){
  if(cb)
    glfwSetMouseButtonCallback(window, glfw_mouse_button_cb);
  else
    glfwSetKeyCallback(window, NULL);
  mouse_button_cb = cb;
}
void gr_mouse_move_function(Mouse_move_cb cb){
  if(cb)
    glfwSetCursorPosCallback(window, glfw_mouse_move_cb);
  else
    glfwSetKeyCallback(window, NULL);
  mouse_move_cb = cb;
}
void gr_mouse_enter_function(Mouse_enter_cb cb){
  if(cb)
    glfwSetCursorEnterCallback(window, glfw_mouse_enter_cb);
  else
    glfwSetKeyCallback(window, NULL);
  mouse_enter_cb = cb;
}
void gr_mouse_scroll_function(Mouse_scroll_cb cb){
  if(cb)
    glfwSetScrollCallback(window, glfw_mouse_scroll_cb);
  else
    glfwSetKeyCallback(window, NULL);
  mouse_scroll_cb = cb;
}

// Window / framebuffer
void gr_window_position_function(Window_pos_cb cb){
  if(cb)
    glfwSetWindowPosCallback(window, glfw_window_pos_cb);
  else
    glfwSetWindowPosCallback(window, NULL);
  window_pos_cb = cb;
}
void gr_window_size_function(Window_size_cb cb){
  if(cb)
    glfwSetWindowSizeCallback(window, glfw_window_size_cb);
  else
    glfwSetWindowSizeCallback(window, NULL);
  window_size_cb = cb;
}
void gr_window_close_function(Window_close_cb cb){
  if(cb)
    glfwSetWindowCloseCallback(window, glfw_window_close_cb);
  else
    glfwSetWindowCloseCallback(window, NULL);
  window_close_cb = cb;
}
void gr_refresh_function(Window_refresh_cb cb){
  if(cb)
    glfwSetWindowRefreshCallback(window, glfw_window_refresh_cb);
  else
    glfwSetWindowRefreshCallback(window, NULL);
  window_refresh_cb = cb;
}
void gr_window_focus_function(Window_focus_cb cb){
  if(cb)
    glfwSetWindowFocusCallback(window, glfw_window_focus_cb);
  else
    glfwSetWindowFocusCallback(window, NULL);
  window_focus_cb = cb;
}
void gr_window_minimize_function(Window_iconify_cb cb){
  if(cb)
    glfwSetWindowIconifyCallback(window, glfw_window_iconify_cb);
  else
    glfwSetWindowIconifyCallback(window, NULL);
  window_iconify_cb = cb;
}
void gr_framebuffer_size_function(Framebuffer_size_cb cb){
  if(cb)
    glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_cb);
  else
    glfwSetFramebufferSizeCallback(window, NULL);
  framebuffer_size_cb = cb;
}

*/

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
  graphics_read_keystates
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
  uint32_t field = SDL_GetRelativeMouseState(&mouse_x, &mouse_y);
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

void gr_open(){
  
  SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  
  // glfwInit();
  
  // window = glfwCreateWindow(640, 480, "window", NULL, NULL);
  // glfwMakeContextCurrent(window);
  // glfwGetWindowSize(window, &screen_width, &screen_height);
  window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  opengl_context = SDL_GL_CreateContext(window);
  SDL_GetWindowSize(window, &screen_width, &screen_height);
  calc_aspect();
  
  gr_activate_transparency(1);
  gr_activate_depth_testing(1);
  // glEnable(GL_CULL_FACE);
  // glEnable(GL_BLEND);
}

void gr_close(){
  SDL_Quit;
}
