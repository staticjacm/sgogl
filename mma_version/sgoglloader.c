#include <WolframLibrary.h>
#include <WolframCompileLibrary.h>
#include "sgogl.h"

DLLEXPORT mint WolframLibrary_getVersion(){return WolframLibraryVersion;}
DLLEXPORT int WolframLibrary_initialize( WolframLibraryData libData) {return 0;}
DLLEXPORT void WolframLibrary_uninitialize( WolframLibraryData libData) {return;}

#define MTensor_getIntegerDataMacro(mt) ((mint *) ((mt)->data))

#define stdargs WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res
// get integer
#define mgi(x) MArgument_getInteger(x)
// get string
#define mgs(x) MArgument_getUTF8String(x)
// get double
#define mgd(x) MArgument_getReal(x)
// return integer
#define mreti(x) MArgument_setInteger(Res, x)
// return double
#define mretr(x) MArgument_setReal(Res, x)
#define mgti(x) (int*)MTensor_getIntegerDataMacro(MArgument_getMTensor(x))

DLLEXPORT int tester(stdargs){
   MArgument_setInteger(Res, 12351561);
   return LIBRARY_NO_ERROR;
}

///////////////////////////////////////////


// int gr_width();
DLLEXPORT int gr_width_m(stdargs){
   mreti(gr_width());
   return LIBRARY_NO_ERROR;
}

// int gr_height();
DLLEXPORT int gr_height_m(stdargs){
   mreti(gr_height());
   return LIBRARY_NO_ERROR;
}

// float gr_width_aspect_mod();
DLLEXPORT int gr_width_aspect_mod_m(stdargs){
   mretr((double)gr_width_aspect_mod());
   return LIBRARY_NO_ERROR;
}
// float gr_height_aspect_mod();
DLLEXPORT int gr_height_aspect_mod_m(stdargs){
   mretr((double)gr_height_aspect_mod());
   return LIBRARY_NO_ERROR;
}
/*
// int gr_mouse_x();
DLLEXPORT int gr_mouse_x_m(stdargs){
   mreti(gr_mouse_x());
   return LIBRARY_NO_ERROR;
}
// int gr_mouse_y();
DLLEXPORT int gr_mouse_y_m(stdargs){
   mreti(gr_mouse_y());
   return LIBRARY_NO_ERROR;
}
*/

// float gr_max_depth();
DLLEXPORT int gr_max_depth_m(stdargs){
   mretr((double)gr_max_depth());
   return LIBRARY_NO_ERROR;
}

// float gr_view_scale(); 
DLLEXPORT int gr_view_scale_m(stdargs){
   mretr((double)gr_view_scale());
   return LIBRARY_NO_ERROR;
}
// float gr_view_width() ;
DLLEXPORT int gr_view_width_m(stdargs){
   mretr((double)gr_view_width());
   return LIBRARY_NO_ERROR;
}
// float gr_view_height();
DLLEXPORT int gr_view_height_m(stdargs){
   mretr((double)gr_view_height());
   return LIBRARY_NO_ERROR;
}
// float gr_view_left();
DLLEXPORT int gr_view_left_m(stdargs){
   mretr((double)gr_view_left());
   return LIBRARY_NO_ERROR;
}
// float gr_view_right();
DLLEXPORT int gr_view_right_m(stdargs){
   mretr((double)gr_view_right());
   return LIBRARY_NO_ERROR;
}
// float gr_view_bottom();
DLLEXPORT int gr_view_bottom_m(stdargs){
   mretr((double)gr_view_bottom());
   return LIBRARY_NO_ERROR;
}
// float gr_view_top();
DLLEXPORT int gr_view_top_m(stdargs){
   mretr((double)gr_view_top());
   return LIBRARY_NO_ERROR;
}

