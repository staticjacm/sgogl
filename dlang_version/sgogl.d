module sgogl;


/******************************/
/** Proxies for SDL values **/

/**
Error codes
**/
enum {
  IERROR_SDL_NONE      = 0b000,
  IERROR_SDL_WINDOW    = 0b001,
  IERROR_SDL_GL        = 0b010
};

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

/*
Here are SDL scancodes taken directly from the scancode header file from the SDL source
I changed the names from SDL_* to GR_* to match the naming scheme of sgogl
**/
enum {
    GR_SCANCODE_UNKNOWN = 0,

    /**
     *  \name Usage page 0x07
     *
     *  These values are from usage page 0x07 (USB keyboard page).
     */
    /* @{ */

    GR_SCANCODE_A = 4,
    GR_SCANCODE_B = 5,
    GR_SCANCODE_C = 6,
    GR_SCANCODE_D = 7,
    GR_SCANCODE_E = 8,
    GR_SCANCODE_F = 9,
    GR_SCANCODE_G = 10,
    GR_SCANCODE_H = 11,
    GR_SCANCODE_I = 12,
    GR_SCANCODE_J = 13,
    GR_SCANCODE_K = 14,
    GR_SCANCODE_L = 15,
    GR_SCANCODE_M = 16,
    GR_SCANCODE_N = 17,
    GR_SCANCODE_O = 18,
    GR_SCANCODE_P = 19,
    GR_SCANCODE_Q = 20,
    GR_SCANCODE_R = 21,
    GR_SCANCODE_S = 22,
    GR_SCANCODE_T = 23,
    GR_SCANCODE_U = 24,
    GR_SCANCODE_V = 25,
    GR_SCANCODE_W = 26,
    GR_SCANCODE_X = 27,
    GR_SCANCODE_Y = 28,
    GR_SCANCODE_Z = 29,

    GR_SCANCODE_1 = 30,
    GR_SCANCODE_2 = 31,
    GR_SCANCODE_3 = 32,
    GR_SCANCODE_4 = 33,
    GR_SCANCODE_5 = 34,
    GR_SCANCODE_6 = 35,
    GR_SCANCODE_7 = 36,
    GR_SCANCODE_8 = 37,
    GR_SCANCODE_9 = 38,
    GR_SCANCODE_0 = 39,

    GR_SCANCODE_RETURN = 40,
    GR_SCANCODE_ESCAPE = 41,
    GR_SCANCODE_BACKSPACE = 42,
    GR_SCANCODE_TAB = 43,
    GR_SCANCODE_SPACE = 44,

    GR_SCANCODE_MINUS = 45,
    GR_SCANCODE_EQUALS = 46,
    GR_SCANCODE_LEFTBRACKET = 47,
    GR_SCANCODE_RIGHTBRACKET = 48,
    GR_SCANCODE_BACKSLASH = 49, /**< Located at the lower left of the return
                                  *   key on ISO keyboards and at the right end
                                  *   of the QWERTY row on ANSI keyboards.
                                  *   Produces REVERSE SOLIDUS (backslash) and
                                  *   VERTICAL LINE in a US layout, REVERSE
                                  *   SOLIDUS and VERTICAL LINE in a UK Mac
                                  *   layout, NUMBER SIGN and TILDE in a UK
                                  *   Windows layout, DOLLAR SIGN and POUND SIGN
                                  *   in a Swiss German layout, NUMBER SIGN and
                                  *   APOSTROPHE in a German layout, GRAVE
                                  *   ACCENT and POUND SIGN in a French Mac
                                  *   layout, and ASTERISK and MICRO SIGN in a
                                  *   French Windows layout.
                                  */
    GR_SCANCODE_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                  *   instead of 49 for the same key, but all
                                  *   OSes I've seen treat the two codes
                                  *   identically. So, as an implementor, unless
                                  *   your keyboard generates both of those
                                  *   codes and your OS treats them differently,
                                  *   you should generate SDL_SCANCODE_BACKSLASH
                                  *   instead of this code. As a user, you
                                  *   should not rely on this code because SDL
                                  *   will never generate it with most (all?)
                                  *   keyboards.
                                  */
    GR_SCANCODE_SEMICOLON = 51,
    GR_SCANCODE_APOSTROPHE = 52,
    GR_SCANCODE_GRAVE = 53, /**< Located in the top left corner (on both ANSI
                              *   and ISO keyboards). Produces GRAVE ACCENT and
                              *   TILDE in a US Windows layout and in US and UK
                              *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                              *   and NOT SIGN in a UK Windows layout, SECTION
                              *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                              *   layouts on ISO keyboards, SECTION SIGN and
                              *   DEGREE SIGN in a Swiss German layout (Mac:
                              *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                              *   DEGREE SIGN in a German layout (Mac: only on
                              *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                              *   French Windows layout, COMMERCIAL AT and
                              *   NUMBER SIGN in a French Mac layout on ISO
                              *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                              *   SIGN in a Swiss German, German, or French Mac
                              *   layout on ANSI keyboards.
                              */
    GR_SCANCODE_COMMA = 54,
    GR_SCANCODE_PERIOD = 55,
    GR_SCANCODE_SLASH = 56,

