# Polling

Poll events with 

```c
void gr_poll_events()
```

Which enqueues all the events to be supplied to callback functions

# Key Callback Function

Use 

```c
typedef void (*Key_cb)(int key, int action, int mods)
void gr_key_function(Key_cb)
```

To register a key callback function

Parameter ``key`` is the particular keyboard key (keycode) which can be any of the GLFW keycode values which have aliases

```c
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
}
```

Parameter ``action`` is one of the GLFW action codes representing a key press (0b1) or key release (0b0), with the second bit (0b10) representing if the key was repeatedly pressed

```c
enum{
  GR_RELEASE  = 0,
  GR_PRESS    = 1,
  GR_REPEAT   = 2
}
```

Parameter ``mods`` can be a combination of any the following, and represent which modifier key was pressed when the ``key`` key was pressed

```c
enum{
  GLFW_MOD_SHIFT          = 0x0001,
  GLFW_MOD_CONTROL        = 0x0002,
  GLFW_MOD_ALT            = 0x0004,
  GLFW_MOD_SUPER          = 0x0008
}
```