// void gr_activate_events(int);
DLLEXPORT int gr_activate_events_m(stdargs){
   gr_activate_events(mgi(Args[0]));
   return LIBRARY_NO_ERROR;
}
// void gr_set_max_depth(float);
DLLEXPORT int gr_set_max_depth_m(stdargs){
   gr_set_max_depth(mgd(Args[0]));
   return LIBRARY_NO_ERROR;
}
// void gr_activate_transparency(int);
DLLEXPORT int gr_activate_transparency_m(stdargs){
   gr_activate_transparency(mgi(Args[0]));
   return LIBRARY_NO_ERROR;
}
// void gr_activate_linear_filtering(int);
DLLEXPORT int gr_activate_linear_filtering_m(stdargs){
   gr_activate_linear_filtering(mgi(Args[0]));
   return LIBRARY_NO_ERROR;
}
// void gr_activate_dithering(int);
DLLEXPORT int gr_activate_dithering_m(stdargs){
   gr_activate_dithering(mgi(Args[0]));
   return LIBRARY_NO_ERROR;
}
// void gr_activate_depth_testing(int);
DLLEXPORT int gr_activate_depth_testing_m(stdargs){
   gr_activate_depth_testing(mgi(Args[0]));
   return LIBRARY_NO_ERROR;
}

// void gr_toggle_window_bordered();
DLLEXPORT int gr_toggle_window_bordered_m(stdargs){
   gr_toggle_window_bordered();
   return LIBRARY_NO_ERROR;
}
// void gr_set_window_brightness(float);
DLLEXPORT int gr_set_window_brightness_m(stdargs){
   gr_set_window_brightness((float)mgd(Args[0]));
   return LIBRARY_NO_ERROR;
}
// void gr_set_window_fullscreen();
DLLEXPORT int gr_set_window_fullscreen_m(stdargs){
   gr_set_window_fullscreen();
   return LIBRARY_NO_ERROR;
}
// void gr_set_window_fullscreen_desktop();
DLLEXPORT int gr_set_window_fullscreen_desktop_m(stdargs){
   gr_set_window_fullscreen_desktop();
   return LIBRARY_NO_ERROR;
}
// void gr_set_window_windowed();
DLLEXPORT int gr_set_window_windowed_m(stdargs){
   gr_set_window_windowed();
   return LIBRARY_NO_ERROR;
}
// void gr_toggle_mouse_grabbed();
DLLEXPORT int gr_toggle_mouse_grabbed_m(stdargs){
   gr_toggle_mouse_grabbed();
   return LIBRARY_NO_ERROR;
}
// int  gr_set_window_icon(char*);
DLLEXPORT int gr_set_window_icon_m(stdargs){
   mreti(gr_set_window_icon(mgs(Args[0])));
   return LIBRARY_NO_ERROR;
}

// void gr_set_input_focus();
DLLEXPORT int gr_set_input_focus_m(stdargs){
   gr_set_input_focus();
   return LIBRARY_NO_ERROR;
}
// void gr_set_window_max_size(int, int);
DLLEXPORT int gr_set_window_max_size_m(stdargs){
   gr_set_window_max_size(mgi(Args[0]), mgi(Args[0]));
   return LIBRARY_NO_ERROR;
}
// void gr_set_window_min_size(int, int);
DLLEXPORT int gr_set_window_min_size_m(stdargs){
   gr_set_window_min_size(mgi(Args[0]), mgi(Args[0]));
   return LIBRARY_NO_ERROR;
}
// void gr_set_window_position(int, int);
DLLEXPORT int gr_set_window_position_m(stdargs){
   gr_set_window_position(mgi(Args[0]), mgi(Args[0]));
   return LIBRARY_NO_ERROR;
}
// void gr_set_window_size(int, int);
DLLEXPORT int gr_set_window_size_m(stdargs){
   gr_set_window_size(mgi(Args[0]), mgi(Args[0]));
   return LIBRARY_NO_ERROR;
}
// void gr_set_window_title(char*);
DLLEXPORT int gr_set_window_title_m(stdargs){
   gr_set_window_title(mgs(Args[0]));
   return LIBRARY_NO_ERROR;
}