    GR_SCANCODE_CAPSLOCK = 57,

    GR_SCANCODE_F1 = 58,
    GR_SCANCODE_F2 = 59,
    GR_SCANCODE_F3 = 60,
    GR_SCANCODE_F4 = 61,
    GR_SCANCODE_F5 = 62,
    GR_SCANCODE_F6 = 63,
    GR_SCANCODE_F7 = 64,
    GR_SCANCODE_F8 = 65,
    GR_SCANCODE_F9 = 66,
    GR_SCANCODE_F10 = 67,
    GR_SCANCODE_F11 = 68,
    GR_SCANCODE_F12 = 69,

    GR_SCANCODE_PRINTSCREEN = 70,
    GR_SCANCODE_SCROLLLOCK = 71,
    GR_SCANCODE_PAUSE = 72,
    GR_SCANCODE_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                                   does send code 73, not 117) */
    GR_SCANCODE_HOME = 74,
    GR_SCANCODE_PAGEUP = 75,
    GR_SCANCODE_DELETE = 76,
    GR_SCANCODE_END = 77,
    GR_SCANCODE_PAGEDOWN = 78,
    GR_SCANCODE_RIGHT = 79,
    GR_SCANCODE_LEFT = 80,
    GR_SCANCODE_DOWN = 81,
    GR_SCANCODE_UP = 82,

    GR_SCANCODE_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                     */
    GR_SCANCODE_KP_DIVIDE = 84,
    GR_SCANCODE_KP_MULTIPLY = 85,
    GR_SCANCODE_KP_MINUS = 86,
    GR_SCANCODE_KP_PLUS = 87,
    GR_SCANCODE_KP_ENTER = 88,
    GR_SCANCODE_KP_1 = 89,
    GR_SCANCODE_KP_2 = 90,
    GR_SCANCODE_KP_3 = 91,
    GR_SCANCODE_KP_4 = 92,
    GR_SCANCODE_KP_5 = 93,
    GR_SCANCODE_KP_6 = 94,
    GR_SCANCODE_KP_7 = 95,
    GR_SCANCODE_KP_8 = 96,
    GR_SCANCODE_KP_9 = 97,
    GR_SCANCODE_KP_0 = 98,
    GR_SCANCODE_KP_PERIOD = 99,

    GR_SCANCODE_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
                                        *   keyboards have over ANSI ones,
                                        *   located between left shift and Y.
                                        *   Produces GRAVE ACCENT and TILDE in a
                                        *   US or UK Mac layout, REVERSE SOLIDUS
                                        *   (backslash) and VERTICAL LINE in a
                                        *   US or UK Windows layout, and
                                        *   LESS-THAN SIGN and GREATER-THAN SIGN
                                        *   in a Swiss German, German, or French
                                        *   layout. */
    GR_SCANCODE_APPLICATION = 101, /**< windows contextual menu, compose */
    GR_SCANCODE_POWER = 102, /**< The USB document says this is a status flag,
                               *   not a physical key - but some Mac keyboards
                               *   do have a power key. */
    GR_SCANCODE_KP_EQUALS = 103,
    GR_SCANCODE_F13 = 104,
    GR_SCANCODE_F14 = 105,
    GR_SCANCODE_F15 = 106,
    GR_SCANCODE_F16 = 107,
    GR_SCANCODE_F17 = 108,
    GR_SCANCODE_F18 = 109,
    GR_SCANCODE_F19 = 110,
    GR_SCANCODE_F20 = 111,
    GR_SCANCODE_F21 = 112,
    GR_SCANCODE_F22 = 113,
    GR_SCANCODE_F23 = 114,
    GR_SCANCODE_F24 = 115,
    GR_SCANCODE_EXECUTE = 116,
    GR_SCANCODE_HELP = 117,
    GR_SCANCODE_MENU = 118,
    GR_SCANCODE_SELECT = 119,
    GR_SCANCODE_STOP = 120,
    GR_SCANCODE_AGAIN = 121,   /**< redo */
    GR_SCANCODE_UNDO = 122,
    GR_SCANCODE_CUT = 123,
    GR_SCANCODE_COPY = 124,
    GR_SCANCODE_PASTE = 125,
    GR_SCANCODE_FIND = 126,
    GR_SCANCODE_MUTE = 127,
    GR_SCANCODE_VOLUMEUP = 128,
    GR_SCANCODE_VOLUMEDOWN = 129,
