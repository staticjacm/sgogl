Use

```c
void gr_open()
```

to open a window and initialize sgogl

The gr_*_function functions are used to set up callbacks for certain events

```c
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
```

These take certain function pointers like *_cb

```c
typedef void (*Key_cb)(int, int, int); // key, action, mods
typedef void (*Mouse_button_cb)(int, int, int); // button, action, mods
typedef void (*Mouse_move_cb)(double, double); // x offset, y offset
typedef void (*Mouse_enter_cb)(int); // enter/leave flag
typedef void (*Mouse_scroll_cb)(double, double); // x offset, y offset
// typedef void (*File_drop_cb)(int, const char**); // number files, paths
// typedef void (*Joystick_cb)(int, int); // joystick, event
typedef void (*Window_pos_cb)(int, int); // x offset, y offset
typedef void (*Window_size_cb)(int, int); // width, height
typedef void (*Window_close_cb)();
typedef void (*Window_refresh_cb)();
typedef void (*Window_focus_cb)(int); // enter/leave flag
typedef void (*Window_iconify_cb)(int); // true/false flag
typedef void (*Framebuffer_size_cb)(int, int); // width, height
```

Example:

```c
void key_function(int key, int action, int mod){ ... }
...
gr_key_function(&key_function)
```

To set up a key pressed/released callback function



    