// void gr_popup_error(char*);
DLLEXPORT int gr_popup_error_m(stdargs){
   gr_popup_error(mgs(Args[0]));
   return LIBRARY_NO_ERROR;
}
// void gr_popup_warning(char*);
DLLEXPORT int gr_popup_warning_m(stdargs){
   gr_popup_warning(mgs(Args[0]));
   return LIBRARY_NO_ERROR;
}
// void gr_popup_info(char*);
DLLEXPORT int gr_popup_info_m(stdargs){
   gr_popup_info(mgs(Args[0]));
   return LIBRARY_NO_ERROR;
}

// int gr_get_window_width();
DLLEXPORT int gr_get_window_width_m(stdargs){
   mreti(gr_get_window_width());
   return LIBRARY_NO_ERROR;
}
// int gr_get_window_height();
DLLEXPORT int gr_get_window_height_m(stdargs){
   mreti(gr_get_window_height());
   return LIBRARY_NO_ERROR;
}

// void gr_color(float, float, float, float);
DLLEXPORT int gr_color_m(stdargs){
   gr_color((float)mgd(Args[0]), (float)mgd(Args[1]), (float)mgd(Args[2]), (float)mgd(Args[3]));
   return LIBRARY_NO_ERROR;
}
// void gr_color_alpha(float);
DLLEXPORT int gr_color_alpha_m(stdargs){
   gr_color_alpha((float)mgd(Args[0]));
   return LIBRARY_NO_ERROR;
}

// unsigned int gr_load_image_ram(const unsigned char* const, unsigned int, int, int, int, unsigned int);
// unsigned int gr_load_image_ext(char*, unsigned int, unsigned int, unsigned int);
DLLEXPORT int gr_load_image_ext_m(stdargs){
   mreti(gr_load_image_ext(mgs(Args[0]), mgi(Args[1]), mgi(Args[2]), mgi(Args[3])));
   return LIBRARY_NO_ERROR;
}
// unsigned int gr_load_image(char*, unsigned int);
DLLEXPORT int gr_load_image_m(stdargs){
   mreti(gr_load_image(mgs(Args[0]), mgi(Args[1])));
   return LIBRARY_NO_ERROR;
}
// void gr_unload_image(unsigned int);
DLLEXPORT int gr_unload_image_m(stdargs){
   gr_unload_image(mgi(Args[0]));
   return LIBRARY_NO_ERROR;
}
// int gr_screenshot(char*);
DLLEXPORT int gr_screenshot_m(stdargs){
   mreti(gr_screenshot(mgs(Args[0])));
   return LIBRARY_NO_ERROR;
}

