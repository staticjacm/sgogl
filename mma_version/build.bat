gcc -m32 -shared -o sgoglM.dll ^
-I"C:\Program Files\Wolfram Research\Mathematica\11.0\SystemFiles\IncludeFiles\C" ^
-I"C:\Program Files\Wolfram Research\Mathematica\11.0\SystemFiles\Links\MathLink\DeveloperKit\Windows-x86-64\CompilerAdditions\mldev64\include" ^
sgoglloader.c ^
-Llib -lsgogl ^
-L"C:\Program Files\Wolfram Research\Mathematica\11.0\SystemFiles\Links\MathLink\DeveloperKit\Windows-x86-64\CompilerAdditions\mldev64\lib" ^
-L"C:\Program Files\Wolfram Research\Mathematica\11.0\SystemFiles\Libraries\Windows-x86-64"