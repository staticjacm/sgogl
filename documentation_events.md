# Registering and checking for events

Register new events with 

```c
void gr_register_events()
```

Which enqueues all events waiting to be read

Check to see if there is currently an event waiting in the queue using

```c
int gr_has_event();
```

# Reading events

First, use 

```c
int gr_read();
```

Which returns the event's type (the event is stored in an internal variable) as one of these:

```c
enum {
  GR_NULL_EVENT,
  GR_KEY_EVENT,
  GR_WINDOW_EVENT,
  GR_CLOSE,
  GR_MOUSE_BUTTON_EVENT,
  GR_MOUSE_MOVE_EVENT,
  GR_MOUSE_WHEEL_EVENT
};
```

If you would like sgogl to **wait** for the next event use

```c
void gr_set_wait_event(int wait)
```

### Closing ``GR_CLOSE``

One of the mose important single events. If you get this one ``GR_CLOSE`` then someone clicked the 'X', or is otherwise trying to close the program

### Keys ``GR_KEY_EVENT``

To get a keyboard event's key use:

```c
int gr_key();
```

Then check if it was pressed or released with

```c
int gr_key_pressed();
```

You can check if the key is a repeat press with

```c
int gr_key_repeated();
```

### Mouse State

You can get the instantaneous mouse state by first using

```c
void gr_read_mouse();
```

Then, to get the mouse x or y screen position use

```c
int gr_mouse_x();
int gr_mouse_y();
```

Remember you can use ``float gr_screen_to_world_x(int x)`` and ``float gr_screen_to_world_y(int y)`` to get the world coordinates from mouse coordinates

To get the mouse left, middle or right button state use

```c
int gr_mouse_left();
int gr_mouse_middle();
int gr_mouse_right();
```

### Mouse ``GR_MOUSE_BUTTON_EVENT``

Those functions above are for the **instantaneous** mouse state

Below are for use after a call to ``gr_read``

```c
int gr_mouse_button();
```

And get the position of the event with

```c
int gr_mouse_button_x();
int gr_mouse_button_y();
```

You can also check if that button was repeatedly pressed use

```c
int gr_mouse_clicks();
```

### Mouse ``GR_MOUSE_MOVE_EVENT``

You can get mouse position after movement with

```c
int gr_mouse_move_x();
int gr_mouse_move_y();
```

And the actual mouse movement delta with

```c
int gr_mouse_move_xrel();
int gr_mouse_move_yrel();
```

### Mouse ``GR_MOUSE_WHEEL_EVENT``

To get the mouse wheel scroll number (the number of scrolls its made) use

```c
int gr_wheel();
```

### Window ``GR_WINDOW_EVENT``

You need to use a new event variable to hold the output of

```c
int gr_window_event();
```

Which holds the type of event the ``GR_WINDOW_EVENT`` was. Then you can check that against each of these:

```c
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
```

And do whatever tf you want