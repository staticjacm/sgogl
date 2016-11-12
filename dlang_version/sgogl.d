
module sgogl;

enum{
  GLFW_KEY_UNKNOWN           = -1 ,
                             
  GLFW_KEY_SPACE             = 32 ,
  GLFW_KEY_APOSTROPHE        = 39 , /* ' */
  GLFW_KEY_COMMA             = 44 , /* , */
  GLFW_KEY_MINUS             = 45 , /* - */
  GLFW_KEY_PERIOD            = 46 , /* . */
  GLFW_KEY_SLASH             = 47 , /* / */
  GLFW_KEY_0                 = 48 ,
  GLFW_KEY_1                 = 49 ,
  GLFW_KEY_2                 = 50 ,
  GLFW_KEY_3                 = 51 ,
  GLFW_KEY_4                 = 52 ,
  GLFW_KEY_5                 = 53 ,
  GLFW_KEY_6                 = 54 ,
  GLFW_KEY_7                 = 55 ,
  GLFW_KEY_8                 = 56 ,
  GLFW_KEY_9                 = 57 ,
  GLFW_KEY_SEMICOLON         = 59 , /* ; */
  GLFW_KEY_EQUAL             = 61 , /* = */
  GLFW_KEY_A                 = 65 ,
  GLFW_KEY_B                 = 66 ,
  GLFW_KEY_C                 = 67 ,
  GLFW_KEY_D                 = 68 ,
  GLFW_KEY_E                 = 69 ,
  GLFW_KEY_F                 = 70 ,
  GLFW_KEY_G                 = 71 ,
  GLFW_KEY_H                 = 72 ,
  GLFW_KEY_I                 = 73 ,
  GLFW_KEY_J                 = 74 ,
  GLFW_KEY_K                 = 75 ,
  GLFW_KEY_L                 = 76 ,
  GLFW_KEY_M                 = 77 ,
  GLFW_KEY_N                 = 78 ,
  GLFW_KEY_O                 = 79 ,
  GLFW_KEY_P                 = 80 ,
  GLFW_KEY_Q                 = 81 ,
  GLFW_KEY_R                 = 82 ,
  GLFW_KEY_S                 = 83 ,
  GLFW_KEY_T                 = 84 ,
  GLFW_KEY_U                 = 85 ,
  GLFW_KEY_V                 = 86 ,
  GLFW_KEY_W                 = 87 ,
  GLFW_KEY_X                 = 88 ,
  GLFW_KEY_Y                 = 89 ,
  GLFW_KEY_Z                 = 90 ,
  GLFW_KEY_LEFT_BRACKET      = 91 , /* [ */
  GLFW_KEY_BACKSLASH         = 92 , /* \ */
  GLFW_KEY_RIGHT_BRACKET     = 93 , /* ] */
  GLFW_KEY_GRAVE_ACCENT      = 96 , /* ` */
  GLFW_KEY_WORLD_1           = 161, /* non-US #1 */
  GLFW_KEY_WORLD_2           = 162, /* non-US #2 */
                             
