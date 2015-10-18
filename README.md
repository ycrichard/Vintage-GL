# Vintage-GL
some simple games based on openGL

------------------------------------------
INSTALLATION:

Compiler: mingw32

Dependence: freeglut

  http://freeglut.sourceforge.net/

Make example:

  g++ -c -o *.o *.c -I"C:\Program Files\Common Files\MinGW\freeglut\include"

  g++ -o example *.o -L"C:\Program Files\Common Files\MinGW\freeglut\lib" -lglu32 -lfreeglut -lopengl32