/* not sure whether there's a reason to enable these */
/*     SDL_SCANCODE_LOCKINGCAPSLOCK = 130,  */
/*     SDL_SCANCODE_LOCKINGNUMLOCK = 131, */
/*     SDL_SCANCODE_LOCKINGSCROLLLOCK = 132, */
    GR_SCANCODE_KP_COMMA = 133,
    GR_SCANCODE_KP_EQUALSAS400 = 134,

    GR_SCANCODE_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                            footnotes in USB doc */
    GR_SCANCODE_INTERNATIONAL2 = 136,
    GR_SCANCODE_INTERNATIONAL3 = 137, /**< Yen */
    GR_SCANCODE_INTERNATIONAL4 = 138,
    GR_SCANCODE_INTERNATIONAL5 = 139,
    GR_SCANCODE_INTERNATIONAL6 = 140,
    GR_SCANCODE_INTERNATIONAL7 = 141,
    GR_SCANCODE_INTERNATIONAL8 = 142,
    GR_SCANCODE_INTERNATIONAL9 = 143,
    GR_SCANCODE_LANG1 = 144, /**< Hangul/English toggle */
    GR_SCANCODE_LANG2 = 145, /**< Hanja conversion */
    GR_SCANCODE_LANG3 = 146, /**< Katakana */
    GR_SCANCODE_LANG4 = 147, /**< Hiragana */
    GR_SCANCODE_LANG5 = 148, /**< Zenkaku/Hankaku */
    GR_SCANCODE_LANG6 = 149, /**< reserved */
    GR_SCANCODE_LANG7 = 150, /**< reserved */
    GR_SCANCODE_LANG8 = 151, /**< reserved */
    GR_SCANCODE_LANG9 = 152, /**< reserved */

    GR_SCANCODE_ALTERASE = 153, /**< Erase-Eaze */
    GR_SCANCODE_SYSREQ = 154,
    GR_SCANCODE_CANCEL = 155,
    GR_SCANCODE_CLEAR = 156,
    GR_SCANCODE_PRIOR = 157,
    GR_SCANCODE_RETURN2 = 158,
    GR_SCANCODE_SEPARATOR = 159,
    GR_SCANCODE_OUT = 160,
    GR_SCANCODE_OPER = 161,
    GR_SCANCODE_CLEARAGAIN = 162,
    GR_SCANCODE_CRSEL = 163,
    GR_SCANCODE_EXSEL = 164,

    GR_SCANCODE_KP_00 = 176,
    GR_SCANCODE_KP_000 = 177,
    GR_SCANCODE_THOUSANDSSEPARATOR = 178,
    GR_SCANCODE_DECIMALSEPARATOR = 179,
    GR_SCANCODE_CURRENCYUNIT = 180,
    GR_SCANCODE_CURRENCYSUBUNIT = 181,
    GR_SCANCODE_KP_LEFTPAREN = 182,
    GR_SCANCODE_KP_RIGHTPAREN = 183,
    GR_SCANCODE_KP_LEFTBRACE = 184,
    GR_SCANCODE_KP_RIGHTBRACE = 185,
    GR_SCANCODE_KP_TAB = 186,
    GR_SCANCODE_KP_BACKSPACE = 187,
    GR_SCANCODE_KP_A = 188,
    GR_SCANCODE_KP_B = 189,
    GR_SCANCODE_KP_C = 190,
    GR_SCANCODE_KP_D = 191,
    GR_SCANCODE_KP_E = 192,
    GR_SCANCODE_KP_F = 193,
    GR_SCANCODE_KP_XOR = 194,
    GR_SCANCODE_KP_POWER = 195,
    GR_SCANCODE_KP_PERCENT = 196,
    GR_SCANCODE_KP_LESS = 197,
    GR_SCANCODE_KP_GREATER = 198,
    GR_SCANCODE_KP_AMPERSAND = 199,
    GR_SCANCODE_KP_DBLAMPERSAND = 200,
    GR_SCANCODE_KP_VERTICALBAR = 201,
    GR_SCANCODE_KP_DBLVERTICALBAR = 202,
    GR_SCANCODE_KP_COLON = 203,
    GR_SCANCODE_KP_HASH = 204,
    GR_SCANCODE_KP_SPACE = 205,
    GR_SCANCODE_KP_AT = 206,
    GR_SCANCODE_KP_EXCLAM = 207,
    GR_SCANCODE_KP_MEMSTORE = 208,
    GR_SCANCODE_KP_MEMRECALL = 209,
    GR_SCANCODE_KP_MEMCLEAR = 210,
    GR_SCANCODE_KP_MEMADD = 211,
    GR_SCANCODE_KP_MEMSUBTRACT = 212,
    GR_SCANCODE_KP_MEMMULTIPLY = 213,
    GR_SCANCODE_KP_MEMDIVIDE = 214,
    GR_SCANCODE_KP_PLUSMINUS = 215,
    GR_SCANCODE_KP_CLEAR = 216,
    GR_SCANCODE_KP_CLEARENTRY = 217,
    GR_SCANCODE_KP_BINARY = 218,
    GR_SCANCODE_KP_OCTAL = 219,
    GR_SCANCODE_KP_DECIMAL = 220,
    GR_SCANCODE_KP_HEXADECIMAL = 221,

    GR_SCANCODE_LCTRL = 224,
    GR_SCANCODE_LSHIFT = 225,
    GR_SCANCODE_LALT = 226, /**< alt, option */
    GR_SCANCODE_LGUI = 227, /**< windows, command (apple), meta */
    GR_SCANCODE_RCTRL = 228,
    GR_SCANCODE_RSHIFT = 229,
    GR_SCANCODE_RALT = 230, /**< alt gr, option */
    GR_SCANCODE_RGUI = 231, /**< windows, command (apple), meta */

    GR_SCANCODE_MODE = 257,    /**< I'm not sure if this is really not covered
                                 *   by any of the above, but since there's a
                                 *   special KMOD_MODE for it I'm adding it here
                                 */

    /* @} *//* Usage page 0x07 */

    /**
     *  \name Usage page 0x0C
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     */
    /* @{ */

    GR_SCANCODE_AUDIONEXT = 258,
    GR_SCANCODE_AUDIOPREV = 259,
    GR_SCANCODE_AUDIOSTOP = 260,
    GR_SCANCODE_AUDIOPLAY = 261,
    GR_SCANCODE_AUDIOMUTE = 262,
    GR_SCANCODE_MEDIASELECT = 263,
    GR_SCANCODE_WWW = 264,
    GR_SCANCODE_MAIL = 265,
    GR_SCANCODE_CALCULATOR = 266,
    GR_SCANCODE_COMPUTER = 267,
    GR_SCANCODE_AC_SEARCH = 268,
    GR_SCANCODE_AC_HOME = 269,
    GR_SCANCODE_AC_BACK = 270,
    GR_SCANCODE_AC_FORWARD = 271,
    GR_SCANCODE_AC_STOP = 272,
    GR_SCANCODE_AC_REFRESH = 273,
    GR_SCANCODE_AC_BOOKMARKS = 274,

    /* @} *//* Usage page 0x0C */

    /**
     *  \name Walther keys
     *
     *  These are values that Christian Walther added (for mac keyboard?).
     */
    /* @{ */

    GR_SCANCODE_BRIGHTNESSDOWN = 275,
    GR_SCANCODE_BRIGHTNESSUP = 276,
    GR_SCANCODE_DISPLAYSWITCH = 277, /**< display mirroring/dual display
                                        switch, video mode switch */
    GR_SCANCODE_KBDILLUMTOGGLE = 278,
    GR_SCANCODE_KBDILLUMDOWN = 279,
    GR_SCANCODE_KBDILLUMUP = 280,
    GR_SCANCODE_EJECT = 281,
    GR_SCANCODE_SLEEP = 282,
    
    GR_SCANCODE_APP1 = 283,
    GR_SCANCODE_APP2 = 284,

    /* @} *//* Walther keys */

    /* Add any other keys here. */

    GR_NUM_SCANCODES = 512 /**< not a key, just marks the number of scancodes
                                 for array bounds */
};

