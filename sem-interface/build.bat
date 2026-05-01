@echo off
gcc main.c labirinto.c mochila.c pilha.c -o jogo
if %errorlevel% neq 0 exit /b
jogo.exe
pause