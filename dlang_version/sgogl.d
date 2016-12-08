module sgogl;

import std.string;


/******************************/
/** Proxies for SDL values **/


/**
Event codes
*/
enum {
  GR_NULL_EVENT,
  GR_KEY_EVENT,
  GR_WINDOW_EVENT,
  GR_CLOSE,
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

enum {
  GR_RELEASED = 0,
  GR_PRESSED  = 1
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


/*******************/
/** Informational **/

extern(C){
  int gr_width();
  int gr_height();
  float gr_width_aspect_mod();
  float gr_height_aspect_mod();
  
  float gr_max_depth();
  
  float gr_view_scale(); 
  float gr_view_width() ;
  float gr_view_height();
  float gr_view_left();
  float gr_view_right();
  float gr_view_bottom();
  float gr_view_top();
}

/************************************/
/** Setting Variables / Parameters **/

extern(C){
  void gr_set_max_depth(float);
  
  void gr_activate_transparency(int);
  void gr_activate_linear_filtering(int);
  void gr_activate_dithering(int);
  void gr_activate_depth_testing(int);
  
  void gr_set_opengl_doublebuffering(int);
  
  void gr_toggle_window_bordered();
  void gr_set_window_brightness(float);
  void gr_set_window_fullscreen();
  void gr_set_window_fullscreen_desktop();
  void gr_set_window_windowed();
  void gr_toggle_mouse_grabbed();
  int  gr_set_window_icon(const(char)*);
  
  void gr_set_input_focus();
  void gr_set_window_max_size(int, int);
  void gr_set_window_min_size(int, int);
  void gr_set_window_position(int, int);
  void gr_set_window_size(int, int);
  void gr_set_window_title(const(char)*);
  
  void gr_popup_error(const(char)*);
  void gr_popup_warning(const(char)*);
  void gr_popup_info(const(char)*);
  
  int gr_get_window_width();
  int gr_get_window_height();
}

void gr_set_window_icon(string s){ gr_set_window_icon(s.toStringz); }

void gr_set_window_title(string s){ gr_set_window_title(s.toStringz); }

void gr_popup_error(string s){ gr_popup_error(s.toStringz); }
void gr_popup_warning(string s){ gr_popup_warning(s.toStringz); }
void gr_popup_info(string s){ gr_popup_info(s.toStringz); }

/*
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
*/
// extern(C) void gr_activate_depth_testing(int);

/************/
/** Colors **/

extern(C){
  void gr_color(float, float, float, float);
  void gr_color_alpha(float);
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
};
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
	The format of images that may be loaded (force_channels).
	SOIL_LOAD_AUTO leaves the image in whatever format it was found.
	SOIL_LOAD_L forces the image to load as Luminous (greyscale)
	SOIL_LOAD_LA forces the image to load as Luminous with Alpha
	SOIL_LOAD_RGB forces the image to load as Red Green Blue
	SOIL_LOAD_RGBA forces the image to load as Red Green Blue Alpha
**/
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
  int gr_screenshot(const(char)*);
}


uint gr_load_image_ext(string file, uint id, uint load_flags, uint soil_flags){ return gr_load_image_ext(file.toStringz, id, load_flags, soil_flags); }
uint gr_load_image(string file, uint id){ return gr_load_image(file.toStringz, id); }
int gr_screenshot(string file){ return gr_screenshot(file.toStringz); }

/***********/
/** Audio **/

extern(C){
  int find_available_mix_chunk_list_id();
  
  int gr_load_wav(char*, int);
  void gr_unload_audio(int);
  
  void gr_set_channel_number(int);
  
  // Warning: using an id not explicitly registered using one of the above functions
  // produces undefined behavior. Bounds checks et al are left out for speed
  int gr_play_once(int);
  int gr_play_once_on(int, int);
  int gr_play(int, int);
  int gr_play_on(int, int, int);
  int gr_play_timed(int, int);
  int gr_play_timed_on(int, int, int);
  
  void gr_pause(int);
  int gr_paused(int);
  void gr_stop(int);
  int gr_stopped(int);
  
  void gr_set_volume(int, int);
  void gr_set_panning(int, int, int);
  void gr_set_mono(int);
  void gr_set_attenuation(int, int);
  void gr_set_no_attenuation(int);
}

void gr_set_panning(int channel, int pan){
  gr_set_panning(channel, pan, 254 - pan);
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
  void gr_wait_for_render();
}

/************/
/** Events **/

extern(C){
  void gr_register_events();
  int gr_has_event();
  
  void gr_read_mouse();
  int gr_mouse_x();
  int gr_mouse_y();
  int gr_mouse_left();
  int gr_mouse_middle();
  int gr_mouse_right();
  
  void gr_set_wait_event(int value);
  int gr_read();
  
  int gr_key_repeated();
  int gr_key_pressed();
  int gr_key();
  
  int gr_mouse_button();
  int gr_mouse_state();
  int gr_mouse_clicks();
  int gr_mouse_button_x();
  int gr_mouse_button_y();
  
  int gr_mouse_move_x();
  int gr_mouse_move_y();
  
  int gr_mouse_move_xrel();
  int gr_mouse_move_yrel();
  
  int gr_wheel();
  
  int gr_window_event();
}

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

extern(C) int gr_open();
extern(C) void gr_close();