/**
Key codes
*/

/*
The macros and the enum block is taken directly from the SDL keycode header
with the names changed to match the sgogl naming scheme
*/
const(int) GR_SCANCODE_MASK = 1<<30;
const(int) GR_SCANCODE_TO_KEYCODE(const(int) X){ return X | GR_SCANCODE_MASK; }

enum 
{
    GR_UNKNOWN = 0,
    
    GR_RETURN = '\r',
    GR_ESCAPE = '\033',
    GR_BACKSPACE = '\b',
    GR_TAB = '\t',
    GR_SPACE = ' ',
    GR_EXCLAIM = '!',
    GR_QUOTEDBL = '"',
    GR_HASH = '#',
    GR_PERCENT = '%',
    GR_DOLLAR = '$',
    GR_AMPERSAND = '&',
    GR_QUOTE = '\'',
    GR_LEFTPAREN = '(',
    GR_RIGHTPAREN = ')',
    GR_ASTERISK = '*',
    GR_PLUS = '+',
    GR_COMMA = ',',
    GR_MINUS = '-',
    GR_PERIOD = '.',
    GR_SLASH = '/',
    GR_0 = '0',
    GR_1 = '1',
    GR_2 = '2',
    GR_3 = '3',
    GR_4 = '4',
    GR_5 = '5',
    GR_6 = '6',
    GR_7 = '7',
    GR_8 = '8',
    GR_9 = '9',
    GR_COLON = ':',
    GR_SEMICOLON = ';',
    GR_LESS = '<',
    GR_EQUALS = '=',
    GR_GREATER = '>',
    GR_QUESTION = '?',
    GR_AT = '@',
    
