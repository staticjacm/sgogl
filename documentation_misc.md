
Get the screen width and height with:

```c
int gr_width();
int gr_height();
```

The screen width and height aspect mods change the width and height depending on what the aspect ratio of the screen is (so the image doesn't get stretched):

```c
float gr_width_aspect_mod();
float gr_height_aspect_mod();
```

You can get the current mouse position with:

```c
int gr_mouse_x();
int gr_mouse_y();
```

You can take a screenshot and save it to a file with:

```c
int gr_screenshot(char* file);
```

