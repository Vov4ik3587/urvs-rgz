if exist *.exe del *.exe
if exist *.dll del *.dll
cl main.cpp kernel32.lib user32.lib gdi32.lib advapi32.lib
cl /LD my_library.cpp kernel32.lib user32.lib gdi32.lib advapi32.lib
del *.obj *.lib *.exp