    GR_LEFTBRACKET = '[',
    GR_BACKSLASH = '\\',
    GR_RIGHTBRACKET = ']',
    GR_CARET = '^',
    GR_UNDERSCORE = '_',
    GR_BACKQUOTE = '`',
    GR_A = 'a',
    GR_B = 'b',
    GR_C = 'c',
    GR_D = 'd',
    GR_E = 'e',
    GR_F = 'f',
    GR_G = 'g',
    GR_H = 'h',
    GR_I = 'i',
    GR_J = 'j',
    GR_K = 'k',
    GR_L = 'l',
    GR_M = 'm',
    GR_N = 'n',
    GR_O = 'o',
    GR_P = 'p',
    GR_Q = 'q',
    GR_R = 'r',
    GR_S = 's',
    GR_T = 't',
    GR_U = 'u',
    GR_V = 'v',
    GR_W = 'w',
    GR_X = 'x',
    GR_Y = 'y',
    GR_Z = 'z',

    GR_CAPSLOCK                = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_CAPSLOCK),

    GR_F1                      = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_F1),
    GR_F2                      = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_F2),
    GR_F3                      = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_F3),
    GR_F4                      = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_F4),
    GR_F5                      = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_F5),
    GR_F6                      = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_F6),
    GR_F7                      = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_F7),
    GR_F8                      = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_F8),
    GR_F9                      = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_F9),
    GR_F10                     = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_F10),
    GR_F11                     = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_F11),
    GR_F12                     = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_F12),

    GR_PRINTSCREEN             = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_PRINTSCREEN),
    GR_SCROLLLOCK              = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_SCROLLLOCK),
    GR_PAUSE                   = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_PAUSE),
    GR_INSERT                  = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_INSERT),
    GR_HOME                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_HOME),
    GR_PAGEUP                  = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_PAGEUP),
    GR_DELETE                  = '\177',
    GR_END                     = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_END),
    GR_PAGEDOWN                = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_PAGEDOWN),
    GR_RIGHT                   = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_RIGHT),
    GR_LEFT                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_LEFT),
    GR_DOWN                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_DOWN),
    GR_UP                      = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_UP),

    GR_NUMLOCKCLEAR            = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_NUMLOCKCLEAR),
    GR_KP_DIVIDE               = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_DIVIDE),
    GR_KP_MULTIPLY             = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_MULTIPLY),
    GR_KP_MINUS                = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_MINUS),
    GR_KP_PLUS                 = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_PLUS),
    GR_KP_ENTER                = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_ENTER),
    GR_KP_1                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_1),
    GR_KP_2                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_2),
    GR_KP_3                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_3),
    GR_KP_4                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_4),
    GR_KP_5                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_5),
    GR_KP_6                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_6),
    GR_KP_7                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_7),
    GR_KP_8                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_8),
    GR_KP_9                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_9),
    GR_KP_0                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_0),
    GR_KP_PERIOD               = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_PERIOD),

    GR_APPLICATION             = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_APPLICATION),
    GR_POWER                   = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_POWER),
    GR_KP_EQUALS               = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_EQUALS),
    GR_F13                     = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_F13),
    GR_F14                     = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_F14),
    GR_F15                     = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_F15),
    GR_F16                     = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_F16),
    GR_F17                     = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_F17),
    GR_F18                     = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_F18),
    GR_F19                     = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_F19),
    GR_F20                     = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_F20),
    GR_F21                     = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_F21),
    GR_F22                     = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_F22),
    GR_F23                     = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_F23),
    GR_F24                     = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_F24),
    GR_EXECUTE                 = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_EXECUTE),
    GR_HELP                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_HELP),
    GR_MENU                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_MENU),
    GR_SELECT                  = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_SELECT),
    GR_STOP                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_STOP),
    GR_AGAIN                   = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_AGAIN),
    GR_UNDO                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_UNDO),
    GR_CUT                     = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_CUT),
    GR_COPY                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_COPY),
    GR_PASTE                   = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_PASTE),
    GR_FIND                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_FIND),
    GR_MUTE                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_MUTE),
    GR_VOLUMEUP                = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_VOLUMEUP),
    GR_VOLUMEDOWN              = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_VOLUMEDOWN),
    GR_KP_COMMA                = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_COMMA),
    GR_KP_EQUALSAS400          = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_EQUALSAS400),

    GR_ALTERASE                = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_ALTERASE),
    GR_SYSREQ                  = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_SYSREQ),
    GR_CANCEL                  = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_CANCEL),
    GR_CLEAR                   = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_CLEAR),
    GR_PRIOR                   = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_PRIOR),
    GR_RETURN2                 = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_RETURN2),
    GR_SEPARATOR               = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_SEPARATOR),
    GR_OUT                     = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_OUT),
    GR_OPER                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_OPER),
    GR_CLEARAGAIN              = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_CLEARAGAIN),
    GR_CRSEL                   = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_CRSEL),
    GR_EXSEL                   = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_EXSEL),

    GR_KP_00                   = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_00),
    GR_KP_000                  = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_000),
    GR_THOUSANDSSEPARATOR      = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_THOUSANDSSEPARATOR),
    GR_DECIMALSEPARATOR        = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_DECIMALSEPARATOR),
    GR_CURRENCYUNIT            = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_CURRENCYUNIT),
    GR_CURRENCYSUBUNIT         = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_CURRENCYSUBUNIT),
    GR_KP_LEFTPAREN            = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_LEFTPAREN),
    GR_KP_RIGHTPAREN           = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_RIGHTPAREN),
    GR_KP_LEFTBRACE            = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_LEFTBRACE),
    GR_KP_RIGHTBRACE           = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_RIGHTBRACE),
    GR_KP_TAB                  = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_TAB),
    GR_KP_BACKSPACE            = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_BACKSPACE),
    GR_KP_A                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_A),
    GR_KP_B                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_B),
    GR_KP_C                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_C),
    GR_KP_D                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_D),
    GR_KP_E                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_E),
    GR_KP_F                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_F),
    GR_KP_XOR                  = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_XOR),
    GR_KP_POWER                = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_POWER),
    GR_KP_PERCENT              = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_PERCENT),
    GR_KP_LESS                 = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_LESS),
    GR_KP_GREATER              = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_GREATER),
    GR_KP_AMPERSAND            = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_AMPERSAND),
    GR_KP_DBLAMPERSAND         = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_DBLAMPERSAND),
    GR_KP_VERTICALBAR          = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_VERTICALBAR),
    GR_KP_DBLVERTICALBAR       = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_DBLVERTICALBAR),
    GR_KP_COLON                = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_COLON),
    GR_KP_HASH                 = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_HASH),
    GR_KP_SPACE                = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_SPACE),
    GR_KP_AT                   = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_AT),
    GR_KP_EXCLAM               = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_EXCLAM),
    GR_KP_MEMSTORE             = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_MEMSTORE),
    GR_KP_MEMRECALL            = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_MEMRECALL),
    GR_KP_MEMCLEAR             = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_MEMCLEAR),
    GR_KP_MEMADD               = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_MEMADD),
    GR_KP_MEMSUBTRACT          = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_MEMSUBTRACT),
    GR_KP_MEMMULTIPLY          = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_MEMMULTIPLY),
    GR_KP_MEMDIVIDE            = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_MEMDIVIDE),
    GR_KP_PLUSMINUS            = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_PLUSMINUS),
    GR_KP_CLEAR                = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_CLEAR),
    GR_KP_CLEARENTRY           = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_CLEARENTRY),
    GR_KP_BINARY               = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_BINARY),
    GR_KP_OCTAL                = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_OCTAL),
    GR_KP_DECIMAL              = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_DECIMAL),
    GR_KP_HEXADECIMAL          = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KP_HEXADECIMAL),

    GR_LCTRL                   = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_LCTRL),
    GR_LSHIFT                  = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_LSHIFT),
    GR_LALT                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_LALT),
    GR_LGUI                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_LGUI),
    GR_RCTRL                   = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_RCTRL),
    GR_RSHIFT                  = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_RSHIFT),
    GR_RALT                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_RALT),
    GR_RGUI                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_RGUI),

    GR_MODE                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_MODE),

    GR_AUDIONEXT               = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_AUDIONEXT),
    GR_AUDIOPREV               = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_AUDIOPREV),
    GR_AUDIOSTOP               = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_AUDIOSTOP),
    GR_AUDIOPLAY               = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_AUDIOPLAY),
    GR_AUDIOMUTE               = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_AUDIOMUTE),
    GR_MEDIASELECT             = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_MEDIASELECT),
    GR_WWW                     = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_WWW),
    GR_MAIL                    = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_MAIL),
    GR_CALCULATOR              = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_CALCULATOR),
    GR_COMPUTER                = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_COMPUTER),
    GR_AC_SEARCH               = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_AC_SEARCH),
    GR_AC_HOME                 = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_AC_HOME),
    GR_AC_BACK                 = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_AC_BACK),
    GR_AC_FORWARD              = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_AC_FORWARD),
    GR_AC_STOP                 = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_AC_STOP),
    GR_AC_REFRESH              = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_AC_REFRESH),
    GR_AC_BOOKMARKS            = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_AC_BOOKMARKS),

    GR_BRIGHTNESSDOWN          = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_BRIGHTNESSDOWN),
    GR_BRIGHTNESSUP            = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_BRIGHTNESSUP),
    GR_DISPLAYSWITCH           = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_DISPLAYSWITCH),
    GR_KBDILLUMTOGGLE          = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KBDILLUMTOGGLE),
    GR_KBDILLUMDOWN            = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KBDILLUMDOWN),
    GR_KBDILLUMUP              = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_KBDILLUMUP),
    GR_EJECT                   = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_EJECT),
    GR_SLEEP                   = GR_SCANCODE_TO_KEYCODE(GR_SCANCODE_SLEEP)
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

