@echo off
gcc main.c grafico.c labirinto.c mochila.c pilha.c -o jogo.exe -IC:\raylib\include -LC:\raylib\lib -lraylib -lgdi32 -lwinmm
if %errorlevel% neq 0 exit /b
jogo.exe
pause