// void gr_draw(unsigned int, float, float, float, float, float, float, float, float);
DLLEXPORT int gr_draw_m(stdargs){
   gr_draw(mgi(Args[0]), (float)mgd(Args[1]), (float)mgd(Args[2]), 
                         (float)mgd(Args[3]), (float)mgd(Args[4]), 
                         (float)mgd(Args[5]), (float)mgd(Args[6]), 
                         (float)mgd(Args[7]), (float)mgd(Args[8])
          );
   return LIBRARY_NO_ERROR;
}
// void gr_draw_centered(unsigned int, float, float, float, float, float, float);
DLLEXPORT int gr_draw_centered_m(stdargs){
   gr_draw_centered(mgi(Args[0]), (float)mgd(Args[1]), (float)mgd(Args[2]), 
                                  (float)mgd(Args[3]), (float)mgd(Args[4]), 
                                  (float)mgd(Args[5]), (float)mgd(Args[6])
                   );
   return LIBRARY_NO_ERROR;
}
// void gr_point_size(float);
DLLEXPORT int gr_point_size_m(stdargs){
   gr_point_size((float)mgd(Args[0]));
   return LIBRARY_NO_ERROR;
}
// void gr_draw_point(float, float, float);
DLLEXPORT int gr_draw_point_m(stdargs){
   gr_draw_point((float)mgd(Args[0]), (float)mgd(Args[1]), (float)mgd(Args[2]));
   return LIBRARY_NO_ERROR;
}
// void gr_draw_line(float, float, float, float, float);
DLLEXPORT int gr_draw_line_m(stdargs){
   gr_draw_line((float)mgd(Args[0]), (float)mgd(Args[1]), (float)mgd(Args[2]), (float)mgd(Args[3]), (float)mgd(Args[4]));
   return LIBRARY_NO_ERROR;
}
// void gr_draw_line_sp(float, float, float, float, float, float);
DLLEXPORT int gr_draw_line_sp_m(stdargs){
   gr_draw_line_sp((float)mgd(Args[0]), (float)mgd(Args[1]), (float)mgd(Args[2]), (float)mgd(Args[3]), (float)mgd(Args[4]), (float)mgd(Args[5]));
   return LIBRARY_NO_ERROR;
}
// void gr_refresh();
DLLEXPORT int gr_refresh_m(stdargs){
   gr_refresh();
   return LIBRARY_NO_ERROR;
}
// void gr_clear_depth();
DLLEXPORT int gr_clear_depth_m(stdargs){
   gr_clear_depth();
   return LIBRARY_NO_ERROR;
}
// void gr_clear();
DLLEXPORT int gr_clear_m(stdargs){
   gr_clear();
   return LIBRARY_NO_ERROR;
}
// void gr_clear_color(float, float, float, float);
DLLEXPORT int gr_clear_color_m(stdargs){
   gr_clear_color((float)mgd(Args[0]), (float)mgd(Args[1]), (float)mgd(Args[2]), (float)mgd(Args[3]));
   return LIBRARY_NO_ERROR;
}
// void gr_clear_colored(float, float, float, float);
DLLEXPORT int gr_clear_colored_m(stdargs){
   gr_clear_colored((float)mgd(Args[0]), (float)mgd(Args[1]), (float)mgd(Args[2]), (float)mgd(Args[3]));
   return LIBRARY_NO_ERROR;
}

// void gr_register_events();
DLLEXPORT int gr_register_events_m(stdargs){
   gr_register_events();
   return LIBRARY_NO_ERROR;
}
// int gr_has_event();
DLLEXPORT int gr_has_event_m(stdargs){
   mreti(gr_has_event());
   return LIBRARY_NO_ERROR;
}

// void gr_read_mouse();
DLLEXPORT int gr_read_mouse_m(stdargs){
   gr_read_mouse();
   return LIBRARY_NO_ERROR;
}
// int gr_mouse_x();
DLLEXPORT int gr_mouse_x_m(stdargs){
   mreti(gr_mouse_x());
   return LIBRARY_NO_ERROR;
}
// int gr_mouse_y();
DLLEXPORT int gr_mouse_y_m(stdargs){
   mreti(gr_mouse_y());
   return LIBRARY_NO_ERROR;
}
// int gr_mouse_left();
DLLEXPORT int gr_mouse_left_m(stdargs){
   mreti(gr_mouse_left());
   return LIBRARY_NO_ERROR;
}
// int gr_mouse_middle();
DLLEXPORT int gr_mouse_middle_m(stdargs){
   mreti(gr_mouse_middle());
   return LIBRARY_NO_ERROR;
}
// int gr_mouse_right();
DLLEXPORT int gr_mouse_right_m(stdargs){
   mreti(gr_mouse_right());
   return LIBRARY_NO_ERROR;
}

// void gr_set_wait_event(int value);
DLLEXPORT int gr_set_wait_event_m(stdargs){
   gr_set_wait_event(mgi(Args[0]));
   return LIBRARY_NO_ERROR;
}
// int gr_read();
DLLEXPORT int gr_read_m(stdargs){
   mreti(gr_read());
   return LIBRARY_NO_ERROR;
}

