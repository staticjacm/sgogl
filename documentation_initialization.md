# Initialization Functions
To open a window and initialize sgogl use

```c
void gr_open();
```

Similarly, **close** the window with

```c
void gr_close();
```

## Rendering

To turn on transparency, dithering, linear filtering or depth testing use:

```c
void gr_activate_transparency(int);
void gr_activate_dithering(int);
void gr_activate_depth_testing(int);
```

## Window

To toggle the window being **bordered** or not use

```c
void gr_toggle_window_bordered();
```

You can set the **brightness** with

```c
gr_set_window_brightness(float brightness);
```

The window can be set into **fullscreen**, or fullscreen desktop with

```c
void gr_set_window_fullscreen();
void gr_set_window_fullscreen_desktop();
```

And changed back to **windowed** (the default) with

```c
void gr_set_window_windowed();
```

Theres something called **mouse grabbing** that you can turn toggle with

```c
void gr_toggle_mouse_grabbed();
```

The window **title** can be set with

```c
void set_window_title(char* title);
```

You can change the **icon** that displays for the window by using

```c
void gr_set_window_icon(char* file)
```

You can automatically set the **focus** for the window with

```c
void gr_set_input_focus();
```

You can change the window **maximum** and **minimum** **sizes** with

```c
void gr_set_window_max_size(int x, int y);
void gr_set_window_min_size(int x, int y);
```

The current **size** can be set programmatically with

```c
void gr_set_window_size(int width, int height);
```

You can get the windows **width** and **height** with

```c
int gr_get_window_width();
int gr_get_window_height();
```

And set the window **position** with

```c
void gr_set_window_position(int x, int y);
```