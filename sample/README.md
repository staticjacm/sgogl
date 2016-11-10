
This folder contains everything you need to compile and link a program using sgogl

Just run build.bat (blah blah blah something system32) and run a.exe

The important thing to take away from this sample folder is that you need glfw3.dll, sgogl.dll and their lib files libglfw3.a and libsgogl.a, then you can link them in the usual way

```c
gcc my_program_name_here.c -Lwhatever_folder_contains_the_lib_files -lglfw3 -lsgogl
```