/******************/
/** Sub-Viewport **/

/*********************/
/** Window Resizing **/

extern(C) {
  void gr_set_window_max_size(int, int);
  void gr_set_window_min_size(int, int);

  void gr_set_window_size(int, int);
}

/*********************/
/** Screen Resizing **/

extern(C) void gr_set_screen_size(int, int);

/**********/
/** View **/
extern(C) {
  void gr_view(float, float, float, float);
  void gr_view_centered(float, float, float, float);
  void gr_view_3d_fxyn(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float);
  void gr_view_3d(float, float, float, float, float, float, float, float, float, float, float, float);

  float gr_screen_to_world_x(int);
  float gr_screen_to_world_y(int);
}

/*******************/
/** Informational **/
extern(C) {
  int gr_screen_width();
  int gr_screen_height();
  float gr_screen_x_aspect_mod();
  float gr_screen_y_aspect_mod();

  int gr_window_width();
  int gr_window_height();
  float gr_window_x_aspect_mod();
  float gr_window_y_aspect_mod();

  float gr_max_depth();

  float gr_view_scale(); 
  float gr_view_width() ;
  float gr_view_height();
  float gr_view_left();
  float gr_view_right();
  float gr_view_bottom();
  float gr_view_top();

  int gr_get_window_width();
  int gr_get_window_height();
}