  GLFW_KEY_ESCAPE            = 256,
  GLFW_KEY_ENTER             = 257,
  GLFW_KEY_TAB               = 258,
  GLFW_KEY_BACKSPACE         = 259,
  GLFW_KEY_INSERT            = 260,
  GLFW_KEY_DELETE            = 261,
  GLFW_KEY_RIGHT             = 262,
  GLFW_KEY_LEFT              = 263,
  GLFW_KEY_DOWN              = 264,
  GLFW_KEY_UP                = 265,
  GLFW_KEY_PAGE_UP           = 266,
  GLFW_KEY_PAGE_DOWN         = 267,
  GLFW_KEY_HOME              = 268,
  GLFW_KEY_END               = 269,
  GLFW_KEY_CAPS_LOCK         = 280,
  GLFW_KEY_SCROLL_LOCK       = 281,
  GLFW_KEY_NUM_LOCK          = 282,
  GLFW_KEY_PRINT_SCREEN      = 283,
  GLFW_KEY_PAUSE             = 284,
  GLFW_KEY_F1                = 290,
  GLFW_KEY_F2                = 291,
  GLFW_KEY_F3                = 292,
  GLFW_KEY_F4                = 293,
  GLFW_KEY_F5                = 294,
  GLFW_KEY_F6                = 295,
  GLFW_KEY_F7                = 296,
  GLFW_KEY_F8                = 297,
  GLFW_KEY_F9                = 298,
  GLFW_KEY_F10               = 299,
  GLFW_KEY_F11               = 300,
  GLFW_KEY_F12               = 301,
  GLFW_KEY_F13               = 302,
  GLFW_KEY_F14               = 303,
  GLFW_KEY_F15               = 304,
  GLFW_KEY_F16               = 305,
  GLFW_KEY_F17               = 306,
  GLFW_KEY_F18               = 307,
  GLFW_KEY_F19               = 308,
  GLFW_KEY_F20               = 309,
  GLFW_KEY_F21               = 310,
  GLFW_KEY_F22               = 311,
  GLFW_KEY_F23               = 312,
  GLFW_KEY_F24               = 313,
  GLFW_KEY_F25               = 314,
  GLFW_KEY_KP_0              = 320,
  GLFW_KEY_KP_1              = 321,
  GLFW_KEY_KP_2              = 322,
  GLFW_KEY_KP_3              = 323,
  GLFW_KEY_KP_4              = 324,
  GLFW_KEY_KP_5              = 325,
  GLFW_KEY_KP_6              = 326,
  GLFW_KEY_KP_7              = 327,
  GLFW_KEY_KP_8              = 328,
  GLFW_KEY_KP_9              = 329,
  GLFW_KEY_KP_DECIMAL        = 330,
  GLFW_KEY_KP_DIVIDE         = 331,
  GLFW_KEY_KP_MULTIPLY       = 332,
  GLFW_KEY_KP_SUBTRACT       = 333,
  GLFW_KEY_KP_ADD            = 334,
  GLFW_KEY_KP_ENTER          = 335,
  GLFW_KEY_KP_EQUAL          = 336,
  GLFW_KEY_LEFT_SHIFT        = 340,
  GLFW_KEY_LEFT_CONTROL      = 341,
  GLFW_KEY_LEFT_ALT          = 342,
  GLFW_KEY_LEFT_SUPER        = 343,
  GLFW_KEY_RIGHT_SHIFT       = 344,
  GLFW_KEY_RIGHT_CONTROL     = 345,
  GLFW_KEY_RIGHT_ALT         = 346,
  GLFW_KEY_RIGHT_SUPER       = 347,
  GLFW_KEY_MENU              = 348,
                             
  GLFW_KEY_LAST              = GLFW_KEY_MENU
}

enum{
  GLFW_MOD_SHIFT          = 0x0001,
  GLFW_MOD_CONTROL        = 0x0002,
  GLFW_MOD_ALT            = 0x0004,
  GLFW_MOD_SUPER          = 0x0008
}

enum{
  GR_RELEASE  = 0,
  GR_PRESS    = 1,
  GR_REPEAT   = 2
}

enum{
  GLFW_MOUSE_BUTTON_1       = 0                   ,
  GLFW_MOUSE_BUTTON_2       = 1                   ,
  GLFW_MOUSE_BUTTON_3       = 2                   ,
  GLFW_MOUSE_BUTTON_4       = 3                   ,
  GLFW_MOUSE_BUTTON_5       = 4                   ,
  GLFW_MOUSE_BUTTON_6       = 5                   ,
  GLFW_MOUSE_BUTTON_7       = 6                   ,
  GLFW_MOUSE_BUTTON_8       = 7                   ,
  GLFW_MOUSE_BUTTON_LAST    = GLFW_MOUSE_BUTTON_8 ,
  GLFW_MOUSE_BUTTON_LEFT    = GLFW_MOUSE_BUTTON_1 ,
  GLFW_MOUSE_BUTTON_RIGHT   = GLFW_MOUSE_BUTTON_2 ,
  GLFW_MOUSE_BUTTON_MIDDLE  = GLFW_MOUSE_BUTTON_3
}

enum{
  GLFW_FOCUSED      = 0x00020001,
  GLFW_ICONIFIED    = 0x00020002,
  GLFW_RESIZABLE    = 0x00020003,
  GLFW_VISIBLE      = 0x00020004,
  GLFW_DECORATED    = 0x00020005,
  GLFW_AUTO_ICONIFY = 0x00020006,
  GLFW_FLOATING     = 0x00020007,
  GLFW_MAXIMIZED    = 0x00020008
}

enum {
  GL_NEVER        = 0x0200,
  GL_LESS         = 0x0201,
  GL_EQUAL        = 0x0202,
  GL_LEQUAL       = 0x0203,
  GL_GREATER      = 0x0204,
  GL_NOTEQUAL     = 0x0205,
  GL_GEQUAL       = 0x0206,
  GL_ALWAYS       = 0x0207
}

