
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
```

You can take a screenshot and save it to a file with:

```c
int gr_screenshot(char* file);
```

You can make a popup pop up by using one of these

```c
void gr_popup_error(char* message);
void gr_popup_warning(char* message);
void gr_popup_info(char* message);
```