/************************************/
/** Setting Variables / Parameters **/

extern(C) {
  void gr_set_keep_window_aspect(int);
  void gr_set_center_screen(int);
  void gr_set_stretch_screen(int);

  void gr_activate_events(int);
  
  void gr_point_size(float);
  void gr_round_points(int);

  void gr_set_max_depth(float);

  void gr_activate_transparency(int);
  void gr_activate_linear_filtering(int);
  void gr_activate_dithering(int);
  void gr_activate_depth_testing(int);

  // set before starting
  void gr_set_opengl_doublebuffering(int);

  void gr_toggle_window_bordered();
  void gr_set_window_brightness(float);
  void gr_set_window_fullscreen();
  void gr_set_window_fullscreen_desktop();
  void gr_set_window_windowed();
  void gr_toggle_mouse_grabbed();
  int  gr_set_window_icon(char*);

  void gr_set_input_focus();
  void gr_set_window_position(int, int);
  void gr_set_window_title(char*);

  void gr_popup_error(char*);
  void gr_popup_warning(char*);
  void gr_popup_info(char*);
}

/************/
/** Colors **/

extern(C) {
  void gr_color(float, float, float, float);
  void gr_color_alpha(float);
}

/************/
/** Images **/


/**
  TAKEN FROM SOIL.h (see http://www.lonesock.net/soil.html)
**/
enum
{
	IMG_POWER_OF_TWO       = 1  ,
	IMG_MIPMAPS            = 2  ,
	IMG_TEXTURE_REPEATS    = 4  ,
	IMG_MULTIPLY_ALPHA     = 8  ,
	IMG_INVERT_Y           = 16 ,
	IMG_COMPRESS_TO_DXT    = 32 ,
	IMG_DDS_LOAD_DIRECT    = 64 ,
	IMG_NTSC_SAFE_RGB      = 128,
	IMG_COCG_Y             = 256, 
	IMG_TEXTURE_RECTANGLE  = 512
};