enum {
	SOIL_FLAG_POWER_OF_TWO      = 1  ,
	SOIL_FLAG_MIPMAPS           = 2  ,
	SOIL_FLAG_TEXTURE_REPEATS   = 4  ,
	SOIL_FLAG_MULTIPLY_ALPHA    = 8  ,
	SOIL_FLAG_INVERT_Y          = 16 ,
	SOIL_FLAG_COMPRESS_TO_DXT   = 32 ,
	SOIL_FLAG_DDS_LOAD_DIRECT   = 64 ,
	SOIL_FLAG_NTSC_SAFE_RGB     = 128,
	SOIL_FLAG_CoCg_Y            = 256,  
	SOIL_FLAG_TEXTURE_RECTANGLE = 512
}

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

// extern(C) void calc_aspect();

/***************/
/** Callbacks **/

extern(C){
  alias Key_cb               = void function(int, int, int); // key, action, mods
  alias Mouse_button_cb      = void function(int, int, int); // button, action, mods
  alias Mouse_move_cb        = void function(double, double); // x offset, y offset
  alias Mouse_enter_cb       = void function(int); // enter/leave flag
  alias Mouse_scroll_cb      = void function(double, double); // x offset, y offset
  alias Window_pos_cb        = void function(int, int); // x offset, y offset
  alias Window_size_cb       = void function(int, int); // width, height
  alias Window_close_cb      = void function();
  alias Window_refresh_cb    = void function();
  alias Window_focus_cb      = void function(int); // enter/leave flag
  alias Window_iconify_cb    = void function(int); // true/false flag
  alias Framebuffer_size_cb  = void function(int, int); // width, height
}
  
extern(C){
  // Keys / mouse
  void gr_key_function(Key_cb);
  void gr_mouse_button_function(Mouse_button_cb);
  void gr_mouse_move_function(Mouse_move_cb);
  void gr_mouse_enter_function(Mouse_enter_cb);
  void gr_mouse_scroll_function(Mouse_scroll_cb);
  
  // Window / framebuffer
  void gr_window_position_function(Window_pos_cb);
  void gr_window_size_function(Window_size_cb);
  void gr_window_close_function(Window_close_cb);
  void gr_refresh_function(Window_refresh_cb);
  void gr_window_focus_function(Window_focus_cb);
  void gr_window_minimize_function(Window_iconify_cb);
  void gr_framebuffer_size_function(Framebuffer_size_cb);
}

/*******************/
/** Informational **/

extern(C){
  int gr_width();
  int gr_height();
  float gr_width_aspect_mod();
  float gr_height_aspect_mod();
  float gr_view_scale();
  float gr_view_width();
  float gr_view_height();
  float gr_view_left();
  float gr_view_right();
  float gr_view_bottom();
  float gr_view_top();
  float gr_max_depth();
  int gr_mouse_x();
  int gr_mouse_y();
}

/************************************/
/** Setting Variables / Parameters **/

extern(C){
  void gr_set_max_depth(float);
  void gr_activate_transparency(int);
  void gr_activate_linear_filtering(int);
  void gr_activate_dithering(int);
  void gr_activate_depth_testing(int);  
}

/************/
/** Colors **/

extern(C) void gr_color(float, float, float, float);
extern(C) void gr_color_alpha(float);

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

enum
{
	IMG_AUTO = 0,
	IMG_L = 1,
	IMG_LA = 2,
	IMG_RGB = 3,
	IMG_RGBA = 4
};

/**
	Creates a 2D OpenGL texture from raw image data.  Note that the raw data is
	_NOT_ freed after the upload (so the user can load various versions).
	\param data the raw data to be uploaded as an OpenGL texture
	\param width the width of the image in pixels
	\param height the height of the image in pixels
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
		int width, int height, int channels,
		unsigned int reuse_texture_ID,
		unsigned int flags
	);

**/

extern(C){
  uint gr_load_image_ram(const(char)*, uint, int, int, int, uint);
  uint gr_load_image_ext(const(char)*, uint, uint, uint);
  uint gr_load_image(const(char)*, uint);
  void gr_unload_image(uint);
  int  gr_screenshot(char*);
}

/*************/
/** Drawing **/

extern(C){
  void gr_draw(uint, float, float, float, float, float, float, float, float);
  void gr_draw_centered(uint, float, float, float, float, float, float);
  void gr_point_size(float);
  void gr_draw_point(float, float, float);
  void gr_draw_line(float, float, float, float, float);
  void gr_draw_line_sp(float, float, float, float, float, float);
  void gr_refresh();
  void gr_clear_depth();
  void gr_clear();
  void gr_clear_color(float, float, float, float);
  void gr_clear_colored(float, float, float, float);
}

/*************/
/** Polling **/

extern(C) void gr_poll_events();

/**********/
/** View **/

extern(C){
  void gr_view(float, float, float, float);
  void gr_view_centered(float, float, float, float);
  
  float gr_screen_to_world_x(int);
  float gr_screen_to_world_y(int);
}

/********************/
/** Initialization **/

extern(C) void gr_open();
