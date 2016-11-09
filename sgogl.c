#include <stdio.h>
#include "include/glfw3.h"
#include "include/soil.h"
#include <gl/gl.h>

float max_depth = 10.0f;
int screen_width, screen_height;
float screen_aspect, x_aspect_mod, y_aspect_mod;
float view_width, view_height, view_scale;
float view_left, view_right, view_bottom, view_top;
int mousex, mousey;
GLFWwindow* window;

/******************************/
/** Proxies for GLFW values **/

enum {
                /* The unknown key */                                           
  GR_UNKNOWN             = GLFW_KEY_UNKNOWN            ,     
  
               /* Printable keys */
  GR_SPACE               = GLFW_KEY_SPACE              ,     
  GR_APOSTROPHE          = GLFW_KEY_APOSTROPHE         ,  /* ' */     
  GR_COMMA               = GLFW_KEY_COMMA              ,  /* , */     
  GR_MINUS               = GLFW_KEY_MINUS              ,  /* - */     
  GR_PERIOD              = GLFW_KEY_PERIOD             ,  /* . */     
  GR_SLASH               = GLFW_KEY_SLASH              ,  /* / */     
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
  GR_SEMICOLON           = GLFW_KEY_SEMICOLON          ,  /* ; */     
  GR_EQUAL               = GLFW_KEY_EQUAL              ,  /* = */     
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
  GR_LEFT_BRACKET        = GLFW_KEY_LEFT_BRACKET       ,  /* [ */     
  GR_BACKSLASH           = GLFW_KEY_BACKSLASH          ,  /* \ */     
  GR_RIGHT_BRACKET       = GLFW_KEY_RIGHT_BRACKET      ,  /* ] */     
  GR_GRAVE_ACCENT        = GLFW_KEY_GRAVE_ACCENT       ,  /* ` */     
  GR_WORLD_1             = GLFW_KEY_WORLD_1            ,  /* non-US #1 */     
  GR_WORLD_2             = GLFW_KEY_WORLD_2            ,  /* non-US #2 */     
                         
          /* Function keys */  
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

int gr_mouse_x(){ return (int)mousex; }
int gr_mouse_y(){ return (int)mousey; }

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

unsigned int gr_load_image(char* file, unsigned int id, unsigned int soil_load_flag, unsigned int soil_flags){
  // Use id = 0 for new id
  return SOIL_load_OGL_texture(file, soil_load_flag, id, soil_flags);
}

unsigned int gr_load_image_standard(char* file, unsigned int id){
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
  // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_SRC_COLOR);
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
  glfwSwapBuffers(window);
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
/** Polling **/

void gr_poll_events(){
  glfwPollEvents();
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
  glfwInit();
  
  window = glfwCreateWindow(640, 480, "window", NULL, NULL);
  glfwMakeContextCurrent(window);
  glfwGetWindowSize(window, &screen_width, &screen_height);
  calc_aspect();
  
  gr_activate_transparency(1);
  gr_activate_depth_testing(1);
  // glEnable(GL_CULL_FACE);
  // glEnable(GL_BLEND);
}


/*************/
/** Testing **/
/**

void test_key_function(int key, int action, int mods){
  printf("A = %d key %d was %d\n", A, key, action);
  if(key == GLFW_KEY_ESCAPE) running = 0;
  else if(key == GLFW_KEY_W) param1 += 0.1;
  else if(key == GLFW_KEY_S) param1 += -0.1;
  else if(key == GLFW_KEY_A) param2 += -0.1;
  else if(key == GLFW_KEY_D) param2 += 0.1;
  else if(key == GLFW_KEY_UP) param3 += 0.5;
  else if(key == GLFW_KEY_DOWN) param3 += -0.5;
}

void close(){
  running = 0;
}

void main(){
  printf("gr_open\n");
  
  gr_open();
  
  gr_key_function(test_key_function);
  gr_window_close_function(close);
  
  // int tex = SOIL_load_OGL_texture("img_test.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
  int tex = gr_load_image("img_test.png", 0, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
  printf("texture id: %d\n", tex);
  
  gr_point_size(6.0f);
  
  float t = 0;
  while(running){
    A = 1;
    glfwPollEvents();
    A = 0;
    
    t += 0.01;
    // gr_clear_color(0, 0, 0, 0);
    // gr_clear();
    gr_clear_depth();
    gr_view(-2, -2, 4, 0);
    float x   = 1.0;
    float y   = 0.0;
    // float x   =  (float)mousex / 100 - 2.5;
    // float y   = -(float)mousey / 100 + 2;
    float anx = 0.5;
    float any = 0.5;
    float ang = t;
    float sx  = 0.5;
    float sy  = 1;
    
    gr_draw_centered(tex, x, y, 2.0, 0.0, sx, sy);
    gr_color_alpha(0.5);
    gr_draw(tex, x, y, 1.0, anx, any, ang, sx, sy);
    
    gr_color(1, 0, 0, 1);
    gr_draw_point(x, y, 1.0);
    gr_color(0, 0, 1, 1);
    gr_draw_point(x + anx, y + any, 1.0);
    gr_color(1, 1, 1, 1);
    gr_draw_line(0.0, 0.0, 0.5, 0.0, 1.0);
    gr_draw_point(0.0, 0.0, 1.0);
    gr_draw_point(0.5, 0.0, 1.0);
    gr_draw_point(1.0, 0.0, 1.0);
    gr_draw_point(1.0, 1.0, 1.0);
    gr_draw_point(1.0, 0.5, 1.0);
    gr_draw_point(0.0, 1.0, 1.0);
    gr_draw_point(0.0, 0.5, 1.0);
    
    // glfwSwapBuffers(window);
    gr_refresh();
  }
}

/**/