enum
{
	IMG_AUTO = 0,
	IMG_L = 1,
	IMG_LA = 2,
	IMG_RGB = 3,
	IMG_RGBA = 4
};

extern(C) {
  uint gr_load_image_ram(const(char)*, uint, int, int, int, uint);
  uint gr_load_image_ext(const(char)*, uint, uint, uint);
  uint gr_load_image(const(char)*, uint);
  void gr_unload_image(uint);
  int gr_screenshot(const(char)*);
}

/***********/
/** Audio **/

extern(C) {
  int find_available_mix_chunk_list_id();

  int gr_load_wav(const(char)*, int);
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
  void gr_resume(int);
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

/***********/
/** Text **/

extern(C){
  uint gr_load_ttf(immutable(char)*, float);
  void gr_draw_text(uint, immutable(char)*, float, float, float, float, float, float, float, float);
  void gr_screen_draw_text(uint, immutable(char)*, float, float, float, float, float, float, float, float);
}

/*************/
/** Drawing **/

extern(C) {
  void gr_screen_draw(uint, float, float, float, float, float, float, float, float);
  void gr_screen_draw_partial(uint, float, float, float, float, float, float, float, float, float, float, float, float);
  void gr_draw(uint, float, float, float, float, float, float, float, float);
  void gr_draw_partial(uint, float, float, float, float, float, float, float, float, float, float, float, float);
  void gr_draw_quad(uint, float, float, float, float, float, float, float, float, float, float, float);
  void gr_draw_quad_solid(float, float, float, float, float, float, float, float, float);
  void gr_draw_centered(uint, float, float, float, float, float, float);
  void gr_draw_point(float, float, float);
  void gr_screen_draw_line(float, float, float, float, float);
  void gr_draw_line(float, float, float, float, float);
  void gr_draw_line_3d(float, float, float, float, float, float);
  void gr_refresh();
  void gr_clear_depth();
  void gr_clear();
  void gr_clear_all();
  void gr_clear_color(float, float, float, float);
  void gr_clear_colored(float, float, float, float);
  void gr_wait_for_render();
}

/************/
/** Events **/

extern(C) {
  void gr_register_events();
  int gr_has_event();

  void gr_read_mouse();
  int gr_mouse_x();
  int gr_mouse_y();
  int gr_mouse_left();
  int gr_mouse_middle();
  int gr_mouse_right();

  void gr_set_wait_event(int);
  int gr_read();

  int gr_key_repeated();
  int gr_key_pressed();
  int gr_key();
  int gr_scancode();

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

/********************/
/** Initialization **/

extern(C) {
  int gr_open();
  void gr_close();
}