// int gr_key_repeated();
DLLEXPORT int gr_key_repeated_m(stdargs){
   mreti(gr_key_repeated());
   return LIBRARY_NO_ERROR;
}
// int gr_key_pressed();
DLLEXPORT int gr_key_pressed_m(stdargs){
   mreti(gr_key_pressed());
   return LIBRARY_NO_ERROR;
}
// int gr_key();
DLLEXPORT int gr_key_m(stdargs){
   mreti(gr_key());
   return LIBRARY_NO_ERROR;
}

// int gr_mouse_button();
DLLEXPORT int gr_mouse_button_m(stdargs){
   mreti(gr_mouse_button());
   return LIBRARY_NO_ERROR;
}
// int gr_mouse_clicks();
DLLEXPORT int gr_mouse_clicks_m(stdargs){
   mreti(gr_mouse_clicks());
   return LIBRARY_NO_ERROR;
}
// int gr_mouse_button_x();
DLLEXPORT int gr_mouse_button_x_m(stdargs){
   mreti(gr_mouse_button_x());
   return LIBRARY_NO_ERROR;
}
// int gr_mouse_button_y();
DLLEXPORT int gr_mouse_button_y_m(stdargs){
   mreti(gr_mouse_button_y());
   return LIBRARY_NO_ERROR;
}

// int gr_mouse_move_x();
DLLEXPORT int gr_mouse_move_x_m(stdargs){
   mreti(gr_mouse_move_x());
   return LIBRARY_NO_ERROR;
}
// int gr_mouse_move_y();
DLLEXPORT int gr_mouse_move_y_m(stdargs){
   mreti(gr_mouse_move_y());
   return LIBRARY_NO_ERROR;
}

// int gr_mouse_move_xrel();
DLLEXPORT int gr_mouse_move_xrel_m(stdargs){
   mreti(gr_mouse_move_xrel());
   return LIBRARY_NO_ERROR;
}
// int gr_mouse_move_yrel();
DLLEXPORT int gr_mouse_move_yrel_m(stdargs){
   mreti(gr_mouse_move_yrel());
   return LIBRARY_NO_ERROR;
}

// int gr_wheel();
DLLEXPORT int gr_wheel_m(stdargs){
   mreti(gr_wheel());
   return LIBRARY_NO_ERROR;
}

// int gr_window_event();
DLLEXPORT int gr_window_event_m(stdargs){
   mreti(gr_window_event());
   return LIBRARY_NO_ERROR;
}

// void gr_view(float, float, float, float);
DLLEXPORT int gr_view_m(stdargs){
   gr_view((float)mgd(Args[0]), (float)mgd(Args[1]), (float)mgd(Args[2]), (float)mgd(Args[3]));
   return LIBRARY_NO_ERROR;
}
// void gr_view_centered(float, float, float, float);
DLLEXPORT int gr_view_centered_m(stdargs){
   gr_view_centered((float)mgd(Args[0]), (float)mgd(Args[1]), (float)mgd(Args[2]), (float)mgd(Args[3]));
   return LIBRARY_NO_ERROR;
}

// float gr_screen_to_world_x(int);
DLLEXPORT int gr_screen_to_world_x_m(stdargs){
   mreti(gr_screen_to_world_x(mgi(Args[0])));
   return LIBRARY_NO_ERROR;
}
// float gr_screen_to_world_y(int);
DLLEXPORT int gr_screen_to_world_y_m(stdargs){
   mreti(gr_screen_to_world_y(mgi(Args[0])));
   return LIBRARY_NO_ERROR;
}

// void gr_open();
DLLEXPORT int gr_open_m(stdargs){
   mreti(gr_open());
   return LIBRARY_NO_ERROR;
}
// void gr_close();
DLLEXPORT int gr_close_m(stdargs){
   gr_close();
   return LIBRARY_NO_ERROR;
}




/**/
