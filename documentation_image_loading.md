Use

```c
unsigned int gr_load_image_standard(char* file, unsigned int index);
```

To load an image with SOIL from file into index. I'm pretty sure that SOIL replaces that index if it exists. If you use an index of 0 then it allocates a new index. The returned value is the actual index for the image, so you should always use that instead of your supplied index.

Alternatively, use

```c
unsigned int gr_load_image(char* file, unsigned int index, unsigned int, unsigned int soil_load_flag, soil_flag);
```

To load an image with SOIL flags in the same way as ``gr_load_image_standard``

You can load images from memory with

```c
unsigned int gr_load_image_ram(const unsigned char* const data, unsigned int id, int gr_width, int gr_height, int channels, unsigned int flags);
```

And unload images with

```c
void gr_unload_image(unsigned int id){
  if(glIsTexture(id)){
    unsigned int idl[1];
    idl[0] = id;
    glDeleteTextures(1, idl);
   }
}
```
