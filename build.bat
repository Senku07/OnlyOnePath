@echo off
md build
pushd build
cl ../src/main.cpp /FC /nologo /Zi /Fe:OOP.exe /I"../dp" /MD /link shell32.lib user32.lib opengl32.lib gdi32.lib kernel32.lib  ../dp/glfw3.lib
if %ERRORLEVEL% == 0 (
OOP.exe
)
popd