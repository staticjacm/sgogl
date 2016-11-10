
Here is a (probably outdated) psuedoheader for dlang

In order to use it you must use implib - which comes with the dmd compiler - on both sgogl.dll and glfw.dll to get OMF (which dmd's linker uses) import libraries for the dlls

```
implib /system sgogl.lib sgogl.dll
implib /system glfw3.lib glfw3.dll
```

The ``/system`` part is so that implib doesn't prepend an underscore to function names

Then you can use

```
dmd my_file_here path_to_glfw_lib path_to_sgogl_lib
```
