# Basics

Clear the color and depth buffers with 

```c
void gr_clear()
```

Clearing the screen fills it with the color 

And then refresh the screen using

```c
void gr_refresh()
```

# Images

Draw the image ``tex`` onto the screen at world position ``(x, y, z)`` anchor point ``(anx, any)`` and rotation angle ``angle`` and scaled by ``(sx, sy)`` with

```c
void gr_draw(unsigned int tex, float x, float y, float z, float anx, float any, float angle, float sx, float sy)
```

Or draw ``tex`` similarly but with anchor point ``(0.5f, 0.5f)`` with

```c
void gr_draw_centered(unsigned int tex, float x, float y, float z, float angle, float sx, float sy)
```

# Points and lines

Points and lines get colored with the color ``(r, g, b, a)`` plugged into the last ``void gr_color(float r, float g, float b, float a)``

You can set the point size with

```c
void gr_point_size(float s)
```

Then draw a point with

```c
void gr_draw_point(float x, float y, float z)
```

And draw a line from ``(x0, y0)`` to ``(x1, y1)`` with depth ``z`` with

```c
void gr_draw_line(float x0, float y0, float x1, float y1, float z)
```

Or use the special version to draw a line going from depth ``z0`` to ``z1`` with

```c
void gr_draw_line_sp(float x0, float y0, float z0, float x1, float y1, float z1)
```

