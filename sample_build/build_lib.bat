gcc -c sgogl.c -Llib -lglfw3dll -lsoil -lopengl32
gcc -shared -o sgogl.dll sgogl.o -Llib -lglfw3dll -lsoil -lopengl32 -Wl,--out-implib,libsgogl.a
